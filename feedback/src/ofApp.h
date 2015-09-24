#pragma once

//include ofMain
#include "ofMain.h"

//include addons
#include "ofxStateMachine.h"
#include "ofxXmlSettings.h"

//include Shared Data for State Machine
#include "sharedData.h"

//include States
#include "flowState.h"
#include "leftState.h"
#include "rightState.h"
#include "outlineState.h"
#include "graphState.h"
#include "dustState.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
private:
    itg::ofxStateMachine<sharedData> stateMachine; // Don't forget to use modified ofxStateMachine for linux
    ofxXmlSettings settings;
};
