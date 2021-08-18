#!/bin/bash

# Echo each command
set -x

# Build Charm++
cd charm
./build charm++ multicore-linux64 clang -j --with-production

# Build NAMD
cd ../namd
./config Linux-x86_64-dpcpp --charm-base $PWD/../charm --tcl-prefix $PWD/../tcl8.5.9-linux-x86_64-threaded --fftw-prefix $PWD/../fftw-linux-x86_64
cd Linux-x86_64-dpcpp
make -j
