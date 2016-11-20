#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include <stdio.h>

#define OSC_PORT_BLOBS 12345
#define OSC_PORT_AUDIO 12346
#define OSC_PORT_MOODS 12347
#define EXPIRATION_TIME 5

struct blob {
    int id;
    float x;
    float y;
    float size;
    float time;
};

class ofApp : public ofBaseApp{
    
    private:
        // Blobs current list
        vector<blob*> blobs;
    
        // OSC channel for Blobs
        ofxOscReceiver blobsReceiver;
    
        // When a new OSC message with blob information
        // arrives, this method will be invoked to
        // create a new blob or update an existing one.
        void addOrUpdateBlob(blob *b);
        void printBlob(blob *b);
        void printBlobs();
        void drawBlobs();
        void removeExpiredBlobs();
    
        // OSC channel for Audio
        ofxOscReceiver audioReceiver;
    
        // OSC channel for Moods
        ofxOscReceiver moodsReceiver;

	public:
		void setup();
		void update();
		void draw();
};
