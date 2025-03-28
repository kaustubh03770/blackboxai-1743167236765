#!/bin/bash

# Create build directory
mkdir -p build
cd build

# Run CMake and make
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Copy the executable to project root
cp KsHealthcare ..