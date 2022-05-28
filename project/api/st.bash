mkdir build
cd build
scan-build cmake ..
scan-build make
mv libMusicial_API_LIB.a ../../builtLibs
cd ../
rm -r ./build