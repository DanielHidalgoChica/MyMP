touch tests//.timeout
CMD="valgrind --leak-check=full /home/daniel/Desktop/University/MP/MyMP/MyLanguage1/dist/Debug/GNU-Linux/mylanguage1  < data/SimpleTextbigrams.txt 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
