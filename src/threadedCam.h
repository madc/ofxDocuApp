#ifndef _THREADED_CAM
#define _THREADED_CAM

#include "ofMain.h"

class threadedCam : public ofThread{
    
public:
    
    int savedFrames;
    int interval;

    string deviceName;
    int camWidth;
    int camHeight;
    
    string path;
    
    ofVideoGrabber vidGrabber;
    ofImage exportImage;
    
    threadedCam(){
        savedFrames = 0;
        
        vidGrabber.setVerbose(true);
    }
    
    void start(){
        vector<ofVideoDevice> devices = vidGrabber.listDevices();
        
        for(vector<ofVideoDevice>::iterator it = devices.begin(); it != devices.end(); ++it) {
            if(it->deviceName == deviceName) {
                vidGrabber.setDeviceID(it->id);
                break;
            }
        }
        
        vidGrabber.initGrabber(camWidth, camHeight, false);
        exportImage.setUseTexture(false);

        startThread(true, false);   // blocking, verbose
    }
    
    void stop(){
        stopThread();

        vidGrabber.close();
    }
    
    void threadedFunction(){
        
        while( isThreadRunning() != 0 ){
            vidGrabber.update();
            
            if (vidGrabber.isFrameNew()){
                exportImage.setFromPixels(vidGrabber.getPixelsRef());
                
                if(path.empty()){
                    path = setupPath();
                }
                
                char countBuff[100];
                sprintf(countBuff, "%07d", savedFrames);
                exportImage.saveImage(path + "/" + ofToString(countBuff) + ".tiff");
                
                if( lock() ){
                    savedFrames++;
                    unlock();
                }
            }
            
            ofSleepMillis(interval);
        }
    }
    
    string setupPath(){
        
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

};

#endif
