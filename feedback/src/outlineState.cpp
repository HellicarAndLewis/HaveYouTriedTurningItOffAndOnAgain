//
//  outlinesate.cpp
//  feedback
//
//  Created by James Bentley on 9/24/15.
//
//

#include "outlineState.h"

void outlineState::setup() {
    dimFac = 1;
}

void outlineState::update() {
    getSharedData().updateCamera(dimFac);
    cvtColor(getSharedData().smallFrame, getSharedData().greyFrame, CV_BGR2GRAY);
    cv::Canny(getSharedData().greyFrame, edgeMat, 100, 100, 3);
    toOf(edgeMat, edge);
    edge.update();
}

void outlineState::draw() {
    edge.draw(0, 0, ofGetWidth(), ofGetHeight());
}

string outlineState::getName() {
    return "outlineState";
}

void outlineState::keyPressed(int key) {
    getSharedData().changeInitialState(key);
    changeState(getSharedData().initialState);
}