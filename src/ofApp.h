#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include <stdio.h>

#define LISTENING_PORT 12345

struct blob {
    int id;
    float x;
    float y;
    float size;
};

class ofApp : public ofBaseApp{
    
    private:
    
        // Blobs current list
        vector<blob> blobs;
    
        // OSC
        ofxOscReceiver receiver;
    
        // When a new OSC message with blob information
        // arrives, this method will be invoked to
        // create a new blob or update an existing one.
        void addOrUpdateBlob(blob b);
        void printBlob(blob b);
        void printBlobs();
        void drawBlobs();

	public:
		void setup();
		void update();
		void draw();
};
