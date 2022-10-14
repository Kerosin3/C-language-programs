#include "db.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
sqlite3 *db;

#define MAX_TEXT_SIZE 256
#define MAX_N_TABLE 100
char *tablename;
char *columnname;
char **tablenames_p;
char *dbname;
int t_glob_size;

int main(int argc, char *argv[])
{

    if ((argc != 4))
    {
        printf("Please enter name of database, table name, column name \n");
        exit(1);
    }
    if (strnlen(argv[1], MAX_TEXT_SIZE) >= MAX_TEXT_SIZE)
    {
        printf("please use less than 256 chars for specifying params\n");
        exit(1);
    }
    if (strnlen(argv[2], MAX_TEXT_SIZE) >= MAX_TEXT_SIZE)
    {
        printf("please use less than 256 chars for specifying params\n");
        exit(1);
    }
    if (strnlen(argv[3], MAX_TEXT_SIZE) >= MAX_TEXT_SIZE)
    {
        printf("please use less than 256 chars for specifying params\n");
        exit(1);
    }
    dbname = argv[1];
    //-------create and fill DB-----------
    /*
     int openOK = fill_db(db);
     if (openOK)
     {
         printf("Error while crating DB, aborting\n");
         return 1;
     }
     else
     {
         printf("DB created!\n");
     return 0;
     }
 */
    if (access(dbname, F_OK) != 0)
    {
        fprintf(stdout, "no such db file exists!\n");
        exit(1);
    }
    //-- check DB is sqlite3 and OK
    int handle_sq = sqlite3_open(dbname, &db); // test db

    if (handle_sq != SQLITE_OK)
    {
        fprintf(stdout, "cannot open specified database! \n");
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);

    tablename = argv[2];
    tablenames_p = 0;
    // check tablenames---------------------------------------
    tablenames_p = calloc(MAX_N_TABLE, sizeof(char *));
    for (size_t i = 0; i < MAX_N_TABLE; i++)
    {
        tablenames_p[i] = calloc(MAX_TEXT_SIZE, sizeof(char));
    }
    get_table_names(db);
    size_t ii = 0;
    int found = 0;
    while (tablenames_p[ii])
    {
        if (ii >= MAX_N_TABLE - 1)
        {
            fprintf(stdout, "no such table!\n");
            exit(1);
        }
        if (!(strncmp(tablename, tablenames_p[ii], strnlen(tablename, MAX_TEXT_SIZE))))
        {
            found = 1;
            break;
        }
        ii++;
    }
    if (found != 1)
    {
        fprintf(stdout, "no such table!\n");
        goto cleanup;
    }
    //-------------------------------------------------
    // check table
    columnname = argv[3];
    if (get_know_whether_columnmane_exists(db))
    {
        fprintf(stdout, "no such column exists!\n");
        goto cleanup;
    }
    //---------------------------------------------------
    // get n rows

    if ((t_glob_size = get_rowsN(db)) < 0)
    {
        fprintf(stdout, "error while getting number of rows!\n");
        goto cleanup;
    }

    //  calculate staticstics
    if (get_summ_scalar(db) < 0)
        printf("there were errors while processing\n");
    sqlite3_close(db);
cleanup:
    for (size_t i = 0; i < MAX_N_TABLE; i++)
    {
        free(tablenames_p[i]);
    }
    free(tablenames_p);
    return 0;
}
