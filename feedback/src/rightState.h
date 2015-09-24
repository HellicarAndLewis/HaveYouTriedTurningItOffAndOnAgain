//
//  rightState.h
//  feedback
//
//  Created by James Bentley on 9/23/15.
//
//

#pragma once

#include "ofxIntegrator.h"
#include "ofxState.h"
#include "sharedData.h"

class rightState : public itg::ofxState<sharedData> {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void stateEnter();
    string getName();
    
    float dimFac, maxArea;
    Integrator<float> percentage;
};