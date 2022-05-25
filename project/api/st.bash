rm -r ./build/*
cd build
cmake ..
make
mv libMusicial_API_LIB.a ../../builtLibs