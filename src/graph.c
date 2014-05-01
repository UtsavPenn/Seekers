/*
    @author: Shallav Varma and Utsav Mehta
    GRAPH API: Methods available
    1.  Create a node: createVertexNode()
    2.  Add edge between two nodes: addEdge(vertexNode*, vertexNode*, float, orientation, orientation)
    3.  Search a Node in a graph: searchNode(int nodeID)
    4.  Delete an edge between two nodes: deleteEdge(vertexNode*, vertexNode*)
    5.  Delete a node: deleteVertexNode(vertexNode *)
    6.  Print the entire graph structure: print()
*/

#include "graph.h"
int xx;

// Used to assign a unique id to each node.
#define ASSIGN_ID() ((xx) = (xx) + 1)

vertexNode * head, * tail, * foundNode;
edgeNode * foundEdge;


edgeNode *n;

/*
    Initializes the graph structure by creating a head node.
*/
void init()
{ 	
	xx = 0;
	head = (vertexNode *)malloc(sizeof(vertexNode));
	head->id = xx;
	head->next = NULL;
	head -> head = NULL;
	head -> tail = NULL;
	tail = head;
}

 
/*
    Search a node of a certain ID and returns pointer to that node.
    @author Shallav 
*/    
vertexNode* searchNode(int nodeID){
  search(nodeID);
  return foundNode; 
}

/*
    Search a node of a given node ID.
    Helper to searchNode.
    foundNode contains the pointer to the found node. If not found, 
    foundNode contains NULL.
*/
void search(int nodeID)
{
    foundNode = head;
    if (nodeID > tail -> id)
    {
        foundNode = NULL;
        return ;
    }
    else if (nodeID == tail -> id)
    {
        foundNode = tail;
        return;
    }
    else
    {
        while (foundNode -> id != nodeID)
        {
            foundNode = foundNode -> next;
        }
     
    }     
} 


/*
    @author Utsav 
    Adds an edge between two vertex nodes.
    @params
    timer : time to traverse path between nodes.
    turnToA: direction in which bot moves when going from node B to node A.
    turnToB: direction in which bot moves when going from node A to node B.
*/  
bool addEdge(vertexNode* nodeA, vertexNode* nodeB, float timer, orientation turntoA, orientation turntoB ){
    edgeNode *EdgeAToB,*EdgeBToA;
    createEdgeNode(nodeB->id);
    EdgeAToB = foundEdge;
    createEdgeNode(nodeA->id);
    EdgeBToA = foundEdge;
    if (EdgeAToB == NULL || EdgeBToA == NULL)
      return false;
    edgeInit(nodeA,EdgeAToB);
    edgeInit(nodeB,EdgeBToA);
    
    EdgeAToB->timer = timer;
    EdgeAToB->turn = turntoB;
    
    EdgeBToA->timer = timer;
    EdgeBToA->turn = turntoA;
    
    return true;
}

/*
    Place the edgeNode to the end of the list containing all the edges
    from the given vertex node.    
*/
void edgeInit(vertexNode *vnode, edgeNode *enode){

    if(vnode->head == NULL){
      vnode->head = enode;
      vnode->tail = vnode->head;
      }
    else{
      vnode->tail->next = enode;
      vnode->tail = enode;
    }
    vnode->tail->next = NULL;

}
/* 
    @author Shallav 
    Deletes a node from graph
    First deletes all the edges emitting from node, then deletes the node.
*/
    
void deleteVertexNode ( vertexNode* nodeA)
{
    vertexNode * iter = head;
    vertexNode * temp = head;
    
    if (nodeA == NULL)
    {
        return;
    }
    //printf("Head ID: %d\n",iter -> id);
    while (iter)
    {
    	printf("ID: %d\n",iter -> id); 
        if (iter == nodeA)
        {
            edgeNode * head = nodeA -> head;
            edgeNode *delNode;
            while(head -> next)
            {
            	delNode = head -> next; 
            	head -> next = delNode -> next;
            	free(delNode);
            	//printf("NotReached\n"); 
            }	
            free(head);
            nodeA -> tail = NULL;       
        }
        else
        {
        	if (iter -> next == nodeA)
        	{
        		temp = iter;
        	}
        	searchEdge(iter,nodeA -> id);
        	if (foundEdge)
        	{   printf("Searched Vertex Node %d\n",iter->id);
        		deleteEdgeAtoB(iter, nodeA);
        	}
        }
        iter = iter -> next;
    }    
    temp -> next = nodeA -> next;
    free(nodeA);
    printf("Done.\n");
}

/*
    Searches if the edge exists between given node and the node with the given ID.
*/  
void searchEdge(vertexNode* vnode, int id){
	 foundEdge = vnode->head;
	 //printf("%p\n",foundEdge);
	 //printf("%d\t%d",foundEdge->id, id);
	while(foundEdge){
		if(foundEdge->id == id)
			return ;
		foundEdge = foundEdge->next;
	}
	
}

/*
    @author Utsav 
    Deletes edge between two vertex nodes.
*/ 
void deleteEdge(vertexNode* nodeA ,vertexNode* nodeB){
    deleteEdgeAtoB(nodeA, nodeB);
    deleteEdgeAtoB(nodeB, nodeA);
}

/*
    @author Utsav 
    Deletes a unidirectional edge  from vertexNode A to vertexNode B.
*/ 
void deleteEdgeAtoB(vertexNode* nodeA, vertexNode* nodeB){
    edgeNode  * temp;
    edgeNode * currentNode;
    currentNode = nodeA->head;
    
    if (nodeA->head->id == nodeB->id){
    	temp = nodeA->head;
    	nodeA->head = temp->next;
    	free(temp);
    	return;
    }
      
    while(currentNode!= nodeA->tail)
    {
    	temp = currentNode;
    	if(currentNode->next->id == nodeB->id){
            temp = currentNode->next;
            currentNode->next = temp->next;
            free(temp);
            return;
        }
        currentNode = currentNode -> next;
    }   
    if(currentNode->id == nodeB->id)
    {
      	free(currentNode);
      	nodeA->tail = temp;      
    } 	
}

/*
    @author Shallav
    Creates an edge with given node ID.
*/
void createEdgeNode (int id)
{
    n = (edgeNode *)malloc(sizeof(edgeNode));
    if ( n != NULL)
    {
        n -> id = id;
    }
   foundEdge = n;
}

/*
    @author Shallav
    Creates a node.
    Returns true if node created successfully, false otherwise.
*/ 
bool createVertexNode ()
{
    vertexNode *n = (vertexNode *)malloc(sizeof(vertexNode));
    if (n == NULL)
    {
        return false;
    }
    else
    {    
        n -> id = ASSIGN_ID();
        n -> head = NULL;
        n -> tail = NULL;
        n -> next = NULL;
        tail -> next = n;
        tail = n;
  		
        return true;
    }
}

/*
    Print the list of all the nodes in the graph.
*/
void printList ()
{
vertexNode * iter;
iter = head;
while (iter)
{
	printf("%p\t",iter);
	printf("%d \n", iter -> id) ;
	iter = iter -> next;
}
printf("%p\t",iter);
}

/*
    Print the graph structure.    
*/
void print(){
	vertexNode *vertical = head;
	edgeNode *horizontal ; 
	while(vertical){
		printf("%d\t",vertical->id);
		horizontal = vertical->head;
		while(horizontal){
			printf("%d\t",horizontal->id);
			horizontal = horizontal->next;
		}
		vertical = vertical->next;
		printf("\n");
	}
}
