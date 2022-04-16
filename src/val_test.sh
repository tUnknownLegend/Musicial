cd /${{ github.workspace }}
cd ./build/tests
valgrind --tool=memcheck --leak-check=yes ./Musicial_test
