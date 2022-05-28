rm -r ./build/*
cd build
scan-build cmake ..
scan-build make
#cmake ..
#make
./Musicial_test