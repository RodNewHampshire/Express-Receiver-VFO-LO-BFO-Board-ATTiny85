/******************************************************************************

  EXPRESS RECEIVER by AD5GH
  (http://www.expressreceiver.com)
  LO, VFO, BFO & CARR. OSC. BOARD
  atTINY85 Software

  Copyright 2017 Rod Gatehouse AD5GH
  Distributed under the terms of the MIT License:
  http://www.opensource.org/licenses/mit-license

  VERSION 1.0.0
  DECEMBER 2017

******************************************************************************/

#include <TinyWireS.h>                                  // I2C Slave lib for ATTinys which use USI; equivalent to Wire.h in the regular Arduino world

#define I2C_SLAVE_ADDR        0x80                      // default SHT31 I2C address

#define LED       4
#define SI570_SEL 3

uint8_t command;


void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  pinMode(SI570_SEL, OUTPUT);
  digitalWrite(SI570_SEL, LOW);

  TinyWireS.begin(I2C_SLAVE_ADDR);                   // join i2c network

  TinyWireS.onReceive(receiveEvent);
}


void loop()
{
  TinyWireS_stop_check();
}

void receiveEvent(uint8_t numBytes)
{
  if (TinyWireS.available())
  {
    if (numBytes < 1) return;

    uint8_t command = TinyWireS.receive();
    
    if ( command == 0x00) 
    {
      digitalWrite(SI570_SEL, HIGH);
      digitalWrite(LED, LOW);
    }
    else
    {
      digitalWrite(SI570_SEL, LOW);
      digitalWrite(LED, HIGH);
    }
  }
}

