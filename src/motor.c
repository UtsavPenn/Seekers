/*
  1. Creates a graph structure representing the environment.
  2. Move the bot in a given direction for given amount of time.
  @Author: Utsav Mehta and Shallav Varma
*/

#include <stdio.h>
#include <bcm2835.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include "motor.h"

#define MOTORA RPI_GPIO_P1_12
#define MOTORB RPI_GPIO_P1_11

graph area;

extern orientation lastTurn;

struct motor_params{
  int pin;
  float duty;
  };

struct motor_params motorleft,motorright;

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

/* 
  Initialize the left and the right motors by setting the 
  corresponding GPIO pins as outputs.
*/
void init_motors(){
   motorleft.pin = MOTORA;
   motorright.pin = MOTORB;
   if(!bcm2835_init())
    return ;

  bcm2835_gpio_fsel(MOTORA, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(MOTORB, BCM2835_GPIO_FSEL_OUTP);
}

/*
  The driver for motors.
*/
void *drivemotors(void *arg){

 struct  motor_params* motor = (struct motor_params*)arg;

 
 while(1){
   bcm2835_gpio_write(motor->pin,HIGH);
   bcm2835_delayMicroseconds(motor->duty*200);
   bcm2835_gpio_write(motor->pin,LOW);
   bcm2835_delayMicroseconds((100-motor->duty)*200);
 
  } 
}

/*
  Runs the bot in straight direction for a given amount of time.
  @args
  time : time for which bot should drive straight. 
*/
void driveStraight(int timer){
  printf("Going Straight\n");
  pthread_t lth ,rth;
  motorright.duty = 3.75;
  motorleft.duty = 11.25;
  
  //Starting motor threads   
  pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
    printf("Threads created in drive straight.: %d \n",timer);  
  sleep(timer);
  
  pthread_cancel(rth);
  pthread_cancel(lth);
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
	printf("Threads cancelled in drive straight. \n");  
}

/*
  Rotates the bot in right direction.
*/
void turnRight(){
  printf("Turning Right\n");
  pthread_t lth ,rth;
  motorright.duty = 7.25;
  motorleft.duty = 11.25;
  
  pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
  
  usleep(1370000);
  
  pthread_cancel(rth);
  pthread_cancel(lth);
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
  
}

/*
  Rotates the bot in left direction.
*/
void turnLeft(){
  printf("Turning Left\n");
  pthread_t lth ,rth;
  motorright.duty =7.25;
  motorleft.duty = 3.75;
  
  pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
  
  usleep(1370000);
  pthread_cancel(rth);
  pthread_cancel(lth);
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
  
}

/*
  Rotates the bot 360 degrees.
*/
void rotate360(){
   pthread_t lth ,rth;
  motorright.duty = 7.25;
  motorleft.duty = 11.25;
  
  pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
  
  usleep(1330000*4);
  
  pthread_cancel(rth);
  pthread_cancel(lth);
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
   
}

/*
  Orients the bot wrt reference direction.
*/
void orient()
{
	printf("\n Orienting itself.: %d \n",lastTurn); 
      sleep(1);
      switch(lastTurn)
      {
              case Right:
                      turnLeft();
                      sleep(1);
                      break;
              case Back:
                      turnRight();
			                sleep(1);
                      turnRight();
                      sleep(1);
                      break;
              case Left:
                      turnRight();
                      sleep(1);
                      break;
              default:
                      break;
      }
}

/*
  Bot moves in the given direction for a given amount of time.  
*/
void moveCar(orientation direction, int timer){
  // Pre - condition: Bot can face in any direction.
  orient(); 
  // Bot faces in the reference direction here.
  switch(direction){
  	case Straight:
  	  driveStraight(timer);
  	break;
  	case Right:
  	  turnRight();
	driveStraight(timer);
  	break;
  	case Left:
  	  turnLeft();
	driveStraight(timer);
  	break;
	case Back:
		turnRight();
		sleep(1);
		turnRight();
		driveStraight(timer);
		break;
  	default:
  	  motorright.duty = 7.25;
  	  motorleft.duty = 7.25;
  	  break; 
  }
  return ;
}

