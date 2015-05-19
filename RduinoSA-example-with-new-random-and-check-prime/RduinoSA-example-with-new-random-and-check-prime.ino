#include <RduinoSA.h>
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  BigNumber::begin();
}

void loop() {
  
  unsigned long start = millis();
  //unsigned long p = rsa.createPrime(0);
  unsigned long endtime = millis()-start;
  Serial.println(endtime);
  start = millis();
  //unsigned long q = rsa.createPrime(1);
  endtime = millis()-start;
  //Serial.println(endtime);
  //unsigned long p = 100000003757;
  //unsigned long q = 100000001389;
  /*Serial.print("p=");
  Serial.println(p);
  Serial.print("q=");
  Serial.println(q);
  Serial.println("------------");*/
 // BigNumber firstprime = rsa.tobignum(p);
  BigNumber firstprime = "100000033417";
  Serial.println(firstprime);
  BigNumber secondprime = "100000034467";
  //BigNumber secondprime = rsa.tobignum(q);
  Serial.println(secondprime);
  BigNumber phi = rsa.phiGenerate(firstprime,secondprime);
  Serial.println(phi);
  BigNumber modular = rsa.modularGenerate(firstprime,secondprime);
  Serial.println(modular);
  BigNumber e = "65537";
  BigNumber d;
  //e = rsa.eGenerate(firstprime,secondprime,phi);
  Serial.print("e is");
  Serial.println(e);
  d = rsa.dGenerate(e,phi);
  Serial.print("d is");
  Serial.println(d);
  BigNumber msg = 256;
  Serial.print(" Message is ");
  Serial.println(msg);
  Serial.print(" Encrypted message is ");
  BigNumber encd = rsa.encrypt(msg,e,modular);
  Serial.println(encd);
  Serial.print("Size of message is ");
  Serial.println(sizeof(encd));
  Serial.print(" Decrypted message is ");
  BigNumber dec = rsa.decrypt(encd,d,modular);
  Serial.println(dec);
  BigNumber newBN = "10";
  Serial.println(sizeof(newBN));
  Serial.println(newBN);
  delay(5000);
}
