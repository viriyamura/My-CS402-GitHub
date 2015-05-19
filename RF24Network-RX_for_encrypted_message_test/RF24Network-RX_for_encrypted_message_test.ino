/*
 Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Simplest possible example of using RF24Network,
 *
 * RECEIVER NODE
 * Listens for messages from the transmitter and prints them out.
 */

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <RduinoSA.h>

// nRF24L01(+) radio attached using Getting Started board 
// for mega RF24 radio(53,48);
RF24 radio(9,10); // for uno
// Network uses that radio
RF24Network network(radio);

// Address of our node
const uint16_t this_node = 0;

// Address of the other node
const uint16_t other_node = 1;

// Structure of our payload
struct payload_t
{
  unsigned long encryptedX;
  unsigned long encryptedY;
};
BigNumber temp1;
BigNumber temp2;
BigNumber d = "352089617";
BigNumber mod = "1467573221";
void setup(void)
{
  Serial.begin(57600);
  Serial.println("RF24Network/examples/helloworld_rx/");
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
  BigNumber::begin();
}

void loop(void)
{
  // Pump the network regularly
  network.update();

  // Is there anything ready for us?
  while ( network.available() )
  {
    // If so, grab it and print it out
    RF24NetworkHeader header;
    payload_t payload;
    //unsigned long recvmsg;
    network.read(header,&payload,sizeof(payload));
    Serial.print("Received packet encrypted X varlue#");
    Serial.println(payload.encryptedX);
    temp1 = rsa.tobignum(payload.encryptedX);
    temp1 = rsa.decrypt(temp1,d,mod);
    Serial.print("Decrypted message for X is");
    Serial.println(temp1);
    Serial.print("Received packet encrypted Y varlue#");
    Serial.println(payload.encryptedY);
    temp2 = rsa.tobignum(payload.encryptedY);
    temp2 = rsa.decrypt(temp2,d,mod);
    Serial.print("Decrypted message for Y is");
    Serial.println(temp2);
    //Serial.print(" at ");
    //Serial.println(payload.ms);
  }
}
// vim:ai:cin:sts=2 sw=2 ft=cpp
