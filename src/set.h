#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXNODES 10

// if nodes are used only in the representation of sets but not exposed to clients,
// this type should be in set.c
typedef struct node {
	int ID;
	struct node * next; // a pointer to the next node
} graph_node;

typedef struct SET{
	struct node * listHead; //points to the first element of the list
} set;

// why is this not just a pointer to a set? (similar questions for ** below).
void addToSet(set **, int ID);
void listSet(set *);
int removeNodeFromSet(set **,int ID);
// sets shouldn't know about graphs; move graph functions to the graph type
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
