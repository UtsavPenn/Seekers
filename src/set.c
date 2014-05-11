#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "Linkedlist.h"

void addToSet(Set ** head, int ID){

	//check if the node exists, don't add
	if(*head == NULL){//first element of the set
		*head = (Set*)malloc(sizeof(Set));
		(*head)->listHead = NULL;
	}
	if(!setContains(*head, ID)){// if the set doesn't contain the given ID

		addToLinkedList(&((*head)->listHead), ID);
	}
}

void listSet(Set * head){

	if(head == NULL)
		return;
	listLinkedList(head->listHead);
}


int removeNodeFromSet(Set ** head, int ID){

	if(isSetEmpty(*head))
	{ 
		return -1;
	}
	return removeNodeFromList(&((*head)->listHead), ID);	
}


void clearSet(Set ** head){

	clearLinkedList(&((*head)->listHead));
}


bool setContains(Set * head, int ID){

	if(head == NULL)
		return false;
	return listContains(head->listHead,ID);
}

int sizeOfSet(Set * head){

	return sizeOfLinkedList(head->listHead);
}

int isSetEmpty(Set * head){

	return isLinkedListEmpty(head->listHead);
}
