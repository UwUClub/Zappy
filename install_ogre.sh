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

git clone https://github.com/bulletphysics/bullet3.git
cd bullet3
if [ -e CMakeCache.txt ]; then
  rm CMakeCache.txt
fi
mkdir -p build_cmake
cd build_cmake
cmake -DBUILD_PYBULLET=ON -DBUILD_PYBULLET_NUMPY=ON -DUSE_DOUBLE_PRECISION=ON -DBT_USE_EGL=ON -DCMAKE_BUILD_TYPE=Release .. || exit 1
sudo make install -j $(command nproc 2>/dev/null || echo 12) || exit 1
cd examples
cd pybullet
if [ -e pybullet.dylib ]; then
  ln -f -s pybullet.dylib pybullet.so
fi
if [ -e pybullet_envs ]; then
  rm pybullet_envs
fi
if [ -e pybullet_data ]; then
  rm pybullet_data
fi
if [ -e pybullet_utils ]; then
  rm pybullet_utils
fi
ln -s ../../../examples/pybullet/gym/pybullet_envs .
ln -s ../../../examples/pybullet/gym/pybullet_data .
ln -s ../../../examples/pybullet/gym/pybullet_utils .
echo "Completed build of Bullet."
cd ..
rm -rf bullet3

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

