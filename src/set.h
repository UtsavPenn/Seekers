#include <stdbool.h>
#define MAXNODES 10

typedef struct Set{

	struct List * listHead; //points to the first element of the list
	
} Set;

/**
* adds the element to the set
* @param- pointer to pointer to the first element of set, node ID
*/
void addToSet(Set **, int ID);

/**
* prints out the list of nodes in the set
* @param- pointer to first element of set
*/
void listSet(Set *);

/**
* removes given element from the set
* @param- pointer to pointer to first element of set, node ID
*/
int removeNodeFromSet(Set **,int ID);

/**
 *returns true if the set contains the given ID
 * 			false otherwise
 * @param- node ID, pointer to first element of the set
 */
bool setContains(Set *, int ID);

/**
 * clears the set
 * @param pointer to first element of the set
 */

void clearSet(Set **);

/**
* returns 1 if the list is empty
* 		  0 otherwise
* @param - pointer to first element of the set
*/
int isSetEmpty(Set *);

