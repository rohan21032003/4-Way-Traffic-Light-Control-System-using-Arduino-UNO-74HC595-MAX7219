/*
  Project: 4-Way Traffic Light
  Author: Rohan

  Arduino UNO
  74HC595 ×2
  MAX7219
*/

#include <LedControl.h>

// MAX7219
LedControl display(10, 8, 9, 1);

// 74HC595
const int data_Pin = 12;
const int latch_Pin = 11;
const int clock_Pin = 13;

// Pedestrian
const int button = 7;

#define PED1 6
#define PED2 6


// ======================
// TIMINGS
// ======================

const unsigned long greenTime = 27000;
const unsigned long yellowTime = 3000;
const unsigned long whiteTime = 10000;

unsigned long previousMillis = 0;
unsigned long pedestrianMillis = 0;


// ======================
// STATES
// ======================

int trafficState = 0;

bool pedestrianRequest = false;

int buttonState = HIGH;
int lastButtonState = HIGH;


// ======================
// REGISTER STORAGE
// ======================

byte reg1 = 0;
byte reg2 = 0;


// ======================
// SETUP
// ======================

void setup() {

pinMode(data_Pin, OUTPUT);
pinMode(latch_Pin, OUTPUT);
pinMode(clock_Pin, OUTPUT);

pinMode(button, INPUT_PULLUP);


// MAX7219

display.shutdown(0,false);

display.setIntensity(0,5);

display.clearDisplay(0);

}


// ======================
// REGISTER UPDATE
// ======================

void updateRegisters() {

digitalWrite(
latch_Pin,
LOW
);

shiftOut(
data_Pin,
clock_Pin,
MSBFIRST,
reg2
);

shiftOut(
data_Pin,
clock_Pin,
MSBFIRST,
reg1
);

digitalWrite(
latch_Pin,
HIGH
);

}


// ======================

void clearRegisters() {

reg1 = 0;

reg2 = 0;

}


// ======================
// DISPLAY
// ======================

void showTime(
int digit,
int value
){

value =
constrain(
value,
0,
99
);

display.setDigit(
0,
digit,
value/10,
false
);

display.setDigit(
0,
digit+1,
value%10,
false
);

}


// ======================
// COUNTDOWN
// ======================

void updateCountdown() {

int elapsed =

(
millis()
-
previousMillis
)
/1000;


switch(
trafficState
){

case 0:
case 1:

showTime(0,30-elapsed);
showTime(2,30-elapsed);
showTime(4,60-elapsed);
showTime(6,90-elapsed);

break;


case 2:
case 3:

showTime(0,90-elapsed);
showTime(2,30-elapsed);
showTime(4,30-elapsed);
showTime(6,60-elapsed);

break;


case 4:
case 5:

showTime(0,60-elapsed);
showTime(2,90-elapsed);
showTime(4,30-elapsed);
showTime(6,30-elapsed);

break;


case 6:
case 7:

showTime(0,30-elapsed);
showTime(2,60-elapsed);
showTime(4,90-elapsed);
showTime(6,30-elapsed);

break;

}

}


// ======================
// TRAFFIC CONTROL
// ======================

void trafficControl() {

clearRegisters();

switch(
trafficState
){

// A GREEN

case 0:

bitSet(reg1,0);

bitSet(reg1,5);

bitSet(reg2,2);

bitSet(reg2,5);

if(
millis()-previousMillis
>=
greenTime
){

trafficState=1;

}

break;


// A YELLOW

case 1:

bitSet(reg1,1);

bitSet(reg1,5);

bitSet(reg2,2);

bitSet(reg2,5);

if(
millis()-previousMillis
>=
greenTime+yellowTime
){

trafficState=2;

previousMillis=
millis();

}

break;


// B GREEN

case 2:

bitSet(reg1,2);

bitSet(reg1,3);

bitSet(reg2,2);

bitSet(reg2,5);

if(
millis()-previousMillis
>=
greenTime
){

trafficState=3;

}

break;


// B YELLOW

case 3:

bitSet(reg1,2);

bitSet(reg1,4);

bitSet(reg2,2);

bitSet(reg2,5);

if(
millis()-previousMillis
>=
greenTime+yellowTime
){

trafficState=4;

previousMillis=
millis();

}

break;


// C GREEN

case 4:

bitSet(reg1,2);

bitSet(reg1,5);

bitSet(reg2,0);

bitSet(reg2,5);

if(
millis()-previousMillis
>=
greenTime
){

trafficState=5;

}

break;


// C YELLOW

case 5:

bitSet(reg1,2);

bitSet(reg1,5);

bitSet(reg2,1);

bitSet(reg2,5);

if(
millis()-previousMillis
>=
greenTime+yellowTime
){

trafficState=6;

previousMillis=
millis();

}

break;


// D GREEN

case 6:

bitSet(reg1,2);

bitSet(reg1,5);

bitSet(reg2,2);

bitSet(reg2,3);

if(
millis()-previousMillis
>=
greenTime
){

trafficState=7;

}

break;


// D YELLOW

case 7:

bitSet(reg1,2);

bitSet(reg1,5);

bitSet(reg2,2);

bitSet(reg2,4);

if(
millis()-previousMillis
>=
greenTime+yellowTime
){

trafficState=0;

previousMillis=
millis();

}

break;

}

updateRegisters();

}


// ======================
// LOOP
// ======================

void loop() {

buttonState =
digitalRead(button);


// pedestrian request

if(

buttonState==LOW

&&

lastButtonState==HIGH

&&

!pedestrianRequest

){

pedestrianRequest=true;

pedestrianMillis=
millis();

}


// PEDESTRIAN MODE

if(
pedestrianRequest
){

clearRegisters();

bitSet(reg1,2);

bitSet(reg1,5);

bitSet(reg2,2);

bitSet(reg2,5);

bitSet(reg1,PED1);

bitSet(reg2,PED2);

updateRegisters();

showTime(0,0);

showTime(2,0);

showTime(4,0);

showTime(6,0);


if(

millis()

-

pedestrianMillis

>=

whiteTime

){

pedestrianRequest=false;

}

}

else{

trafficControl();

updateCountdown();

}


lastButtonState =
buttonState;

}
