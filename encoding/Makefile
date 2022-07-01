build:
	mkdir -p out
	mkdir -p build
	clang -c -Wpedantic -std=c11 sources/main.c -o build/main.o
	clang -c -Wpedantic -std=c11 sources/chars_table.c -o build/chars_table.o
	clang -c -Wpedantic -std=c11 sources/multichar.c -o build/multichar.o
	clang build/main.o build/multichar.o build/chars_table.o -o out/app
clean:
	rm -rfv out
	rm -rfv build
	rm *.txt
