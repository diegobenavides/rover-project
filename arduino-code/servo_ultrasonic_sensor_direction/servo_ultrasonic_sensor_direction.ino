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
#define MOTOR_B2 12
#define MAX_DISTANCE 200 
#define N_SAMPLES 6 // number of samples that the sensor is going to take
#define TRIGGER_PIN  8 
#define ECHO_PIN     11 
#define INTERVAL 100 //Time define between samples in dist sensor
#define DELAY 50
#define BIGDELAY 1000000


/*==============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/

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
float test_array[N_SAMPLES] = {11.11,12.22,23.33,44.44,55.55,66.66};
unsigned long next_meas = millis() + INTERVAL;

/*==============================================================================
 *SETUP()
 *============================================================================*/

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


/*==============================================================================
 *LOOP()
 *============================================================================*/

void loop()
{
  d();
  //serial_communication();
  
  //This is working fine
  
  
  if (next_meas <= millis()) {
    next_meas = millis() + INTERVAL;
    servo_move(*current_angle,*current_dir);
  
  }
  serial_communication();
  //evade_obst(field_vision);
  
  
  
  /*
  
  servo_move(*current_angle,*current_dir);
 
  /*Serial.println("Here Start ");

  
 
 /* 
  //ord(90); 
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
*/  
   
}


/*==============================================================================
 *FUNCTIONS                                                                
 *============================================================================*/
 
void evade_obst(float arr[]){
 
  for(pos = 0; pos <= 5; pos += 1){
   Serial.println(arr[pos]);
  }
  if (arr[2] < MIN_DIST){
      Serial.println(arr[2]);
      Serial.println("in 2");
    if (arr[3]< MIN_DIST){
      return standby();
    }
    else{
      return move_left();
    }
  }
  if (arr[3]< MIN_DIST){
      Serial.println("in 3");
      return move_right();
    }
}     


//THIS MODULE IS TO TALK WITH THE ARDUINO AND NEGOCIATE FOR THE INFORMATION AND CONTROL
void serial_communication(){
  char inByte = Serial.read();
  if(Serial.available() == 0)
  {
    //Serial.println(inByte);
    switch(inByte){
      case ('q'):
        
        Serial.println(field_vision[0]);
        /*
        for(pos = 0; pos <= 5; pos += 1){
          Serial.println(field_vision[pos]);             
        }
        */
        break;
      case ('w'):
        Serial.println(test_array[1]);
        break;
      case ('t'):
        Serial.println(test_array[2]);
        break;
      case ('y'):
        Serial.println(test_array[3]);
        break;
      case ('u'):
        Serial.println(test_array[4]);
        break;
      case ('i'):
        Serial.println(test_array[5]);
        break;
      default: 
       set_state(inByte);
       break;
    }
  }
}

//FUNCTION CREATE TO MAKE A BIG DELAY JUST TO DEBUG
void d()
{
  delay(BIGDELAY);
}
//FUNCTION TO KNOW THE DISTANCE FIRST DISTANCE SENSOR
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
//FUNCTION TO TAKE THE DISTANCE OF THE FIRST DISTANCE SENSOR "3 PINS"
void distance_measurement(int pos){

  Serial.print(" Position: ");
  Serial.print(pos);
  Serial.print(" Distance: ");
  dist = us_distance(USSENSORPIN);
  Serial.print(dist);
  Serial.println(" cm");
  last_measurement_position=pos;

}

//FUNCTION TO TAKE THE DISTANCE 
float cm_dist_HC(){

  delay(50);                    
  unsigned int uS = sonar.ping();
  unsigned int dist;
  dist = uS / US_ROUNDTRIP_CM;
  return (dist);
}

//FUNCTION TO KNOW THE MEASURE OF THE DISTANCE SENSOR
void distance_measurement_HC(float print_distance){
  
  Serial.print("Ping: ");
  Serial.print(print_distance);
  Serial.println("cm");
}


//FUNCTION TO SELECT THE CHANGE TO THE DIFFERENT ANGLES TO MAKE THE MEASURE OF THE 
//DISTANCE SENSOR
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
      break;
  }
}

//FUNCTION TO SELECT THE STATES
void set_state(int state){
  switch (state) {
    case ('s'):
      standby();
      delay(DELAY);
      break;
    case ('f'):
      move_foward();
      delay(DELAY);
      break;
    case ('b'):
      move_back();
      delay(DELAY); 
      break;
    case ('l'):
      move_left();
      delay(DELAY);
      
      break;
    case ('r'):
      move_right();
      delay(DELAY);
      
      break;
    default:
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

//FIRST FUNCTION CREATE TO MOVE THE SERVO
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

//FUNCTION TO CENTER THE SERVO TO 90 DEGREES
void ord(int ang){
  myservo.write(ang);
  d();
}


