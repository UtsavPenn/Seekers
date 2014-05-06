#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXNODES 20

#include "data.h"

void addToSet_graph(edgeSet **, edge*);
void listSet_graph(edgeSet *);
int removeNodeFromSet_graph(edgeSet **, node*);
void addToLinkedList_graph(edgeSet **, edge *,node*);
void listLinkedList_graph(edge *);
bool setContains_graph(edgeSet *, edge*);
void clearSet_graph(edgeSet **);

int removeNodeFromList_graph(edgeSet **, edge *, node *);
edge * searchNodeInLinkedList_graph(edge *, node*);
edge * findEdge_graph(edgeSet *, node*);
int sizeOfLinkedList_graph(edge *);
int isLinkedListEmpty_graph(edge *);
int isSetEmpty_graph(edgeSet *);
bool listContains_graph(edge *, node*);
void clearLinkedList_graph(edgeSet ** ,edge *);
