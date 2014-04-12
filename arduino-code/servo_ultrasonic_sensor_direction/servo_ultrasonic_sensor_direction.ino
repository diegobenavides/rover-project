#include <Servo.h>

#define SERVODELAY 3
#define MEASUREMENTINTERVAL 30
#define SERVOPIN 11
#define USSENSORPIN 2 //Pata del MEGA cambiar al UNO
#define MINDIST 8
#define MOTOR_A1 3
#define MOTOR_A2 5
#define MOTOR_B1 6
#define MOTOR_B2 9

Servo myservo;
 
int pos = 0;
int interval = 20 ;
int last_measurement_position = 0;
float dist = 0;

float us_distance(int us_pin);
void distance_measurement(int pos);
void update_course(int pos, int dist);
void sweep_sensor();
void moveFoward();
void moveBack();
void moveLeft();
void moveRight();
void standby();
void get_state();

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
}


void loop()
{
  //sweep_sensor();
  set_state(1,1000);
  set_state(2,1000);
  set_state(4,1000);
  set_state(3,1000);
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
  Serial.print(" °\n");
  Serial.print(" Distance: ");
  dist = us_distance(USSENSORPIN);
  Serial.print(dist);
  Serial.println(" cm");
  last_measurement_position=pos;

}

void update_course(int pos, int dist){
  /*
  if (pos < 60){
    if (dist < MINDIST) {
      digitalWrite(RIGHTPIN, HIGH);
    }
  } else if (pos < 120){
    if (dist < MINDIST) {
      digitalWrite(BACKWARDPIN, HIGH);
    } else {
      digitalWrite(FORWARDPIN, HIGH);
    }
  } else {
    if (dist < MINDIST) {
      digitalWrite(LEFTPIN, HIGH);
    }
  }
*/
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

//STATES OF THE MACHINE
void move_foward(int t){
  digitalWrite(MOTOR_A1,HIGH);
  digitalWrite(MOTOR_A2,LOW);
  digitalWrite(MOTOR_B1,HIGH);
  digitalWrite(MOTOR_B2,LOW);
  delay(t);
}

void move_back(int t){
  digitalWrite(MOTOR_A1,LOW);
  digitalWrite(MOTOR_A2,HIGH);
  digitalWrite(MOTOR_B1,LOW);
  digitalWrite(MOTOR_B2,HIGH);
  delay(t);
}

void move_left(int t){
  digitalWrite(MOTOR_A1,HIGH);
  digitalWrite(MOTOR_A2,LOW);
  digitalWrite(MOTOR_B1,LOW);
  digitalWrite(MOTOR_B2,HIGH);
  delay(t);
}

void move_right(int t){
  digitalWrite(MOTOR_A1,LOW);
  digitalWrite(MOTOR_A2,HIGH);
  digitalWrite(MOTOR_B1,HIGH);
  digitalWrite(MOTOR_B2,LOW);
  delay(t);
}

void standby(int t){
  digitalWrite(MOTOR_A1,LOW);
  digitalWrite(MOTOR_A2,LOW);
  digitalWrite(MOTOR_B1,LOW);
  digitalWrite(MOTOR_B2,LOW);
  delay(t);
}

void set_state(int state,int t){
  switch (state) {
    case (0):
    Serial.print("Case1");
    standby(t);
    break;
    case (1):
    Serial.print("Case1");
    move_foward(t);
    break;
    case (2):
    Serial.print("Case2");
    move_back(t);
    break;
    case (3):
    Serial.print("Case3");
    move_left(t);
    break;
    case (4):
    Serial.print("Case4");
    move_right(t);
    break;
    default: 
      Serial.print("Default");
  }
}

