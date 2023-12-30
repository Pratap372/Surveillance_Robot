#include <NewPing.h> 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 
NewPing sonar(D6, D5);

char auth[] = "ENTER BLYNK AUTH CODE";
char ssid[] = "ENTER YOUR WI-FI NAME";
char pass[] = "ENTER YOUR WIFI PASSWORD";
long distance;

int IN1 = D8;
int IN2 = D7;
int IN3 = D4;
int IN4 = D3;
int EN1 = D2;  
               // Pin 1 of L293D IC, D6 Pin of NodeMCU
int EN2 = D1; 
const int autopin = D0;

BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
  // MOVE TO GET DATA
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);
  
// Joystick Movement
  if (y>350)
  {
    Serial.print("forward");
    forward(1);
  }
  if (y<170) 
    {
      Serial.print("backward");
      backward(1);
    }
   if (x<132)
    {
      Serial.print("left");
      turnLeft(1);
    }
  if (x>380) 
    {
      Serial.print("right");
      turnRight(1);
    }
  if ((y==256) && (x==256))
    {
      Serial.print("stop");
      brake(1);
     }
}


BLYNK_WRITE(V2)
{
  int speed = param.asInt(); // assigning incoming value from pin V2 to a variable
    analogWrite(EN1, speed);//sets the motors speed
    analogWrite(EN2, speed);//sets the motors speed
}
void setup()
{ 
pinMode(EN1, OUTPUT);   
pinMode(EN2, OUTPUT); 
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
}
void loop() {
  if (autopin==HIGH ){
autopilot();
}
else
{
Blynk.run();
}
}

//functions 
void autopilot()
{
 delay(50);
distance = sonar.ping_cm();
if (distance < 30 ) {

for (int i = 0; i <= 300; i++) {
backward(1);
}

for (int i = 0; i <= 300; i++) {
coast(1);
}

for (int i = 0; i <= 500; i++) {
turnLeft(1);
}
forward(1);
}
else {
forward(1);
}
}
void forward(int time)
{
motorAForward();
motorBForward();
delay(time);
}
void backward(int time)
{
motorABackward();
motorBBackward();
delay(time);
}
void turnLeft(int time)
{
motorABackward();
motorBForward();
delay(time);
}
void turnRight(int time)
{
motorAForward();
motorBBackward();
delay(time);
}
void coast(int time)
{
motorACoast();
motorBCoast();
delay(time);
}
void brake(int time)
{
motorABrake();
motorBBrake();
delay(time);
}

void motorAForward()
{
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
}

void motorABackward()
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
}
void motorBForward()
{
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void motorBBackward()
{
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void motorACoast()
{
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
}
void motorABrake()
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
}
void motorBCoast()
{
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void motorBBrake()
{
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
 
