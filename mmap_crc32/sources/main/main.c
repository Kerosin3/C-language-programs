#include "mapping.h"

int main(int argc, char *argv[])
{
    if ((argc > 2 || (argc == 1)))
    {
        printf("please specify just a filename, exiting..\n");
        exit(1);
    }
    size_t len_path = (strnlen(argv[1], 257));
    if ((!len_path) || (len_path == 257))
    {
        printf("please enter a valid path to a file\n");
        return 1;
    }

    if (!calc_hashcrc32(argv[1]))
        printf("there were errors during crc32 computation\n");
    return 0;
}
