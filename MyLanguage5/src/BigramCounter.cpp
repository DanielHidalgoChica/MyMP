/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 12 February 2023, 11:00
 */

#include <fstream>
#include <string>
#include "BigramCounter.h"

using namespace std;

bool findBigram(const Bigram &bigram, const string & _validCharacters)
{
    char first = bigram.at(0);
    char second = bigram.at(1);
    
    
    int pos_1 = _validCharacters.find(first);
    int pos_2 = _validCharacters.find(second);
    
    return !(pos_1 < 0 || pos_2 < 0);
}

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

BigramCounter::BigramCounter(const std::string &validChars)
{
    int len = validChars.length();
    
    allocate(len);
    
    this->_validCharacters = validChars;
}

BigramCounter::BigramCounter(const BigramCounter &orig) 
{
    int len = orig._validCharacters.length();
    
    allocate(len);
    this->copy(orig);
}

BigramCounter::~BigramCounter() {
    
    deallocate();
}

int BigramCounter::getSize() const 
{
    return this->_validCharacters.length();
}

int BigramCounter::getNumberActiveBigrams() const
{
    int c = 0; // Counter
    int len = this->getSize();
    
    for (int i = 0; i < len; i ++) {
        for (int j = 0; j < len; j++) {
            if (this->_frequency[i][j] > 0)
                c++;
        }
    }
    
    return c;
}

bool BigramCounter::setFrequency(const Bigram& bigram, int frequency)
{
    char first = bigram.at(0);
    char second = bigram.at(1);
    
    int pos_1 = this->_validCharacters.find(first);
    int pos_2 = this->_validCharacters.find(second);
    
    if (pos_1 < 0|| pos_2 < 0) return false;
    else {
        this->_frequency[pos_1][pos_2] = frequency;
        return true;
    }
}

void BigramCounter::increaseFrequency(const Bigram & bigram, int frequency)
{
    if (!(findBigram(bigram, this->_validCharacters))) {
        string MSG_EXC = "In method: BigramCounter::increaseFrequency(const Bigram & bigram, int frequency = 0): \"Invalid Bigram\"";
        throw std::out_of_range(MSG_EXC);       
    } else {
        
        char first = bigram.at(0);
        char second = bigram.at(1); 
        
        int pos_1 = this->_validCharacters.find(first);
        int pos_2 = this->_validCharacters.find(second);
        
        if (frequency == 0)
            this->_frequency[pos_1][pos_2] += 1;
        else 
            this->_frequency[pos_1][pos_2] += frequency;

    }
}

BigramCounter& BigramCounter::operator=(const BigramCounter& orig)
{
    if (this->_frequency != orig._frequency)
    {
        deallocate();
        
        int newlen = orig.getSize();
        
        allocate(newlen);
        
        this->copy(orig);
    }

    return(*this);
}

BigramCounter& BigramCounter::operator+=(const BigramCounter& rhs)
{
    int len = this->getSize();
    
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            Bigram aux_bgr(rhs._validCharacters.at(i), rhs._validCharacters.at(j));
            
            this->increaseFrequency(aux_bgr); 
        }
    }
    
    return (*this);
}


void BigramCounter::calculateFrequencies(const char* filename)
{
    ifstream iStream;
    iStream.open(filename);
    
    if (!iStream) {
        string MSG_EXC = "In method \"void BigramCounter::calculateFrequencies(const char* filename)\": "
                "file cannot be opened or error ocurred while reading";
        throw std::ios_base::failure(MSG_EXC);
    }
    
    int len = this->getSize();

    deallocate();

    this->_validCharacters = DEFAULT_VALID_CHARACTERS;
    
    char actual;
    iStream.get(actual);
    
    char next;
    iStream.get(next);
    
    Bigram aux_bgr;
    while (iStream.good()) {
        
        bool actual_valid = isValidCharacter(actual,this->_validCharacters);
        bool next_valid = isValidCharacter(next,this->_validCharacters);
        bool both_valid = actual_valid && next_valid;
        
        if (both_valid) {
            aux_bgr.at(1) = actual;
            aux_bgr.at(2) = next;
            this->increaseFrequency(aux_bgr);
        } 
        
        actual = next;
        iStream.get(next);
    }
    
    iStream.close();
}

Language BigramCounter::toLanguage()
{
    Language ret_lan;
    
    int len = this->getSize();
    string val_chars = this->_validCharacters;
    
    for (int i = 0; i < len; i++) 
    {
        for (int j = 0; j < len; j++)
        {
            if (this->_frequency[i][j] > 0)
            {
                Bigram aux_bgr(val_chars.at(i),val_chars.at(j));
                BigramFreq aux_bf;
                
                aux_bf.setBigram(aux_bgr);
                aux_bf.setFrequency(this->_frequency[i][j]);
                
                ret_lan.append(aux_bf);
            }
        }
    }
    
    return(ret_lan);
}

const int& BigramCounter::operator()(int row, int column) const
{
    return (this->_frequency[row][column]);
}

int& BigramCounter::operator()(int row, int column) 
{
    return (this->_frequency[row][column]);
}

void BigramCounter::allocate(int size)
{
    this->_frequency = new int* [size];
    for (int i = 0; i < size; i++)
    {
        _frequency[i] = new int [size];
    }
}

void BigramCounter::deallocate()
{
    int len = this->_validCharacters.length();
    for (int i = 0; i < len; i++)
        delete [] this->_frequency[i];
    delete [] this->_frequency;
    _frequency = nullptr;
}

void BigramCounter::copy(const BigramCounter& orig)
{
    this->_validCharacters = orig._validCharacters;
    
    // Copiamos uno a uno
    
    int len = this->_validCharacters.length();
    
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            this->_frequency[i][j] = orig._frequency[i][j];
}