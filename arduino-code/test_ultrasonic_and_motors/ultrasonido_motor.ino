int us_pin = 8; // connected to the Trig on the module, this serves as both Trigger and Echo
int motor0 = 11;
int motor1 = 10;
float dist = 0;

void setup()
{
Serial.begin(115200);
pinMode(us_pin, OUTPUT);
pinMode(motor0, OUTPUT);
pinMode(motor1, OUTPUT);
digitalWrite(us_pin, HIGH); // Trig pin is normally HIGH
}

float us_distance()
{
  unsigned long time;
  unsigned long sizeofpulse;
  float distance;
  
  pinMode(us_pin, OUTPUT); //return digital pin to OUTPUT mode after reading
  digitalWrite(us_pin, LOW);
  delayMicroseconds(25);
  digitalWrite(us_pin, HIGH); //Trig pin pulsed LOW for 25usec
  time = micros(); //record timer
  pinMode(us_pin, INPUT); //change pin to INPUT to read the echo pulse 
  sizeofpulse = pulseIn(us_pin, LOW, 18000); //should be approx 150usec, timeout at 18msec
  time = micros() - time - sizeofpulse; // amount of time elapsed since we sent the trigger pulse and detect the echo pulse, then subtract the size of the echo pulse
  distance = (time*340.29/2/10000)-3; // convert to distance in centimeters
  return distance;
}

void loop()
{
  Serial.print(" Distance: ");
  dist = us_distance();
  Serial.print(dist);
  Serial.println(" cm");
  if (dist <= 10) {
    digitalWrite(motor0, LOW);
    digitalWrite(motor1, HIGH);
  } else if (dist >= 40) {
    digitalWrite(motor1, LOW);
    digitalWrite(motor0, HIGH);
  } else {
    digitalWrite(motor1, LOW);
    digitalWrite(motor0, LOW);
  }    
  delay(100);
}
