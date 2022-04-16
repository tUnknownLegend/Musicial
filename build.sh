cd /${{ github.workspace }}
rm -r ./build
mkdir ./build
cd ./build
cmake ..
cmake --build .