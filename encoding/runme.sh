#/bin/bash
echo "compiling C prj"
make clean
make 
echo "converting CP1251  to UTF8"
./out/app test_files/cp1251.txt out/cp1251_to_utf8.txt cp
echo "converting KOI8  to UTF8"
./out/app test_files/koi8.txt out/koi8_to_utf8.txt koi
echo "converting ISO8859-5 to UTF8"
./out/app test_files/iso-8859-5.txt out/iso8859_to_utf8.txt iso
