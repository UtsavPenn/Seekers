#define CAPACITY 20

typedef struct STACK{

	int array[CAPACITY];//capacity of Stack
	int tos;//length of stack
}Stack;


/**
initializes the Stack
*/
void initStack(Stack *);

/**
@param - pointer to the Stack
removes and returns the element at top of stack
*/
int pop(Stack *);

/**
@param - pointer to the Stack and the element
pushes the element at top of stack
*/
void push(Stack * , int);

/**
@param - pointer to the Stack
returns true if stack is empty
false otherwise
*/
bool isStackEmpty(Stack *);

/**
@param - pointer to the Stack
prints out the entire stack
*/
void printStack(Stack *);
