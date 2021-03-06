/*JumperTouchSensor library V1.0
by JX Pan MAY 2014

It basically turns jumpers into touch sonsors

The only function returns integer between 1-17. If the bare end of the jumper attached to “pinToMeasure” is pressed by your finger, the return value would be 2 or more

BASED ON CODE FROM HERE: http://playground.arduino.cc/Code/CapacitiveSensor/

*/


#include <JumperTouchSensor.h>
#include <Arduino.h>
int JTS::readCapacitivePin(int pinToMeasure) {
// Variables used to translate from Arduino to AVR pin naming
volatile uint8_t* port;
volatile uint8_t* ddr;
volatile uint8_t* pin;
// Here we translate the input pin number from
// Arduino pin number to the AVR PORT, PIN, DDR,
// and which bit of those registers we care about.
byte bitmask;
port = portOutputRegister(digitalPinToPort(pinToMeasure));
ddr = portModeRegister(digitalPinToPort(pinToMeasure));
bitmask = digitalPinToBitMask(pinToMeasure);
pin = portInputRegister(digitalPinToPort(pinToMeasure));
// Discharge the pin first by setting it low and output
*port &= ~(bitmask);
*ddr |= bitmask;
delay(1);
// Make the pin an input with the internal pull-up on
*ddr &= ~(bitmask);
*port |= bitmask;

// Now see how long the pin to get pulled up. This manual unrolling of the loop
// decreases the number of hardware cycles between each read of the pin,
// thus increasing sensitivity.
uint8_t cycles = 17;
if (*pin & bitmask) { cycles = 0;}
else if (*pin & bitmask) { cycles = 1;}
else if (*pin & bitmask) { cycles = 2;}
else if (*pin & bitmask) { cycles = 3;}
else if (*pin & bitmask) { cycles = 4;}
else if (*pin & bitmask) { cycles = 5;}
else if (*pin & bitmask) { cycles = 6;}
else if (*pin & bitmask) { cycles = 7;}
else if (*pin & bitmask) { cycles = 8;}
else if (*pin & bitmask) { cycles = 9;}
else if (*pin & bitmask) { cycles = 10;}
else if (*pin & bitmask) { cycles = 11;}
else if (*pin & bitmask) { cycles = 12;}
else if (*pin & bitmask) { cycles = 13;}
else if (*pin & bitmask) { cycles = 14;}
else if (*pin & bitmask) { cycles = 15;}
else if (*pin & bitmask) { cycles = 16;}

// Discharge the pin again by setting it low and output
// It's important to leave the pins low if you want to 
// be able to touch more than 1 sensor at a time - if
// the sensor is left pulled high, when you touch
// two sensors, your body will transfer the charge between
// sensors.
*port &= ~(bitmask);
*ddr |= bitmask;

return cycles;
}

