//
//  graphState.cpp
//  feedback
//
//  Created by James Bentley on 9/24/15.
//
//

#include "graphState.h"

void graphState::setup() {
    dimFac = 1;
}

void graphState::update() {
    getSharedData().updateCamera(dimFac);
    if(!getSharedData().smallFrame.empty()) {
        absdiff(getSharedData().smallFrame, previous, diff);
        previous = getSharedData().smallFrame.clone();
        diff.update();
        columnMean = meanCols(diff);
    }
    if(columnMean.rows > 1 && vals.size() == 0) {
        for(int k = 0; k < 3; k++) {
            for(int i=0; i < columnMean.rows; i++) {
                vals.push_back(new Integrator<float>());
                vals[i + k*columnMean.rows]->set(0);
            }
        }
    }
    for(int k = 0; k < 3; k++) {
        for(int i=0; i < columnMean.rows; i++) {
            Vec3b cur = columnMean.at<Vec3b>(i);
            vals[i + k*columnMean.rows]->target(cur[k]);
            vals[i + k*columnMean.rows]->update();
        }
    }
}

void graphState::draw() {

    ofSetColor(255);
    ofSetLineWidth(2);
    for(int k = 0; k < 3; k++) {
        ofNoFill();
        ofBeginShape();
        for(int i = 0; i < columnMean.rows; i++) {
            ofVertex(ofMap(i, 0, columnMean.rows, 0, ofGetWidth()), ofGetHeight()/2 + ofMap(vals[i + k*columnMean.rows]->val, 0, 100, 0, -ofGetHeight()));
        }
        ofEndShape();
        ofBeginShape();
        for(int i = 0; i < columnMean.rows; i++) {
            ofVertex(ofMap(i, 0, columnMean.rows, 0, ofGetWidth()), ofGetHeight()/2 + ofMap(vals[i + k*columnMean.rows]->val, 0, 100, 0, ofGetHeight()));
        }
        ofEndShape();
    }
    if(getSharedData().initialState != this.getName()) {
        changeState(getSharedData().initialState);
    }
}

void graphState::stateEnter() {
    ofBackground(0);
    ofSetBackgroundAuto(true);
}

void graphState::keyPressed(int key) {
    getSharedData().changeInitialState(key);
    changeState(getSharedData().initialState);
}

string graphState::getName() {
    return "graphState";
}