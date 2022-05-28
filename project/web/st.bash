mkdir build
cd build
scan-build cmake ..
scan-build make
mv libserverLib.a ../../builtLibs/
cd ../
rm -r ./build