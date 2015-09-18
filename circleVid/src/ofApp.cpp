#include "ofApp.h"

void fillPage(float diameter) {
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(0);
    float yMargin = (ofGetHeight() - diameter)/2;
    float xMargin = (ofGetWidth() - diameter)/2;
    ofRect(0, 0, ofGetWidth(), yMargin);
    ofRect(0, 0, xMargin, ofGetHeight());
    ofRect(0, ofGetHeight() - yMargin - 1, ofGetWidth(), yMargin + 10);
    ofRect(ofGetWidth() - xMargin - 1, 0, xMargin + 10, ofGetHeight());
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    mask.loadImage("Circle.png");
    player = new ofxAVFVideoPlayer();
    player->setPixelFormat(OF_PIXELS_RGBA);
    player->setLoopState(OF_LOOP_NORMAL);
    player->loadMovie("movies/cats1.mp4");
    started = player->isLoaded();

    settings.loadFile("settings.xml");
    diameter = settings.getValue("settings:diameter", 500.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(player->isLoaded() && !started) {
        player->play();
        started = true;
    }
    player->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255);
    player->draw(0, 0, ofGetWidth(), ofGetHeight());
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(0);
    fillPage(diameter);
    mask.draw(ofGetWidth()/2, ofGetHeight()/2, diameter, diameter);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP) {
        diameter+=10;
        diameter = MIN(diameter, MAX(ofGetWidth(), ofGetHeight()));
    }
    if(key == OF_KEY_DOWN) {
        diameter-=10;
        diameter = MAX(diameter, 0);
    }
}

void ofApp::exit() {
    settings.setValue("settings:diameter", diameter);
    settings.saveFile("settings.xml");
}
