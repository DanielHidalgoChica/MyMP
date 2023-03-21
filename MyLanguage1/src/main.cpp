/*
 * Metodología de la Programación: Language1
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 *
 * Created on 7 de febrero de 2023, 14:02
 */


/**
 * This program reads from the stardard input, an integer n (number of elements) 
 * and a list of n pairs bigram-frequency. The pairs are stored in an array, 
 * and then it is sorted in decreasing order of frequency. After that, 
 * all the bigrams are changed to uppercase. The sorted array is finally shown 
 * in the stardard output. 
 * Running example:
 * > language1 < data/miniquijotebigrams.txt 
 */


#include <string>
#include <cstring>

#include "Bigram.h"
#include "BigramFreq.h"
#include "ArrayBigramFreqFunctions.h"

using namespace std;

int main() {
    // Read the number of elements
    
    int nElements;
    
    int DIM = 1000;
    
    BigramFreq bigram_freq_array[DIM];
    
    // Read of the array of BigramFreq's
    
    readArrayBigramFreq(bigram_freq_array,DIM,nElements);
    
    // Sort
    
    sortArrayBigramFreq(bigram_freq_array,nElements);
    
    // Turn it to uppercase
    
    toUpperArrayBigramFreq(bigram_freq_array,nElements);
    
    // Print
    
    printArrayBigramFreq(bigram_freq_array,nElements);
    
}

