#define motor1Dir 7
#define motor2Dir 8
#define motor1PWM 9
#define motor2PWM 10
#define motor1Enable 11
#define motor2Enable 12

#include <avr/interrupt.h>


#include "WProgram.h"
void initMotorDriver();
void setMotorVel(int dirPin, int pwmPin, int velocity);
void setLeftMotorSpeed(int velocity);
void setRightMotorSpeed(int velocity);
void readLineSensor(int * outputArray);
void setup();
void goForward();
void goRight();
void goLeft();
void loop();
void initMotorDriver()
{
  pinMode(motor1Dir, OUTPUT);
  pinMode(motor2Dir, OUTPUT);

  pinMode(motor1Enable, OUTPUT);
  pinMode(motor2Enable, OUTPUT);
  digitalWrite(motor1Enable,HIGH);
  digitalWrite(motor2Enable,HIGH);

}


void setMotorVel(int dirPin, int pwmPin, int velocity){
  if (velocity >= 255) velocity = 255;
  if (velocity <= -255) velocity = -255;

  if (velocity == 0)
  {
    digitalWrite(dirPin, HIGH);
    digitalWrite(pwmPin, HIGH);
  }
  else if(velocity <0){  // Reverse
    digitalWrite(dirPin, HIGH);
    analogWrite(pwmPin, velocity);
  }
  else if(velocity >0){ // Forward
    digitalWrite(dirPin,LOW);
    analogWrite(pwmPin, 255+velocity);
  }
}


void setLeftMotorSpeed(int velocity)
{
  setMotorVel(motor1Dir, motor1PWM, velocity);

}

void setRightMotorSpeed(int velocity){
  setMotorVel(motor2Dir, motor2PWM, velocity);
}


void readLineSensor(int * outputArray)
{
  for (int i =0; i <4; i++)
  {
    outputArray[i] = analogRead(i);
  }
}

void setup(){
  Serial.begin(9600);
  initMotorDriver();
  setLeftMotorSpeed(0);
  setRightMotorSpeed(0);
//  initEncoders();

}

void goForward()
{
  setLeftMotorSpeed(255);
  setRightMotorSpeed(255);
}

void goRight()
{
  setLeftMotorSpeed(255);
  setRightMotorSpeed(-100);
}

void goLeft()
{
  setLeftMotorSpeed(-100);
  setRightMotorSpeed(255);
}



void loop()
{

  int sensors[4];

  readLineSensor(sensors);

  Serial.print("Sensor Values : " );

  for (int i =0; i <4; i++)
  {
    Serial.print( sensors[i]);
    Serial.print(" " );
  }

  Serial.println(" ");

  if(( sensors[0] <200) || (sensors[1] <200))  // 250 is a measured threshold between white & black
  {
    goLeft();
    delay(100);
  }
   else if(( sensors[2] <200) || (sensors[3] <200))
  {
    goRight();
    delay(100);
  }
  else
  goForward();
  
  delay(100);
  
  
}




int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

