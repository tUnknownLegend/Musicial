mkdir build
cd build
scan-build cmake ..
scan-build make
mv libQT_LIB.a ./../../../builtLibs
cd ../
rm -r ./build