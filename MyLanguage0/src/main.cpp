/* 
 * File:   main.cpp
 * Author: Daniel Hidalgo Chica
 *
 * Created on March 2, 2023, 10:43 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Bigram.h"

using namespace std;

/**
 * This program reads a text (without spaces) with a undefined number of 
 * characters and a text with two characters (bigram). It finds the bigrams 
 * contained in the first text, storing them in an array of Bigram. 
 * After that, the bigrams of the array are shown in the standard output. 
 * Then it converts to uppercase the bigrams in the array that are equals to the 
 * bigram of the second text. Finally the bigrams of the array are shown again 
 * in the standard output. 
 * Running example:
 * > language0 < data/SimpleText.txt
 */

// Function to check if two bigrams are equal

bool areEqual (Bigram bigram1, Bigram bigram2) {
    return (bigram1.getText() == bigram2.getText());
}

// Function to convert a string to lowercase

void toLower (string & str) {
    
    int len = str.length();

    for (int i = 0; i < len; i++)
        str.at(i) = tolower(str.at(i));    
}


int main() {
    // This string contains the list of characters that are considered as
    // valid within a word. The rest of characters are considered as
    // separators
    
    const string validCharacters = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

    // Read a text
    
    string text = "";
    cin >> text;
    
    // Read a bigram (tex with two characters)
    
    string bigram_compare_str;
    cin >> bigram_compare_str;
    
    Bigram bigram_compare(bigram_compare_str);
    
    
    // Find the bigrams in text and put them in an array of Bigrams
    
    int len = text.length();
    
    // Convert the text to lowercase
    
    toLower(text);
    
    // As the maximum number of bigrams is the length of the string minus 1:
    
    Bigram bigrams_array[len-1];
    int used = 0;
    
    for (int i = 0; i < len-1; i++) {
        
        char present_char = text.at(i);
        char next_char = text.at(i+1);
        
        bool both_valid = isValidCharacter(present_char, validCharacters) 
                          && isValidCharacter(next_char, validCharacters);
        
        if (both_valid) {
            bigrams_array[used] = Bigram(present_char, next_char);
            used++;
        }   
    }
    
    
    
    // Show the bigrams stored in the array and the number of bigrams stored
    
    cout << used << '\n';
    
    for (int i = 0; i < used; i++) {
        cout << bigrams_array[i].toString();
        cout << endl;    
    }
    
    cout << '\n';
    
    // Convert to uppercase the bigrams in the array that are equals to input bigram
    
    for (int i = 0; i < used; i++) {
        if (areEqual(bigram_compare, bigrams_array[i]))
            toUpper(bigrams_array[i]);
    }
    
    // Show again the bigrams stored in the array
    
    cout << used << '\n';

    
    for (int i = 0; i < used; i++) {
        cout << bigrams_array[i].toString();
        cout << endl;
    }           
    
    return (0);
}




