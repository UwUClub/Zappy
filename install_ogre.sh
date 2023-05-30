#!/bin/bash

# Step 1: Check if cmake is installed
if ! command -v cmake &> /dev/null
then
    echo "CMake could not be found. Please install it first."
    exit
fi

# Step 2: Check if git is installed
if ! command -v git &> /dev/null
then
    echo "git could not be found. Please install it first."
    exit
fi

# Step 3: Download Ogre3D source code
git clone https://github.com/OGRECave/ogre.git
cd ogre

# Step 4: Create build directory and navigate into it
mkdir build
cd build

# Step 5: Run CMake to generate build files
cmake ..

# Step 6: Build and install Ogre3D
make
sudo make install
rm -rf ogre