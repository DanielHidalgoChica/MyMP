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
#include <fstream>

using namespace std;

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";

Language::Language() : _languageId("unknown"), _size(0) {}

Language::Language(int numberBigrams) : _languageId("unknown"), _size(0) 
{
    if (numberBigrams < 0 || numberBigrams > DIM_VECTOR_BIGRAM_FREQ)
        throw std::out_of_range("In constructor: too many Bigrams");
    else {
        for (int i = 0; i < numberBigrams; i++) {
            _vectorBigramFreq[i] = BigramFreq();
            _size++;
        }
    }
}

const string & Language::getLanguageId() const {return _languageId;}

void Language::setLanguageId(string id) {_languageId = id;}

const BigramFreq & Language::at(int index) const {
    bool wrong_index = index < 0 || index >= _size;
    string MSG_EXC = "In Method \"const BigramFreq & Language::at(int index)\""
                           " given index out of range";
    
    if (wrong_index) throw std::out_of_range(MSG_EXC);
    else return _vectorBigramFreq[index];
    
}

BigramFreq & Language::at(int index) 
{
    bool wrong_index = index < 0 || index >= _size;
    string MSG_EXC = "In Method \"const BigramFreq & Language::at(int index)\""
                           " given index out of range";
    
    if (wrong_index) throw std::out_of_range(MSG_EXC);
    else {
        return _vectorBigramFreq[index];
    }    
}

int Language::getSize() const {return _size;}

int Language::findBigram(const Bigram& bigram) const {
    bool found = false;
    string bigram_str = bigram.getText();
    
    int c = 0;
    int pos = -1;
    
    while (!found && c < _size) {
        found = (_vectorBigramFreq[c].getBigram().getText() == bigram_str);
        if (!found) c++;
        else pos = c;
    }
    
    return(pos);
}

std::string Language::toString() const {
    string str = "";
    
    str += MAGIC_STRING_T + '\n';
    str += _languageId + '\n';
    
    str += to_string(_size);
    
    for (int i = 0; i < _size; i++) {
        str = str + '\n' + _vectorBigramFreq[i].getBigram().toString();
        str = str + ' ' + to_string(_vectorBigramFreq[i]. getFrequency());
    }
    
    return(str);
}


void Language::sort() {
    // We'll sort the array using a selection algorithm

    for (int left = 0; left < _size - 1; left++) {

        int max_freq = _vectorBigramFreq[left].getFrequency();
        int pos_max = left;

        bool swap_needed = false;

        for (int i = left + 1; i < _size; i++) {

            bool new_max = _vectorBigramFreq[i].getFrequency() > max_freq || ((_vectorBigramFreq[i].getFrequency()
                    == max_freq && _vectorBigramFreq[i].getBigram().getText()
                    < _vectorBigramFreq[pos_max].getBigram().getText()));

            if (new_max) {

                swap_needed = true;

                max_freq = _vectorBigramFreq[i].getFrequency();
                pos_max = i;
            }
        }

        if (swap_needed) {
            BigramFreq aux = _vectorBigramFreq[left];
            _vectorBigramFreq[left] = _vectorBigramFreq[pos_max];
            _vectorBigramFreq[pos_max] = aux;
        }

    }
}

void Language::save(const char fileName[]) const {
    ofstream outputStream;
    
    outputStream.open(fileName);
    
    if (!outputStream) {
        const string MSG_EXC = "In method \"void Language::save("
        "const char fileName[])\": file cannot be opened or error ocurred"
        "while writing";
        
        throw std::ios_base::failure(MSG_EXC);
    }
    
    outputStream << toString();
    
    outputStream.close();
}

void Language::load(const char fileName[]) {
    ifstream inputStream;
    
    // Opens the Stream with a certain file
    
    inputStream.open(fileName);
    
    if (!inputStream) {
        string MSG_EXC = "In method \"void Language::load("
        "const char fileName[])\": file cannot be opened or error ocurred"
        "while reading";
        throw std::ios_base::failure(MSG_EXC);
    }
    
    
    string poss_magic_string;
    inputStream >> poss_magic_string;

    if (poss_magic_string != MAGIC_STRING_T) {
        string MSG_EXC = "In method \"void Language::load("
        "const char fileName[])\": Invalid magic string";
        throw std::invalid_argument(MSG_EXC);
    } 
    
    // We read the langua ge

    inputStream >> _languageId;

    // We read the number of Bigrams

    int bigram_counter;

    inputStream >> bigram_counter;

    if (bigram_counter > DIM_VECTOR_BIGRAM_FREQ || bigram_counter < 0) {
        string MSG_EXC = "In method \"void Language::load("
        "const char fileName[])\": Too many or negative BigramFreqs";
        throw std::out_of_range(MSG_EXC);
    }
    
    
    string aux_bgr_str;
    int aux_freq;
    
    _size = 0; // Por si acaso no estaba recién inicializado el objeto Language
    
    for (int i = 0; i < bigram_counter; i++) {
  
        inputStream >> aux_bgr_str >> aux_freq;

        Bigram aux_bigram = Bigram(aux_bgr_str);
        
        _vectorBigramFreq[i].setBigram(aux_bigram);
        
        _vectorBigramFreq[i].setFrequency(aux_freq);
        
        _size++;
    }
    
    // Closes the stream
    
    inputStream.close();
}


void Language::append(const BigramFreq& bigramFreq) {
    int pos_bigram = findBigram(bigramFreq.getBigram());
    bool full_array = (_size == DIM_VECTOR_BIGRAM_FREQ);
    
    if (pos_bigram >= 0) {
        int new_freq = _vectorBigramFreq[pos_bigram].getFrequency() + bigramFreq.getFrequency();
        _vectorBigramFreq[pos_bigram].setFrequency(new_freq);
    }
    else 
        if (!full_array) {
            _vectorBigramFreq[_size] = bigramFreq;
            _size++;
        }
        else {
            string MSG_EXC = "In method \"void Language::append("
            "const char fileName[])\": too many bigramFreqs";
            throw std::out_of_range(MSG_EXC);
        }
}

void Language::join(const Language& language) {
    for (int i = 0; i < language._size; i++) {
        append(language._vectorBigramFreq[i]);
    }
}