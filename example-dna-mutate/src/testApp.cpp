#include "testApp.h"

//--------------------------------------------------------------
testApp::testApp(){

}

//--------------------------------------------------------------
void testApp::setup(){

	dna.setup(ofGetWidth());
	y = 0;
	
	dna.print();
	
	ofSetBackgroundAuto(false);
	ofBackground(255);
	ofSetFrameRate(60);
	

}

//--------------------------------------------------------------
void testApp::update(){
	if(ofGetFrameNum()<10) ofBackground(255);
	y++;
	if(y>ofGetHeight())
		y=0;
	
	float m = ofMap( mouseX, 0, ofGetWidth(), 0, 0.21);
	float n = ofMap( mouseY, 0, ofGetHeight(), 0, 1);
	dna.mutate(m);
//	dna.mutate(m, n);
}


//--------------------------------------------------------------
void testApp::draw(){
	
	vector<float> * data = dna.getDna();
	
	for(int i=0; i<ofGetWidth(); i++){
		
		float val = data->at(i);

		ofSetColor(val*255);

		glBegin(GL_POINTS);
		glVertex2f(i,y);
		glEnd();
//		ofRect(i, y, 1, 1);
	}
	
	
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate())+
					   "\ngen: " +ofToString(dna.generation)+ 
					   "\nmate: " +ofToString(dna.mateMode), 5, 15);
		
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	setup();
	dna.mateMode = (dna.mateMode+1)%4;
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

