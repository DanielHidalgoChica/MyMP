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

void BigramFreq::setBigram(const Bigram& bigram) {
    _bigram = bigram;
}

void BigramFreq::setFrequency(int frequency) {
    
    const string MSG_EXC = "In Method void BigramFreq::setFrequency(const int frequency)\""
                           " negative frequency";
    
    if (frequency < 0) throw std::out_of_range (MSG_EXC);
    else _frequency = frequency;
}

std::string BigramFreq::toString() const {
    return(_bigram.toString() + " " + to_string(_frequency));
}

void BigramFreq::serialize(ostream& outputStream) {
//    this->_bigram.serialize();
//    ostream::write()
}

void BigramFreq::deserialize(istream& outputStream) {
    
}

ostream& operator<<(std::ostream& os,const BigramFreq & bigramFreq)
{
    
}

istream& operator>>(std::istream& is, BigramFreq& bigramFreq)
{
    
}

bool operator>(const BigramFreq& bigramFreq1,const BigramFreq& bigramFreq2)
{   
    int freq1 = bigramFreq1.getFrequency();
    int freq2 = bigramFreq2.getFrequency();
    
    bool gret_freq = freq1 > freq2;
    bool eq_freq = freq1 == freq2;
    bool gret_text = bigramFreq1.getBigram().getText() > bigramFreq2.getBigram().getText();
    
    return (gret_freq || (eq_freq && gret_text));
}

bool operator<(const BigramFreq& bigramFreq1,const BigramFreq& bigramFreq2)
{   
    return bigramFreq2 > bigramFreq1;
}

bool operator==(BigramFreq bigramFreq1, BigramFreq bigramFreq2)
{
    return !((bigramFreq1 > bigramFreq2) || (bigramFreq1 < bigramFreq2s))
}

bool operator!=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2)
{
   return !(bigramFreq1==bigramFreq2);
}

bool operator<=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2)
{
    return (bigramFreq1 > bigramFreq2) || (bigramFreq1==bigramFreq2);
}

bool operator<=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2)
{
    return !(bigramFreq1>=bigramFreq2);
}