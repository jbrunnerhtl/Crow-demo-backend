#!/bin/sh
# Build file

rm -rf build
mkdir -p build 
cd build

cmake ..
cmake --build .
if test $? -eq 0; then
    echo "build successfull"
    ./crow-backend
else
    echo "build failed"
fi
