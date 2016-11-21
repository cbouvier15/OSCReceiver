#include "ofApp.h"
#include "BlobManager.hpp"

void ofApp::setup(){
    BlobManager.init();
}

void ofApp::update(){
    BlobManager.update();
}

void ofApp::draw(){
    BlobManager.draw();
}
