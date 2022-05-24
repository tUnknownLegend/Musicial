rm -r ./build/*
cd build
cmake ..
make
cd ./project/server
mv libserverLib.a ../../../../builtLibs/