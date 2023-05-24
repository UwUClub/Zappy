#! /bin/bash

#check if there is a build directory, if not create one
if [ ! -d "build" ]; then
    mkdir build
fi
if [ ! -f "./git/hooks/pre-commit" ]; then
    touch ./git/hooks/pre-commit
    echo "#! /bin/bash" >> ./git/hooks/pre-commit
    echo "sh clean.sh" >> ./git/hooks/pre-commit
    chmod +x ./git/hooks/pre-commit
fi
cd build
cmake ..
make -j16
cp zappy_gui ../
cp zappy_server ../
cp zappy_ia ../
cd ..