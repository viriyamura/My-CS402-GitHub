#include <RduinoSA.h>

void setup()
{
  Serial.begin(9600);
  BigNumber::begin();
}
void loop()
{
  BigNumber a="100000033417";
  BigNumber b="100000034467";
  BigNumber modular = rsa.modularGenerate(a,b);
  Serial.print("modular is");
  Serial.println(modular);
  BigNumber phi = rsa.phiGenerate(a,b);
  Serial.print("phi is");
  Serial.println(phi);
  BigNumber e = "65537";
  BigNumber d;
  //e = rsa.eGenerate(a,b,phi);
  Serial.print("e is");
  Serial.println(e);
  d = rsa.dGenerate(e,phi);
  Serial.print("d is");
  Serial.println(d);
  BigNumber msg = 256;
  Serial.print("Message is ");
  Serial.println(msg);
  Serial.print("Encrypted message is ");
  unsigned long starttime =millis();
  BigNumber encd = rsa.encrypt(msg,e,modular);
  unsigned long endtime = millis()-starttime;
  Serial.println(encd);
  Serial.println("time for encrypt is ");
  Serial.println(endtime);
  Serial.print("Decrypted message is ");
  starttime =millis();
  //BigNumber encd = "54189501";
  //BigNumber d = "311906471";
  //BigNumber modular = "1143724697";
  BigNumber dec = rsa.decrypt(encd,d,modular);
  endtime = millis()-starttime;
  //unsigned long newdec = (long)dec;
  
  //dec = rsa.tobignum(dec);
  Serial.println(dec);
  Serial.print("time for decrypt is ");
  Serial.println(endtime);
  delay(5000);
  
}
