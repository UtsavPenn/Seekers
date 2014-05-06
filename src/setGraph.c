#include "setGraph.h"

void listLinkedList_graph(edge * head){
	edge * current = head;
	if(current == NULL){
		//printf("List Empty!");
		return;
	}
	while(current != NULL){
		printf(" %d\t", current-> dest -> id);
		current = current->next;
	}
}


void listSet_graph(edgeSet * head){

	if(head == NULL)
		return;
	listLinkedList_graph(head->listHead);
}

void addToSet_graph(edgeSet ** head, edge * temp){

	//check if the node exists, don't add
	if(*head == NULL){//first element of the edgeSet
		*head = (edgeSet*)malloc(sizeof(edgeSet));
		(*head)->listHead = NULL;
	}
	if(!setContains_graph(*head, temp)){
		addToLinkedList_graph(head,(*head)->listHead, temp -> dest);
	}
}


/**
 * @param- pointer to first element, node ID
 * returns nothing
 */
void addToLinkedList_graph(edgeSet ** edgeSetHead, edge * head, node * nodeA){

	if(head == NULL){//first node of the list
		head = (edge*)malloc(sizeof(edge));
		head->dest = nodeA;
		head->next = NULL;
		(*edgeSetHead)->listHead = head;
		return;
	}
	edge * current = head;
	while(current->next != NULL){//traverse till the end of the list
		current = current->next;
	}
	current->next = (edge*)malloc(sizeof(edge));
	current->next->dest = nodeA;
	current->next->next = NULL;
	(*edgeSetHead)->listHead = head;
}

/**
 * @param pointer to first element
 * returns nothing
 * clears the entire list
 */
void clearLinkedList_graph(edgeSet ** edgeSetHead, edge * head){

	// graph_node * current =head;
	edge * temp;
	while(head->next != NULL){//last node
		temp = head->next;
		free(head);
		head = temp;
		(*edgeSetHead)->listHead = temp;

	}
	if(head->next == NULL)//last element
		free(head);
		head=NULL;
		(*edgeSetHead)->listHead = NULL;
}

void clearSet_graph(edgeSet ** head){

	clearLinkedList_graph(head, (*head)->listHead);
}


bool setContains_graph(edgeSet * head, edge* temp){

	//printf("Inside edgeSetContains: %p\n",head);
	if(head==NULL || temp == NULL)
		return false;
	return listContains_graph(head->listHead , temp -> dest);
}


/**
 * @param- node ID, pointer to first element of the list
 * returns true if the list contains the given ID
 * 			false otherwise
 */
bool listContains_graph(edge * head, node * nodeA){

	if(searchNodeInLinkedList_graph(head, nodeA) == NULL)
		return false;
	return true;
}


/**
 * returns the pointer to the node with given ID
 */
edge * searchNodeInLinkedList_graph(edge * head, node * nodeA){

	edge * current = head;

	while(current != NULL){
		if(current -> dest == nodeA)
			return current;
		else{
			current = current->next;
		}
	}
	return NULL;
}

int removeNodeFromSet_graph(edgeSet ** head, node* nodeA){
	if(isSetEmpty_graph(*head)){ return -1;}
	return removeNodeFromList_graph(head, (*head)->listHead, nodeA);	
}


int removeNodeFromList_graph(edgeSet ** edgeSetHead, edge * head, node * nodeA){

	edge * current = head;
	edge * temp;

	if(head->next == NULL){//only one node in list
		if(head->dest == nodeA){
			free(head);
			head=NULL;
			(*edgeSetHead)->listHead = NULL;
			return 1;
		}
	}
	else{//more than one node in list
		//if first one is the Required one!
		if(current->dest == nodeA){
			temp= current->next;
			free(head);
			// head = temp;
			(*edgeSetHead)->listHead = temp;
			return 1;
		}
		while(current->next != NULL){//check rest of the nodes
				if(current->next->dest == nodeA){
					temp= current->next->next;
					free(current->next);
					current->next = temp;
					return 1;
				}
				current=current->next;
			}
		}
	return -1;
}


/**
* @param - 
* returns 1 if the list is empty
* 		  0 otherwise
*/
int isLinkedListEmpty_graph(edge * head){

	if(sizeOfLinkedList_graph(head)!=0)
		return 0;
	return 1;
}

int isSetEmpty_graph(edgeSet * head){

	return isLinkedListEmpty_graph(head->listHead);
}


 /* 
 * returns number of nodes in the list
 */
int sizeOfLinkedList_graph(edge * head){

	edge * current = head;
	int len=0;
	if(current == NULL)
		return len;//empty list
	while(current != NULL){
		len++;
		current= current->next;
	}

	return len;
}

/**
*
*/
int sizeOfSet_graph(edgeSet * head){

	return sizeOfLinkedList_graph(head->listHead);
}


edge * findEdge_graph(edgeSet * head, node* nodeA)
{
	//printf("Here.");
	edge * current = head -> listHead;

	while(current != NULL){
		if(current -> dest == nodeA)
			return current;
		else{
			current = current->next;
		}
	}
	return NULL;
}
