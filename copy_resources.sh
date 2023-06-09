#! /bin/bash

echo "Copying resources to build directory..."

# if cannot find ../assets
if [ ! -d "../assets" ]; then
    mkdir tmp
    cd tmp
fi

cp -r ../assets ./

echo "Done"

# if in tmp
if [ -d "../assets" ]; then
    cd ..
    rm -rf tmp
fi

