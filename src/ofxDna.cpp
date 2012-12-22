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
#include "ofxDna.h"

ofxDna::ofxDna(){
	mateMode = 0;
	boundsMode = 2;
	poolelements = 0;
}

// setup	

void ofxDna::setup(int num) {
	setNum(num);
}

void ofxDna::setup(vector<float>* data) {
	setNum(data->size());
	for (int i = 0; i < data->size(); i++) {
		dna[i] = data->at(i);
	}
}

void ofxDna::setup(ofxDna & d) {
	setNum(d.num);
	for (int i = 0; i < d.dna.size(); i++) {
		dna[i] = d.dna[i];
	}
}

void ofxDna::setup(ofxDna & d, float dev) {
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
ofxDna * ofxDna::setNum(int n) {
	num = n;
	dna.assign(num, 0);
	return setRandomDNA();
}

/**
 * @return num
 */
int ofxDna::size() {
	return num;
}
int ofxDna::getNum() {
	return num;
}

/**
 * @param dna
 * @return
 */
ofxDna * ofxDna::setDna(ofxDna * d) {
	return setDna(d->dna);
}

/**
 * @param data
 * @return
 */
ofxDna * ofxDna::setDna( vector<float>& data) {
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
vector<float>* ofxDna::getDna() {
	return &dna;
}

float ofxDna::get(int n) {
	return dna[n];
}
float ofxDna::getGene(int n) {
	return dna[n];
}

ofxDna * ofxDna::setGene(int n, float val) {
	dna[n] = val;
	return this;
}
ofxDna * ofxDna::set( int n,  float val) {
	dna[n] = val;
	return this;
}

ofxDna * ofxDna::setRandomDNA() {
	for (int i = 0; i < dna.size(); i++) {
		dna[i] = ofRandom(1);
	}
	return this;
}

void ofxDna::incGeneration(){
	generation++;
}

ofxDna * ofxDna::mutate(float prob) {
	incGeneration();
	for (int i = 0; i < num; i++) {
		if (ofRandom(1) < prob)
			dna[i] = ofRandom(1.0000001f);
	}
	bound();
	return this;
}

ofxDna * ofxDna::mutate(float prob, float amout) {
	incGeneration();
	// for (int i = 0; i < num; i++) {
	// float rnd = random(1f);
	// if (rnd > a && rnd < b)
	// dna[i] = random(1.0000001f);
	// }
	// return this;
	for (int i = 0; i < num; i++) {
		if (ofRandom(1) < prob)
			dna[i] += ofRandom(-amount, amount);
	}
	bound();
	return this;
}

// mate
ofxDna * ofxDna::mate(ofxDna & dnaparent) {
	return mate(dnaparent, 0.5f);
}

// mate
ofxDna * ofxDna::mate(ofxDna & dnaparent, float param) {
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

ofxDna * ofxDna::crossover1(ofxDna & dnaparent) {
	int pt = (int) ofRandom(dna.size());
	for (int i = 0; i < num; i++) {
		if (i < pt)
			continue;
		else
			dna[i] = dnaparent.dna[i];
	}
	return this;
}

ofxDna * ofxDna::crossover2(ofxDna & dnaparent, float prob) {
	for (int i = 0; i < num; i++) {
		bool useOtherGene = ofRandom(1) > prob;
		if (useOtherGene)
			dna[i] = dnaparent.dna[i];
	}
	return this;
}

ofxDna * ofxDna::crossover3(ofxDna & dnaparent, float percent) {
	float per0 = 1.0f - percent;
	float per1 = percent;
	for (int i = 0; i < num; i++) {
		dna[i] = per0 * dna[i] + per1 * dnaparent.dna[i];
	}
	return this;
}

ofxDna * ofxDna::crossover4(ofxDna & dnaparent) {
	for (int i = 0; i < num; i++) {
		dna[i] = ofRandom(dna[i], dnaparent.dna[i]);
	}
	return this;
}


void ofxDna::bound(){
	
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
ofxDna * ofxDna::mutateGene(int gene, float dev) {
	dna[gene] += ofRandom(-dev, dev);
	
	return this;
}

/**
 * @param dnatarget
 * @return
 */
float ofxDna::difference(ofxDna & dnatarget) {
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
vector<float> ofxDna::differenceDNA(ofxDna & dnatarget) {
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
float ofxDna::differenceGene(int gene, ofxDna & dnatarget) {
	return ABS(dnatarget.dna[gene] - dna[gene]);
}

/**
 * @param dnatarget
 * @return
 */
float ofxDna::fitness(ofxDna & dnatarget) {
	return 1.0f - (difference(dnatarget) / num);
}

void ofxDna::print() {
	printDna();
}

void ofxDna::printDna() {
	cout << "dna num: " + ofToString(num) + "\n";
	for (int i = 0; i < num; i++) {
		cout << ofToString(dna[i]) + " ";
	}
	cout << endl;
}

string ofxDna::toString() {
	string data = "";
	for (int i = 0; i < num; i++) {
		data += ofToString(dna[i]) + " ";
	}
	return data;
}

ofxDna * ofxDna::setMateMode(int mateMode) {
	this->mateMode = mateMode;
	return this;
}

int ofxDna::getMateMode() {
	return mateMode;
}

ofxDna * ofxDna::setBoundsMode(int boundsMode) {
	this->boundsMode = boundsMode;
	return this;
}

int ofxDna::getBoundsMode() {
	return boundsMode;
}

