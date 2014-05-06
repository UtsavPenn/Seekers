
/*    
    Orientation gives the direction of motion of the bot
    with respect to reference. 
*/
typedef enum{
  Straight,
  Right,
  Back,
  Left
} orientation;

struct edgeSet;
/*
        It  represents all the nodes in graph structure.
*/ 
typedef struct node{
int id;    //  used for identification of the node.
struct edgeSet* edges; // Set of edges from a node.
struct node *next; // Pointer to the next node
}node;

/*
    Represents an edge between two nodes in the graph. For each node
    in the graph there is a set of edges that connect the node with different nodes.
*/
typedef struct edge{
  node * dest;  // other end of the edge. One end is the node in which set a particular object is contained
  int timer;                 //time taken to traverse the edge
  orientation turn;          //direction of motion from node containing the edge object to the destination node
  //Set implementation using linked list.
  struct edge *next;
}edge;


typedef struct graph{
    // Function pointers that define methods that can be aplied to the graph object.
    void (*addNode)(void *self);
    void (*addEdge)(void *self, int, int, int, orientation);
    void (*deleteEdge)(void *self, node*, node*);
    void (*deleteNode)(void *self, node*);
    node* (*findNode)(void *self, int);
    
    // And data goes here.
    node * head;
    node * tail;
} graph;

// Represent the set of edges.
typedef struct edgeSet{
	edge * listHead; //points to the first element of the list
} edgeSet;

