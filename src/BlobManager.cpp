//
//  BlobManager.cpp
//  OSCReceiverSendero
//
//  Created by Christian Bouvier on 11/20/16.
//
//

#include "BlobManager.hpp"

void init();
void update();
void draw();

BlobManagerClass* BlobManagerClass::_instance = NULL;

BlobManagerClass::BlobManagerClass() {}

BlobManagerClass* BlobManagerClass::instance() {
    if (_instance == NULL) {
        _instance = new BlobManagerClass();
    }
    return _instance;
}

void BlobManagerClass::init() {
    // OSC receiver for Blobs
    receiver.setup(OSC_PORT_BLOBS);
}

void BlobManagerClass::update() {
    // Check for waiting messages
    // on blobs OSC channel
    while(receiver.hasWaitingMessages()){
        
        // Get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // Check for blob messages
        if(m.getAddress() == "/blob"){
            blob *newBlobData =  new blob();
            newBlobData->id = m.getArgAsInt32(0);
            newBlobData->x = m.getArgAsFloat(1);
            newBlobData->y = m.getArgAsFloat(2);
            newBlobData->size = m.getArgAsFloat(3);
            newBlobData->time = ofGetElapsedTimef();
            addOrUpdateBlob(newBlobData);
        }
    }
    
    // Clean expired blobs
    removeExpiredBlobs();
}

void BlobManagerClass::draw() {
    ofSetColor(255,0,0);
    ofFill();
    drawBlobs();
}

void BlobManagerClass::addOrUpdateBlob(blob *b){
    bool exist = false;
    int i = 0;
    while (not exist and i<blobs.size()) {
        exist = blobs[i]->id == b->id;
        i++;
    }
    
    if (not exist)
        blobs.push_back(b);
    else
        blobs[--i] = b;
}

void BlobManagerClass::printBlobs(){
    for(int i=0; i<blobs.size(); i++)
        printBlob(blobs[i]);
}

void BlobManagerClass::printBlob(blob *b){
    cout << "ID: " << b->id << " x: " << b->x << "- y:" << b->y << "- size:" << b->size << endl;
}

void BlobManagerClass::drawBlobs(){
    for(int i=0; i<blobs.size(); i++)
        ofDrawCircle(blobs[i]->x*((float) ofGetWidth()), blobs[i]->y*((float) ofGetHeight()), blobs[i]->size*100.0f);
}

void BlobManagerClass::removeExpiredBlobs(){
    if (blobs.size() > 0){
        float now = ofGetElapsedTimef();
        
        for (int i=0; i<blobs.size(); i++) {
            if (now - blobs[i]->time > EXPIRATION_TIME){
                blob* b = blobs[i];
                blobs[i] = blobs.back();
                blobs.pop_back();
                delete b;
                i--;
            }
        }
    }
}

void BlobManagerClass::printStatus(){
    printBlobs();
}
