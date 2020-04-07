# ArduinoSwitch
 Arduino Switch allows easy implementation of buttons/switches using just a few lines of code.
 It depends on the ArduinoTimer library internally and needs to be installed as as well.
* It is required that the begin() be called on any instance of TimerClass before begin() is called on an instance of SwitchClass.
 * The instance is initialised by calling initializeSwitch(uint8_t pin) and passing pin number as the argument.

```
#include <Switch.h>
volatile const uint8_t ToggleLedButton = 6;
TimerClass T1;
SwitchClass S1;
void setup() {
  T1.begin();       //It's necessary to call begin on any TimerClass object first, then SwitchClass object
  S1.begin();
  S1.initializeSwitch(ToggleLedButton);
  S1.shortPress(toggleLed);
  S1.longPress(toggleBlinking);
}
```
 ##### Any of the following functions can be called to get callbacks when the button is pressed in different ways. The code in these callback function should be written as if it were an ISR
 * shortPress(Fptr* void(uint8_t)) takes a function with uint8_t as its argument and calls it when the button is pressed once or short pressed with the switch id.
 ```
 void toggleLed(uint8_t buttonId){
    if(LedState)
    digitalWrite(LedPin, LOW);
    else
    digitalWrite(LedPin, HIGH);
    LedState ^= 1;
}
 S1.shortPress(toggleLed);
 ```
 * doublePress(Fptr* void(uint8_t)) takes a function pointer with uint8_t as its argument and calls it when the button is pressed twice quickly passing the switch id.
 * longPress(Fptr* void(uint8_t)) takes a function pointer with uint8_t as its argument and calls it when the button is held pressed  for a certain time passing the switch id.
 * continuousLongPress(Fptr* void(uint8_t)) takes a function pointer with uint8_t as its argument and continuously calls it every 70ms while button is held pressed.
 
##### Functions to be added
* Add callback for rising and falling on the pin the switch is connected to.

##### Example code:(Also included in the examples folder as a .ino file)
  Can be driectly copied in a new sketch
```
#include <Arduino.h>
#include <Switch.h>

TimerClass T1;
SwitchClass S1;

volatile const uint8_t LedPin = 13;
volatile const uint8_t ToggleLedButton = 6;
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
  S1.initializeSwitch(ToggleLedButton);
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
```
