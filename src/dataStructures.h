#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

// documentation! this is unreadable
// You are cooking in a lot of assumptions that will make this code hard to reuse, 
// e.g. that there is only one graph.

// shouldn't be in a header
int xx ;

#define ASSIGN_ID() ((xx) = (xx) + 1)

typedef enum{
    false,
    true} bool;

typedef enum{
  Straight,
  Right,
  Back,
  Left
} orientation;

struct edgeNode {
  struct edgeNode * next;
  int id
  // can this be negative?
  int distance;
  orientation turn;
};

struct vertexNode {
int id;
struct edgeNode *head,*tail;
struct vertexNode *next;
};

// put these when you define the structs, not down here where they can get lost
typedef struct edgeNode edgeNode;
typedef struct vertexNode vertexNode;

// If you are writing embedded C code, don't take a dependence on the heap.
// Instead, pass in a pointer to the memory will the node will be created
bool createVertexNode();
edgeNode * createEdgeNode(int);
void deleteEdgeAtoB(vertexNode *, vertexNode *);
void deleteEdge(vertexNode *, vertexNode *);
void deleteVertexNode(vertexNode *);
bool addEdge(vertexNode *,vertexNode *, float, orientation, orientation);
vertexNode * search(int);
edgeNode * searchEdge(vertexNode*, int );
// init what? In C, use names that bind operations with the types or objects they operate on
void init();
void print();
void edgeInit(vertexNode *, edgeNode *)
// shouldn't be in a header
vertexNode *head;
vertexNode *tail;

