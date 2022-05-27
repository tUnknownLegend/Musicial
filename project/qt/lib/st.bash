rm -r ./build/*
cd build
cmake ..
make
mv libQT_LIB.a ./../../../builtLibs