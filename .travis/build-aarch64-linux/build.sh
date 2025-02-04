#!/bin/sh

set -e
set -x

export PKG_CONFIG_PATH=$HOME/.local/lib/pkgconfig:$PKG_CONFIG_PATH

cd dynarmic
mkdir build && cd build
cmake .. -DBoost_INCLUDE_DIRS=${PWD}/../externals/ext-boost -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc-8 -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++-8 -G Ninja
ninja

qemu-aarch64 -L /usr/aarch64-linux-gnu ./tests/dynarmic_tests [JitA64] -d yes
