#ifndef RduinoSA_h
#define RduinoSA_h
#include <Arduino.h>
#include <BigNumber.h>

class RduinoSA
{
	public:
		//constructor
		RduinoSA();
		~RduinoSA();
		BigNumber encrypt(BigNumber message,BigNumber e, BigNumber modular);
		/*encrypt decimal value message with public key (e,modular)*/
		BigNumber decrypt(BigNumber decryptedMessage, BigNumber d, BigNumber modular);
		/*encrypt decimal value message with private key (d,modular) */
		BigNumber modularGenerate(BigNumber prime1, BigNumber prime2);
		/* generate modular value from two prime number */
		BigNumber phiGenerate(BigNumber prime1, BigNumber prime2);
		/* generate phi value */
 		BigNumber dGenerate(BigNumber a, BigNumber b);
		/* generate d value that use in private key set a is for e value and b is for phi value*/
		BigNumber eGenerate(BigNumber a, BigNumber b, BigNumber bound);
		/* generate e value that use in public key set */
		BigNumber gcdr(BigNumber a, BigNumber b);
		/* gcd function, use in e generating */	
		BigNumber add0(BigNumber old);
		/* part of long to bignum converting*/
		BigNumber addbot(int bot);
		/* part of long to bignum converting*/
		BigNumber addmid(int mid, int bot);
		/* part of long to bignum converting*/
		BigNumber addtop(int top, int mid, int bot);
		/* part of long to bignum converting*/
		BigNumber tobignum(unsigned long data);
		/*convert BigNumber to long data type*/
		boolean isPrime(unsigned int x);
		/*prime checking function*/
		unsigned long createPrime(int a);
		/*prime random*/
  private:
};
extern RduinoSA rsa;
#endif
