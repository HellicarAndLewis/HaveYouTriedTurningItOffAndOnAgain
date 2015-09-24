//
//  rightState.cpp
//  feedback
//
//  Created by James Bentley on 9/23/15.
//
//

#include "rightState.h"

void rightState::setup() {
    dimFac = 1.0;
    percentage = 0;
    maxArea = 0;
    percentage.force = 0.005;
    percentage.target(ofGetWidth());
}

void rightState::stateEnter() {
    ofBackground(0);
    ofSetBackgroundAuto(true);
}

void rightState::update() {
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

void rightState::draw() {
    ofSetColor(255);
    ofRect(ofGetWidth() - percentage.val, 0, ofGetWidth(), ofGetHeight());
//    drawMat(getSharedData().frame, 320*1, 0);
//    drawMat(getSharedData().greyFrame, 320*2, 0);
//    drawMat(getSharedData().greyBackground, 320*3, 0);
//    drawMat(getSharedData().greyDiff, 320*4, 0);
 //   ofSetColor(255, 0, 0);
 //   getSharedData().finder.draw();
}

string rightState::getName() {
    return "rightState";
}

void rightState::keyPressed(int key) {
    getSharedData().changeInitialState(key);
    getSharedData().changeThreshold(key);
    changeState(getSharedData().initialState);
    if(key == ' ') getSharedData().captureBackground();
}