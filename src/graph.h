/*
    author @ Utsav Mehta and Shallav Varma
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "setGraph.h"

/*
    Initializes a graph object.
*/
void graphInit(graph *);

/*
    Allocates a new node  in the graph.
*/
void addNode(graph *);

/*
    Adds an edge between two nodes.
    @param: 
    IDs of the node between which edge is to be added, 
    timer value and direction of going from argument 2 node to argument 3 node.
*/
void addEdge(graph * area, int nodeId1, int nodeId2, int timer,orientation direction );

/*
    Malloc an edge and return pointer to it.
*/
edge * createEdge ();

/* 
    Deletes an edge from node A to B.
    Note: it only deletes the edge from A to B not from B to A
*/ 
void deleteEdgeAtoB(node *, edge *);

/*
Completely deletes the edge from node A to node B i.e both from A to B and B to A.
*/
void deleteEdge(graph *, node *, node *);

/*
    Deletes the node and all its edges from the graph.
    @param
    Pointer to node which is to be deleted
*/
void deleteNode(graph *, node *);


/*
    Look for a node with given ID and return pointer to it.
    @param
    ID of the node to be searched.
    @return
    Pointer to the vertex node if found, else NULL.
*/
node* findNode(graph *, int );

/*
  Prints out the entire graph with all the nodes
  along side the nodes that are directly connected to it.
*/
void print(graph*);

/*
    Print the list of nodes int the graph.
*/
void printlist(graph*);


