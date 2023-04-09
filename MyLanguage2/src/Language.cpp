/*
 * Metodología de la Programación: Language2
 * Curso 2022/2023
 */

/** 
 * @file Language.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */

/*
private:
    std::string _languageId; ///< language identifier
    BigramFreq _vectorBigramFreq[DIM_VECTOR_BIGRAM_FREQ]; ///< array of BigramFreq
    int _size; ///< Number of elements in _vectorBigramFreq
*/

#include "Language.h"
#include <string>

using namespace std;

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";

Language::Language() : _languageId("unknown"), _vectorBigramFreq[DIM_VECTOR_BIGRAM_FREQ],
                       _size(0) {}
Language::Language(int numberBigrams) : _languageId("unknown"), _vectorBigramFreq[DIM_VECTOR_BIGRAM_FREQ],
                                        _size(0) {}
const string & Language::getLanguageId() const {return _languageId;}

void Language::SetLanguageId(string id) {_languageId = id;}

const BigramFreq & Language::at(int index) const {
    bool wrong_index = index < 0 || index >= _size;
    string MSG_EXC = "In Method \"const BigramFreq & Language::at(int index)\""
                           " given index out of range";
    
    if (wrong_index) throw std::out_of_range(MSG_EXC);
    else {
        return _vectorBigramFreq[index];
    }
}

BigramFreq & Language::at(int index) {
    bool wrong_index = index < 0 || index >= _size;
    string MSG_EXC = "In Method \"const BigramFreq & Language::at(int index)\""
                           " given index out of range";
    
    if (wrong_index) throw std::out_of_range(MSG_EXC);
    else {
        return _vectorBigramFreq[index];
    }    
}

int Language::getSize() const {return _size;}

int Language::findBigram(Bigram bigram) const {
    bool found = false;
    string bigram_str = bigram.getText();
    
    int c = 0;
    int pos = -1;
    
    while (!found && c < _size) {
        found = (_vectorBigramFreq[c]->getBigram()->getText() == bigram_str);
        if (!found) c++;
        else pos = c;
    }
    
    return(pos);
}

std:string Language::toString() const {
    string str = "";
    
    str = to_string(_size);
    
    for (int i = 0; i < _size; i++) {
        str = str + '\n' + _vectorBigramFreq[i].getBigram().toString();
        str = str + ' ' + to_string(_vectorBigramFreq[i]. getFrequency());
    }
    
    return(str);
}