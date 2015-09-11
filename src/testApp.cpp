#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(26);
    ofBackground(255, 255, 255);

    tCam.interval   = 1000; // in ms
    tCam.deviceName = "Logitech Camera";

	tCam.camWidth 		= 1280;
	tCam.camHeight 		= 720;
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0);
    ofDrawBitmapString("Framerate/Frames saved: " + ofToString((int)ofGetFrameRate()) + "/" + ofToString(tCam.savedFrames), 20, 20);
    ofDrawBitmapString("Status:", 20, 40);

    if(tCam.isThreadRunning()) {
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("RECORDING", 80, 40);
    } else {
        ofDrawBitmapString("NOT RECORDING", 80, 40);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    // start/pause recording w. spacebar
    if(key == 32) {
        if(tCam.isThreadRunning()) {
            tCam.stop();
        } else {
            tCam.start();
        }
    }

    //reset recording, start new folder w. r-key
    if(key == 114) {
        tCam.reset();
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
