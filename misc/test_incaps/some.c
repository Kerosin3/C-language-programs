#include "some.h"

typedef struct node {
	unsigned count;
	struct node *prev;
	struct node *next;
} node;

node* init(){
	return (node*) malloc(sizeof(node));
}
void destroy_node(node* some_node){
	free(some_node->next);
	free(some_node->prev);
}
