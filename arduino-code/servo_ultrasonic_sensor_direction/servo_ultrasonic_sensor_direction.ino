#include <Servo.h> 

#define SERVODELAY 3
#define MEASUREMENTINTERVAL 20
#define SERVOPIN 22
#define USSENSORPIN 23

#define FORWARDPIN 50
#define BACKWARDPIN 51
#define LEFTPIN 52
#define RIGHTPIN 53
#define MINDIST 8

Servo myservo; 
 
int pos = 0;
int interval = 20 ;
int last_measurement_position = 0;
float dist = 0;
 
void setup() 
{ 
  myservo.attach(SERVOPIN);
  Serial.begin(115200);
  pinMode(USSENSORPIN, OUTPUT);
  digitalWrite(USSENSORPIN, HIGH);
  pinMode(FORWARDPIN, OUTPUT);
  digitalWrite(FORWARDPIN, LOW);
  pinMode(BACKWARDPIN, OUTPUT);
  digitalWrite(BACKWARDPIN, LOW);
  pinMode(LEFTPIN, OUTPUT);
  digitalWrite(LEFTPIN, LOW);
  pinMode(RIGHTPIN, OUTPUT);
  digitalWrite(RIGHTPIN, LOW);
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
  digitalWrite(FORWARDPIN, LOW);
  digitalWrite(BACKWARDPIN, LOW);
  digitalWrite(LEFTPIN, LOW);
  digitalWrite(RIGHTPIN, LOW);
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
}

void loop() 
{ 
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
