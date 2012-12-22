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
	int num;
	int generation;

	int mateMode;
	int boundsMode;
	
	int poolelements;

	// //////// 

    ofxDna(){
		mateMode = 0;
		boundsMode = 2;
		poolelements = 0;
	}
    ~ofxDna(){}
    
	
	void setup(int num) {
		setNum(num);
	}

	void setup(vector<float>* data) {
		setNum(data->size());
		for (int i = 0; i < data->size(); i++) {
			dna[i] = data->at(i);
		}
	}

	void setup(ofxDna & d) {
		setNum(d.num);
		for (int i = 0; i < d.dna.size(); i++) {
			dna[i] = d.dna[i];
		}
	}

	void setup(ofxDna & d, float dev) {
		setNum(d.num);
		for (int i = 0; i < d.dna.size(); i++) {
			dna[i] = d.dna[i]+ ofRandom(-dev, dev);
		}
	}


	// //////// 

	/**
	 * set num genes
	 * 
	 * @param n
	 * @return
	 */
	ofxDna * setNum(int n) {
		num = n;
		dna.assign(num, 0);
		return setRandomDNA();
	}

	/**
	 * @return num
	 */
	int size() {
		return num;
	}
	int getNum() {
		return num;
	}
	
	/**
	 * @param dna
	 * @return
	 */
	ofxDna * setDna(ofxDna * d) {
		return setDna(d->dna);
	}

	/**
	 * @param data
	 * @return
	 */
	ofxDna * setDna( vector<float>& data) {
		if (data.size() != dna.size())
			setNum(data.size());

		for (int i = 0; i < num; i++) {
			dna[i] = data[i];
		}

		return this;
	}

	/**
	 * @return dna float[]
	 */
	vector<float>* getDna() {
		return &dna;
	}

	float get(int n) {
		return dna[n];
	}
	float getGene(int n) {
		return dna[n];
	}
	
	ofxDna * setGene(int n, float val) {
		dna[n] = val;
		return this;
	}
	ofxDna * set( int n,  float val) {
		dna[n] = val;
		return this;
	}

	ofxDna * setRandomDNA() {
		for (int i = 0; i < dna.size(); i++) {
			dna[i] = ofRandom(1);
		}
		return this;
	}
	
	void incGeneration(){
		generation++;
	}

	ofxDna * mutate(float a) {
		incGeneration();
		for (int i = 0; i < num; i++) {
			if (ofRandom(1) < a)
				dna[i] = ofRandom(1.0000001f);
		}
//		bound();
		return this;
	}

	ofxDna * mutate(float a, float b) {
		incGeneration();
		// for (int i = 0; i < num; i++) {
		// float rnd = random(1f);
		// if (rnd > a && rnd < b)
		// dna[i] = random(1.0000001f);
		// }
		// return this;
		for (int i = 0; i < num; i++) {
			if (ofRandom(1) < a)
				dna[i] += ofRandom(-b, b);
		}
		bound();
		return this;
	}

	// mate
	ofxDna * mate(ofxDna & dnaparent) {
		return mate(dnaparent, 0.5f);
	}

	// mate
	ofxDna * mate(ofxDna & dnaparent, float param) {
		incGeneration();
		switch (mateMode) {
		case 0:
			return crossover1(dnaparent);
		case 1:
			return crossover2(dnaparent, param);
		case 2:
			return crossover3(dnaparent, param);
		case 3:
			return crossover4(dnaparent);
		}
		return this;
	}

	ofxDna * crossover1(ofxDna & dnaparent) {
		int pt = (int) ofRandom(dna.size());
		for (int i = 0; i < num; i++) {
			if (i < pt)
				continue;
			else
				dna[i] = dnaparent.dna[i];
		}
		return this;
	}

	ofxDna * crossover2(ofxDna & dnaparent, float prob) {
		for (int i = 0; i < num; i++) {
			bool useOtherGene = ofRandom(1) > prob;
			if (useOtherGene)
				dna[i] = dnaparent.dna[i];
		}
		return this;
	}

	ofxDna * crossover3(ofxDna & dnaparent, float percent) {
		 float per0 = 1.0f - percent;
		 float per1 = percent;
		for (int i = 0; i < num; i++) {
			dna[i] = per0 * dna[i] + per1 * dnaparent.dna[i];
		}
		return this;
	}

	ofxDna * crossover4(ofxDna & dnaparent) {
		for (int i = 0; i < num; i++) {
			dna[i] = ofRandom(dna[i], dnaparent.dna[i]);
		}
		return this;
	}

	
	void bound(){
		
		if(boundsMode == 0) {
			return;
		}
		
		if (boundsMode == 1) {
			for(int i=0; i<dna.size();i++) {
				if (dna[i] > 1)
					dna[i] = 1;
				if (dna[i] < 0)
					dna[i] = 0;
			}
		}
		if (boundsMode == 2) {
			for(int i=0; i<dna.size();i++) {
				while (dna[i] > 1)
					dna[i] -= 1;
				while (dna[i] < 0)
					dna[i] += 1;
			}
		}
		
		
		
	}
	
	/**
	 * @param gene
	 * @param dev
	 * @return
	 */
	ofxDna * mutateGene(int gene, float dev) {
		dna[gene] += ofRandom(-dev, dev);

		return this;
	}

	/**
	 * @param dnatarget
	 * @return
	 */
	float difference(ofxDna & dnatarget) {
		float val = 0.f;
		for (int i = 0; i < num; i++) {
			val += ABS(dnatarget.dna[i] - dna[i]);
		}
		return val;
	}

	/**
	 * @param dnatarget
	 * @return
	 */
	vector<float> differenceDNA(ofxDna & dnatarget) {
		vector <float> dif; dif.assign(dnatarget.num, 0);
		for (int i = 0; i < num; i++) {
			dif[i] = ABS(dnatarget.dna[i] - dna[i]);
		}
		return dif;
	}

	/**
	 * @param gene
	 * @param dnatarget
	 * @return
	 */
	float differenceGene(int gene, ofxDna & dnatarget) {
		return ABS(dnatarget.dna[gene] - dna[gene]);
	}

	/**
	 * @param dnatarget
	 * @return
	 */
	 float fitness(ofxDna & dnatarget) {
		return 1.0f - (difference(dnatarget) / num);
	}

     void print() {
		printDna();
	}

	void printDna() {
		cout << "dna num: " + ofToString(num) + "\n";
		for (int i = 0; i < num; i++) {
			cout << ofToString(dna[i]) + " ";
		}
		cout << endl;
	}

	string toString() {
		string data = "";
		for (int i = 0; i < num; i++) {
			data += ofToString(dna[i]) + " ";
		}
		return data;
	}

	ofxDna * setMateMode(int mateMode) {
		this->mateMode = mateMode;
		return this;
	}

	int getMateMode() {
		return mateMode;
	}

	ofxDna * setBoundsMode(int boundsMode) {
		this->boundsMode = boundsMode;
		return this;
	}

    int getBoundsMode() {
		return boundsMode;
	}

	

};
