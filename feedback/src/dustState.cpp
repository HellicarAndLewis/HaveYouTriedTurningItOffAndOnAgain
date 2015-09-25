//
//  dustState.cpp
//  feedback
//
//  Created by James Bentley on 9/22/15.
//
//

#include "dustState.h"

void dustState::setup() {
    dimFac = 0.3;
    glPointSize(25.0);
    mesh.setMode(OF_PRIMITIVE_POINTS);
}

void dustState::update() {
    getSharedData().updateCamera(dimFac);
    farneback.calcOpticalFlow(getSharedData().smallFrame);
    if(farneback.getFlow().rows > 1 && colors.size() == 0) {
        Mat flow = farneback.getFlow();
        for(int x=0; x < flow.cols; x++) {
            for(int y=0; y < flow.rows; y++) {
                Integrator<ofVec2f> newInt;;
                newInt.attraction = 0.3;
                newInt.damping = 0.5;
                //newInt.set(ofVec2f(x, y));
                ofVec2f newVec = ofVec2f(x, y);
                colors.push_back(make_pair(newInt, newVec));
                cout<<colors.size()<<endl;
                mesh.addVertex(ofVec2f(x, y));
                mesh.addColor(0.0f);
            }
        }
    }
    updateColors();
}

void dustState::draw() {
    ofSetColor(255);
    ofScale(ofGetWidth()/farneback.getFlow().cols, ofGetWidth()/farneback.getFlow().cols);
    mesh.draw();
}

void dustState::keyPressed(int key) {
    getSharedData().changeInitialState(key);
    changeState(getSharedData().initialState);
}

void dustState::stateEnter() {
    ofBackground(0);
    getSharedData().updateCamera(dimFac);
    farneback.calcOpticalFlow(getSharedData().smallFrame);
    ofSetBackgroundAuto(true);
}


void dustState::updateColors() {
    if(colors.size() > 0) {
        Mat flow = farneback.getFlow();
        int meshIndex = 0;
        for(int x=0; x < flow.cols; x++) {
            for(int y=0; y < flow.rows; y++) {
                colors[y + x*flow.rows].first.target(farneback.getFlowPosition(x, y));
                colors[y + x*flow.rows].first.update();
                float diff = (colors[y + x*flow.rows].second - colors[y + x*flow.rows].first.val).length();
                mesh.setColor(meshIndex, diff);
                meshIndex++;
            }
        }
    }
}

string dustState::getName() {
    return "dustState";
}