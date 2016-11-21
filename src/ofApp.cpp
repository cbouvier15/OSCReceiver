#include "ofApp.h"
#include "BlobManager.hpp"
#include "MoodsManager.hpp"

void ofApp::setup(){
    BlobManager.init();
    MoodsManager.init();
}

void ofApp::update(){
    BlobManager.update();
    MoodsManager.update();
}

void ofApp::draw(){
    BlobManager.draw();
    MoodsManager.draw();
}

void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT){
        MoodsManager.printStatus();
    }
    
    if (key == OF_KEY_RIGHT){
        BlobManager.printStatus();
    }
}
