#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"
#include <OneButton.h>
#include <SoftwareSerial.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


OneButton sensors[7] = {OneButton(14, true), OneButton(15, true), 
                        OneButton(16, true), OneButton(17, true),
                        OneButton(18, true), OneButton(19, true),
                        OneButton(3, true)};
//unsigned long timer = 0;
bool completed = false;
uint8_t num = 0;

// put function declarations here:
void myFunction();

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  for (uint8_t i = 0; i<7; i++){
    sensors[i].attachLongPressStart(myFunction);
    sensors[i].setPressTicks(30);

  }
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card or USB drive!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);
}

void loop() {
  if (completed) return;
  for (uint8_t i = 0; i<7; i++){
    num = i+1;
    sensors[i].tick();
  }
  
  //if (millis()>timer){
  //  digitalWrite(13, LOW);
  //}
  bool allDone = true;
  for (uint8_t i = 0; i<7; i++){
    if (!sensors[i].isLongPressed()) allDone = false;
  }
  if (allDone){
    completed = true;
    digitalWrite(2, LOW);
    //myDFPlayer.playMp3Folder(8);
    return;
  }
}

// put function definitions here:
void myFunction() {
  myDFPlayer.playMp3Folder(num);
}