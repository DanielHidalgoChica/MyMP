/*
 * Metodología de la Programación: Language2
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

#include <iostream>
#include <fstream>

#include "Language.h"

using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "language2 <file1.bgr> [<file2.bgr> ... <filen.bgr>] <outputFile.bgr> " << endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally the resulting Language is saved in an output file. The 
 * program must have at least an input file and an output file. 
 * The output Language will have as language identifier, the one of the first
 * file (<file1.bgr>). If an input file <file*.bgr> has a language identifier
 * different from the one of the first file (<file1.bgr>), then it will not
 * be included in the union.
 * Running example:
 * > language2 <file1.bgr> [<file2.bgr> ... <filen.bgr>] <outputFile.bgr> 
 */
int main(int argc, char* argv[]) {
    
//    Language language;
    ifstream inputStream;
    string cadena_magica;
    string language_id;
    string bigram_str;
    int frequency;
    
    int bigram_c;
    
    if(argc < 3) {
        showEnglishHelp(cerr);
        return (1);
    }
    
    // To esto paece que va pal método open (o load, idk)
    
    for (int i = 1; i < argc-1; i++) {
        
        cout << " Fichero de entrada: "<< argv[i] << endl;
        
        inputStream.open(argv[i]);
        
        if(inputStream) {
            inputStream >> cadena_magica;
            cout << '\n' << cadena_magica;
            inputStream >> language_id;
            cout << '\n' << language_id;
            inputStream >> bigram_c;
            cout << '\n' << bigram_c;
        } else {
            // throw... creo
        }
        
        for (int j = 0; j < bigram_c; j++) {
            inputStream >> bigram_str;
            inputStream >> frequency;
            
            cout << bigram_str << ' ' << to_string(frequency) << '\n';
        }
        
        inputStream.close();

        
    }
    
//    language.load(argv[1]);
    
    return (0);
}

