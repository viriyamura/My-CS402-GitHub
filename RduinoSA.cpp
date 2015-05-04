#include "RduinoSA.h"

const BigNumber one = 1;
const BigNumber rei = 0;

RduinoSA rsa;

RduinoSA::RduinoSA()
{

}

RduinoSA::~RduinoSA()
{

}

BigNumber RduinoSA::encrypt(BigNumber message,BigNumber e, BigNumber modular)
{
	BigNumber temp = message.powMod(e,modular);
	return temp;
}

BigNumber RduinoSA::decrypt(BigNumber encryptedMessage, BigNumber d, BigNumber modular)
{
	BigNumber temp = encryptedMessage.powMod(d,modular);
	return temp;
}

BigNumber RduinoSA::modularGenerate(BigNumber prime1, BigNumber prime2)
{
	BigNumber temp = prime1*prime2;
	return temp;
}

BigNumber RduinoSA::phiGenerate(BigNumber prime1, BigNumber prime2)
{
	BigNumber temp = (prime1-one)*(prime2-one);
	return temp;
}

BigNumber RduinoSA::dGenerate(BigNumber a, BigNumber b)
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

BigNumber RduinoSA::eGenerate(BigNumber a, BigNumber b, BigNumber bound)
{
	BigNumber x, y, z;
    BigNumber g = 2;
    for(z=17;x!=1||y!=1;z+=2){
            x=rsa.gcdr(a,z);
            y=rsa.gcdr(b,z);
            }
    return z-g;
}

BigNumber RduinoSA::gcdr(BigNumber a, BigNumber b) //www.math.wustl.edu/~victor/mfmm/compaa/gcd.c
{
  if(a==rei) return b;
  return gcdr(b%a,a);
}























