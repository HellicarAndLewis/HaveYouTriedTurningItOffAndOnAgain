//
//  sharedData.cpp
//  feedback
//
//  Created by James Bentley on 9/22/15.
//
//

#include "sharedData.h"

void sharedData::setup() {
    thresh = 10;
    maxVal = 255;
    finder.setMaxArea(50000);
    finder.setMinArea(500);
}

void sharedData::changeInitialState(int key) {
    switch (key) {
        case '1':
            initialState = "flowState";
            break;
        case '2':
            initialState = "leftState";
            break;
        case '3':
            initialState = "rightState";
            break;
        case '4':
            initialState = "outlineState";
            break;
        case '5':
            initialState = "graphState";
            break;
        case '6':
            initialState = "dustState";
            break;
        default:
            break;
    }
}

void sharedData::changeThreshold(int key) {
    switch (key) {
        case OF_KEY_UP :
            thresh++;
            break;
        case OF_KEY_DOWN :
            thresh--;
            break;
        default:
            break;
    }
}

void sharedData::setupCamera(int width, int height) {
#ifdef __arm__
    cam.setup(width, height, true);
#elif __APPLE__
    cam.setVerbose(true);
    cam.setDeviceID(0);
    cam.initGrabber(width, height);
#endif
}

void sharedData::updateCamera(float dimFac) {
#ifdef __arm__
    frame = cam.grab();
#elif __APPLE__
    cam.update();
    frame = toCv(cam.getPixelsRef());
#endif
    if(!frame.empty()) {
        cv::Mat dst;
        flip(frame, dst, 1);
        toOf(dst, colorImage);
        colorImage.update();
        if(dimFac != 1)
            resize(dst, smallFrame, cv::Size(round(dimFac*frame.cols), round(dimFac*frame.rows)));
        else smallFrame = dst;
    }
}

void sharedData::findCountours() {
    if(!greyBackground.empty()) {
        cvtColor(frame, greyFrame, CV_BGR2GRAY);
        absdiff(greyBackground, greyFrame, greyDiff);
        threshold(greyDiff, greyDiff, thresh, maxVal, THRESH_BINARY);
        finder.findContours(greyDiff);
    }
}

void sharedData::captureBackground() {
    if(!frame.empty()) {
        cvtColor(frame, greyFrame, CV_BGR2GRAY);
        greyBackground = greyFrame.clone();
    }
}
