//
//  graphState.h
//  feedback
//
//  Created by James Bentley on 9/24/15.
//
//

#ifndef __feedback__graphState__
#define __feedback__graphState__

#include "ofxState.h"
#include "sharedData.h"
#include "ofxCv.h"
#include "ofxIntegrator.h"

class graphState : public itg::ofxState<sharedData> {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    string getName();
    void stateEnter();
    
    float dimFac;
    Mat previous;
    ofImage diff;
    Mat columnMean;
    
    vector< Integrator<float>* > vals;

};


#endif /* defined(__feedback__graphState__) */
