#include <RduinoSA.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BigNumber::begin();
}

void loop() {
  BigNumber encryptedMessage = "1007321275";
  String s3 = encryptedMessage.toString();
  unsigned  long newlong = (long)c;
  Serial.println(newlong);
  Serial.println(s3);
  unsigned long s3l = s3.toInt();
  Serial.println(s3l);
  String newS3 = String(s3l);
  Serial.print("new string from long");
  Serial.println(newS3);
  
  /*BigNumber b = newS3;
  Serial.print("String to BN test");
  Serial.println(b);*/
}
