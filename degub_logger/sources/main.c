#include <stdio.h>
#include <stdlib.h>
#include "debug_logger.h"

int main(int argc, char *argv[])
{

    init_recording("somelogfile.log");
    write_to_log(WARNING, "hohohoohoho");
    write_to_log(ERROR, "hohohodasdadasdaohoho");
    write_to_log(INFO, "hohohodas1111111111dadasdaohoho");
    stop_recording();
    return 0;
}
