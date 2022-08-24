#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofEnableDepthTest();

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_mesh.clear();
	this->frame_mesh.clear();

	auto R = 200;
	auto r = 10;
	auto v_span = 3;
	auto u_span = 6;

	int index = 0;
	for (auto v = 0; v < 360; v += v_span) {

		for (auto u = 0; u < 360; u += u_span) {

			auto noise_seed = this->make_point(R, r, u + u_span * 0.5, v + v_span * 0.5);
			auto noise_value = ofNoise(glm::vec4(noise_seed * 0.02, ofGetFrameNum() * 0.01));
			auto height = 30;
			if (noise_value < 0.55) {
				
				height = ofMap(noise_value, 0, 0.55, 0, 10);
			}

			vector<glm::vec3> vertices;
			vertices.push_back(this->make_point(R, r, u, v));
			vertices.push_back(this->make_point(R, r, u + u_span, v));
			vertices.push_back(this->make_point(R, r, u + u_span, v + v_span));
			vertices.push_back(this->make_point(R, r, u, v + v_span));
			vertices.push_back(this->make_point(R, r + height, u, v));
			vertices.push_back(this->make_point(R, r + height, u + u_span, v));
			vertices.push_back(this->make_point(R, r + height, u + u_span, v + v_span));
			vertices.push_back(this->make_point(R, r + height, u, v + v_span));

			int index = this->face_mesh.getNumVertices();
			this->face_mesh.addVertices(vertices);
			this->frame_mesh.addVertices(vertices);

			for (int i = 0; i < 8; i++) {

				if (i < 4) {

					this->face_mesh.addColor(ofColor(255));
					this->frame_mesh.addColor(ofColor(0));
				}
				else {

					this->face_mesh.addColor(ofColor(ofMap(height, 0, 30, 0, 255)));
					this->frame_mesh.addColor(ofColor(0));
				}
			}

			// Face Index

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 2);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

			this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
			this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 5);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 1);

			this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
			this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 2);

			this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);
			this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 7); this->face_mesh.addIndex(index + 3);

			this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 7); this->face_mesh.addIndex(index + 4);
			this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 0);

			// Frame Index

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 1);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 2);
			this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 3);
			this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 0);

			this->frame_mesh.addIndex(index + 4); this->frame_mesh.addIndex(index + 5);
			this->frame_mesh.addIndex(index + 5); this->frame_mesh.addIndex(index + 6);
			this->frame_mesh.addIndex(index + 6); this->frame_mesh.addIndex(index + 7);
			this->frame_mesh.addIndex(index + 7); this->frame_mesh.addIndex(index + 4);

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 4);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 5);
			this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 6);
			this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 7);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.6666666666666666);

	this->face_mesh.drawFaces();
	this->frame_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}