#include <BigNumber.h>

void setup() {
  Serial.begin(9600);  
  BigNumber::begin();
}

void loop() {
  unsigned long lmax = 4294967;
  if(lmax>999999999){  
    int bot = lmax%10000;
    int mid = (lmax/10000)%1000;
    int top = lmax/10000000;
    Serial.println(bot);
    Serial.println(mid);
    Serial.println(top);
    Serial.println("------------");
    BigNumber newby = top;
    Serial.println(newby);
    newby *= 1000;
    Serial.println(newby);
    newby += mid;
    Serial.println(newby);
    newby *= 10000;
    Serial.println(newby);
    newby += bot;
    Serial.println(newby);
    Serial.println("------------");
  }
  else if(lmax<=999999999&&lmax>99999999){
    int bot = lmax%10000;
    int mid = (lmax/10000)%1000;
    int top = lmax/10000000;
    Serial.println(bot);
    Serial.println(mid);
    Serial.println(top);
    Serial.println("------------");
    BigNumber newby = top;
    Serial.println(newby);
    newby *= 1000;
    Serial.println(newby);
    newby += mid;
    Serial.println(newby);
    newby *= 10000;
    Serial.println(newby);
    newby += bot;
    Serial.println(newby);
    Serial.println("------------");
  }
  else if(lmax<=99999999&&lmax>9999999){
    int bot = lmax%1000;
    int mid = (lmax%1000000)/1000;
    int top = lmax/1000000;
    Serial.println(bot);
    Serial.println(mid);
    Serial.println(top);
    Serial.println("------------");
    BigNumber newby = top;
    Serial.println(newby);
    newby *= 1000;
    Serial.println(newby);
    newby += mid;
    Serial.println(newby);
    newby *= 1000;
    Serial.println(newby);
    newby += bot;
    Serial.println(newby);
    Serial.println("------------");
  }
  else if(lmax<=9999999&&lmax>999999){
    int bot = lmax%1000;
    int mid = (lmax%1000000)/1000;
    int top = lmax/1000000;
    Serial.println(bot);
    Serial.println(mid);
    Serial.println(top);
    Serial.println("------------");
    BigNumber newby = top;
    Serial.println(newby);
    newby *= 1000;
    Serial.println(newby);
    newby += mid;
    Serial.println(newby);
    newby *= 1000;
    Serial.println(newby);
    newby += bot;
    Serial.println(newby);
    Serial.println("------------");
  }
  else if(lmax<=
  delay(10000);
}
