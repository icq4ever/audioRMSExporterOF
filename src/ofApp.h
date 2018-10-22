#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void exportToJSON();

	ofSoundPlayer player;
	static constexpr size_t nBandsToGet=128;
	std::array<float, nBandsToGet> fftSmoothed{{0}};

	float meterEase = 0.5;
	double level, audioLevel, audioLevel2;
	double db;

	//audioPlayer
	vector<float> frames;
	uint64_t timer;

	// check is Saved
	bool bExportDone = false;
	bool bRecording = false;

	// some GUI
	// ofxPanel gui;
	void setupGUI();
	ofxDatGuiButton* loadBtn;
	ofxDatGuiButton* beginBtn;

	void onButtonEvent(ofxDatGuiButtonEvent e);
};
