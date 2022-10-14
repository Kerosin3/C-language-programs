#ifndef _DB
#define _DB

#include "misc.h"
#include <limits.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

#define tablesize 90 // for table creating from supplied file

extern char *tablename;
extern char *columnname;
extern char *dbname;
extern char **tablenames_p;
extern int t_glob_size;

int get_know_whether_columnmane_exists(sqlite3 *db);
int get_table_names(sqlite3 *db);
long int get_summ_scalar(sqlite3 *db);
int get_rowsN(sqlite3 *db);
int fill_db(sqlite3 *db);

#endif
