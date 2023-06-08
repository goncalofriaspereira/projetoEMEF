/* Modbus RTU Slave Library modified by Gonçalo Pereira
   Library by: https://github.com/CMB27/ModbusRTUSlave
  Master/client port configured using the following settings:
  - Baud Rate: 38400
  - Data Bits: 8
  - Parity: None
  - Stop Bit(s): 1
  - Slave/Server ID: 10
*/

#include "ModbusRTUSlave.h"
#include <SoftwareSerial.h>

const byte id = 10;
const unsigned long baud = 38400;
const unsigned int bufSize = 256;

const unsigned int numCoils = 4;
const unsigned int numDiscreteInputs = 4;
const unsigned int numHoldingRegisters = 2;
const unsigned int numInputRegisters = 2;

byte holdingBuffer[numHoldingRegisters] = {};

const byte inputDigitalPins[numDiscreteInputs] = {4,7,8,9};
const byte outputDigitalPins[numCoils] = {10,11,12,13};
const byte inputAnalogPins[numInputRegisters] = {A0, A1};
const byte outputAnalogPins[numHoldingRegisters] = {5,6};

const byte enabler_pin = 2;
byte buf[bufSize];
ModbusRTUSlave modbus(Serial, buf, bufSize, enabler_pin);

void setup() {
  pinMode(inputDigitalPins[0], INPUT);
  pinMode(inputDigitalPins[1], INPUT);
  pinMode(inputDigitalPins[2], INPUT);
  pinMode(inputDigitalPins[3], INPUT);
  pinMode(outputDigitalPins[0], OUTPUT);
  pinMode(outputDigitalPins[1], OUTPUT);
  pinMode(outputDigitalPins[2], OUTPUT);
  pinMode(outputDigitalPins[3], OUTPUT);
  pinMode(inputAnalogPins[0], INPUT);
  pinMode(inputAnalogPins[1], INPUT);
  pinMode(outputAnalogPins[0], OUTPUT);
  pinMode(outputAnalogPins[1], OUTPUT);
  
  Serial.begin(baud);
  modbus.begin(id, baud);
  modbus.configureCoils(numCoils, coilRead, coilWrite);
  modbus.configureDiscreteInputs(numDiscreteInputs, discreteInputRead);
  modbus.configureHoldingRegisters(numHoldingRegisters, holdingRegisterRead, holdingRegisterWrite);
  modbus.configureInputRegisters(numInputRegisters, inputRegisterRead);
}

void loop() {
  modbus.poll();
}

char coilRead(unsigned int address) {
  switch (address) {
    case 0:
      return digitalRead(outputDigitalPins[0]);
    case 1:
      return digitalRead(outputDigitalPins[1]);
    case 2:
      return digitalRead(outputDigitalPins[2]);
    case 3:
      return digitalRead(outputDigitalPins[3]);
    default:
      return -1;
  }
}

boolean coilWrite(unsigned int address, boolean value) {
  switch (address) {
    case 0:
      digitalWrite(outputDigitalPins[0], value);
      break;
    case 1:
      digitalWrite(outputDigitalPins[1], value);
      break;
    case 2:
      digitalWrite(outputDigitalPins[2], value);
      break;
    case 3:
      digitalWrite(outputDigitalPins[3], value);
      break;
    default:
      return false;
  }
  return true;
}

char discreteInputRead(unsigned int address) {
  if (address > 3){
    return -1;
  }
  return digitalRead(inputDigitalPins[address]);
}

long holdingRegisterRead(unsigned int address) {
  int readTemp;
  switch (address) {
    case 0:
      readTemp = map(holdingBuffer[0], 0, 255, 0, 1024);
      return readTemp;
    case 1:
      readTemp = map(holdingBuffer[1], 0, 255, 0, 1024);
      return readTemp;
    default:
      return -1;
  }
}

boolean holdingRegisterWrite(word address, word value) {
  switch (address) {
    case 0:
      holdingBuffer[0] = map(value, 0, 1024, 0, 255);
      analogWrite(outputAnalogPins[0], holdingBuffer[0]);
      break;
    case 1:
      holdingBuffer[1] = map(value, 0, 1024, 0, 255);
      analogWrite(outputAnalogPins[1], holdingBuffer[1]);
    default:
      return false;
  }
  return true;
}

long inputRegisterRead(word address) {
  if(address > 3){
    return -1;
  }
  return analogRead(inputAnalogPins[address]);
}
