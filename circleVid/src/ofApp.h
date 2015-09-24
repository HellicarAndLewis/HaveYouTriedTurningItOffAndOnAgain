#pragma once

#include "ofMain.h"
#include "ofxXMLSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
        void exit();
    
        ofxXmlSettings settings;
        ofVideoPlayer* player;
        ofImage mask;
        float diameter;
        bool started;
};
