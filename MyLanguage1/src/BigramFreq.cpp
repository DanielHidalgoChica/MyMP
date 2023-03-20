/* 
 * File:   BigramFreq.cpp
 * Author: daniel
 * 
 * Created on March 20, 2023, 19:04 AM
 */

#include "BigramFreq.h"
#include <string>
#include <cstring>
#include "Bigram.h"

using namespace std;

BigramFreq::BigramFreq() {
    _bigram = Bigram();
    _frequency = 0;
}

const Bigram & BigramFreq::getBigram () const {
    return (_bigram);
}

int BigramFreq::getFrequency() const {
    return(_frequency);
}

void BigramFreq::setBigram(const Bigram & bigram) {
    _bigram = bigram;
}

void BigramFreq::setFrequency(const int frequency) {
    _frequency = frequency;
}

std::string BigramFreq::toString() const {
    return(_bigram.toString() + " " + to_string(_frequency));
}
