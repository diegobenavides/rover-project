#include <Servo.h>
#include <NewPing.h>

#define SERVODELAY 3
#define MEASUREMENTINTERVAL 30
#define SERVOPIN 3
#define USSENSORPIN 2
#define MINDIST 8
#define MOTOR_A1 2  
#define MOTOR_A2 4
#define MOTOR_B1 7
#define MOTOR_B2 8
#define MAX_DISTANCE 200 
#define N_SAMPLES 6 // number of samples that the sensor is going to take
#define TRIGGER_PIN  12 
#define ECHO_PIN     11 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;

int pos = 0;
int last_measurement_position = 0;
float dist = 0;
int angle = 15;
int *current_angle = &angle;
int dir = 1;
int *current_dir = &dir;
float field_vision[N_SAMPLES];
float MIN_DIST = 25;
float us_distance(int us_pin);
void distance_measurement(int pos);
void update_course(int pos, int dist);
void sweep_sensor();
void moveFoward();
void moveBack();
void moveLeft();
void moveRight();
void standby();
void set_state();
void servo_move(int angle,int dir1);
char actions = ' ';

void setup()
{
  myservo.attach(SERVOPIN);
  Serial.begin(9600);
  pinMode(USSENSORPIN, OUTPUT);
  digitalWrite(USSENSORPIN, HIGH);
  
  pinMode(MOTOR_A1, OUTPUT);
  digitalWrite(MOTOR_A1, LOW);
  pinMode(MOTOR_A2, OUTPUT);
  digitalWrite(MOTOR_A2, LOW);
  pinMode(MOTOR_B1, OUTPUT);
  digitalWrite(MOTOR_B1, LOW);
  pinMode(MOTOR_B2, OUTPUT);
  digitalWrite(MOTOR_B2, LOW);
  Serial.print("ROVER PROYECT INITIALIZE\n");
}


void loop()
{
  Serial.println(Serial.available());
  serial_communication();
  
  delay(500);   
  /*
  servo_move(*current_angle,*current_dir);
  delay(100);
  
  for(pos = 0; pos <= 5; pos += 1){
    
    Serial.println(field_vision[pos]);
    if (field_vision[pos] > MIN_DIST){
      Serial.println("M");
    }else{
      Serial.println("m..............");
    }
    
  }

  servo_move(75,1);
  distance_measurement_HC();
  delay(500);
  servo_move(105,1);
  distance_measurement_HC();
  delay(500);
  servo_move(135,1);
  distance_measurement_HC();
  delay(500);
  servo_move(165,1);
  distance_measurement_HC();
  delay(500);

  
  Serial.println("Print the data in array: ");
  for(pos = 0; pos <= 5; pos += 1){
    Serial.println(field_vision[pos]);
  }
  delay(1500);
  
  
   actions = 's';
  while(Serial.available()>0){
    actions = Serial.read(); 
  }
  
  set_state(actions); 
  delay(500); 
   move_foward(800);
   standby(5000);
   move_back(800);
   standby(5000);
   
   standby(10);
   delay(1000);
   move_back(10);
   delay(1000);
   move_left(10);
   delay(1000);
   move_right(10);
   delay(1000);  
   */
   
   
}

void serial_communication(){
  char inByte = Serial.read();
  if(Serial.available() == 0)
  {
    switch(inByte){
  
    case ('s'):
      Serial.println("Reading");//Reading data from arduino
      break;
    case ('f'):
      Serial.println("Move Foward");
      set_state(inByte);
      break;
    case ('b'):
      Serial.println("Move back");
      set_state(inByte);
      break;
    case ('l'):
      Serial.println("Turn left");
      set_state(inByte);
      break;
    case ('r'):
      Serial.println("Turn right");
      set_state(inByte);
      break;
    default: 
      Serial.println("Default");
      set_state(inByte);
      break;
    }
  }
}

void d()
{
  delay(100000);
}

float us_distance(int us_pin)
{
  unsigned long time;
  unsigned long sizeofpulse;
  float distance;

  pinMode(us_pin, OUTPUT);
  digitalWrite(us_pin, LOW);
  delayMicroseconds(25);
  digitalWrite(us_pin, HIGH);
  time = micros();
  pinMode(us_pin, INPUT);
  sizeofpulse = pulseIn(us_pin, LOW, 18000);
  time = micros() - time - sizeofpulse;
  distance = (time*340.29/2/10000)-3;
  return distance;
}
void distance_measurement(int pos){

  Serial.print(" Position: ");
  Serial.print(pos);
  Serial.print(" Distance: ");
  dist = us_distance(USSENSORPIN);
  Serial.print(dist);
  Serial.println(" cm");
  last_measurement_position=pos;

}


