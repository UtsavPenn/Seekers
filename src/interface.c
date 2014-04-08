#include "interface.h"
extern vertexNode *head;
extern vertexNode *tail;
vertexNode* currGraph;

extern edgeNode* current_searchedge; 
param* res;
param * getParam(pathNode * curr)
{
	
	int id = 0;
	if(curr->next != NULL)
	{
		 id = curr ->next-> id;
		 //printf("%d ff\n",id);
	}
	else return NULL;
	
	if(id == 2)
	{
		currGraph = head;
	}
	
	searchEdge(currGraph, id);
	
	//printf("%p\n",current);
	if (current_searchedge != NULL)
	{
		res = (param*)current_searchedge;
		printf("%d",current_searchedge->turn);
		res->turn = current_searchedge->turn;
		res->timer = current_searchedge->distance;
	}
	else
	{
		res->turn = 0;
		res->timer = 0;
	}
	return res;
 }
	
