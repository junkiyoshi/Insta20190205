#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofColor color(255);
	int radius = 320;

	vector<glm::vec2> locations;
	for (int i = 0; i < 5; i++) {

		float noise_seed = ofRandom(1000);
		for (int deg = 0; deg < 360; deg += 5) {

			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_radius = ofMap(ofNoise(noise_seed, noise_location.x, noise_location.y, ofGetFrameNum() * 0.005), 0, 1, radius * 0.5, radius);

			auto location = glm::vec2(noise_radius * cos(deg * DEG_TO_RAD), noise_radius * sin(deg * DEG_TO_RAD));
			locations.push_back(location);
		}
	}

	for (auto location : locations) {

		bool draw_circle = false;
		float circle_alpha = 0;
		for (auto other : locations) {

			if (location == other) { continue; }

			auto distance = glm::distance(location, other);
			if (distance < 25) {

				float alpha = ofMap(distance, 0, 25, 255, 32);
				ofSetColor(color, alpha);

				ofDrawLine(location, other);

				if (circle_alpha < alpha) { circle_alpha = alpha; }
				draw_circle = true;
			}
		}

		if (draw_circle) {

			ofSetColor(color, circle_alpha);
			ofDrawCircle(location, 3);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}