// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

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

