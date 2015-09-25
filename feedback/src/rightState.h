#pragma once

#include "ofxIntegrator.h"
#include "ofxState.h"
#include "sharedData.h"

class Glow : public ofxCv::RectFollower {
protected:
    ofColor color;
    Integrator <float> left, width;
    float startedDying;
    float deathPoint;
public:
    Glow()
    :startedDying(0) {
    }
    void setup(const cv::Rect& track);
    void update(const cv::Rect& track);
    void kill();
    void draw();
};

class rightState : public itg::ofxState<sharedData> {
public:
    void setup();
    void update();
    void draw();
    string getName();
    void keyPressed(int key);
    
    float dimFac;
    
    ofxCv::ContourFinder contourFinder;
    ofxCv::RectTrackerFollower<Glow> tracker;
};
