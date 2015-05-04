#include <RduinoSA.h>

void setup()
{
  Serial.begin(9600);
  BigNumber::begin();
}
void loop()
{
  BigNumber a="41057";
  BigNumber b="51871";
  BigNumber modular = rsa.modularGenerate(a,b);
  Serial.print("modular is");
  Serial.println(modular);
  BigNumber phi = rsa.phiGenerate(a,b);
  Serial.print("phi is");
  Serial.println(phi);
  BigNumber e;
  BigNumber d;
  e = rsa.eGenerate(a,b,phi);
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
  Serial.print(" Decrypted message is ");
  BigNumber dec = rsa.decrypt(encd,d,modular);
  Serial.println(dec);
  delay(5000);
  
}
