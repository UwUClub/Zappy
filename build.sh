#! /bin/bash

#check if there is a build directory, if not create one
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake ..
make -j16
cp zappy_gui ../
cp zappy_server ../
cp zappy_ia ../
cd ..