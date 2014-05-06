#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define CAPACITY 20

typedef struct STACK{
	// give the invariants and describe the stack abstraction here
	int array[CAPACITY];
	int tos;//top of stack
}stack;
// it's actually a good idea to define a destructor for a new datatype, even if it is trivial.
// It's call gives you a way to tell the reader that the data structure will no longer be used.
// Moreover, it gives you more flexibility to change the representation later, e.g. to use the heap,
// without breaking the already-written client code.
void initStack(stack *);
int pop(stack *);
void push(stack * , int);
bool isStackEmpty(stack *);
void printStack(stack *);
void clearStack(stack *);
