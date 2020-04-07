#include <Arduino.h>
#include <Switch.h>

TimerClass T1;
SwitchClass S1;

volatile const uint8_t LedPin = 13;
volatile const uint8_t ToggleLed = 6;
volatile const uint8_t BlinkToggle = A5;
volatile bool LedState = false, BlinkEnabled = false, SleepEnabled = true;

void toggleLed(uint8_t Id){
    if(LedState)
    digitalWrite(LedPin, LOW);
    else
    digitalWrite(LedPin, HIGH);
    LedState ^= 1;
}

void timerDone(uint8_t id){
    if(BlinkEnabled)
    toggleLed(0);
}

void toggleBlinking(uint8_t switchId){
    BlinkEnabled ^= 1;
}

void sleep(){
  T1.powerDown(SLEEP_MODE_IDLE);          //Stop CPU and FLASH clocks (Using other sleep modes causes delay in wake up)
}

void setup() {
  pinMode(LedPin, OUTPUT);
  Serial.begin(9600); Serial.println("Setting up things...");
  T1.begin();                             //It's necessary to call begin on any TimerClass object first, then SwitchClass object
  T1.initializeTimer();
  T1.setCallBackTime(500, TIMER_MODE_REPEAT, timerDone);
  S1.begin();
  S1.initializeSwitch(ToggleLed);
  S1.shortPress(toggleLed);
  S1.longPress(toggleBlinking);
  Serial.println("Done.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SleepEnabled){
    sleep();
  }
}
