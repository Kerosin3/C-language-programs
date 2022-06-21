#/bin/bash
echo "compiling via gcc c11 std"
gcc -std=c11 -Wall -Wpedantic main.c -o app
echo "============================================="
echo "============================================="
echo "=========starting file analysis=============="
echo "passing not valid zip-jpg file"
./app non-zipjpeg.jpg
echo "============================================="
echo "============================================="
echo "============================================="
echo "passing valid zip-jpg file"
./app zipjpeg.jpg
echo "================done========================="
