#include <BigNumber.h>

void setup()
{
  Serial.begin(9600);  
  BigNumber::begin();
}

/*BigNumber power(int n, BigNumber x)
{
  if(n==0){
    return 1;
  }
  else{
    BigNumber temp=x*x;
    if(n%2==1){
      n = (n-1)/2;
      Serial.println(n);
      return power(n,temp)*x;
    }
    else{
      n = n/2;
      Serial.println(n);
      return power(n,temp);
    }
  }
}*/

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
	if (b == 1) return 1;
	while (a > 1) {
	q = a / b;
	t = b;
        b = a % b;
        a = t;
		t = x0;
        x0 = x1 - q * x0;
        x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

void loop()
{
  BigNumber p1="61657";
  BigNumber p2="62011";
  BigNumber modular = p1*p2;
  Serial.print("modular is");
  Serial.println(modular);
  BigNumber one = 1;
  BigNumber phi = (p1-one)*(p2-one);
  BigNumber e;
  BigNumber d;
  Serial.print("phi is");
  Serial.println(phi);
  //e=finde(p1-one,p2-one,phi);
  e = BigNumber("17");
  //fix e
  Serial.print("E is");
  Serial.println(e);
  //d=findd(e, phi);
  d = BigNumber("3598389233");
  //fix d
  Serial.print("D is");
  Serial.println(d);
  BigNumber msg = 256;
  BigNumber encd = enc(msg,e,modular);
  /*enc(message,e,modular)*/
  Serial.println(encd);
  /*BigNumber dec = power(d,encd);
  dec%=t2;
  delay(5000);*/
  Serial.println();
}
