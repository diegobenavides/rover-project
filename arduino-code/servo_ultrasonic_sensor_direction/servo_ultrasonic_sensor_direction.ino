#include <Servo.h>

#define SERVODELAY 3
#define MEASUREMENTINTERVAL 30
#define SERVOPIN 11
#define USSENSORPIN 2
#define MINDIST 8
#define MOTOR_A1 3  
#define MOTOR_A2 5
#define MOTOR_B1 6
#define MOTOR_B2 9
#define N_SAMPLES 6 // number of samples that the sensor are going to take

Servo myservo;

int pos = 0;
int last_measurement_position = 0;
float dist = 0;
int angle = 15;
int *current_angle = &angle;
int dir = 1;
int *current_dir = &dir;
float field_vision[N_SAMPLES];


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
  for(pos = 0; pos <= 5; pos += 1){
  Serial.println(field_vision[pos]);
  }
  delay(1500);
  
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

void update_course(int pos, int dist){

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
void servo_move(int angle,int dir1){
  
  switch(angle){
    myservo.write(angle);
    case(15):
      Serial.println("15 degrees");
      *current_angle = 45;
      *current_dir = 1;
      field_vision[0] = us_distance(USSENSORPIN);
      break;  
    case(45):
      Serial.println("45 degrees");
      field_vision[1] = us_distance(USSENSORPIN);
      if (dir1 == 1){
        *current_angle = 75;
      }
      else{
        *current_angle = 15;
      }
      break;
    case(75):
      Serial.println("75 degrees");
      field_vision[2] = us_distance(USSENSORPIN);
      if (dir1 == 1){
        *current_angle = 105;
      }
      else{
        *current_angle = 45;
      }
      break;
    case(105):
      Serial.println("105 degrees");
      field_vision[3] = us_distance(USSENSORPIN);
      if (dir1 == 1){
        *current_angle = 135;
      }
      else{
        *current_angle = 75;
      }
      break;
    case(135):
      
      Serial.println("135 degrees");
      field_vision[4] = us_distance(USSENSORPIN);
      if (dir1 == 1){
        *current_angle = 165;
      }
      else{
        *current_angle = 105;
      }
      break;
    case(165):
      Serial.println("165 degrees");
      field_vision[5] = us_distance(USSENSORPIN);
      *current_angle = 135;
      *current_dir = -1;
      break;
    default:
      Serial.println("Defaut State");
      break;
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
      Serial.print("Case 0");
      standby(t);
      break;
    case (1):
      Serial.print("Case 1");
      move_foward(t);
      break;
    case (2):
      Serial.print("Case 2");
      move_back(t);
      break;
    case (3):
      Serial.print("Case 3");
      move_left(t);
      break;
    case (4):
      Serial.print("Case 4");
      move_right(t);
      break;
    default: 
      Serial.print("Default");
      break;
  }
}

