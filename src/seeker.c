#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "init.h"

// why returning a void*? for that matter, why are you defining these functions at all?
void *objectDetect(void *arg)
{
	printf("detected\n");
	startDetect();
	//return;
}

// why are you returning a void* ?
void *objectSearch(void *arg)
{
	printf("here\n");
    	startSearch();
	//return ;
}

void errorDisp(int x)
{
	if (x)
	{
        	 printf("ERROR; return code from pthread_create() is %d\n", x);
     	}
	//return;
}
// why aren't you using C++11 threads instead?
int main()
{
	pthread_t threads[2];
	int retVal[2];
	retVal[0] = pthread_create(&threads[0], NULL, objectDetect, NULL);
	errorDisp(retVal[0]);
	retVal[1] = pthread_create(&threads[1], NULL, objectSearch, NULL);
	errorDisp(retVal[1]);
	//printf("Here\n");
	pthread_exit(NULL);
	return 0;
}
