/*
 * Switch.h
 *
 * Created: 11/3/2017 2:10:34 PM
 *  Author: orencollaco
 * 
 * MIT License

Copyright (c) 2020 Oren Collaco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 * 
 * 
 */ 


#ifndef SWITCH_H_
#define SWITCH_H_

////#include "Essential.h"
#include "Timer.h"

class SwitchClass{
	
 public:
	
		static uint8_t SwitchState, i, PinBuffer[3];
		
		static bool NotFirstSpawn, AllSamePtr_EN, AllShort_EN, AllLong_EN, AllDouble_EN, AllContinuousLong_EN, AllFallingEdge_EN, AllRisingEdge_EN;
		
		static SwitchClass *Sptr[8];
		
		static Fptr AllShortPressPtr, AllLongPressPtr, AllDoublePressPtr, AllContinuousLongPressPtr, AllRisingEdgePtr, AllFallingEdgePtr, PinStateChangePtr;
		
		static void begin();
		
		static void callOnPinStateChange(Fptr);
		
		static void doNothing(uint8_t);
		
		static void callAllOjectLongWait(uint8_t timer_ID);
		
		static void callAllProcessStateChange();
		
		static void callAllDoubleWait(uint8_t timer_ID);
		
		static void pollAllSwitches();
		
		static void enableSamePtrMode(bool set);
		
		static void pinStateChanged();

		static void setPinChangeInterrupt(uint8_t Pin);
		
		
		TimerClass aTimer;
		
		Fptr ShortPressPtr, LongPressPtr, DoublePressPtr, ContinuousLongPressPtr, RisingEdgePtr, FallingEdgePtr; 
		
		bool S, S_EN, ShortPress_EN, LongPress_EN, ContinuousLongPress_EN, DoublePress_EN, Timer_EN, FallingEdge_EN, RisingEdge_EN;
		
		bool Old_S, S_Pressed, S_PressedOnce, S_DoublePressed, S_LongPressed;
		
		uint8_t Switch_ID, PinNumber, PortNumber, MyTimerID;
		
		uint16_t timeSincePressedOnce, TimePassed;;
		
		void initializeSwitch(uint8_t pinNumber);
		
		void pollSwitch();
		
		//void updatePinBuffers();
		
		void longWaitComplete();
		
		void doubleWaitComplete();
		
		void fallingEdge(Fptr callback);
		
		void risingEdge(Fptr callback);
		
		void shortPress(Fptr callback);
		
		void longPress(Fptr callback);
		
		void continuousLongPress(Fptr callback);
		
		void doublePress(Fptr callback);
		
		void detectShortPress();
		
		void detectLongPress();
		
		void detectDoublePress();
		
		void processStateChange();
		
		uint8_t getSwitchID();
		
};

extern SwitchClass Switch;

#endif /* SWITCH_H_ */