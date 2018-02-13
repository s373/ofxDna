/* ofxDna
 * André Sier 2011
 *
 * http://www.karlsims.com/papers/siggraph91.html
 *
 * ofxDna is a c++ class to handle simple genetic
 * evolution, mating, crossover of objects genotypes
 *
 * licensed under lgpl
 * copyright 2011 André Sier
 * astronaut @ s373.net
 */

#pragma once
#include "ofMain.h"

class ofxDna {
public:

	vector<float> dna;
	string 	dnastring;
	int num;
	int generation;

	int mateMode;
	int boundsMode;

	int poolelements;


    ofxDna();
    ~ofxDna(){}

    // setup
	void setup(int num) ;
	void setup(vector<float>* data);
	void setup(string &data);
	void setup(ofxDna & d);
	void setup(ofxDna & d, float dev);

	ofxDna * setNum(int n);
	int size();
	int getNum();
	void incGeneration();

	// set
	ofxDna * setDna(ofxDna * d);
	ofxDna * setDna( string &data);
	ofxDna * setDna( vector<float>& data);
	ofxDna * setGene(int n, float val);
	ofxDna * set( int n,  float val);
	ofxDna * setRandomDNA();
	ofxDna * setMateMode(int mateMode);
	ofxDna * setBoundsMode(int boundsMode);

	// get
	vector<float>* getDna();
	string & getDnaString();
	float get(int n);
	float getGene(int n);
	int getMateMode();
    int getBoundsMode();


	// mutate
	ofxDna * mutate(float prob);
	ofxDna * mutate(float prob, float amount);
	ofxDna * mutateGene(int gene, float dev) ;

	// mate
	ofxDna * mate(ofxDna & dnaparent);
	ofxDna * mate(ofxDna & dnaparent, float param);

	// difference
	float difference(ofxDna & dnatarget) ;
	vector<float> differenceDNA(ofxDna & dnatarget) ;
	float differenceGene(int gene, ofxDna & dnatarget) ;
	float fitness(ofxDna & dnatarget) ;

	//mix
	void mix(ofxDna &dnatarget, float amount);

	// data
	void print() ;
	void printDna() ;
	string toString() ;

protected:
	void bound();

	ofxDna * crossover1(ofxDna & dnaparent);
	ofxDna * crossover2(ofxDna & dnaparent, float prob);
	ofxDna * crossover3(ofxDna & dnaparent, float percent);
	ofxDna * crossover4(ofxDna & dnaparent);



};
