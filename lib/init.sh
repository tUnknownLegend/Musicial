#sudo apt update
#sudo apt-get install install -y valgrind
sudo apt-get update
sudo apt-get install libgtest-dev
sudo apt-get install cmake # install cmake
sudo cmake /usr/src/gtest/CMakeLists.txt
sudo make /usr/src/gtest
sudo cp /usr/src/gtest*.a /usr/lib
sudo ln -s /usr/lib/libgtest.a /usr/local/lib/gtest/libgtest.a
sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/gtest/libgtest_main.a
sudo apt-get install lcov
sudo apt-get install genhtml
sudo apt-get install valgrind
sudo apt-get install -y cppcheck
#sudo apt-get install python-pip  
#sudo pip install cpplint
#python -m cpplint --recursive --exclude=source/catch.hpp --filter=-legal/copyright,-build/include_subdir source/* 
#sudo cpplint --recursive

#cpplint --extensions=c project/include/* project/src/*  

#cd ${{ github.workspace }}