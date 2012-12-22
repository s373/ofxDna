#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxDna.h"


class LineAgent {
public:		
	ofxDna dna;
	ofPoint origin;
	float rad, rad2;
	
	void setup(ofPoint &loc, float radius) {
		origin = loc;
		dna.setup(10 * 2);
		rad = radius; 
		rad2 = rad/2;
	}	
	void display() {
		for (int i=0; i<dna.getNum()-1;i+=2) {
			float x = dna.getGene(i) * rad + origin.x - rad2; 
			float y = dna.getGene(i+1) * rad + origin.y - rad2; 
			ofLine(origin.x, origin.y, x, y);
			ofRect(x, y, 3, 3);
		}
	}
};



class testApp : public ofBaseApp{

	public:

		testApp();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);

	
	
	LineAgent la[100];
	
};

#endif
