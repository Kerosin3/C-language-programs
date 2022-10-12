#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "db.h"

sqlite3 *db;

int main(int argc, char *argv[]){
	int openOK = fill_db(db);
	if (openOK) {
		printf("Error while crating DB, aborting\n");
		return 1;
	} else {
		printf("DB created!\n");
	}
//	get_column(db);


	sqlite3_close(db);
	return 0;
}
