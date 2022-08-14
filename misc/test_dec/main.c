#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>
#include <limits.h>

typedef struct s {int field0; unsigned field1; } t;

typedef struct tnode {
	int count;
	struct tnode *left;
	int total;
} tnode;

void test_me(const char[]);
void test_you(size_t, const char[]);

int main(int argc, char *argv[])
{
	tnode s_node;
	s_node.count = 0;
	tnode tt_node;
	s_node.left = &tt_node;


	int x = 666;
	int const * p_int = &x;
	if (p_int){
		printf("not null \n");
		printf("value is %d\n",*p_int);
		p_int = (void*)0;
	} else {
		printf("null!!\n");
	}
	char* some_str = "hahahah";
	char str[1];
	str[0] = '\0';


	test_me(some_str);
	test_me(str);
	return 0;
}

void
test_me(const char s1[static 1]){
	printf("the string is %s \n",s1);
}
void 
test_you(size_t len,
	const char char_arr[len]){
	printf("test you %s \n",char_arr);
}
