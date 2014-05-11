#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linkedlist.h"

#define btoa(listContains) ((listContains)?"true":"false")

void addToLinkedList(List ** head, int ID){

	if((*head) == NULL){//first node of the list
		(*head) = (List *)malloc(sizeof(List));
		(*head)->ID = ID;
		(*head)->next = NULL;
		return;
	}
	List ** current = head;
	while((*current)->next != NULL){//traverse till the end of the list
		(*current) = (*current)->next;
	}
	(*current)->next = (List*)malloc(sizeof(List));
	(*current)->next->ID = ID;
	(*current)->next->next = NULL;
}

void listLinkedList(List * head){

	List * current = head;
	if(current == NULL){
		printf("List Empty!\n");
		return;
	}
	int i=0;
	while(current != NULL){
		printf("Node %d\n", current->ID);
		current = current->next;
	}
}

int removeNodeFromList(List ** head, int ID){

	List ** current = head;
	List * temp;

	if((*head)->next == NULL){//only one node in list
		if((*head)->ID == ID){
			free((*head));
			(*head) = NULL;
			return 1;
		}
	}
	else{//more than one node in list
		//if first one is the Required one!
		if((*current)->ID == ID){
			temp = (*current) -> next;
			free((*head));
			return 1;
		}
		while((*current)->next != NULL){//check rest of the nodes
				if((*current)->next->ID == ID){
					temp = (*current)->next->next;
					free((*current)->next);
					(*current)->next = temp;
					return 1;
				}
				(*current) = (*current)->next;
			}
		}
	return -1;
}

int searchNodeInLinkedList(List * head, int ID){

	List * current = head;

	while(current != NULL){
		if(current->ID == ID)
			return 1;
		else{
			current = current->next;
		}
	}
	return 0;
}

void clearLinkedList(List ** head){

	List * temp;
	while((*head)->next != NULL){//last node
		temp = (*head)->next;
		free((*head));
		(*head) = temp;
	}
	if((*head)->next == NULL)//last element
		free((*head));
		(*head) = NULL;
}

bool listContains(List * head, int ID){

	if(searchNodeInLinkedList(head, ID)==0)
		return false;
	return true;
}

int sizeOfLinkedList(List * head){

	List * current = head;
	int len=0;
	if(current == NULL)
		return len;//empty list
	while(current != NULL){
		len++;
		current= current->next;
	}

	return len;
}

int isLinkedListEmpty(List * head){

	if(sizeOfLinkedList(head)!=0)
		return 0;
	return 1;
}
