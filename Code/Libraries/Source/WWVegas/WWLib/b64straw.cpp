// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep


#include	"always.h"
#include	"b64straw.h"
#include	"base64.h"
#include	<string.h>


int Base64Straw::Get(void * source, int slen)
{
	int total = 0;

	char * from;
	int fromsize;
	char * to;
	int tosize;

	if (Control == ENCODE) {
		from = PBuffer;
		fromsize = sizeof(PBuffer);
		to = CBuffer;
		tosize = sizeof(CBuffer);
	} else {
		from = CBuffer;
		fromsize = sizeof(CBuffer);
		to = PBuffer;
		tosize = sizeof(PBuffer);
	}

	/*
	**	Process the byte request in code blocks until there are either
	**	no more source bytes available or the request has been fulfilled.
	*/
	while (slen > 0) {

		/*
		**	Transfer any processed bytes available to the request buffer.
		*/
		if (Counter > 0) {
			int len = (slen < Counter) ? slen : Counter;
			memmove(source, &to[tosize-Counter], len);
			Counter -= len;
			slen -= len;
			source = ((char *)source) + len;
			total += len;
		}
		if (slen == 0) break;

		/*
		**	More bytes are needed, so fetch and process another base 64 block.
		*/
		int incount = Straw::Get(from, fromsize);
		if (Control == ENCODE) {
			Counter = Base64_Encode(from, incount, to, tosize);
		} else {
			Counter = Base64_Decode(from, incount, to, tosize);
		}
		if (Counter == 0) break;
	}

	return(total);
}
