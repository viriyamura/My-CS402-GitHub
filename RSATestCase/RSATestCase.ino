#include <BigNumber.h>
const BigNumber one = 1;
const BigNumber rei = 0;

void setup()
{
  Serial.begin(9600);  
  BigNumber::begin();
}
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

void loop()
{
  BigNumber p1="41057";
  BigNumber p2="51871";
  //p1 and p2 is prime
  BigNumber modular = p1*p2;
  // bit-lenght of modular is key lenght
  Serial.print("modular is");
  Serial.println(modular);
  BigNumber one = 1;
  BigNumber phi = (p1-one)*(p2-one);
  BigNumber e;
  BigNumber d;
  Serial.print("phi is");
  Serial.println(phi);
  e=finde(p1-one,p2-one,phi);
  //e = BigNumber("17");
  //fix e
  Serial.print("E is");
  Serial.println(e);
  d=findd(e, phi);
  //d = BigNumber("3598389233");
  //fix d
  Serial.print("D is");
  Serial.println(d);
  BigNumber msg = 256;
  BigNumber encd = enc(msg,e,modular);
  /*enc(message,e,modular)*/
  Serial.println(encd);
  BigNumber dec = enc(encd,d,modular);
  Serial.println(dec);
  /*BigNumber dec = power(d,encd);
  dec%=t2;*/
  delay(5000);
  Serial.println();
}
