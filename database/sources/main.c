#include "db.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
sqlite3 *db;

#define MAX_TEXT_SIZE 256

char *tablename;
char *columnname;
char **tablenames_p;
char *dbname;

int main(int argc, char *argv[])
{

    if ((argc != 4))
    {
        printf("Please enter name of database, table name, column name \n");
        exit(1);
    }
    if (strnlen(argv[1], MAX_TEXT_SIZE) >= MAX_TEXT_SIZE)
    {
        printf("please enter text less that 1000 chars\n");
        exit(1);
    }
    if (strnlen(argv[2], MAX_TEXT_SIZE) >= MAX_TEXT_SIZE)
    {
        printf("please enter font less that 100 chars\n");
        exit(1);
    }
    if (strnlen(argv[3], MAX_TEXT_SIZE) >= MAX_TEXT_SIZE)
    {
        printf("please enter font less that 100 chars\n");
        exit(1);
    }
    dbname = argv[1];
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
    }
*/
    int handle_sq = sqlite3_open(dbname, &db);

    if (handle_sq != SQLITE_OK)
    {
        fprintf(stdout, "cannot open specified database! \n");
        sqlite3_close(db);
        exit(1);
    }
    
    sqlite3_close(db);

    tablename = argv[2];
    tablenames_p = 0;

    tablenames_p = calloc(100, sizeof(char*));
    for (size_t i = 0; i<100; i++) {
	    tablenames_p[i] = calloc(MAX_TEXT_SIZE, sizeof(char));
    }


    get_table_names(db); 
    size_t ii = 0; 
    int found = 0;
    while( tablenames_p[ii] ){
	    if (ii >= 99) {
        	fprintf(stdout, "no such table!\n");
		exit(1);
	    }
	    if (!(strncmp(tablename, tablenames_p[ii], strnlen(tablename, MAX_TEXT_SIZE)))) {
		found = 1;
		break;
	    }
	ii++;
    }
    if (found!=1){
	fprintf(stdout, "no such table!\n");
		goto cleanup;

    } 
    columnname = argv[3];
   get_know_whether_tablename(db);
/*
    char colname[MAX_TEXT_SIZE] = {0};
    int col_n = 0;
    sscanf(argv[3], "%s", colname, &col_n);
    columnN col = 0;
    if (!strncmp(colname, "year", 5))
    {
        col = year;
    }
    else if (!strncmp(colname, "age", 4))
    {
        col = age;
    }
    else
    {
        fprintf(stdout, "no such column\n");
        exit(1);
    }*/
//    get_rows(db);
    //get_summ_scalar(db );
    get_column(db); 
        sqlite3_close(db);
cleanup:
    for (size_t i = 0; i<100; i++) {
	    free(tablenames_p[i]);
    }
    free(tablenames_p);
    return 0;
}
