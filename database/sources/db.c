#include "db.h"

int callback(void *some, int argc, char **argv, char **ColName);
char const *const execute_commands[99];

int fill_db(sqlite3* db){
	//sqlite3 *db;
	char *err_msg = 0 ;

	int handle_sq = sqlite3_open("testdb.db",&db);
	
	if (handle_sq != SQLITE_OK){
		fprintf(stdout,"cannot open database! \n");
		sqlite3_close(db);
		return 1;
	}
	
	for (size_t i = 0;i<99; i++) {
		handle_sq = sqlite3_exec(db,execute_commands[i],0,0,&err_msg);
		if (handle_sq != SQLITE_OK){
			printf("error while preforming command to DB\n");
			sqlite3_free(err_msg);
			sqlite3_close(db);
			return 1;
		}
	}
	
//	int last_id = sqlite3_last_insert_rowid(db);
	//printf("last id %d\n",last_id);

//	char *sql = "SELECT Id, age FROM oscar WHERE id = ?";
	char *sql = "SELECT COUNT(*) FROM oscar";
	sqlite3_stmt *res;
	handle_sq = sqlite3_prepare_v2(db,sql,-1,&res,0);
	
//	sqlite3_step(res);
/*
	if (handle_sq == SQLITE_OK){
		sqlite3_bind(res);
	} else {
		printf("error\n");
	}
*/	
	size_t count = 0;
	/*while((handle_sq = sqlite3_step(res) == SQLITE_ROW)){
		count++;
		printf("-->%d\n",sqlite3_column_int(res,0));
	}
		printf("count is %lu \n",count);
	if (handle_sq == SQLITE_DONE){
		printf("count is %lu \n",count);
	}
*/


	int step = sqlite3_step(res);
	if (step == SQLITE_ROW){
		printf("%d: \n",sqlite3_column_int(res,0));
//		printf("%s: \n",sqlite3_column_text(res,1));
	}
	
	sqlite3_finalize(res);


	return 0;
}

int get_column(sqlite3* db){

	//char *sql = "SELECT * FROM oscar";
//	char *sql = "PRAGMA table_info(oscar)";
	//char *sql = "PRAGMA table_info(oscar)";
	char *sql = "SELECT length(oscar))";
	
	char *err_msg = 0 ;
	int handle_sq ;

	sqlite3_open("testdb.db",&db);

	handle_sq = sqlite3_exec(db,sql,callback,0,&err_msg);
	if (handle_sq != SQLITE_OK){
		printf("-error while preforming command to DB\n");
		sqlite3_free(err_msg);
		sqlite3_close(db);
		return 1;
	} else { printf("OK\n"); }
	return 0;

}

int callback(void *some, int argc, char **argv, char **ColName){
	some = 0;
	size_t id = 0;
	size_t year = 0;
	size_t age = 0;

	for (size_t i = 0; i < argc ; i++ ) {
		printf("%s = %s \n", ColName[i],argv[i] ? argv[i] : "Null" );	
		//printf("-\n");
    		//sscanf(part_beg, "%ld %ld", &x, &y);
	}
	printf("\n");
	return 0;
}

