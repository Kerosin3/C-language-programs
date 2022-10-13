#include "db.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
sqlite3 *db;


#define MAX_TEXT_SIZE 256

int main(int argc, char *argv[])
{


    if ( (argc !=4)) 
    {
    	printf("Please enter name of database, table name, column name \n");
        exit(1);
    }
    if (strnlen(argv[1], MAX_TEXT_SIZE) > MAX_TEXT_SIZE)
    {
        printf("please enter text less that 1000 chars\n");
        exit(1);
    }
    if (strnlen(argv[2], MAX_TEXT_SIZE) > MAX_TEXT_SIZE)
    {
        printf("please enter font less that 100 chars\n");
        exit(1);
    }
    if (strnlen(argv[3], MAX_TEXT_SIZE) > MAX_TEXT_SIZE)
    {
        printf("please enter font less that 100 chars\n");
        exit(1);
    }
    int openOK = fill_db(db, argv[1]);
    if (openOK)
    {
        printf("Error while crating DB, aborting\n");
        return 1;
    }
    else
    {
        printf("DB created!\n");
    }
    //	get_rows(db);
    //	get_column(db);
    get_summ_scalar(db, 2);

    sqlite3_close(db);
    return 0;
}
