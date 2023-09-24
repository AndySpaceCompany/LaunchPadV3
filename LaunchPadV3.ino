/*
  This is the 3rd version of the launch pad software on arduino nano/uno/mega
  github: https://github.com/AndySpaceCompany/LaunchPadV3
*/
//========DEFINE=======
#include <Servo.h>
#define button 4
#define led 17
#define buzz 6
#define mosfet 2
Servo arms;
byte arm = 0; 
boolean button_state = 0;
//========SETUP========
void setup() {
  pinMode(mosfet, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  arms.attach(8);
  arms.write(0);
  int i = 0;
  while (i < 5) {
    i++;
    digitalWrite(led, 1);
    digitalWrite(buzz, 1);
    delay(100);
    digitalWrite(led, 0);
    digitalWrite(buzz, 0);
    delay(900);
  }
}
//==================LOOP=============
void loop() {
  //=======IDLE state=========
  button_state = (!digitalRead(4));
  digitalWrite(led, 1);
  delay(100);
  digitalWrite(led, 0);
  delay(900);
  //======Pendind========
  if (button_state == 1) {
    int l = 0;
    digitalWrite(13, 1);
    while(l < 10) {
      l++;
      digitalWrite(led, 1);
      digitalWrite(buzz, 1);
      delay(100);
      digitalWrite(led, 0);
      digitalWrite(buzz, 0);
      delay(900);
    }
    //======LAUNCH!!!==========
    digitalWrite(led, 1);
    digitalWrite(buzz, 1);
    while (arm < 60) {
      arm++;
      arms.write(arm);
      delay(25);
    }
    delay(1000);
    digitalWrite(buzz, 0);
    digitalWrite(mosfet, 1);
    delay(1000);
    digitalWrite(mosfet, 0);
    digitalWrite(13, 1);
    digitalWrite(led, 0);
    delay(5000);
    while (arm > 0) {
      arm--;
      arms.write(arm);
      delay(50);
    }
  }
}
