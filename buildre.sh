#! /bin/bash

bash clean.sh
mkdir build
cd build
cmake ..
make -j16
cp zappy_gui ../
cp zappy_server ../
cd ..