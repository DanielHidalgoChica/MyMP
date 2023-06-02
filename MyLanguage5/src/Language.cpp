/*
 * Metodología de la Programación: Language5
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

#include "Language.h"

#include <string>
#include <fstream>

using namespace std;

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";
const string Language::MAGIC_STRING_B="MP-LANGUAGE-B-1.0";

using namespace std;

Language::Language() : _languageId("unknown"), _size(0), _vectorBigramFreq(nullptr) {}

Language::Language(const int numberBigrams) : _languageId("unknown")
{
    if (numberBigrams < 0) {
        string MSG_EXC = "In Method \"const BigramFreq & Language::Language(const int numberBigrams)\""
                               " negative number of bigrams";
        throw std::out_of_range(MSG_EXC);
    } else {
        allocate(numberBigrams);
    }
}

const string & Language::getLanguageId() const {return _languageId;}

void Language::setLanguageId(const string& id) {_languageId = id;}

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

double Language::getDistance(const Language& otherLanguage) const {
    bool any_empty = getSize() == 0;
    
    if (any_empty) {
        string MSG_EXC = "In Method \"double Language::getDistance(const Language& otherLanguage) const\""
                           " Calculating distance to an empty Language object";
        throw std::invalid_argument(MSG_EXC);
    }
    // We calculate the sum of the differences in ranks in both Language's for every 
    // bigram in this Language    
        
    double sum_diff_ranks = 0;
    
    for (int i = 0; i < _size; i++) {
        int pos_in_this_language = i;
        int pos_in_other_language = otherLanguage.findBigram(_vectorBigramFreq[i].getBigram());
        
        if (pos_in_other_language == -1) pos_in_other_language = _size;
        
        sum_diff_ranks += abs(pos_in_this_language - pos_in_other_language);
    }
    
    return sum_diff_ranks/(_size*_size);
}

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

        BigramFreq max_bf = _vectorBigramFreq[left];
        int pos_max = left;

        bool swap_needed = false;

        for (int i = left + 1; i < _size; i++) {
            
            if (_vectorBigramFreq[i] > max_bf) {
                swap_needed = true;
                max_bf = _vectorBigramFreq[i];
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

void Language::save(const char fileName[], char mode) const {
    ofstream outputStream;
    
    outputStream.open(fileName);
    
    if (!outputStream) {
        const string MSG_EXC = "In method \"void Language::save("
        "const char fileName[])\": file cannot be opened or error ocurred"
        "while writing";
        
        throw std::ios_base::failure(MSG_EXC);
    }
    
    outputStream << this->toString();
    
    outputStream.close();
}

void Language::load(const char fileName[]) {
    deallocate();
    
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
    
    // We read the languageID

    inputStream >> _languageId;

    // We read the number of Bigrams
    deallocate();

    inputStream >> _size;
    allocate(_size); // Reserve memory for _size BigramFreqs
 

    if (_size < 0) {
        string MSG_EXC = "In method \"void Language::load("
        "const char fileName[])\": Too many or negative BigramFreqs";
        throw std::out_of_range(MSG_EXC);
    }
    
    
    string aux_bgr_str;
    int aux_freq;
    
    for (int i = 0; i < _size; i++) {
  
        inputStream >> aux_bgr_str >> aux_freq;

        Bigram aux_bigram = Bigram(aux_bgr_str);
        
        _vectorBigramFreq[i].setBigram(aux_bigram);
        
        _vectorBigramFreq[i].setFrequency(aux_freq);
    }
    
    // Closes the stream
    
    inputStream.close();
}


void Language::append(const BigramFreq& bigramFreq) {
        
    int pos_bigram = findBigram(bigramFreq.getBigram());

    if (pos_bigram >= 0) {
        int new_freq = _vectorBigramFreq[pos_bigram].getFrequency() + bigramFreq.getFrequency();
        _vectorBigramFreq[pos_bigram].setFrequency(new_freq);
    }
    else  {
        reallocate(_size+1);
        _vectorBigramFreq[_size-1] = bigramFreq;
    }
}

void Language::allocate(int nElements)
{
    _vectorBigramFreq = new BigramFreq[nElements];
    _size = nElements;
}

void Language::deallocate() 
{
    delete [] this->_vectorBigramFreq;
    _vectorBigramFreq = nullptr;
    _size = 0;
}

void Language::reallocate(int newSize) {
    
    if (newSize >= 0) { 
        BigramFreq * bf_ptr = new BigramFreq[newSize];

        for (int i = 0; i < newSize && i < this->_size; i++)
            bf_ptr[i] = this->_vectorBigramFreq[i];

        this->deallocate();
        this->_vectorBigramFreq = bf_ptr;
        this->_size = newSize;
    }
}

void Language::copy(const Language& otherLanguage){
        
    this->_languageId = otherLanguage._languageId;
    this->_size = otherLanguage._size;
        
    for (int i = 0; i < _size; i++)
        this->_vectorBigramFreq[i] = otherLanguage._vectorBigramFreq[i];
} 

Language::Language(const Language& orig) {
  this->allocate(orig._size);
  this->copy(orig);
}




/**
 * @brief Destructor of class Language
 */
Language::~Language() {
    deallocate();
}

/**
 * @brief Overloading of the assignment operator for Language class
 * @param orig the Language object used as source for the assignment
 * @return A reference to this object
 */
    
Language & Language::operator=(const Language& orig) {
    
    if (&orig != this) {
        this->deallocate();
        this->allocate(orig._size);
        this->copy(orig);
    }
    
    return(*this);
}

Language Language::operator+=(Language language) {
    for (int i = 0; i < language._size; i++) 
        append(language._vectorBigramFreq[i]);
    return (*this);
}

BigramFreq & Language::operator[](int index)
{
    return _vectorBigramFreq[index];
}

const BigramFreq & Language::operator[](int index) const
{
    return _vectorBigramFreq[index];
}

ostream& operator<<(ostream &os, const Language& language)
{
    os << language.toString();
    return os;
}

istream& operator>>(istream &is, Language& language)
{
    string languageId;
    int size;
    string MAGIC_STRING_T = language.MAGIC_STRING_T;
  
    string poss_magic_string;
    is >> poss_magic_string;
    
    if (poss_magic_string != MAGIC_STRING_T) {
        string MSG_EXC = "In method \"void Language::load("
        "const char fileName[])\": Invalid magic string";
        throw std::invalid_argument(MSG_EXC);
    } 

    // We read the languageID

    is >> languageId;
    language.setLanguageId(languageId);

    // We read the number of Bigrams
    language.deallocate();

    is >> size; 
    language._size = size;

    if (size < 0) {
        string MSG_EXC = "In method \"void Language::load("
        "const char fileName[])\": Too many or negative BigramFreqs";
        throw std::out_of_range(MSG_EXC);
    }
    
    language.allocate(size); // Reserve memory for _size BigramFreqs

    string aux_bgr_str;
    int aux_freq;
    
    for (int i = 0; i < size; i++) {
        
        BigramFreq aux_bf;
  
        is >> aux_bf;
        
        language._vectorBigramFreq[i] = aux_bf;
    }
    
    return (is);
}
