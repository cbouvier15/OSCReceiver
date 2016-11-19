#include "ofApp.h"

void ofApp::setup(){    
    cout << "listening for osc messages on port " << LISTENING_PORT << "\n";
    receiver.setup(LISTENING_PORT);
}

void ofApp::update(){
    
    // Check for waiting messages
    while(receiver.hasWaitingMessages()){
        
        // Get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // Check for blob messages
        if(m.getAddress() == "/blob"){
            blob newBlobData;
            newBlobData.id = m.getArgAsInt32(0);
            newBlobData.x = m.getArgAsFloat(1);
            newBlobData.y = m.getArgAsFloat(2);
            newBlobData.size = m.getArgAsFloat(3);
            addOrUpdateBlob(newBlobData);
            printBlobs();
        }
    }
}

void ofApp::draw(){
    ofSetColor(255,0,0);
    ofFill();
    drawBlobs();
}

void ofApp::addOrUpdateBlob(blob b){
    bool exist = false;
    int i = 0;
    while (not exist and i<blobs.size()) {
        exist = blobs[i].id == b.id;
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

void ofApp::printBlob(blob b){
    cout << "ID: " << b.id << "x: " << b.x << "- y:" << b.y << "- size:" << b.size << endl;
}

void ofApp::drawBlobs(){
    for(int i=0; i<blobs.size(); i++)
        ofDrawCircle(blobs[i].x*((float) ofGetWidth()), blobs[i].y*((float) ofGetHeight()), blobs[i].size*100.0f);
}
