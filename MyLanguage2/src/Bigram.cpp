/* 
 * File:   Bigram.cpp
 * Author: daniel
 * 
 * Created on March 2, 2023, 10:51 AM
 */

#include <cctype>
#include <string>
#include <cstring>
#include "Bigram.h"

using namespace std;

Bigram::Bigram (const std::string & text) {
    if (text.length() == 2) {
        strcpy(_text, text.c_str());
    } else {
        strcpy(_text, "__");
    }
}

Bigram::Bigram (char first, char second) {    
    _text[0] = first;
    _text[1] = second;
    _text[2] = '\0';
}

Bigram::Bigram (char text[]) {
    strcpy(_text, text);
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
        return(_text[index]);
}

char & Bigram::at(int index) {
    
    string const MSG_EXC = "In Method \"char & Bigram::at(int index)\""
                           " Index can only be 1 or 0";
    
    if (index < 0 || index > 1)
        throw std::out_of_range (MSG_EXC);
    else 
        return (_text[index]);
}



// Now we will implement the functions outside of the Bigram class

bool isValidCharacter (char character, const string & validCharacters) {
    
    int len = validCharacters.length();
    
    bool found = false;
    
    for (int i = 0; i < len && found == false; i++)
        if (validCharacters.at(i) == character) found = true;
    
    return (found);
}

void Bigram::toUpper () {
    _text[0] = toupper(_text[0]);
    _text[1] = toupper(_text[1]);
}