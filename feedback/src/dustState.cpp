//
//  dustState.cpp
//  feedback
//
//  Created by James Bentley on 9/24/15.
//
//

#include "dustState.h"

void dustState::setup() {
    dimFac = 1;
    areaSet  = false;
}

void dustState::update() {
    getSharedData().updateCamera(dimFac);
    flow.calcOpticalFlow(getSharedData().smallFrame);
    time = ofGetSeconds();
    if(time%2 == 0) {
        if(!areaSet) {
            setArea(getSharedData().smallFrame.cols/2 - 50, getSharedData().smallFrame.rows/2 - 50, 100, 100);
            areaSet = true;
        }
    } else {
        areaSet = false;
    }
}

void dustState::draw() {
    ofSetColor(0, 0, 0, 20);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255);
    flow.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void dustState::keyPressed(int key) {
    getSharedData().changeInitialState(key);
    changeState(getSharedData().initialState);
    if(key == ' ') {
        setArea(getSharedData().smallFrame.cols/2 - 50, getSharedData().smallFrame.rows/2 - 50, 100, 100);
    }
}

string dustState::getName() {
    return "dustState";
}

void dustState::stateEnter() {
    ofBackground(0);
    ofSetBackgroundAuto(false);
    time = ofGetSeconds();
}

void dustState::setArea(int x, int y, int width, int height) {
    ofVec2f p1(x,y);
    ofVec2f p2(x+width, y+height);
    rect.set(p1,p2.x-p1.x,p2.y-p1.y);
    vector<KeyPoint> keypoints;
    vector<KeyPoint> keypointsInside;
    vector<cv::Point2f> featuresToTrack;
    cvtColor(getSharedData().smallFrame, getSharedData().greyFrame, CV_BGR2GRAY);
    FAST(getSharedData().greyFrame,keypoints,2);
    for(int i=0;i<keypoints.size();i++){
        if(rect.inside(toOf(keypoints[i].pt))){
            keypointsInside.push_back(keypoints[i]);
        }
    }
#if CV_MAJOR_VERSION>=2 && (CV_MINOR_VERSION>4 || (CV_MINOR_VERSION==4 && CV_SUBMINOR_VERSION>=1))
    KeyPointsFilter::retainBest(keypointsInside,30);
#endif
    KeyPoint::convert(keypointsInside,featuresToTrack);
    flow.setFeaturesToTrack(featuresToTrack);
}