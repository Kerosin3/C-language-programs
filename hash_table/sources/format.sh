#/bin/sh
find . -regex '.*\.\(c\|h\|cc\|cxx\)' -exec clang-format -style=file -i {} \;

