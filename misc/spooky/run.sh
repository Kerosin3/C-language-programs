#!/bin/sh
gcc --std=c11 main.c -L . -lspookyhash
cur_dir=$(pwd)
LD_LIBRARY_PATH=$cur_dir
export LD_LIBRARY_PATH
exec ./a.out
