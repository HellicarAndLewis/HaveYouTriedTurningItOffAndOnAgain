#include "ofApp.h"

void ofApp::swapPlayer() {
    currentPlayer ++;
    currentPlayer %= 2;
}

void stopAndLoadNewVid(ofVideoPlayer* vidPlayer, string vidToLoad) {
    vidPlayer->stop();
    vidPlayer->close();
    vidPlayer->loadMovie(vidToLoad);
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(30, 30, 30);
    
    vision.setupCamera(0, 320, 240);
    
    ttf.loadFont("Helvetica.ttf", 48);
    ttfSmall.loadFont("Helvetica.ttf", 14);
    
    img.allocate(320, 240, OF_IMAGE_GRAYSCALE);
    smiley.loadImage("Smiley.png");
    
    lastTime = ofGetElapsedTimef() - 10.0;
    
    ofDirectory moviesDir("movies");
    moviesDir.allowExt("mp4");
    moviesDir.allowExt("mov");
    moviesDir.listDir();
    for(int i=0; i < moviesDir.numFiles(); i++) {
        string path = moviesDir.getPath(i);
        movies.push_back(path);
    }
    
    smilePct = 0.0;
    smoothPct = 0.0;
    
    for(int i=0; i<2; i++) {
        players[i] = new ofVideoPlayer();
        //players[i] = new ofVideoPlayer();
        players[i]->setLoopState(OF_LOOP_NORMAL);
        players[i]->setPixelFormat(OF_PIXELS_RGB);
        players[i]->loadMovie(movies[i]);
    }
    currentMovie = 0;
    players[currentPlayer]->setPaused(false);
    players[currentPlayer]->play();
}

//--------------------------------------------------------------
void ofApp::update(){
    vision.update();
    img.setFromPixels(vision.gray.getPixels(), vision.gray.width, vision.gray.height, OF_IMAGE_GRAYSCALE);
    
    smiles = ofxSmile::getSmile(img);
    smilePct = 0.0;
    for(int i=0; i < smiles.size(); i++) {
        if(smiles[i].second > smilePct) smilePct = smiles[i].second;
    }
    
    smoothPct *= 0.8;
    smoothPct += MAX(0, smilePct) * 0.2;
    
    if(ofGetElapsedTimef() - lastTime > 2.0) {
        if(smoothPct > 0.50) {
            smileDetected = true;
            ++currentMovie;
            currentMovie %= movies.size();
            stopAndLoadNewVid(players[currentPlayer], movies[currentMovie]);
            swapPlayer();
            players[currentPlayer]->play();
            players[currentPlayer]->setPaused(false);
            lastTime = ofGetElapsedTimef();
        } else {
            smileDetected = false;
        }
    }
    players[currentPlayer]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    players[currentPlayer]->draw(0, 0, ofGetWidth(), ofGetHeight());
    vision.color.draw(ofGetWidth() - 320, 0);
    unsigned long long now = ofGetElapsedTimef();
    ofDrawBitmapString("smile        = " + ofToString(smilePct, 2), 20, 20);
    ofDrawBitmapString("smile smooth = " + ofToString(smoothPct, 2), 20, 36);
    
    if(smileDetected) {
        ofSetColor(255);
        for(int i=0; i < smiles.size() ; i++) {
            float faceX = smiles[i].first.x;
            float faceY = smiles[i].first.y;
            float faceWidth = smiles[i].first.z;
            float faceHeight = smiles[i].first.w;
            if(smiles[i].second > 0.50) smiley.draw(ofGetWidth() - vision.color.width + faceX, faceY, faceWidth, faceHeight);
        }
        ofSetColor(255, 255, 255, 255);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ')
    {
        vision.togglePlayback();
    }
    
    // if you need to adjust the camera properties
    if(key == 's')
    {
        vision.camera.videoSettings();
    }
}