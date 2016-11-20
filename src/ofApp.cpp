#include "ofApp.h"

void ofApp::setup(){
    // OSC receiver for Blobs
    blobsReceiver.setup(OSC_PORT_BLOBS);
    
    // OSC receiver for Audio
    audioReceiver.setup(OSC_PORT_AUDIO);
    
    // OSC receiver for Blobs
    moodsReceiver.setup(OSC_PORT_MOODS);    
}

void ofApp::update(){
    
    // Check for waiting messages
    // on blobs OSC channel
    while(blobsReceiver.hasWaitingMessages()){
        
        // Get the next message
        ofxOscMessage m;
        blobsReceiver.getNextMessage(m);
        
        // Check for blob messages
        if(m.getAddress() == "/blob"){
            blob *newBlobData =  new blob();
            newBlobData->id = m.getArgAsInt32(0);
            newBlobData->x = m.getArgAsFloat(1);
            newBlobData->y = m.getArgAsFloat(2);
            newBlobData->size = m.getArgAsFloat(3);
            newBlobData->time = ofGetElapsedTimef();
            addOrUpdateBlob(newBlobData);
            printBlobs();
        }
    }
    
    // Clean expired blobs
    removeExpiredBlobs();
}

void ofApp::draw(){
    ofSetColor(255,0,0);
    ofFill();
    drawBlobs();
}

void ofApp::addOrUpdateBlob(blob *b){
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

void ofApp::printBlobs(){
    for(int i=0; i<blobs.size(); i++)
        printBlob(blobs[i]);
}

void ofApp::printBlob(blob *b){
    cout << "ID: " << b->id << " x: " << b->x << "- y:" << b->y << "- size:" << b->size << endl;
}

void ofApp::drawBlobs(){
    for(int i=0; i<blobs.size(); i++)
        ofDrawCircle(blobs[i]->x*((float) ofGetWidth()), blobs[i]->y*((float) ofGetHeight()), blobs[i]->size*100.0f);
}

void ofApp::removeExpiredBlobs(){
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
