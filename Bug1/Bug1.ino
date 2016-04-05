/*
 * 
 * 
 * http://malike.github.io/Design-Thinking-Approach-For-Hobby-Robotic-Project/
 * 
 * 
 * by malike_st
 * 
 * 
 */
 #include <Servo.h>


#define SWITCHBUTTON 7
#define MAN 1
#define MOVE_LEFT 0x1B
#define MOVE_RIGHT 0x1C
#define MOVE_FORWARD 0x1D
#define STOP 0x1E
#define FRONT_SERVO_DATA_PIN 0x02
#define REAR_SERVO_DATA_PIN 0x04
#define SENSOR_ECHO_PIN 0x09
#define SENSOR_TRIGGER_PIN 0x0A
    

int command;
int PREV_SWITCHBUTTON=1;    

void resetLegMovement(struct Bug bug);
void moveForward(struct Bug bug);
void turnLeft(struct Bug bug);  
void turnRight(struct Bug bug);
void stopBug(struct Bug bug);
void senseDistance(struct Bug bug);
void localize(struct Bug bug);

//Bug struct

struct Bug{

  String name;
  Servo frontServo;
  Servo rearServo;
  int bugSpeed;
  long lengOfBug;
  int legCenter;
  int frontRightLegForward;
  int frontLeftLegForward;
  int frontRightLegTurnRight;
  int frontRightLegTurnLeft;
  int frontLeftLegTurnRight;
  int frontLeftLegTurnLeft;  
  int rearRightLegUp;
  int rearLeftLegUp ;
  
     
};

/*
 * create bug1
 */
struct Bug bug1;

/* 
 *  the setup function runs once when you press reset or power the board
 *  
 */
void setup() {
  
  bug1.name="Bug1";
  bug1.legCenter = 90; 
  bug1.frontRightLegForward = 120;
  bug1.frontLeftLegForward = 60;
  bug1.frontRightLegTurnRight = 0;
  bug1.frontRightLegTurnLeft = 0;
  bug1.frontLeftLegTurnRight =0;
  bug1.frontLeftLegTurnLeft = 0;  
  bug1.rearRightLegUp = 70;
  bug1.rearLeftLegUp = 110;
  bug1.bugSpeed = 150;
  
  
  bug1.frontServo.attach(FRONT_SERVO_DATA_PIN);
  bug1.rearServo.attach(REAR_SERVO_DATA_PIN);
       
  Serial.begin(9600);        
  Serial.flush();
  while(Serial.available()){
    Serial.read();
  }
  pinMode(SWITCHBUTTON, INPUT);
  Serial.println("0:-]");
  resetLegMovement(bug1);   
  Serial.println((MAN==0) ? "MANUAL" : "AUTO" +String(" On"));       
}


// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0 && MAN == 0)  {
   if(digitalRead(SWITCHBUTTON) == HIGH){    
    command = Serial.read();
     switch (command) {
        case STOP:
          stopBug(bug1);
         break;
        case MOVE_LEFT:
          turnLeft(bug1);
         break;
       case MOVE_RIGHT:
          turnRight(bug1); 
         break;
       case MOVE_FORWARD:
          moveForward(bug1);
         break;      
       default:
          /*
           * Do nothing here
           */
         break; 
       }         
     }    
    }else{     
       autoMovement(bug1); 
    }        
}     


    


void resetLegMovement(struct Bug bug) {
  bug.frontServo.write(bug.legCenter);
  bug.rearServo.write(bug.legCenter);
  Serial.println(" Movement for "+bug.name+" resetted");      
}

    
void moveForward(struct Bug bug) { 
  bug.frontServo.write(bug.frontRightLegForward);
  bug.rearServo.write(bug.rearLeftLegUp);
  delay(70);       
  resetLegMovement(bug);
  delay(140);               
  bug.frontServo.write(bug.frontLeftLegForward);
  bug.rearServo.write(bug.rearRightLegUp);
  delay(70);               
  resetLegMovement(bug);
  delay(140); 
  Serial.println(bug.name+" moved forward");           
}


void turnLeft(struct Bug bug) {  
  bug.frontServo.write(bug.frontRightLegForward);
  bug.rearServo.write(bug.rearLeftLegUp);
  Serial.println(bug.frontRightLegForward);
  delay(70);      
  resetLegMovement(bug);
  delay(140);       
  bug.frontServo.write(bug.frontLeftLegForward);
  bug.rearServo.write(bug.rearRightLegUp);
  Serial.println(bug.frontLeftLegForward);
  delay(70);             
  resetLegMovement(bug);
  delay(140);
  Serial.println(bug.name+" turned left");                  
}

void turnRight(struct Bug bug) {        
  bug.frontServo.write(bug.frontRightLegForward);
  bug.rearServo.write(bug.rearLeftLegUp);
  Serial.println(bug.frontRightLegForward);
  delay(70);      
  resetLegMovement(bug);
  delay(140);               
  bug.frontServo.write(bug.frontLeftLegForward);
  bug.rearServo.write(bug.rearRightLegUp);
  Serial.println(bug.frontLeftLegForward);
  delay(70);               
  resetLegMovement(bug);
  delay(140);       
  Serial.println(bug.name+" turned right");                  
}

void stopBug(struct Bug bug){
  if(PREV_SWITCHBUTTON == 1){
    Serial.println(bug.name+" stopping. :|");
    PREV_SWITCHBUTTON=0;       
  }
}

   
void senseDistance(struct Bug bug) {
}

void localize(struct Bug bug) {
}


void autoMovement(struct Bug bug){
 if(digitalRead(SWITCHBUTTON) == HIGH){  
    moveForward(bug);
  }else{    
    stopBug(bug);
  }
}  




