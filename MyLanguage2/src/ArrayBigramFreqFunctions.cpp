/* 
 * File:   BigramFreq.cpp
 * Author: daniel
 * 
 * Created on March 20, 2023, 19:04 AM
 */

#include <iostream>
#include <string>
#include <cstring>

#include "Bigram.h"
#include "BigramFreq.h"
#include "ArrayBigramFreqFunctions.h"

using namespace std;

void readArrayBigramFreq(BigramFreq array[], const int dim, int& nElements) {
    
    // We read the number o elements to put into the array
    cin >> nElements;
    
    bool read = nElements > 0;
    
    int aux_freq; 
    string aux_bigram_text;
        
    if (read) {
        
        if (nElements > dim) nElements = dim;
        
        for (int i = 0; i < nElements; i++) {
            cin >> aux_bigram_text;
            cin >> aux_freq;
            
            
            BigramFreq aux_bigram_freq;
            
            aux_bigram_freq.setBigram(Bigram(aux_bigram_text));
            aux_bigram_freq.setFrequency(aux_freq);
            
            array[i] = aux_bigram_freq;
        }
    }
}

void printArrayBigramFreq(const BigramFreq array[], const int nElements) {
    cout << nElements << '\n';
    for (int i = 0; i < nElements; i++) {
        cout << array[i].getBigram().toString() << ' '; 
        cout << to_string(array[i].getFrequency());
        cout << '\n';
    }
}

void swapElementsArrayBigramFreq(BigramFreq array[], int nElements, int first,
                                int second) 
{
    const string MSG_EXC = "In function void swapElementsArrayBigramFreq: "
                            "out of range indexes"; 
    bool out = first < 0 || second < 0 || 
               first >= nElements || second >= nElements;
    if (out) throw std::out_of_range(MSG_EXC);
    else 
    {
        BigramFreq aux = array[first];   
        array[first] = array[second];
        array[second] = aux;
    }
}

void sortArrayBigramFreq(BigramFreq array[], const int nElements) {
    // We'll sort the array using a selection algorithm
    
    for (int left = 0; left < nElements-1; left++) {
        
        int max_freq = array[left].getFrequency();
        int pos_max = left;
        
        bool swap_needed = false;
        
        for (int i = left+1; i < nElements; i++) {
            
            bool new_max = array[i].getFrequency() > max_freq || (array[i].getFrequency() 
                        == max_freq && array[i].getBigram().getText() 
                        < array[pos_max].getBigram().getText());
            
            if (new_max)  {
                
                swap_needed = true;
                
                max_freq = array[i].getFrequency();
                pos_max = i;
            }
    	}
        
        if (swap_needed)
            swapElementsArrayBigramFreq(array, nElements, left, pos_max);
    }
}

void toUpperArrayBigramFreq(BigramFreq array[], const int nElements) {
    for (int i = 0; i < nElements; i++) {
        
        Bigram aux_bigram = array[i].getBigram();
        aux_bigram.toUpper();
        array[i].setBigram(aux_bigram);
    }
}