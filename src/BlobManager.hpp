//
//  BlobManager.hpp
//  OSCReceiverSendero
//
//  Created by Christian Bouvier on 11/20/16.
//
//

#ifndef BlobManager_hpp
#define BlobManager_hpp

#include <stdio.h>
#include "ofxOsc.h"

#define EXPIRATION_TIME 5
#define OSC_PORT_BLOBS 12345

#define BlobManager (*BlobManagerClass::instance())

struct blob {
    int id;
    float x;
    float y;
    float size;
    float time;
};

class BlobManagerClass {
private:
    static BlobManagerClass* _instance;
    BlobManagerClass();
    
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
    
public:
    static BlobManagerClass* instance();
    
    void init();
    void update();
    void draw();
};

#endif /* BlobManager_hpp */
