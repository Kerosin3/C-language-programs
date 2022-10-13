#ifndef _DB
#define _DB

#include "misc.h"
#include <limits.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>
#include <tgmath.h>

typedef enum
{
    id = 0,
    year,
    age,
    name,
    movie
} columnN;

long int get_summ_scalar(sqlite3 *db, columnN);
int get_rows(sqlite3 *db);
int fill_db(sqlite3 *db,char* dbname);

int get_column(sqlite3 *db);
#endif
