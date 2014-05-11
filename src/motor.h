
/*struct which contains the attributes required for moving the motor*/
typedef struct motor{
  int pin;
  float duty;
  float ontime;
  }motor;

/*struct which contains the function pointers necessary for the movement of the bot*/
typedef struct bot {
  motor motorright;
  motor motorleft; 
  
  void (*turnRight)(struct bot* self);
  void (*turnLeft)(struct bot *self);
  void (*driveStraight)(struct bot *self, int timer);
  void (*rotate360)(struct bot *self);
  void (*startmotors)(struct bot *self, int timer);
  void (*orient)(struct bot* self);
}bot;

/*initialises the motor pins and aaigns the function pointers to specific functions*/
void motor_init(bot*);

/*rotates the bot 360*/
void rotate360(bot*);

/*turns the bot right*/
void turnRight(bot*);

/*turns the bot leftt*/
void turnLeft(bot*);

/*moves the bot Straight*/
void driveStraight(bot*, int);

/*starts the motors*/
void startmotors(bot*,int);

/*an interface function for dfs code to move the bot according to the graph*/
void moveCar(bot, orientation, int);
