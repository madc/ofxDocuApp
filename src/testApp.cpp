#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(26);
    ofBackground(255, 255, 255);
    
	camWidth 		= 1280;
	camHeight 		= 720;
    
    interval        = 25; // in Frames
    recStatus       = "Not Recording";
    
    savedFrames     = 0;
	    
    vidGrabber.setDeviceID(1);
    
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth, camHeight);
}

//--------------------------------------------------------------
void testApp::update(){
	    
    if(ofGetFrameNum() == lastGrab + interval )
    {
        vidGrabber.update();

        lastGrab = ofGetFrameNum();
        
        if (vidGrabber.isFrameNew()){
            unsigned char * vidPixels = vidGrabber.getPixels();
            drawImage.setFromPixels(vidPixels, camWidth, camHeight, OF_IMAGE_COLOR);
            
            if(recStatus == "Recording") {
                
                if(path.empty()){
                    path = setupPath();
                }
                
                savedFrames++;
                
                char countBuff[100];
                sprintf(countBuff, "%07d", savedFrames);
                
                drawImage.saveImage(path + "/" + ofToString(countBuff) + ".tiff");
            }
        }
    }
}

string testApp::setupPath(){
    
    // Building the folder structure based on the date
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    
    char dateBuff[11];
    sprintf(dateBuff, "%04d-%02d-%02d", (1900 + timePtr->tm_year), (timePtr->tm_mon+1), timePtr->tm_mday);
    
    string path = "rec/" + ofToString(dateBuff);

    
    // Creating folders, suffixing _## if the folder already exists
    ofDirectory dir;
    if(!dir.doesDirectoryExist(path)){
        dir.createDirectory(path, true, true);
    } else {
        int folderCount = 1;
        while(true) {
            
            char countBuff[3];
            sprintf(countBuff, "%02d", folderCount);
            
            if(!dir.doesDirectoryExist(path + "_" + ofToString(countBuff))){
                path += "_" + ofToString(countBuff);
                dir.createDirectory(path, true, true);
                break;
            }
            
            folderCount++;
        }
    }

    return path;
}

//--------------------------------------------------------------
void testApp::draw(){
    //ofSetColor(255);
    //drawImage.draw(0, 0);
        
    ofSetColor(0);
    ofDrawBitmapString("Framerate/Frames saved: " + ofToString((int)ofGetFrameRate()) + "/" + ofToString(savedFrames), 20, 20);
    ofDrawBitmapString("Status:", 20, 40);
    
    if(recStatus == "Recording") {
        ofSetColor(255, 0, 0);
    }
    ofDrawBitmapString(recStatus, 80, 40);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == 32) {
        if(recStatus == "Not Recording") {
            recStatus = "Recording";
        } else {
            recStatus = "Not Recording";
        }
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