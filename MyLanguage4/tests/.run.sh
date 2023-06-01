touch tests//.timeout
CMD="valgrind --leak-check=full /home/daniel/Desktop/University/MP/MyMP/MyLanguage4/dist/Debug/GNU-Linux/mylanguage4  ../Books/fortunata.bgr ../Books/quijote.bgr ../Books/fortunata.bgr 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
