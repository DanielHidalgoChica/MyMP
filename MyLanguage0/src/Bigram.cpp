/* 
 * File:   Bigram.cpp
 * Author: daniel
 * 
 * Created on March 2, 2023, 10:51 AM
 */

using namespace std;

#include <cctype>
#include "Bigram.h"

Bigram::Bigram (const std::string & text) {
    if (text.length() == 2) {
        _text = text;
    } else {
        _text = "__";
    };
}

Bigram::Bigram (char first, char second) {
    
    // We initialize the string and push both characters
    
    _text = "";
    _text.push_back(first);
    _text.push_back(second);
}

string Bigram::getText() const {
    return (_text);
}

string Bigram::toString() const {
    return (_text);
}

const char & Bigram::at(int index) const {
    
    string const MSG_EXC = "In Method \"const char & Bigram::at(int index)\""
                           " Index can only be 1 or 0";
    
    if (index < 0 || index > 1) 
        throw std::out_of_range (MSG_EXC);
    else
        return(_text.at(index));
}

char & Bigram::at(int index) {
    
    string const MSG_EXC = "In Method \"char & Bigram::at(int index)\""
                           " Index can only be 1 or 0";
    
    if (index < 0 || index > 1)
        throw std::out_of_range (MSG_EXC);
    else 
        return (_text.at(index));
}



// Now we will implement the functions outside of the Bigram class

bool isValidCharacter (char character, const string & validCharacters) {
    
    int len = validCharacters.length();
    
    bool found = false;
    
    for (int i = 0; i < len && found == false; i++)
        if (validCharacters.at(i) == character) found = true;
    
    return (found);
}

void toUpper (Bigram & bigram) {
    
    bigram.at(0) = toupper(bigram.at(0));
    bigram.at(1) = toupper(bigram.at(1));
    
}