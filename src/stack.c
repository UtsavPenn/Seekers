#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

// #define btoa(isStackEmpty) ((isStackEmpty)?"true":"false")

void initStack(Stack * stack){

	stack->tos = 0;//length of the stack
}

int pop(Stack * stack){

	int top;
	if(stack->tos == 0)//empty stack!
		return -1;
	return stack->array[--(stack->tos)];
}

void push(Stack * stack, int ID) {

	if(stack->tos == CAPACITY)
		printf("Stack full\n");
	else
		stack->array[(stack->tos)++] = ID;
}

void printStack(Stack * stack){

	int i=0;
	while(i!= stack->tos)
	{
		printf("Element %d: %d\n",i,stack->array[i]);
		i++;
	}
}

bool isStackEmpty(Stack * stack){

	if(stack->tos == 0)
		return true;
	return false;
}
