/*
 * Metodología de la Programación: Language3
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
#include "Language.h"
#include "BigramFreq.h"
#include <cstring>
using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "language4 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << endl;
}

/**
 * This program reads an undefined number of Language objects from the set of 
 * files passed as parameters to main(). All the Languages object, except the 
 * first one, must be stored in a dynamic array of Language objects. Then, 
 * for each Language in the dynamic array, this program prints to the 
 * standard output the name of the file of that Language and the distance from 
 * the first Language to the current Language. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Language with the minimum|maximum distance to the Language 
 * of the first file and its language identifier.
 * 
 * At least, two Language files are required to run this program.
 * Running example:
 * > language3 [-t min|max] <file1.bgr> <file2.bgr> [  ... <filen.bgr>] 
 */
int main(int argc, char* argv[]) {

    if (argc < 3) {
        showEnglishHelp(cerr);
        return (1);
    }

    int pos_first_language;
    int number_of_languages = 0;
    Language * language_ptr = nullptr;

    bool sin_opcion = true; // Nos indica si el programa se está ejecutando
                            // sin opciones

    if (argv[1][0] == '-') {
        if (argv[1][1] != 't') {
            showEnglishHelp(cerr);
            return(1);
        }    
        
        if (strcmp(argv[2],"min") && strcmp(argv[2],"max")) {
            showEnglishHelp(cerr);
            return(1);
        }
        
        
        sin_opcion = false;
        pos_first_language = 3;
                
        // We declare the dynamic array of Language objects with the Language
        // objects extracted from the files from argv[4] to argv[argc-1], because
        // argv[3] is the file we will use to compare distances
        
        number_of_languages = (argc-1) - 3;
        
    } else {
        pos_first_language = 1;
        number_of_languages = argc-2;
    }
    
    if(number_of_languages < 1){
        showEnglishHelp(cerr);
        return 1;
    }
    
    language_ptr = new Language[number_of_languages];
    
    for(int i = 0; i < number_of_languages; i++) {
        language_ptr[i].load(argv[i+pos_first_language+1]);
    }
    
    // Now we have already created our dynamic array of languages
    
    Language first_language;
    first_language.load(argv[pos_first_language]);
    
    // We look for the Language with min/max distance from our first language
    
    bool buscamos_min = sin_opcion || (!sin_opcion && (argv[2] == "min"));
    
    
    double dist = -1;
    double max_min_dist;
    
    if (buscamos_min) max_min_dist = 99999;
    else max_min_dist = -1;
    
    int pos_max_min_dist = -1; // Position in the dynamic array
                               // of the array with the max/min distance
    bool nuevo_min_max = true;
    
    for (int i = 0; i < number_of_languages; i++) {
        
        dist = first_language.getDistance(language_ptr[i]);
        
        nuevo_min_max = (buscamos_min && (dist < max_min_dist)) || 
                        (!buscamos_min && (dist > max_min_dist));
        
        if (nuevo_min_max) {
            pos_max_min_dist = i;
            max_min_dist = dist;
        }
    }

    for (int i = pos_first_language+1; i < argc; i++) {
        cout << "Distance to " << argv[i] << ": " << first_language.getDistance(language_ptr[i-pos_first_language-1]) << endl;
    }
    
    if (buscamos_min) {
        cout << "Nearest language file: " << argv[pos_max_min_dist+pos_first_language+1] << endl;
        cout << "Identifier of the nearest language: " << language_ptr[pos_max_min_dist].getLanguageId() << endl;
    } else {
        cout << "Farthest language file: " << argv[pos_max_min_dist+pos_first_language+1] << endl;
        cout << "Identifier of the farthest language: " << language_ptr[pos_max_min_dist].getLanguageId() << endl;
    }  
    
    delete [] language_ptr;
    return(0);
} 

