#include "testApp.h"

//--------------------------------------------------------------
testApp::testApp(){

}

//--------------------------------------------------------------
void testApp::setup(){
	
	for (int i=0; i<100;i++) {
		float rad = (float)ofGetWidth()/12;
		ofPoint loc((i%10)*ofGetWidth()/10+rad/2, (i/10)*ofGetHeight()/10+rad/2);
		la[i].setup(loc, rad);
	}
	
	ofSetFrameRate(60);	

}

//--------------------------------------------------------------
void testApp::update(){
	

}


//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(255);
	
	if (ofGetMousePressed(0)) {    
		for (int i=0;i<100;i++) {
			la[i].dna.mutate(  ofMap(mouseX, 0, ofGetWidth(), 0, 0.1) );
		}
	} 
	
	if (ofGetMousePressed(2)) {    
		for (int i=0;i<99;i++) {
			la[i].dna.mate( la[i+1].dna, ofMap(mouseX, 0, ofGetWidth(), 0, 0.1)  );
		}
	} 
	
	for (int i=0;i<100;i++) {
		la[i].display();
	}
	string txt = "notmutating"; 
	if (ofGetMousePressed(0)) txt = "mutating";
	if (ofGetMousePressed(2)) txt = "mating";
	txt += "\nmutationindex: "+ofToString(ofMap(mouseX, 0, ofGetWidth(), 0, 0.1));
	ofSetColor(0);
	ofDrawBitmapString(txt, 5, 20);	
	
		
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	
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

