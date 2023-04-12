touch tests//.timeout
CMD="valgrind --leak-check=full /home/daniel/Desktop/University/MP/MyMP/MyLanguage2/dist/Debug/GNU-Linux/mylanguage2  ../Books/BodasdeSangre_FedericoGarciaLorca.bgr ../Books/quijote.bgr tests/output/spanish.bgr 1> tests//.out13 2>&1"
eval $CMD
rm tests//.timeout
