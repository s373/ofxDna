#include "testApp.h"

//--------------------------------------------------------------
testApp::testApp(){

}

//--------------------------------------------------------------
void testApp::setup(){

	A.setup(ofGetWidth()/2);
	B.setup(ofGetWidth()/2);
	y = 0;
		
	ofSetBackgroundAuto(false);
	ofBackground(255);
	ofSetFrameRate(60);

}

//--------------------------------------------------------------
void testApp::update(){
	
	if(ofGetMousePressed(0)){ 
		ofxDna temp(A);
		A.mate( B, ofMap(mouseX, 0, ofGetWidth(), 0., 1));
		B.mate( temp, ofMap(mouseX, 0, ofGetWidth(), 0., 1));
	}

			   
	if(ofGetMousePressed(2)){
		A.mutate( ofMap(mouseX, 0, ofGetWidth(), 0., 1));
		B.mutate( ofMap(mouseX, 0, ofGetWidth(), 0., 1));
	}
								 
			   
	
	y++;
	if(y>ofGetHeight())
		y=0;
	
}


//--------------------------------------------------------------
void testApp::draw(){
		
	for(int i=0; i<ofGetWidth()/2; i++){		
		float val = A.getGene(i);//dataA->at(i);
		ofSetColor(val*255);		
		ofRect(i, y, 1, 1);
	}
	for(int i=0; i<ofGetWidth()/2; i++){			
		ofSetColor(B.getGene(i)*255);		
		ofRect(i+ofGetWidth()/2, y, 1, 1);
	}
	
	
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate())+
					   "\ngen: " +ofToString(A.generation)+ 
					   "\nmate: " +ofToString(A.mateMode) + " "+ ofToString(B.mateMode), 5, 15);
		
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	if(key=='a'){
		int m = A.getMateMode();
		m = (m+1)%4;
		A.setMateMode(m);
		cout <<"A matemode " << m << endl;
	} 
	if(key=='b'){
		int m = B.getMateMode();
		m = (m+1)%4;
		B.setMateMode(m);
		cout << "B matemode " << m << endl;
	} 
	
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

