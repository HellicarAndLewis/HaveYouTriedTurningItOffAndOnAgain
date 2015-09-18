#pragma once

#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxSmile.h"
#include "ofxAVFVideoPlayer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void swapPlayer();

		void keyPressed(int key);
    
    ofImage img, smiley;
    
    SimpleCV vision;
    
    float smilePct;
    float lastTime;
    float smoothPct;
    int currentPlayer;
    ofxAVFVideoPlayer* players[2];
    vector<string> movies;
    int currentMovie;
    bool smileDetected;
    vector<pair<ofVec4f,float> > smiles;
    float smileX, smileY, smileWidth, smileHeight;
    
    ofTrueTypeFont ttf;
    ofTrueTypeFont ttfSmall;
};
