//
//  sharedData.h
//  feedback
//
//  Created by James Bentley on 9/22/15.
//
//
#pragma once

#ifdef __arm__
#include "ofxCvPiCam.h"// <--- for Linux
#endif

#include "ofxCv.h"
#include "ofxStateMachine.h"

using namespace cv;
using namespace ofxCv;

class sharedData {
public:
    void setup();
    void changeInitialState(int key);
    void changeThreshold(int key);
    void setupCamera(int width, int height);
    void updateCamera(float dimFac);
    void captureBackground();
    void findCountours();
#ifdef __arm__
    ofxCvPiCam cam;
#elif __APPLE__
    ofVideoGrabber cam;
#endif
    Mat frame, greyFrame, greyBackground, greyDiff, smallFrame;
    ContourFinder finder;
    ofImage colorImage;
    string initialState;
    float thresh, maxVal;
};