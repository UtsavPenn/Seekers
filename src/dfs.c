//#include "dataStructures.h"
#include "motor.h"
#include "dfs.h"
#include "init.h"


extern bool objectFound;               //From opencv
graph area;
bot robot;
motor_init(&robot);

orientation currentOrientation;                          
orientation lastPostionSeen = Straight;     

orientation lastTurn;

int distanceToNextNode; //Distance to be travelled to the next node

static set* markedNodes;   // Set for storing nodes visited
static set* frontierNodes; // Set for storing frontier nodes to be explored
static stack spine;        // Spine for storing node IDs

/*
 It creates the graph structure using Graph API.
 */
void run ()
{
	lastTurn = Straight;
    int i = 0;
    // Creates a linked list with number of nodes = number of times the loop executes.
    
    graphInit(&area);
    while(i < 9)
    {
        area.addNode(&area);
        i++;
    }
    // Adding edges between various nodes of graph.
    area.addEdge(&area, 0, 1, 3, Right);
    area.addEdge(&area, 1, 2, 3, Right);
    area.addEdge(&area, 2, 5, 3, Straight);
    area.addEdge(&area, 5, 4, 3, Left);
    area.addEdge(&area, 4, 3, 3, Left);
    area.addEdge(&area, 1, 4, 3, Straight);
    area.addEdge(&area, 0, 3, 3, Straight);
    area.addEdge(&area, 3, 6, 3, Straight);
    area.addEdge(&area, 6, 7, 3, Right);
    area.addEdge(&area, 7, 8, 3, Right);
    area.addEdge(&area, 4, 7, 3, Straight);
    area.addEdge(&area, 5, 8, 3, Straight);
    
    print(&area);
    
}

/**
@description:
    initializes spine

*/

void init_Dfs()
{
  initStack(&spine);    //Initializes the stack     
}


/**
@description:
    Given a node id with reference to the graph,
    the neighbouring nodes are added to the frontier set
*/

void addNeigbourNodesToFrontier(int id){
  node* v = findNode(&area,id);
    //Found the vertex node

    //Create a temp head edgeNode
    edge* temp_head = v->edges -> listHead; 
    while(temp_head!=NULL)  //Traverse and add all ids into the frontier
    {

        /*if(markedNodes.find(temp_head->astPosid) != markedNodes.end())
            frontierNodes.insert(temp_head->id);
        */
          //change
        if(setContains(markedNodes,temp_head->dest-> id) == 0)
            addToSet(&frontierNodes,temp_head->dest->id);
        
        temp_head = temp_head-> next;
    }

}

/**
@description:
    The next node to be traversed is decided
    Incorporates the last position seen by the bot

@return : Returns the ID of the next node to be traversed

*/

int DecideNextNode(int currentNodeID){

    node* v = findNode(&area,currentNodeID);
    //Found the vertex node

    //Create a temp head edge
    //Set of edges at node v
    edge* temp_head = v-> edges -> listHead; 
    
    /*    if(lastPostionSeen ==Left)
    {

        while(temp_head!=NULL)  //Traverse the edge nodes and check if the id matches
                                // and return true
        {
            if(temp_head->turn == lastPostionSeen)
                {
                    lastPostionSeen = Straight;
                    return temp_head->id;         
                }
            temp_head = temp_head->next;
        }
    }
    else if(lastPostionSeen == Right)
    {

        while(temp_head!=NULL)  //Traverse the edge nodes and check if the id matches
                                // and return true
        {
            if(temp_head->turn == lastPostionSeen)
                {
                    lastPostionSeen = Straight;
                    return temp_head->id;         
                }
            temp_head = temp_head->next;
        }
    }

    else
    {
    */
        while(temp_head!=NULL)  
                                
        {
        /*    if(markedNodes.find(temp_head->id) !=markedNodes.end())
                return temp_head->id;
        */
           if(setContains(markedNodes,temp_head->dest ->id) == 0)
            {
                return temp_head->dest->id;
            }
        
            temp_head = temp_head->next;
        }

    

    return 0;  
}
    

/**
@description: Given the current node and next node
              to be traversed, the function returns only after 
              the bot has traversed to the next node

*/              

void moveToNextNode(int currentNodeID ,int nextNodeID)    //Decides on which  node to move to
{
    node* v = findNode(&area,currentNodeID);
    //Found the vertex node
    //Create a temp head edge

    edge* temp_head = v -> edges -> listHead; 
    orientation direction ;
    while(temp_head!=NULL) 
    {
        if(temp_head-> dest -> id == nextNodeID){
            direction = temp_head->turn;
            //lastTurn = direction;
		//lastPositionSeen = lastTurn;
            distanceToNextNode = temp_head->timer;
            break;
    }

        temp_head = temp_head->next;
    }   

    robot->moveCar(direction, distanceToNextNode);
    lastTurn  = direction;
    printf("Node explored : %d \n", currentNodeID);

}

