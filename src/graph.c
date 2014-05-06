/*
    @author: Shallav Varma and Utsav Mehta
    GRAPH API: Methods available
    1.  Create a graph object: graphInit(graph *)
    2.  Create a node: addNode(graph *)
    3.  Add edge between two nodes: addEdge(graph *, int, int, int, orientation)
    4.  Search a Node in a graph: findNode(graph *, int nodeID)
    5.  Delete an edge between two nodes: deleteEdge(graph *, node*, node*)
    6.  Delete a node: deleteNode(graph *, node *)
    7.  Print the entire graph structure: print(graph *)
*/

#include "graph.h"
//graph area;

/*
    Initializes a graph object.
*/
void graphInit(graph * area)
{
    // Point all the functions in the graph strucuture to appropriate function definitons. 
    area -> addNode = &addNode;
    area -> addEdge = &addEdge;
    area -> deleteEdge = &deleteEdge;
    area -> deleteNode = &deleteNode;
    area -> findNode = &findNode;
    
    // Malloc of graph required when compiling with g++, not gcc, despite of declaring area as global.
    area -> head = (node*)malloc(sizeof(node));
    area -> tail = (node*)malloc(sizeof(node));
    
    //Malloc graph head.
    area -> head -> edges = (edgeSet*)malloc(sizeof(edgeSet));
    area -> head = (node *)malloc(sizeof(node));
    area -> head -> id = 0 ;
    area -> head -> next = NULL;
    area -> tail = area -> head;
}
 

/*
    Creates a node.
*/ 
void addNode (graph * area)
{
    node *n = (node *)malloc(sizeof(node));
    edgeSet *edges = (edgeSet*)malloc(sizeof(edgeSet));
    static int x = 0;
    n -> id = ++x;
    n -> edges = edges;
    n -> edges -> listHead = NULL;
    n -> next = NULL;
    area -> tail -> next = n;
    area -> tail = n;
        
}

/*
    Adds an edge between two nodes.
    @params
    timer : time to traverse path between nodes.
    direction: direction from node1 to node2.
*/  
void addEdge(graph * area, int nodeId1, int nodeId2, int timer,orientation direction ){
    edge *EdgeAToB,*EdgeBToA;
    node * node1 = findNode(area, nodeId1);
    node * node2 = findNode(area, nodeId2);    

    EdgeAToB = createEdge();
    EdgeAToB -> dest = node2;
    EdgeAToB -> timer = timer;
    EdgeAToB -> turn = direction;
    addToSet_graph (&(node1 -> edges),EdgeAToB);

    switch(direction)
    {
        case Straight : direction = Back; break;
        case Back : direction = Straight; break;
        case Right : direction = Left; break;
        case Left : direction = Right; break;
        default: break;
    }

    EdgeBToA = createEdge();
    EdgeBToA -> dest = node1;
    EdgeBToA -> timer = timer;
    EdgeBToA -> turn = direction;
    addToSet_graph (&(node2 -> edges),EdgeBToA);
}


/*
    Mallocs an edge.
*/
edge * createEdge ()
{
    edge * n;
    n = (edge *)malloc(sizeof(edge));
    if ( n != NULL)
    {
        return n;
    }
    return NULL;
}

/*
    Search a node of a given node ID
    and return pointer to the node.
*/
node * findNode(graph * area, int nodeID)
{
    node * foundNode = area -> head;
    if (nodeID > area -> tail -> id)
    {
        foundNode = NULL;
    }
    else if (nodeID == area -> tail -> id)
    {
        foundNode = area -> tail;
    }
    else
    {
        while (foundNode -> id != nodeID)
        {
            foundNode = foundNode -> next;
        }
     
    }  
    return foundNode;   
} 

/*
    Deletes a node from graph
    First deletes all the edges emitting from node, then deletes the node.
*/
    
void deleteNode (graph * area, node* nodeA)
{
    node * iter = area -> head -> next;
    node * temp = area -> head -> next;
    
    if (nodeA == NULL)
    {
        return;
    }
    while (iter)
    {
        if (iter == nodeA)
        {
            clearSet_graph(&(iter -> edges));   
        }
        else
        {
        	if (iter -> next == nodeA)
        	{
        		temp = iter;
        	}
            edge * temp2 = findEdge_graph(iter -> edges,nodeA);
            if (setContains_graph(iter -> edges, temp2))
            {
                removeNodeFromSet_graph(&(iter -> edges), nodeA);
            }
        }
        iter = iter -> next;
    }    
    temp -> next = nodeA -> next;
    free(nodeA);
    //printf("Done.\n");
}

/*
    Deletes edge between two nodes.
*/ 
void deleteEdge(graph * area, node* end1 ,node* end2){
    edge* temp = findEdge_graph(end1 -> edges, end2);
    deleteEdgeAtoB(end1, temp );
    temp = findEdge_graph(end2 -> edges, end1);
    deleteEdgeAtoB(end2, temp);
}

/*
    Deletes a unidirectional edge  from node A to node B.
*/ 
void deleteEdgeAtoB(node* nodeA, edge* end){
    if (setContains_graph(nodeA -> edges, end))
        {
            removeNodeFromSet_graph(&(nodeA -> edges), end -> dest);
        }
	
}

/*
    Print the list of all the nodes in the graph.
*/
void printList (graph * area)
{
node * iter;
iter = area -> head;
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
void print(graph * area){
	node *vertical = area -> head -> next;
	while(vertical){
		printf("%d\t",vertical -> id);
		listSet_graph(vertical -> edges);
		vertical = vertical->next;
		printf("\n");
	}
}


/*
int main()
{
    int i = 0;
    //printf("%lu",sizeof(area.head));
    graphInit(&area);
    while(i < 6)
    {
        addNode(&area);
        i++;
    }
    addEdge(&area, 0, 2, 10, Straight);
    addEdge(&area, 1, 2, 10, Straight);
    addEdge(&area, 1, 3, 10, Straight);
    addEdge(&area, 2, 4, 10, Straight);
    addEdge(&area, 2, 6, 10, Straight);
    addEdge(&area, 4, 5, 10, Straight);
    addEdge(&area, 3, 6, 10, Straight);
    print(&area);
    printf("Node found: %d\n", findNode(&area,6) -> id);
    deleteNode(&area, findNode(&area,6));
    print(&area);
    printf("\n");
    deleteEdge(&area, findNode(&area,2),findNode(&area,4));
    print(&area);
    return 0;
}
*/