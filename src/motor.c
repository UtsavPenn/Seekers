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
#include <time.h> 
#include <sys/types.h> 
#include "motor.h"

#define MOTORA RPI_GPIO_P1_12
#define MOTORB RPI_GPIO_P1_11

extern orientation lastTurn;
/* 
  Initialize the left and the right motors by setting the 
  corresponding GPIO pins as outputs.
*/

void motor_init(bot* car){
   car->motorleft.pin = MOTORA;
   car->motorright.pin = MOTORB;
  
   if(!bcm2835_init())
    return ;
  
  bcm2835_gpio_fsel(MOTORA, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(MOTORB, BCM2835_GPIO_FSEL_OUTP);
 	
  car->turnRight = &turnRight; 
  car->turnLeft = &turnLeft;
  car->driveStraight = &driveStraight;
  car->startmotors = &startmotors;
  car->rotate360 = &rotate360;
  car->orient = &orient;
}

/*
  The driver for motors.
*/
void *drivemotors(void *arg){
 time_t now;
 struct tm *tm;
 int entryTime;
 now = time(0);
 tm = localtime (&now);
 motor* mot = (motor*)arg; 
 entryTime = tm->tm_sec;

 while(tm->tm_sec <= entryTime + mot->ontime){
   printf("Entry time %d\n",tm->tm_sec);
   bcm2835_gpio_write(mot->pin,HIGH);
   bcm2835_delayMicroseconds(mot->duty*200);
   bcm2835_gpio_write(mot->pin,LOW);
   bcm2835_delayMicroseconds((100-mot->duty)*200);
   now = time(0);
   tm = localtime (&now);
   
  } 
}
/*
  Runs the bot in straight direction for a given amount of time.
  @args
  time : time for which bot should drive straight. 
*/


void startmotors(bot* car){
  time_t now;
  struct tm *tm;
  pthread_t lth ,rth;
  pthread_create(&rth,NULL,drivemotors,(void*)&car->motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&car->motorleft);
  
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
}


void driveStraight(bot* car, int timer){
  printf("Going Straight\n");
  car->motorright.duty = 3.75;
  car->motorleft.duty = 11.25;
  car->motorleft.ontime = timer;
  car->motorright.ontime = timer;
  startmotors(car);
}

/*
  Rotates the bot in right direction.
*/
void turnRight(bot* car){
  printf("Turning Right\n");
  car->motorright.duty = 7.25;
  car->motorleft.duty = 11.25;
  car->motorleft.ontime = 1.37;
  car->motorright.ontime = 1.37;
  startmotors(car);
}

/*
  Rotates the bot in left direction.
*/
void turnLeft(bot* car){
  printf("Turning Left\n");
  car->motorright.duty =7.25;
  car->motorleft.duty = 3.75;
  car->motorleft.ontime = 1.37;
  car->motorright.ontime = 1.37;
  startmotors(car); 
  
}

/*
  Rotates the bot 360 degrees.
*/
void rotate360(bot* car){
  car->motorright.duty = 7.25;
  car->motorleft.duty = 11.25;
  car->motorleft.ontime = 5.48;
  car->motorright.ontime = 5.48;
  startmotors(car);
   
}

/*
  Orients the bot wrt reference direction.
*/
void orient(bot* car)
{
	printf("\n Orienting itself.: %d \n",lastTurn); 
      sleep(1);
      switch(lastTurn)
      {
              case Right:
                      car->turnLeft();
                      sleep(1);
                      break;
              case Back:
                      car->turnRight();
		      sleep(1);
                      car->turnRight();
                      sleep(1);
                      break;
              case Left:
                      car->turnRight();
                      sleep(1);
                      break;
              default:
                      break;
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

