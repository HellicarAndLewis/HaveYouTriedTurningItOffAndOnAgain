#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofThread", OF_LOG_ERROR);
    
    stateMachine.enableKeyEvents();
    stateMachine.enableAppEvents();
    
    stateMachine.getSharedData().setup();
    
    settings.loadFile("settings.xml");
    stateMachine.getSharedData().initialState = settings.getValue("settings:initialState", "graphState");
    stateMachine.getSharedData().setupCamera(320, 240);
    stateMachine.addState<flowState>();
    stateMachine.addState<leftState>();
    stateMachine.addState<rightState>();
    stateMachine.addState<outlineState>();
    stateMachine.addState<graphState>();
    stateMachine.addState<dustState>();
    
    stateMachine.changeState("graphState");
    ofHideCursor();
    
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::exit() {
    settings.setValue("settings:initialState", stateMachine.getSharedData().initialState);
    settings.saveFile("settings.xml");
}