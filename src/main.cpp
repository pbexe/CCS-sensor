#include "Arduino.h"
#include "SevSeg.h"
#include <math.h>
 
int sensorPin = A5;
long highest = 0;
long lowest = 100;
 
double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  return Temp;
}

SevSeg sevseg; //Initiate a seven segment controller object

void setup() {

byte numDigits = 4;

byte digitPins[] = {2, 3, 4, 5};

byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);

sevseg.setBrightness(90);

}

void loop() {
     int readVal=analogRead(sensorPin);
 long temp =  Thermistor(readVal);
 if(temp > highest){
     highest = temp;
 }
  if(temp < lowest){
     lowest = temp;
 }

if(millis() % 2000 > 1000){
    sevseg.setNumber(highest, 0);

} else{
sevseg.setNumber(lowest, 0);

}

sevseg.refreshDisplay(); // Must run repeatedly

}