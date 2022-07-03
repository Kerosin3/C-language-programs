#include <stdio.h>

typedef struct {
	void* data;
	struct a_node* next_node;
} a_node;

int main(int argc, char *argv[])
{
	int a = 666;
	int b = 667;
	a_node test_node;
	a_node test_node_next;
	test_node.data = &a;
	test_node.next_node = &test_node_next;
	test_node_next.data = &b;
	printf("pointer is %p \n",&test_node_next);
	test_node_next.next_node = NULL;
	printf("value is %d \n",*(int*)test_node.data);
	a_node* nn = test_node.next_node;
	printf("point it to next node adress: %d \n",*(int*) nn->data);
//	printf("value is %d \n",*(int*)((test_node.next_node))->data);
	//printf("value is %p \n",*(int*)test_node.next_node->data);
	
	return 0;
}
