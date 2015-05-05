/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
 /*
 Modified from ManiacBug's example for an encrypted communication
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <RduinoSA.h>
//#include "printf.h"
const BigNumber oneone = 1;
const BigNumber reirei = 0;
//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
//const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};
/*char* role_friendlny_name[3];
role_friendly_name[0] = "invalid";
role_friendly_name[1] = "Ping out";
role_friendly_name[2] = "Pong Back";*/
// The role of the current running sketch
role_e role = role_pong_back;
BigNumber prime1 = 0;
BigNumber prime2 = 0;
BigNumber e = 0;
BigNumber d = 0;
BigNumber mod = 0;
BigNumber phi = 0;
BigNumber plainMessage = 0;
BigNumber encryptedMessage = 0;

void setup(void)
{
  //
  // Print preamble
  //

  Serial.begin(57600);
  //printf_begin();
  Serial.println("\n\rRF24/examples/GettingStarted/\n\r");
  //Serial.print("ROLE: ");
  //Serial.println(role_friendlyname[role]);
  Serial.println("*** PRESS 'T' to begin key generating and send public key to other");
  //
  // Setup and configure rf radio
  //

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  radio.setPayloadSize(32);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  //
  // Start listening
  //

  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
}

void loop(void)
{
  //
  // Ping out role.  Repeatedly send the current time
  //

  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();
	if(prime1==reirei&&prime2==reirei)
	{
		Serial.println("Please set first prime number to generate key");
		prime1 = Serial.parseInt();
		Serial.println("Please set second prime number to generate key");
		prime2 = Serial.parseInt();
	}
	if(prime1>reirei&&prime2>reirei&&mod==reirei&&phi==reirei&&e==reirei&&d==reirei)
	{
		mod = rsa.modularGenerate(prime1,prime2);
		Serial.println(mod);
		phi = rsa.phiGenerate(prime1,prime2);
		Serial.println(phi);
		e = rsa.eGenerate(prime1,prime2,phi);
		Serial.println(e);
		d = rsa.dGenerate(e,phi);
		Serial.println(d);
	}
	
	
    // Take the time, and send mod value.  This will block until complete
    //unsigned long time = millis();
    Serial.print("Now sending mod = ");
	Serial.println(mod);
    //Serial.print(time);
    //Serial.print(one);
    bool ok = radio.write( &mod, sizeof(mod) );
    
    if (ok)
      Serial.println("ok...");
    else
      Serial.println("failed.\n\r");

    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      Serial.println("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      //unsigned long got_time;
      int ack = 0;
      radio.read( &ack, sizeof(ack) );

      // Spew it
      Serial.println("Got response");
      Serial.print(ack);
      //Serial.print(" ");
      //Serial.println(millis()-got_time);
    }
	radio.stopListening();
	Serial.print("Now sending e = ");
	Serial.println(e);
	ok = radio.write( &e, sizeof(e) );
	 
    if (ok)
      Serial.println("ok...");
    else
      Serial.println("failed.\n\r");

    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    started_waiting_at = millis();
    timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      Serial.println("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      //unsigned long got_time;
      int ack = 0;
      radio.read( &ack, sizeof(ack) );

      // Spew it
      Serial.println("Got response");
      Serial.print(ack);
      //Serial.print(" ");
      //Serial.println(millis()-got_time);
    }
    // Try again 1s later
	if(encryptedMessage==reirei)
	{
		timeout = false;
		while ( ! radio.available() && ! timeout )
			if (millis() - started_waiting_at > 10000 )
				timeout = true;

		// Describe the results
		if ( timeout )
		{
			Serial.println("Failed, response timed out.\n\r");
		}
		else
		{
		radio.read( &encryptedMessage, sizeof(encryptedMessage) );
		}
      // Spew it
      Serial.print("Got encrypted message");
      Serial.println(encryptedMessage);
      //Serial.print(" ");
      //Serial.println(millis()-got_time);
    }
	if(encryptedMessage>reirei)
	{
		plainMessage = rsa.decrypt(encryptedMessage,d,mod);
		encryptedMessage = 0;
	}
	Serial.println(plainMessage);
    delay(5000);
  }

  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //

  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
		if(e==reirei&&mod==reirei)
		{
			bool done = false;
			while(!done)
			{
				done = radio.read(&e, sizeof(e));
				Serial.print("Got e value = ");
				Serial.println(e);
				delay(20);
			}
			radio.stopListening();
			int ack = 1;
			radio.write(&ack, sizeof(ack));
			Serial.println("Sent response.");
			bool done2 = false;
			radio.startListening();
			while(!done2)
			{
				done2 = radio.read(&mod, sizeof(mod));
				Serial.print("Got modular value = ");
				Serial.println(mod);
				delay(20);
			}
			radio.stopListening();
			Serial.println("Sent response.");
		}
		if(e>reirei&&mod>reirei&&plainMessage==0)
		{
			Serial.println("Please input message to encrypted");
			plainMessage = Serial.parseInt();
			encryptedMessage = rsa.encrypt(plainMessage,e,mod);
		}
		if(encryptedMessage>0)
		{
			Serial.print("Now sending encrypted message = ");
			Serial.println(encryptedMessage);
			bool ok4 = radio.write(&encryptedMessage, sizeof(encryptedMessage));
			if (ok4)
				Serial.println("ok...");
			else
				Serial.println("failed.\n\r");
			//radio.startListening();
			/*started_waiting_at = millis();
			timeout = false;
			while(!radio.available()&&!timeout)
				if(millis() - started_waiting_at > 200 )
					timeout = true;*/
			encryptedMessage = 0;	
		}
     
      radio.startListening();
    }
  }

  //
  // Change roles
  //

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      Serial.println("*** CHANGING TO HOST ROLE -- PRESS 'R' TO SWITCH BACK");

      // Become the primary transmitter (ping out)
      role = role_ping_out;
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      Serial.println("*** CHANGING TO CHILD ROLE -- PRESS 'T' TO SWITCH BACK");
      
      // Become the primary receiver (pong back)
      role = role_pong_back;
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
    }
  }
  }
// vim:cin:ai:sts=2 sw=2 ft=cpp
