#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofBackground(0);
	
	// player.load("hour.mp3");
	player.load("2.mp3", true);
	player.setLoop(true);
	player.play();
}

//--------------------------------------------------------------
void ofApp::update(){

	//update sound playing system
	ofSoundUpdate();
	

	float *val = ofSoundGetSpectrum(nBandsToGet);
	level = 0;
	for(int i=0; i<nBandsToGet; i++){
		fftSmoothed[i] *= 0.96f;
		if(fftSmoothed[i] < val[i])	fftSmoothed[i] = val[i];
		
		level += fftSmoothed[i] * fftSmoothed[i];
	}
	level = sqrt(level / nBandsToGet);
	// cout << level << endl;

	// level = 20 * log10(level);
	db = 20 * log(level);

	// bgColor = (int)ofMap(level, 0, 1, 0, 255, true);
	audioLevel = ofMap(level, 0, 1, 0, ofGetWidth() - 100, true);
	audioLevel2 = ofMap(db, -96, 0, 0, ofGetWidth() - 100, true);
}

//--------------------------------------------------------------
void ofApp::draw(){

	// ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	ofSetColor(255, 255, 0);
	ofFill();
	ofDrawRectangle(50, 50, audioLevel, 20);
	ofSetColor(255);
	ofNoFill();
	ofDrawRectangle(50, 50, ofGetWidth()-100, 20);

	ofDrawBitmapStringHighlight(ofToString(int(level*100)), 50, 100, ofColor(ofColor::fromHex(0xFFFF00)), ofColor(ofColor::fromHex(0x000000)));

	ofSetColor(255, 255, 0);
	ofFill();
	ofDrawRectangle(50, 250, audioLevel2, 20);
	ofSetColor(255);
	ofNoFill();
	ofDrawRectangle(50, 250, ofGetWidth()-100, 20);

	ofDrawBitmapStringHighlight(ofToString(int(db)) + " dB", 50, 300, ofColor(ofColor::fromHex(0xFFFF00)), ofColor(ofColor::fromHex(0x000000)));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ }
//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){ }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){ }
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){ }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){ }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){ }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }