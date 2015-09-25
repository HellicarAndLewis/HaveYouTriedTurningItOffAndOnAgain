//
//  dustState.h
//  feedback
//
//  Created by James Bentley on 9/24/15.
//
//

#pragma once

#include "ofxState.h"
#include "sharedData.h"
#include "ofxCv.h"
#include "ofxIntegrator.h"

class dustState : public itg::ofxState<sharedData> {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    string getName();
    void stateEnter();
    void updateColors();
    
    float dimFac;
    
    ofMesh mesh;
    vector< pair<Integrator<ofVec2f>, ofVec2f> > colors;
    FlowFarneback farneback;
    ofVec2f p1;
    ofRectangle rect;
    bool areaSet;
    int time;
};
