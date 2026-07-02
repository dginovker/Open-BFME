// cl: /DNDEBUG

#include	"always.h"
#include	"int.h"
#include	"mpmath.h"
#include	"rng.h"

int bignum::Error = 0;
bool bignum::Carry = false;
bool bignum::Borrow = false;
bignum bignum::Remainder;


//BigInt Gcd(const BigInt & a, const BigInt & n);
#ifdef _MSC_VER
BigInt Generate_Prime(RandomNumberGenerator & rng, int pbits, BigInt const * dummy);
#endif

