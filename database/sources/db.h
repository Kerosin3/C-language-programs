#ifndef _DB
#define _DB

#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>
#include "misc.h"

int fill_db();

int get_column(sqlite3* db);
#endif
