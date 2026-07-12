// cl: /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// WWLib Base64 encoder/decoder, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWLib/base64.cpp).
#include	"always.h"
#include	"base64.h"

/*
**	This is the magic padding character used to fill out the encoded data to a multiple of
**	4 characters even though the source data is less than necessary to accomplish this.
**	The pad character lets the decoder know of this condition and it will compensate
**	accordingly.
*/
static char const * const _pad = "=";

/*
**	This encoder translation table will convert a 6 bit number into an ASCII character.
*/
static char const * const _encoder = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
**	The decoder translation table takes an ASCII character and converts it into a
**	6 bit number.
*/
#define	BAD	0xFE			// Ignore this character in source data.
#define	END	0xFF			// Signifies premature end of input data.
static unsigned char const _decoder[256] = {
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,62,BAD,BAD,BAD,63,
	52,53,54,55,56,57,58,59,60,61,BAD,BAD,BAD,END,BAD,BAD,
	BAD,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
	15,16,17,18,19,20,21,22,23,24,25,BAD,BAD,BAD,BAD,BAD,
	BAD,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,51,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD
};

int const PacketChars = 4;


/*
**	The packet type is used to construct and disect the Base64 data blocks. The data
**	consists of three source data bytes mapped onto four 6 bit Base64 code elements.
*/
typedef union {
	struct {
#ifdef BIG_ENDIAN
		unsigned char C1;
		unsigned char C2;
		unsigned char C3;
#else
		unsigned char C3;
		unsigned char C2;
		unsigned char C1;
#endif
		unsigned char pad;
	} Char;
	struct {
#ifdef BIG_ENDIAN
		unsigned O1:6;
		unsigned O2:6;
		unsigned O3:6;
		unsigned O4:6;
#else
		unsigned O4:6;
		unsigned O3:6;
		unsigned O2:6;
		unsigned O1:6;
#endif
		unsigned pad:8;
	} SubCode;
	unsigned int Raw;
}	PacketType;


int Base64_Encode(void const * source, int slen, void * dest, int dlen)
{
	/*
	**	Check the parameters for legality.
	*/
	if (source == NULL || slen == 0 || dest == NULL || dlen == 0) {
		return(0);
	}

	/*
	**	Process the source data in blocks of three bytes. Fewer than three bytes
	**	results in special padding output characters (automatically discarded
	**	during the decode process).
	*/
	int total = 0;
	unsigned char const * sptr = (unsigned char const *)source;
	unsigned char * dptr = (unsigned char *)dest;
	while (slen > 0 && dlen >= PacketChars) {

		/*
		**	Fetch 24 bits of source data.
		*/
		PacketType packet;

		int pad = 0;
		packet.Raw = 0;
		packet.Char.C1 = *sptr++;
		slen--;
		if (slen) {
			packet.Char.C2 = *sptr++;
			slen--;
		} else {
			pad++;
		}
		if (slen) {
			packet.Char.C3 = *sptr++;
			slen--;
		} else {
			pad++;
		}

		/*
		**	Translate and write 4 characters of Base64 data. Pad with pad
		**	characters if there is insufficient source data for a full packet.
		*/
		*dptr++ = _encoder[packet.SubCode.O1];
		*dptr++ = _encoder[packet.SubCode.O2];
		if (pad < 2) {
			*dptr++ = _encoder[packet.SubCode.O3];
		} else {
			*dptr++ = _pad[0];
		}
		if (pad < 1) {
			*dptr++ = _encoder[packet.SubCode.O4];
		} else {
			*dptr++ = _pad[0];
		}

		dlen -= PacketChars;
		total += PacketChars;
	}

	/*
	**	Add a trailing null as a courtesy measure.
	*/
	if (dlen > 0) {
		*dptr = '\0';
	}

	/*
	**	Return with the total number of characters in the output buffer.
	*/
	return(total);
}


int Base64_Decode(void const * source, int slen, void * dest, int dlen)
{
	/*
	**	Check the parameters for legality.
	*/
	if (source == NULL || slen == 0 || dest == NULL || dlen == 0) {
		return(0);
	}

	int total = 0;
	unsigned char const * sptr = (unsigned char const *)source;
	unsigned char * dptr = (unsigned char *)dest;
	while (slen > 0 && dlen > 0) {

		PacketType packet;
		packet.Raw = 0;

		/*
		**	Process input until a full packet has been accumulated or the
		**	source is exhausted.
		*/
		int pcount = 0;
		while (pcount < PacketChars && slen > 0) {
			unsigned char c = *sptr++;
			slen--;

			unsigned char code = _decoder[c];

			/*
			**	An unrecognized character is skipped.
			*/
			if (code == BAD) continue;

			/*
			**	The "=" character signifies the end of data regardless of what
			**	the source buffer length value may be.
			*/
			if (code == END) {
				slen = 0;
				break;
			}

			/*
			**	A valid Base64 character was found so add it to the packet
			**	data.
			*/
			switch (pcount) {
				case 0:
					packet.SubCode.O1 = code;
					break;
				case 1:
					packet.SubCode.O2 = code;
					break;
				case 2:
					packet.SubCode.O3 = code;
					break;
				case 3:
					packet.SubCode.O4 = code;
					break;
			}
			pcount++;
		}

		/*
		**	A packet block is ready for output into the destination buffer.
		*/
		*dptr++ = packet.Char.C1;
		dlen--;
		total++;
		if (dlen > 0 && pcount > 2) {
			*dptr++ = packet.Char.C2;
			dlen--;
			total++;
		}
		if (dlen > 0 && pcount > 3) {
			*dptr++ = packet.Char.C3;
			dlen--;
			total++;
		}
	}

	/*
	**	Return with the total number of characters decoded into the
	**	output buffer.
	*/
	return(total);
}
