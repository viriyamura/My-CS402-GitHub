#include <BigNumber.h>
const BigNumber one = 1;
const BigNumber rei = 0;

BigNumber enc(BigNumber message,BigNumber e, BigNumber modular)
{
  BigNumber temp = message.powMod(e,modular);
  /*Serial.print("temp is");
  Serial.println(temp);
  temp%=modular;
  for debug*/
  return temp;
}

BigNumber gcdr(BigNumber a, BigNumber b) //www.math.wustl.edu/~victor/mfmm/compaa/gcd.c
{
  if(a==0) return b;
  return gcdr(b%a,a);
}
    
BigNumber finde(BigNumber t1, BigNumber t2, BigNumber limit)
{
    BigNumber x, y, z;
    BigNumber g = 2;
    for(z=17;x!=1||y!=1;z+=2){
            x=gcdr(t1,z);
            y=gcdr(t2,z);
            }
    return z-g;
}

BigNumber findd(BigNumber a, BigNumber b)
{
	BigNumber b0 = b, t, q;
	BigNumber x0 = 0, x1 = 1;
	if (b == one) return one;
	while (a > one) {
	q = a / b;
	t = b;
        b = a % b;
        a = t;
	t = x0;
        x0 = x1 - q * x0;
        x1 = t;
	}
	if (x1 < rei) x1 += b0;
	return x1;
}


void setup()
{
  Serial.begin(9600);  
  BigNumber::begin();
}

void loop(){
  char ch[4] = "efg";
  //ch is message to encrypted
  BigNumber encd[3];
  int a[3];
  int i;
  int b;
  BigNumber temp;
  BigNumber p1="41057";
  BigNumber p2="51871";
  //p1 and p2 is prime
  BigNumber modular = p1*p2;
  BigNumber phi = (p1-one)*(p2-one);
  BigNumber e;
  BigNumber d;
  e=finde(p1-one,p2-one,phi);
  d=findd(e, phi);
  for(i=0;i<=2;i++){
    a[i]=ch[i];
    temp = a[i];
    encd[i] = enc(temp,e,modular);
    Serial.print("Encrypted Character at");
    Serial.print(i);
    Serial.print("position is");
    Serial.println(encd[i]);
  }
  for(i=0;i<=2;i++){
    encd[i] = enc(encd[i],d,modular);
    b = encd[i];
    Serial.print("Decrypted Value is ");
    Serial.println(b);
    Serial.print("Character is ");
    ch[i] = char(b);
    Serial.println(ch[i]);
    
  }
  delay(5000);
}

