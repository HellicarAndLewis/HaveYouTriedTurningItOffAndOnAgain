//
//  flowState.h
//  feedback
//
//  Created by James Bentley on 9/22/15.
//
//

#pragma once

#include "ofxIntegrator.h"
#include "ofxState.h"
#include "sharedData.h"

class flowState : public itg::ofxState<sharedData> {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void stateEnter();
    void stateExit();
    void drawFlow(int x, int y, int width, int height);
    void updateLocs();
    string getName();
private:
    FlowFarneback farneback;
    float dimFac;
    int stepSize;
    vector< Integrator<ofVec2f>* > locs;
};
