#include "rightState.h"

using namespace ofxCv;
using namespace cv;

const float dyingTime = 1;

void Glow::setup(const cv::Rect& track) {
    color.setHsb(ofRandom(0, 255), 255, 255);
    left = toOf(track).getCenter().x;
    deathPoint = toOf(track).getCenter().x;
    width = 0.0;
    width.attraction = 0.1;
    left.attraction = 0.1;
}

void Glow::update(const cv::Rect& track) {
    left.target(toOf(track).getLeft());
    width.target(toOf(track).getWidth());

    left.update();
    width.update();
}

void Glow::kill() {
    float curTime = ofGetElapsedTimef();
    if(startedDying == 0) {
        startedDying = curTime;
        deathPoint = left.val + width.val/2;
    } else if(curTime - startedDying > dyingTime) {
        dead = true;
    }
}

void Glow::draw() {
    ofPushStyle();
    ofFill();
    if(startedDying) {
        left.target(deathPoint);
        width.target(0);
        left.update();
        width.update();
    }
//    float size = 16;
    ofSetColor(255);
    ofRect(left.val, 0, width.val, ofGetHeight());
    ofPopStyle();
}

void rightState::setup() {
    dimFac = 1.0;
    ofSetVerticalSync(true);
    ofBackground(0);
    
    contourFinder.setMinAreaRadius(1);
    contourFinder.setMaxAreaRadius(100);
    contourFinder.setThreshold(15);
    
    // wait for half a frame before forgetting something
    tracker.setPersistence(15);
    // an object can move up to 50 pixels per frame
    tracker.setMaximumDistance(50);
}

void rightState::update() {
    getSharedData().updateCamera(dimFac);
    if(!getSharedData().smallFrame.empty()) {
        //blur(movie, 10);
        contourFinder.findContours(getSharedData().smallFrame);
        tracker.track(contourFinder.getBoundingRects());
    }
}

void rightState::draw() {
    ofSetColor(255);
    ofScale(ofGetWidth()/getSharedData().smallFrame.cols, ofGetHeight()/getSharedData().smallFrame.rows);
//    contourFinder.draw();
    vector<Glow>& followers = tracker.getFollowers();
    for(int i = 0; i < followers.size(); i++) {
        followers[i].draw();
    }
}

void rightState::keyPressed(int key) {
    getSharedData().changeInitialState(key);
    getSharedData().changeThreshold(key);
    changeState(getSharedData().initialState);
}

string rightState::getName() {
    return "rightState";
}
