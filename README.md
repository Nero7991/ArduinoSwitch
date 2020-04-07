# ArduinoSwitch
 Arduino Switch allows easy implementation of buttons/switches using just a few lines of code.

 It depends on the ArduinoTimer library internally and needs to be installed as as well.

 It is required that the begin() be called on any instance of TimerClass before begin() is called on an instance of SwitchClass.

 The instance is initialised by calling initializeSwitch(uint8_t pin) and passing pin number as the argument.

 Any of the following functions can be called to get callbacks when the button is pressed in different ways

 The shortPress(Fptr* void(uint8_t)) takes a function with uint8_t as its argument and calls it when 
