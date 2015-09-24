//
//  leftState.cpp
//  feedback
//
//  Created by James Bentley on 9/23/15.
//
//

#include "leftState.h"

void leftState::setup() {
    dimFac = 1.0;
    percentage = 0;
    maxArea = 0;
    percentage.force = 0.01;
    percentage.target(ofGetWidth());
}

void leftState::stateEnter() {
    ofBackground(0);
    ofSetBackgroundAuto(true);
}

void leftState::update() {
    getSharedData().updateCamera(dimFac);
    getSharedData().findCountours();
    maxArea = 0;
    for(int i=0; i < getSharedData().finder.size(); i++) {
        float area = getSharedData().finder.getContourArea(i);
        maxArea = (area > maxArea) ? area : maxArea;
        if(maxArea == area) {
            ofRectangle rect = toOf(getSharedData().finder.getBoundingRect(i));
            float newPercentage = (rect.x + rect.width) / getSharedData().greyDiff.rows;
            percentage.target(newPercentage*ofGetWidth());
        }
    }
    percentage.update();
}

void leftState::draw() {
    ofSetColor(255);
    ofRect(0, 0, ofGetWidth() - percentage.val, ofGetHeight());
//    drawMat(getSharedData().frame, 320*1, 0);
//    drawMat(getSharedData().greyFrame, 320*2, 0);
//    drawMat(getSharedData().greyBackground, 320*3, 0);
//    drawMat(getSharedData().greyDiff, 320*4, 0);
    ofSetColor(255, 0, 0);
    //getSharedData().finder.draw();
}

string leftState::getName() {
    return "leftState";
}

void leftState::keyPressed(int key) {
    getSharedData().changeInitialState(key);
    getSharedData().changeThreshold(key);
    changeState(getSharedData().initialState);
    if(key == ' ') getSharedData().captureBackground();
}