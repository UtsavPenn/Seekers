#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXNODES 20

typedef struct node_s{
	int ID;
	struct node_s * next; // a pointer to the next node
} graph_node;

typedef struct SET{
	struct node_s * listHead; //points to the first element of the list
} set;



void addToSet(set **, int ID);
void listSet(set *);
int removeNodeFromSet(set **,int ID);
void addToLinkedList(set **, graph_node *,int ID);
void listLinkedList(graph_node *);
bool setContains(set *, int ID);
void clearSet(set **);

int removeNodeFromList(set **, graph_node *, int ID);
graph_node * searchNodeInLinkedList(graph_node *, int ID);
int sizeOfLinkedList(graph_node *);
int isLinkedListEmpty(graph_node *);
int isSetEmpty(set *);
bool listContains(graph_node *, int ID);
void clearLinkedList(set ** ,graph_node *);
