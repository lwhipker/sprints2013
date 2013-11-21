// Arduino PWM Speed Control：
// Pin definitions for PWM speed control using 
// DFRobot Arduino Compatible Motor Shield (2A):

#include "MotorRobotBase.h"
#include "Sensor.h"

#define Motor MotorRobotBase

void forward (Motor &m1, Motor &m2) 
{
  int speed; 
  // speed up
  for (speed = 0; speed <= 255; speed += 5) {
    m1.forward(speed);
    m2.forward(speed);
    delay(30); 
  }
  // speed down
  for (speed = 255; speed >= 0; speed -= 5) {
    m1.forward(speed);
    m2.forward(speed);
    delay(30);
  }
}

void backward (Motor &m1, Motor &m2) 
{
  int speed; 
  // speed up
  for (speed = 0; speed <= 255; speed += 5) {
    m1.reverse(speed);
    m2.reverse(speed);
    delay(30); 
  }
  // speed down
  for (speed = 255; speed >= 0; speed -= 5) {
    m1.reverse(speed);
    m2.reverse(speed);
    delay(30);
  }
}

void twist_right (Motor &m1, Motor &m2) 
{
  int speed; 
  // speed up
  for (speed = 0; speed <= 255; speed += 5) {
    m1.forward(speed);
    m2.reverse(speed);
    delay(30); 
  }
  // speed down
  for (speed = 255; speed >= 0; speed -= 5) {
    m1.forward(speed);
    m2.reverse(speed);
    delay(30);
  }
}

void twist_left (Motor &m1, Motor &m2) 
{
  int speed; 
  // speed up
  for (speed = 0; speed <= 255; speed += 5) {
    m1.reverse(speed);
    m2.forward(speed);
    delay(30); 
  }
  // speed down
  for (speed = 255; speed >= 0; speed -= 5) {
    m1.reverse(speed);
    m2.forward(speed);
    delay(30);
  }
}

void go_right(Motor &m1, Motor &m2) 
{
     m1.reverse(0);
     m2.reverse(30); 
}

void go_left(Motor &m1, Motor &m2) 
{
     m1.reverse(30);
     m2.reverse(0);
}
void go_straight(Motor &m1, Motor &m2) 
{
     m1.reverse(30);
     m2.reverse(30);
}

Motor right_motor(Motor::MOTOR_1);
Motor left_motor(Motor::MOTOR_2);
Sensor center_light(Sensor::SENSOR_0);
Sensor right_light(Sensor::SENSOR_3);

/* int avg_illumination = 511;  */

void setup () 
{ 
  int ii;
  int current_level;
  
  Serial.begin(9600);
  
  right_motor.setup();
  left_motor.setup();
  center_light.setup();
  center_light.set_mode(Sensor::SIMPLEX_MODE);
  center_light.calibrate();
  right_light.setup();
  right_light.set_mode(Sensor::SIMPLEX_MODE);
  right_light.calibrate();

} 

void loop () 
{
  int center_light_level;
  int right_light_level;
  int center_d;
  int right_d;
  
  char light_str[255];
  
  #define RT_SENSE 100
  #define CT_SENSE 100
  
  center_light.read(center_light_level);
  center_d = center_light_level - center_light.get_light_level();
  right_light.read(right_light_level);
  right_d = right_light_level - right_light.get_light_level();
  Serial.print(center_d);
  Serial.print(":");
  Serial.print(center_light_level);
  Serial.print("\n");
  Serial.print(right_d);
  Serial.print(":");
  Serial.print(right_light_level);
  Serial.print("\n");
  
  int right = 0;
  int center = 0;
  

  if (abs(center_d)>=CT_SENSE) {
      center = 1;
  }
  if (abs(right_d)>=RT_SENSE) {
      right = 1;
  }
  
  if (right && !center) {
     go_right(left_motor, right_motor);
  }
  if (center && !right) {
     go_left(left_motor, right_motor);
  }
  if (!center && !right) {
     go_straight(left_motor, right_motor);
  }
  if (center && right) {
     go_right(left_motor, right_motor);    
  }
  
/*
  if (light_level > 1000) {  
    Serial.write("1000\n");    
  } else  if (light_level > 900) {  
    Serial.write("900\n");    
  } else  if (light_level > 800) {  
    Serial.write("800\n");    
  } else  if (light_level > 700) {  
    Serial.write("700\n");    
  }  else  if (light_level > 600) {  
    Serial.write("600\n");    
  }  else  if (light_level > 500) {  
    Serial.write("500\n");    
  }  else  if (light_level > 400) {  
    Serial.write("400\n");    
  }  else  if (light_level > 300) {  
    Serial.write("300\n");    
  }  else  if (light_level > 200) {  
    Serial.write("200\n");    
  }  else  if (light_level > 100) {  
    Serial.write("100\n");    
  }   else  { 
    Serial.write("00\n");    
  } 
*/
  
  delay(30);
}