char const *const execute_commands[99] = {

"CREATE TABLE IF NOT EXISTS oscar (   id INTEGER,  year INTEGER,  age INTEGER,  name TEXT,  movie TEXT);",
"INSERT INTO oscar VALUES(1,1928,22,'Janet Gaynor','Seventh Heaven Street Angel and Sunrise: A Song of Two Humans');",
"INSERT INTO oscar VALUES(2,1929,37,'Mary Pickford','Coquette');",
"INSERT INTO oscar VALUES(3,1930,28,'Norma Shearer','The Divorcee');",
"INSERT INTO oscar VALUES(4,1931,63,'Marie Dressler','Min and Bill');",
"INSERT INTO oscar VALUES(5,1932,32,'Helen Hayes','The Sin of Madelon Claudet');",
"INSERT INTO oscar VALUES(6,1933,26,'Katharine Hepburn','Morning Glory'); ",
"INSERT INTO oscar VALUES(7,1934,31,'Claudette Colbert','It Happened One Night');",
"INSERT INTO oscar VALUES(8,1935,27,'Bette Davis','Dangerous');",
"INSERT INTO oscar VALUES(9,1936,27,'Luise Rainer','The Great Ziegfeld');",
"INSERT INTO oscar VALUES(10,1937,28,'Luise Rainer','The Good Earth');",
"INSERT INTO oscar VALUES(11,1938,30,'Bette Davis','Jezebel');",
"INSERT INTO oscar VALUES(12,1939,26,'Vivien Leigh','Gone with the Wind');",
"INSERT INTO oscar VALUES(13,1940,29,'Ginger Rogers','Kitty Foyle');",
"INSERT INTO oscar VALUES(14,1941,24,'Joan Fontaine','Suspicion');",
"INSERT INTO oscar VALUES(15,1942,38,'Greer Garson','Mrs. Miniver');",
"INSERT INTO oscar VALUES(16,1943,25,'Jennifer Jones','The Song of Bernadette');",
"INSERT INTO oscar VALUES(17,1944,29,'Ingrid Bergman','Gaslight');",
"INSERT INTO oscar VALUES(18,1945,40,'Joan Crawford','Mildred Pierce');",
"INSERT INTO oscar VALUES(19,1946,30,'Olivia de Havilland','To Each His Own');",
"INSERT INTO oscar VALUES(20,1947,35,'Loretta Young','The Farmer''s Daughter');",
"INSERT INTO oscar VALUES(21,1948,32,'Jane Wyman','Johnny Belinda');",
"INSERT INTO oscar VALUES(22,1949,33,'Olivia de Havilland','The Heiress');",
"INSERT INTO oscar VALUES(23,1950,29,'Judy Holliday','Born Yesterday');",
"INSERT INTO oscar VALUES(24,1951,38,'Vivien Leigh','A Streetcar Named Desire');",
"INSERT INTO oscar VALUES(25,1952,54,'Shirley Booth','Come Back Little Sheba');",
"INSERT INTO oscar VALUES(26,1953,24,'Audrey Hepburn','Roman Holiday');",
"INSERT INTO oscar VALUES(27,1954,25,'Grace Kelly','The Country Girl');",
"INSERT INTO oscar VALUES(28,1955,48,'Anna Magnani','The Rose Tattoo');",
"INSERT INTO oscar VALUES(29,1956,41,'Ingrid Bergman','Anastasia');",
"INSERT INTO oscar VALUES(30,1957,28,'Joanne Woodward','The Three Faces of Eve');",
"INSERT INTO oscar VALUES(31,1958,41,'Susan Hayward','I Want to Live!');",
"INSERT INTO oscar VALUES(32,1959,39,'Simone Signoret','Room at the Top');",
"INSERT INTO oscar VALUES(33,1960,29,'Elizabeth Taylor','BUtterfield 8');",
"INSERT INTO oscar VALUES(34,1961,27,'Sophia Loren','Two Women');",
"INSERT INTO oscar VALUES(35,1962,31,'Anne Bancroft','The Miracle Worker');",
"INSERT INTO oscar VALUES(36,1963,31,'Patricia Neal','Hud');",
"INSERT INTO oscar VALUES(37,1964,29,'Julie Andrews','Mary Poppins');",
"INSERT INTO oscar VALUES(38,1965,25,'Julie Christie','Darling');",
"INSERT INTO oscar VALUES(39,1966,35,'Elizabeth Taylor','Who''s Afraid of Virginia Woolf?');",
"INSERT INTO oscar VALUES(40,1967,60,'Katharine Hepburn','Guess Who''s Coming to Dinner');",
"INSERT INTO oscar VALUES(41,1968,61,'Katharine Hepburn','The Lion in Winter');",
"INSERT INTO oscar VALUES(42,1969,26,'Barbra Streisand','Funny Girl');",
"INSERT INTO oscar VALUES(43,1970,35,'Maggie Smith','The Prime of Miss Jean Brodie');",
"INSERT INTO oscar VALUES(44,1971,34,'Glenda Jackson','Women in Love');",
"INSERT INTO oscar VALUES(45,1972,34,'Jane Fonda','Klute');",
"INSERT INTO oscar VALUES(46,1973,27,'Liza Minnelli','Cabaret');",
"INSERT INTO oscar VALUES(47,1974,37,'Glenda Jackson','A Touch of Class');",
"INSERT INTO oscar VALUES(48,1975,42,'Ellen Burstyn','Alice Doesn''t Live Here Anymore');",
"INSERT INTO oscar VALUES(49,1976,41,'Louise Fletcher','One Flew Over the Cuckoo''s Nest');",
"INSERT INTO oscar VALUES(50,1977,36,'Faye Dunaway','Network');",
"INSERT INTO oscar VALUES(51,1978,32,'Diane Keaton','Annie Hall');",
"INSERT INTO oscar VALUES(52,1979,41,'Jane Fonda','Coming Home');",
"INSERT INTO oscar VALUES(53,1980,33,'Sally Field','Norma Rae');",
"INSERT INTO oscar VALUES(54,1981,31,'Sissy Spacek','Coal Miner''s Daughter');",
"INSERT INTO oscar VALUES(55,1982,74,'Katharine Hepburn','On Golden Pond');",
"INSERT INTO oscar VALUES(56,1983,33,'Meryl Streep','Sophie''s Choice');",
"INSERT INTO oscar VALUES(57,1984,49,'Shirley MacLaine','Terms of Endearment');",
"INSERT INTO oscar VALUES(58,1985,38,'Sally Field','Places in the Heart');",
"INSERT INTO oscar VALUES(59,1986,61,'Geraldine Page','The Trip to Bountiful');",
"INSERT INTO oscar VALUES(60,1987,21,'Marlee Matlin','Children of a Lesser God');",
"INSERT INTO oscar VALUES(61,1988,41,'Cher','Moonstruck');",
"INSERT INTO oscar VALUES(62,1989,26,'Jodie Foster','The Accused');",
"INSERT INTO oscar VALUES(63,1990,80,'Jessica Tandy','Driving Miss Daisy');",
"INSERT INTO oscar VALUES(64,1991,42,'Kathy Bates','Misery');",
"INSERT INTO oscar VALUES(65,1992,29,'Jodie Foster','The Silence of the Lambs');",
"INSERT INTO oscar VALUES(66,1993,33,'Emma Thompson','Howards End');",
"INSERT INTO oscar VALUES(67,1994,36,'Holly Hunter','The Piano');",
"INSERT INTO oscar VALUES(68,1995,45,'Jessica Lange','Blue Sky');",
"INSERT INTO oscar VALUES(69,1996,49,'Susan Sarandon','Dead Man Walking');",
"INSERT INTO oscar VALUES(70,1997,39,'Frances McDormand','Fargo');",
"INSERT INTO oscar VALUES(71,1998,34,'Helen Hunt','As Good as It Gets');",
"INSERT INTO oscar VALUES(72,1999,26,'Gwyneth Paltrow','Shakespeare in Love');",
"INSERT INTO oscar VALUES(73,2000,25,'Hilary Swank','Boys Don''t Cry');",
"INSERT INTO oscar VALUES(74,2001,33,'Julia Roberts','Erin Brockovich');",
"INSERT INTO oscar VALUES(75,2002,35,'Halle Berry','Monster''s Ball');",
"INSERT INTO oscar VALUES(76,2003,35,'Nicole Kidman','The Hours');",
"INSERT INTO oscar VALUES(77,2004,28,'Charlize Theron','Monster');",
"INSERT INTO oscar VALUES(78,2005,30,'Hilary Swank','Million Dollar Baby');",
"INSERT INTO oscar VALUES(79,2006,29,'Reese Witherspoon','Walk the Line');",
"INSERT INTO oscar VALUES(80,2007,61,'Helen Mirren','The Queen');",
"INSERT INTO oscar VALUES(81,2008,32,'Marion Cotillard','La Vie en rose');",
"INSERT INTO oscar VALUES(82,2009,33,'Kate Winslet','The Reader');",
"INSERT INTO oscar VALUES(83,2010,45,'Sandra Bullock','The Blind Side');",
"INSERT INTO oscar VALUES(84,2011,29,'Natalie Portman','Black Swan');",
"INSERT INTO oscar VALUES(85,2012,62,'Meryl Streep','The Iron Lady');",
"INSERT INTO oscar VALUES(86,2013,22,'Jennifer Lawrence','Silver Linings Playbook');",
"INSERT INTO oscar VALUES(87,2014,44,'Cate Blanchett','Blue Jasmine');",
"INSERT INTO oscar VALUES(88,2015,54,'Julianne Moore','Still Alice');",
"INSERT INTO oscar VALUES(89,2016,26,'Brie Larson','Room');",
    };

