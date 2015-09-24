//
//  outline.h
//  feedback
//
//  Created by James Bentley on 9/24/15.
//
//

#ifndef __feedback__outline__
#define __feedback__outline__

#include "ofxState.h"
#include "sharedData.h"
#include "ofxCv.h"

class outlineState : public itg::ofxState<sharedData> {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    string getName();
    
    Mat edgeMat;
    ofImage edge;
    float dimFac;
};


#endif /* defined(__feedback__outline__) */
