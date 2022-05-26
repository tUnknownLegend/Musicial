rm -r ./build/*
cd build
cmake ..
make
mv libserverLib.a ../../builtLibs/