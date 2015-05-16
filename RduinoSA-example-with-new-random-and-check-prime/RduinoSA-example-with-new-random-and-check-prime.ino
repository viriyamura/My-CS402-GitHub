#include <RduinoSA.h>
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  BigNumber::begin();
}

boolean isPrime(unsigned int x){
  unsigned long sqrtx = sqrt(x);
  for(int i=2;i<=sqrtx;i++){
    if(x%i==0){
      return true;
    }
  }
  return false;
}

unsigned int gcd (unsigned int a, unsigned int b )
{
  unsigned int c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

void loop() {
  unsigned int p;
  unsigned int q;
  boolean check = true;
  unsigned long start=millis();
  while(check){
    p = random(10000,65535);
    if(p%2==0){
      p++;
    }
    check=isPrime(p);
  }
  check = true;
  for(int i = 10 ; check ; i+=10){
    q = random(p-i,p+i);
    if(q%2==0){
      q++;
    }
    if(p!=q){
      check=isPrime(q);
    }
  }
  unsigned long time = millis()-start;
  Serial.print("p=");
  Serial.println(p);
  Serial.print("q=");
  Serial.println(q);
  Serial.print("time=");
  Serial.println(time);
  unsigned int x = gcd(p-1,q-1);
  Serial.print("gcd=");
  Serial.println(x);
  Serial.println("------------");
  BigNumber firstprime = rsa.tobignum((unsigned long)p);
  Serial.println(firstprime);
  BigNumber secondprime = rsa.tobignum((unsigned long)q);
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
  Serial.print(" Decrypted message is ");
  BigNumber dec = rsa.decrypt(encd,d,modular);
  Serial.println(dec);
 
  delay(5000);
}
