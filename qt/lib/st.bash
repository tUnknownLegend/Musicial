rm -r ./build/*
cd build
scan-build cmake ..
scan-build make
./Musicial_test