/**
@description: 
    Checks if neighbor node exists in the frontier
    Returns bool
*/
int checkIfNeighborExistsInFrontier(int nodeID) 
{
    node* v = findNode(&area,nodeID);
    //Found the vertex node

    //Create a temp head edgeNode
    edge* temp_head = v->edges-> listHead; 

    while(temp_head!=NULL)  //Traverse the edge nodes and check if the id matches
                            // and return true
    {
        /*
        if(frontierNodes.find(temp_head->id) != frontierNodes.end())
            return 1;
       */
        if(setContains(frontierNodes,temp_head->dest->id) == 1)
            return 1;
            
        temp_head = temp_head-> next;
    }
    return 0;

}





int findNextNode(orientation currentOrienation, int nodeID)
{
  // Find the vertex node
  int foundID;
  node* v = findNode(&area,nodeID);
  edge* temp_head = v-> edges -> listHead;

  orientation direction ;
   
  while(temp_head!=NULL) 
    {
      if(temp_head-> dest->id == nodeID){
	direction = temp_head->turn;
	//lastTurn = direction;
	//lastPositionSeen = lastTurn;
	distanceToNextNode = temp_head->timer;
	break;
      }

      temp_head = temp_head->next;
    }   
  
      
      return foundID;
}


void startSearch()
{
    bool flag;
    int currentNodeID = 0;  //Current node while starting is 0
    bool objLostFlag;
   int turnsTaken;    

    bool dfsRunning = false;
    
    currentOrientation = Straight;

    init_Dfs();         //Initialize the stack spine
    motor_init(&robot);
    run();

    int nextNodeID;
    int cnt = 0;
	
	printf("here2\n");
while(1)
{
    //scanAndSearch();    
	printf("here3\n");
    

    if(objectFound == true)
    {
      // empty the DFS Sets and set dfsRunning to false;
      
      clearSet(&frontierNodes);
      clearSet(&markedNodes);
      clearStack(&spine);
      
      // Given currentNodeID find , find next node with my current orientation
      nextNodeID = findNextNode(currentOrientation,currentNodeID);
      
      // move to next node
      
      moveToNextNode(currentNodeID, nextNodeID);
      currentNodeID = nextNodeID;
      
      
      /********** ********************
    	printf("Obj found: %d",cnt);
	    cnt ++;
	    rotate360();
    	objectFound = false;	
      ********************************/

    }
    else
    {
      turnsTaken = 4;
      while(turnsTaken >0 )
	{
	  
	  turnRight();       // Turn 90 and check for obj	  

	 switch( currentOrientation)
	{
	case Straight:
		currentOrientation = Right;
		break;
        case Right:
                currentOrientation = Back;
                break;
        case Back:
                currentOrientation = Left;
                break;
        case Left:
                currentOrientation = Straight;
                break;


	}
	  
	  // scan and search

	  if(objectFound == true){
	    flag = true;
	    break;	 
	  }
	  turnsTaken--;
	}
      
      if(flag == true){
	continue;
	flag = false;
      }

      if(!dfsRunning)
	{
	      addNeigbourNodesToFrontier(currentNodeID);
	      addToSet(&markedNodes,currentNodeID);  
	      push(&spine, currentNodeID);
	      nextNodeID = DecideNextNode(currentNodeID);
	      objLostFlag = true;
	}


        printf("Spine. \n");
        printStack(&spine);
        printf("\n\n");

        printf("Next node to be traversed: %d\n", nextNodeID);
     
        moveToNextNode(currentNodeID,nextNodeID); //Move to the next node
        currentNodeID = nextNodeID;             
        
        addToSet(&markedNodes,currentNodeID);   //Current Node has been traversed. Add to the set
        addNeigbourNodesToFrontier(currentNodeID);  //Adding frontier nodes from the new current node
        removeNodeFromSet(&frontierNodes,currentNodeID); //Removing the current node from frontier
     
        printf("Done nodes : \n");
        listSet(markedNodes);
        printf("Frontier Nodes : \n");
        listSet(frontierNodes);



        if (checkIfNeighborExistsInFrontier(currentNodeID)) //Check if neighbor exists in frontier
        {                                                   // If so visit there
         
            push(&spine, currentNodeID);  //Change
            nextNodeID = DecideNextNode(currentNodeID);
        }
        else
        { 
        if(isStackEmpty(&spine))
            return ; // Done traversing. Stop
        else
            {
                nextNodeID = pop(&spine);                
            }
        }
            
       }
        
}
}


/*
  Bot moves in the given direction for a given amount of time.  
*/
void moveCar(bot car, orientation direction, int timer){
  // Pre - condition: Bot can face in any direction.
  orient(); 
  // Bot faces in the reference direction here.
  switch(direction){
  	case Straight:
  	  car.driveStraight(timer);
  	break;
  	case Right:
  	  car.turnRight();
	driveStraight(timer);
  	break;
  	case Left:
  	  car.turnLeft();
	  car.driveStraight(timer);
  	break;
	case Back:
		car.turnRight();
		sleep(1);
		car.turnRight();
		car.driveStraight(timer);
		break;
  	default:
  	  car.motorright.duty = 7.25;
  	  car.motorleft.duty = 7.25;
  	  break; 
  }
  return ;
}

