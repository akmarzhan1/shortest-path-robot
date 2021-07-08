#include <AFMotor.h> //library for the DC motors 

AF_DCMotor leftMotor(2, MOTOR12_1KHZ); //defining DC motors 
AF_DCMotor rightMotor(3, MOTOR34_1KHZ);

//defining the sensors 
#define left A2 
#define left_center A3
#define right_center A4
#define right A5

//defining the arrays to store the overall path and use the shortcut 
char path[20]; 
int i;
int j;
char retrace[20];

void setup() 
{
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(left_center, INPUT);
  pinMode(right_center, INPUT);
 }


//Sensor pathray |Corresponding action
//  1 0 0 1     following the line - go straight
//  1 0 1 1     only left_center sensor on the line - turn left
//  1 1 0 1     only right_center sensor on the line - turn right
//  1 1 0 0     turn right
//  0 0 1 1     turn left 
//  1 0 0 0     turn right (intersection) - should run an extra inch to understand what kind of intersection, if possible - go straight
//  0 0 0 1     turn left (intersection)
//
//  1 1 1 1     no line found - turn 180 degrees
//  0 0 0 0     continuous line - run an extra inch to understand if it is an intersection or end  and go to the left if an intersection

//running an extra inch when making a right turn or having a situation with a continuous line to define what type of intersection it is
//or what is there - an intersection or the end of the maze
void runExtraInch(void)
{
  straight();
  delay(200);
  stop();
}

//implementing the above sensor pathray/action framework 
void loop() {
  if(!analogRead(left)==0 && digitalRead(left_center)==0 && digitalRead(right_center)==0 && digitalRead(right)==0)
     { turn_left();
     }
  else if(!analogRead(left)==0 && !analogRead(left_center)==0 && digitalRead(right_center)==0 && digitalRead(right)==0)
     { turn_left();
     }
  else if(!analogRead(left)==0 && !analogRead(left_center)==0 && digitalRead(right_center)==0 && !analogRead(right)==0)
     { turn_left();
     }

  else if(!analogRead(right)==0 && digitalRead(right_center)==0 && digitalRead(left_center)==0 && digitalRead(left)==0)
     { runExtraInch();
       if (!analogRead(right)==0 && !analogRead(right_center)==0 && !analogRead(left_center)==0 && !analogRead(left)==0){
       turn_right();
       }
       else{
       straight();
       }
     }
  else if(!analogRead(right)==0 && !analogRead(right_center)==0 && digitalRead(left_center)==0 && digitalRead(left)==0)
     { turn_right();
     }
  else if(!analogRead(right)==0 && !analogRead(right_center)==0 && digitalRead(left_center)==0 && !analogRead(left)==0)
     { turn_right();
     }

  else if(!analogRead(right)==0 && digitalRead(right_center)==0 && digitalRead(left_center)==0 && !analogRead(left)==0)
     { straight();
     }
   else if(!analogRead(right)==0 && !analogRead(right_center)==0 && !analogRead(left_center)==0 && !analogRead(left)==0)
     { back();
     }  
  else if(digitalRead(right)==0 && digitalRead(right_center)==0 && digitalRead(left_center)==0 && digitalRead(left)==0)
  {   runExtraInch();
       if (digitalRead(right)==0 && digitalRead(right_center)==0 && digitalRead(left_center)==0 && digitalRead(left)==0){
       delay(5000);
       replay(); 
       }
       else{
       turn_left();
       }
  }
}

//function for turning left 
void turn_left()  
{   
  leftMotor.setSpeed(255); //Define maximum velocity
  leftMotor.run(BACKWARD); //rotate the motor anti-clockwise
  rightMotor.setSpeed(255); //Define maximum velocity
  rightMotor.run(FORWARD);  //rotate the motor clockwise
    
   path[i]='L';
   i++;
   if(path[i-2]=='B')
     { shortcut();
     }
}

//function for going straight  
void straight()                                             
{ 
  leftMotor.setSpeed(255); //Define maximum velocity
  leftMotor.run(FORWARD); //rotate the motor clockwise
  rightMotor.setSpeed(255); //Define maximum velocity
  rightMotor.run(FORWARD);  //rotate the motor clockwise
    
    path[i]='S';
    i++;
    if(path[i-2]=='B')  
      { shortcut();
      }
 }

//function for turning right 
void turn_right()                                                 
{ 
  leftMotor.setSpeed(255); //Define maximum velocity
  leftMotor.run(FORWARD); //rotate the motor clockwise
  rightMotor.setSpeed(255); //Define maximum velocity
  rightMotor.run(BACKWARD); //rotate the motor anti-clockwise
      
  path[i]='R';
  if(path[i-2]=='B')
     { shortcut();
     }
}    

//function for going backward
void back()                                                        
{   
  leftMotor.setSpeed(255); //Define maximum velocity
  leftMotor.run(BACKWARD); //rotate the motor anti-clockwise
  rightMotor.setSpeed(255); //Define maximum velocity
  rightMotor.run(BACKWARD);  //rotate the motor anti-clockwise
       
   path[i]=='B';
    i++;
}

//function that implements the shortcut and removes the unnecessary moves 
void shortcut()                                                  
{  int done=0;
  if(path[i-3]=='L' && path[i-1]=='R')
     { i=i-3;
        path[i]='B';
        done=1;
     }
   if(path[i-3]=='L' && path[i-1]=='S' && done==0)
     { i=i-3;
        path[i]='R';
        done=1;
     }
    if(path[i-3]=='L' && path[i-1]=='L' && done==0)
     { i=i-3;
        path[i]='S';
        done=1;
     }
   if(path[i-3]=='S' && path[i-1]=='L' && done==0)
     { i=i-3;
        path[i]='R';
        done=1;
     }
   if(path[i-3]=='S' && path[i-1]=='S' && done==0)
     { i=i-3;
        path[i]='B';
        done=1;
     }        
   if(path[i-3]=='R'&&path[i-1]=='L'&&done==0)
     { i=i-3;
        path[i]='B';
        done=1;
     }
}

//resolving the maze using the new shortest path 
void replay()                                                
{
   for(j=0,i=0;j<=i,path[i]!='\0';i++,j++)
    { retrace[j]=path[i];
    }
    retrace[j]='\0';
   for(j=0;retrace[j]!='\0';j++)
      {  if(retrace[j]=='L')
         { turn_left();}
        else if(retrace[j]=='R')
          { turn_right();}
        else if(retrace[j]=='S')
          { straight();}
        else if(retrace[j]=='B')
           { back();}
     }
     
  if(digitalRead(right)==0 && digitalRead(right_center)==0 && digitalRead(left_center)==0 && digitalRead(left)==0)
  stop();
}

//function to stop
void stop()                                                         
{     
  leftMotor.setSpeed(0); //Define minimum velocity
  leftMotor.run(RELEASE); //rotate the motor clockwise
  rightMotor.setSpeed(0); //Define minimum velocity
  rightMotor.run(RELEASE); //stop the motor when release the button
} 