float cm_dist_HC(){

  delay(50);                    
  unsigned int uS = sonar.ping();
  unsigned int dist;
  dist = uS / US_ROUNDTRIP_CM;
  return (dist);
}

void distance_measurement_HC(float print_distance){
  
  Serial.print("Ping: ");
  Serial.print(print_distance);
  Serial.println("cm");
}


void update_course(int pos, int dist){

}


void servo_move(int angle,int dir1){
  switch(angle){
    case(15):
      myservo.write(angle);
      field_vision[0] = cm_dist_HC();
      *current_angle = 45;
      *current_dir = 1;
      break;
    case(45):
      myservo.write(angle);
      field_vision[1] = cm_dist_HC();
      if (dir1 == 1){
        *current_angle = 75;
      }
      else{
        *current_angle = 15;
      }
      break;
    case(75):
      myservo.write(angle);
      field_vision[2] = cm_dist_HC();
      if (dir1 == 1){
        *current_angle = 105;
      }
      else{
        *current_angle = 45;
      }
      break;
    case(105):
      myservo.write(angle);
      field_vision[3] = cm_dist_HC();
      if (dir1 == 1){
        *current_angle = 135;
      }
      else{
        *current_angle = 75;
      }
      break;
    case(135):
      myservo.write(angle);
      field_vision[4] = cm_dist_HC();
      if (dir1 == 1){
        *current_angle = 165;
      }
      else{
        *current_angle = 105;
      }
      break;
    case(165):
      myservo.write(angle);
      field_vision[5] = cm_dist_HC();
      *current_angle = 135;
      *current_dir = -1;
      break;
    default:
      Serial.println("Defaut State");
      break;
  }
}

void set_state(int state){
  switch (state) {
    case ('s'):
      Serial.println("Standby");
      standby();
      break;
    case ('f'):
      Serial.println("Move Foward");
      move_foward();
      break;
    case ('b'):
      Serial.println("Move back");
      move_back();
      break;
    case ('l'):
      Serial.println("Turn left");
      move_left();
      break;
    case ('r'):
      Serial.println("Turn right");
      move_right();
      break;
    default: 
      Serial.println("Default");
      standby();
      break;
  }
}


//STATES OF THE MACHINE
void move_foward(){
  digitalWrite(MOTOR_A1,HIGH);
  digitalWrite(MOTOR_A2,LOW);
  digitalWrite(MOTOR_B1,HIGH);
  digitalWrite(MOTOR_B2,LOW);
}

void move_back(){
  digitalWrite(MOTOR_A1,LOW);
  digitalWrite(MOTOR_A2,HIGH);
  digitalWrite(MOTOR_B1,LOW);
  digitalWrite(MOTOR_B2,HIGH);
}

void move_left(){
  digitalWrite(MOTOR_A1,HIGH);
  digitalWrite(MOTOR_A2,LOW);
  digitalWrite(MOTOR_B1,LOW);
  digitalWrite(MOTOR_B2,HIGH);
}

void move_right(){
  digitalWrite(MOTOR_A1,LOW);
  digitalWrite(MOTOR_A2,HIGH);
  digitalWrite(MOTOR_B1,HIGH);
  digitalWrite(MOTOR_B2,LOW);
  
}

void standby(){
  digitalWrite(MOTOR_A1,LOW);
  digitalWrite(MOTOR_A2,LOW);
  digitalWrite(MOTOR_B1,LOW);
  digitalWrite(MOTOR_B2,LOW);
  
}


void sweep_sensor(){

  for(pos = 1; pos <= 180; pos += 1)
  {
    myservo.write(pos);
    if(pos >= last_measurement_position+MEASUREMENTINTERVAL){
      distance_measurement(pos);
      update_course(pos, dist);
    }
    delay(SERVODELAY);
  }
  for(pos = 180; pos>=0; pos-=1)
  {
    myservo.write(pos);
    if(pos <= last_measurement_position-MEASUREMENTINTERVAL){
      distance_measurement(pos);
      update_course(pos, dist);
    }
    delay(SERVODELAY);
  }
  
}



