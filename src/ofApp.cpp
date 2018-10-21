#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofBackground(0);

	ofSetWindowTitle("RMS exporter to JSON");
	
	// player.load("hour.mp3");
	player.load("2.mp3");
	// player.setLoop(true);
	player.play();

	ofxJSONElement json;
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
	level = ofMap(level, 0, 1, 0, 1, true);
	// cout << level << endl;

	// level = 20 * log10(level);
	db = 20 * log(level);
	
	audioLevel = ofMap(level, 0, 1, 0, ofGetWidth() - 100, true);
	audioLevel2 = ofMap(db, -96, 0, 0, ofGetWidth() - 100, true);

	// save every 50 ms
	if(ofGetElapsedTimeMillis() - timer > 50 && player.isLoaded()){
		if(player.isPlaying()){
			// save currentPlayer's RMS value to vector
			frames.push_back(level);
			cout << level << endl;
			timer = ofGetElapsedTimeMillis();
		} else {
			cout << "done!" <<endl;
			exportToJSON();
		}
	}	
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

void ofApp::exportToJSON(){
	ofxJSONElement json;

	Json::Value vec(Json::arrayValue);
	for(uint i=0; i<frames.size(); i++){
		vec.append(frames[i]);
	}
	json["frames"] = vec;

	if(!bExportDone){
		if(json.save("export/frames.json", true)){
			ofLogNotice("ofApp::exportToJSON") << "export finished";
			bExportDone = true;
		}  else {
		ofLogNotice("ofApp::exportToJSON") << "export failed!";
		cout << "json.getRawString() " << endl;
	} else {
		ofExit();
	}
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