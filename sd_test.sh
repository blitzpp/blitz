#!/bin/bash

mkdir install
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install/ ../
make install
cd ../testsuite/
g++ -I../install/include/ -L../install/lib/ strided-domain.cpp
./a.out
