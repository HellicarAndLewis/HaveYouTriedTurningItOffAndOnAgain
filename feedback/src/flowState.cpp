//
//  flowState.cpp
//  feedback
//
//  Created by James Bentley on 9/22/15.
//
//

#include "flowState.h"

void flowState::setup() {
    dimFac = 0.5;
}

void flowState::update() {
    getSharedData().updateCamera(dimFac);
    farneback.calcOpticalFlow(getSharedData().smallFrame);
    if(farneback.getFlow().rows > 1 && locs.size() == 0) {
        Mat flow = farneback.getFlow();
        for(int x=0; x < flow.cols; x++) {
            for(int y=0; y < flow.rows; y++) {
                locs.push_back( new Integrator<ofVec2f>());
                cout<<locs.size()<<endl;
            }
        }
    }
    updateLocs();
}

void flowState::draw() {
    ofSetColor(255);
    drawFlow(0, 0, ofGetWidth(), ofGetHeight());
}

void flowState::keyPressed(int key) {
    getSharedData().changeInitialState(key);
    changeState(getSharedData().initialState);
}

void flowState::stateEnter() {
    ofBackground(0);
    getSharedData().updateCamera(dimFac);
    farneback.calcOpticalFlow(getSharedData().smallFrame);
    ofSetBackgroundAuto(true);
}

void flowState::stateExit() {
    
}

void flowState::updateLocs() {
    if(locs.size() > 0) {
        Mat flow = farneback.getFlow();
        for(int x=0; x < flow.cols; x++) {
            for(int y=0; y < flow.rows; y++) {
                locs[y + x*flow.rows]->target(ofVec2f(farneback.getFlowPosition(x, y)));
                locs[y + x*flow.rows]->update();
            }
        }
    }
}

void flowState::drawFlow(int x, int y, int width, int height) {
    if(locs.size() > 0) {
        ofVec2f offset(x,y);
        Mat flow = farneback.getFlow();
        int numLines = 0;;
        ofVec2f scale(width/flow.cols, height/flow.rows);
        for(int x = 0; x < flow.cols; x++) {
            for(int y = 0; y < flow.rows; y++) {
                numLines++;
                ofVec2f cur = ofVec2f(x, y) * scale + offset;
                ofLine(cur, locs[y + x*flow.rows]->val * scale + offset);
            }
        }
    }
}

string flowState::getName() {
    return "flowState";
}