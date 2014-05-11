#include <stdbool.h>

typedef struct List {

	int ID;
	struct List * next; // a pointer to the next node

} List;

/**
* adds the element at the end of the list
* @param- pointer to pointer to first element, node ID
*/
void addToLinkedList(List **,int);

/**
* removes given element from the list
* @param- pointer to pointer to first element, node ID
*/
int removeNodeFromList(List **, int);

/**
* prints out the list of nodes in the list
* @param- pointer to first element
*/
void listLinkedList(List *);

/**
* returns the pointer to the node with given ID
* @param- pointer to first element
*/
int searchNodeInLinkedList(List *, int);

/**
 * returns number of nodes in the list
 * @param- pointer to first element
 */
int sizeOfLinkedList(List *);

/**
* @param - pointer to first element
* returns 1 if the list is empty
* 		  0 otherwise
*/
int isLinkedListEmpty(List *);

/**
 *returns true if the list contains the given ID
 * 			false otherwise
 * @param- node ID, pointer to first element of the list
 */
bool listContains(List *, int);

/**
 * clears the entire list
 * @param pointer to first element
 */
void clearLinkedList(List **);
