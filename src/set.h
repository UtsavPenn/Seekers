#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXNODES 10

typedef struct node {
	int ID;
	struct node * next; // a pointer to the next node
} graph_node;

typedef struct SET{
	struct node * listHead; //points to the first element of the list
} set;

<<<<<<< HEAD
void addToSet(set **, int ID);
void listSet(set *);
int removeNodeFromSet(set **,int ID);
void addToLinkedList(set **, graph_node *,int ID);
void listLinkedList(graph_node *);
bool setContains(set *, int ID);
void clearSet(set **);

int removeNodeFromList(set **, graph_node *, int ID);
=======
// graph_node * createList();
// void initSet(set * head);
void addToSet(set *, int ID);
void addToLinkedList(set *, graph_node *,int ID);
void listLinkedList(graph_node *);
void listSet(set *);
int removeNodeFromList(set *, graph_node *, int ID);
int removeNodeFromSet(set *,int ID);
>>>>>>> a440a65589add3a059e8eff39d3c8c556b6bc90c
graph_node * searchNodeInLinkedList(graph_node *, int ID);
int sizeOfLinkedList(graph_node *);
int isLinkedListEmpty(graph_node *);
int isSetEmpty(set *);
bool listContains(graph_node *, int ID);
<<<<<<< HEAD
void clearLinkedList(set ** ,graph_node *);
=======
bool setContains(set *, int ID);
void clearLinkedList(set * ,graph_node *);
void clearSet(set *);
>>>>>>> a440a65589add3a059e8eff39d3c8c556b6bc90c
