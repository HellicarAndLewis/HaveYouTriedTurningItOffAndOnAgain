//
//  flowState.cpp
//  feedback
//
//  Created by James Bentley on 9/22/15.
//
//

#include "flowState.h"

void flowState::setup() {
    dimFac = 0.3;
    mesh.setMode(OF_PRIMITIVE_LINES);
}

void flowState::update() {
    getSharedData().updateCamera(dimFac);
    farneback.calcOpticalFlow(getSharedData().smallFrame);
    if(farneback.getFlow().rows > 1 && locs.size() == 0) {
        Mat flow = farneback.getFlow();
        for(int x=0; x < flow.cols; x++) {
            for(int y=0; y < flow.rows; y++) {
                Integrator<ofVec2f> *newInt = new Integrator<ofVec2f>();
                newInt->attraction = 0.3;
                newInt->damping = 0.5;
                locs.push_back(newInt);
                mesh.addVertex(ofVec2f(x, y));
                mesh.addVertex(ofVec2f(x, y));
            }
        }
    }
    updateLocs();
}

void flowState::draw() {
    ofSetColor(255);
    ofScale(ofGetWidth()/farneback.getFlow().cols, ofGetWidth()/farneback.getFlow().cols);
    mesh.draw();
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
        int meshIndex = 0;
        for(int x=0; x < flow.cols; x++) {
            for(int y=0; y < flow.rows; y++) {
		ofVec2f newLoc = ofVec2f(farneback.getFlowPosition(x, y));
		ofVec2f oldLoc = mesh.getVertex(meshIndex+1);
		ofVec2f diff = newLoc - oldLoc;
		if( diff.length() > 100) {
			diff.normalize();
			diff*=100;
			newLoc = diff + oldLoc;
		}
                locs[y + x*flow.rows]->target(newLoc);
                locs[y + x*flow.rows]->update();
                mesh.setVertex(meshIndex, locs[y + x*flow.rows]->val);
                meshIndex += 2;
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
    }
}

string flowState::getName() {
    return "flowState";
}
