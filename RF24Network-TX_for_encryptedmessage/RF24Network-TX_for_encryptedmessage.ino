/*
 Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Simplest possible example of using RF24Network 
 *
 * TRANSMITTER NODE
 * Every 2 seconds, send a payload to the receiver node.
 */

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <RduinoSA.h>

// nRF24L01(+) radio attached using Getting Started board 
RF24 radio(9,10);

// Network uses that radio
RF24Network network(radio);

// Address of our node
const uint16_t this_node = 1;

// Address of the other node
const uint16_t other_node = 0;

// How often to send 'hello world to the other unit
const unsigned long interval = 2000; //ms

// When did we last send?
unsigned long last_sent;

// How many have we sent already
unsigned long packets_sent;

// fixed message for testing
//BigNumber message = 256;
// fixed public key for testing
BigNumber e = "65537";
BigNumber mod = "1467573221";
//BigNumber encryptedMessageX;
//BigNumber encryptedMessageY;
unsigned long sendmessage;
// Structure of our payload
struct payload_t
{
  unsigned long encryptedX;
  unsigned long encryptedY;
};

void setup(void)
{
  Serial.begin(57600);
  Serial.println("RF24Network/examples/helloworld_tx/");
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
  BigNumber::begin();
}

void loop(void)
{
  // Pump the network regularly
  network.update();

  // If it's time to send a message, send it!
  unsigned long now = millis();
  if ( now - last_sent >= interval  )
  {
    last_sent = now;

    Serial.print("Sending...");
    payload_t payload;
    int msgX = analogRead(A1);
    int msgY = analogRead(A2);
    BigNumber emsgX = BigNumber(msgX);
    BigNumber emsgY = BigNumber(msgY);
    emsgX = rsa.encrypt(emsgX,e,mod);
    emsgY = rsa.encrypt(emsgY,e,mod);
    payload.encryptedX = (long)emsgX;
    payload.encryptedY = (long)emsgY;
    Serial.println(payload.encryptedX);
    Serial.println(msgX);
    Serial.println(payload.encryptedY);
    Serial.println(msgY);
    RF24NetworkHeader header(/*to node*/ other_node);
    bool ok = network.write(header,&payload,sizeof(payload));
    if (ok)
      Serial.println("ok.");
    else
      Serial.println("failed.");
  }
}
// vim:ai:cin:sts=2 sw=2 ft=cpp
