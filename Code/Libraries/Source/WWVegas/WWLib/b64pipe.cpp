// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep


#include	"always.h"
#include	"b64pipe.h"
#include	"base64.h"
#include	<string.h>


int Base64Pipe::Put(void const * source, int slen)
{
	if (source == NULL || slen < 1) {
		return(Pipe::Put(source, slen));
	}

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

	if (Counter > 0) {
		int len = (slen < (fromsize-Counter)) ? slen : (fromsize-Counter);
		memmove(&from[Counter], source, len);
		Counter += len;
		slen -= len;
		source = ((char *)source) + len;

		if (Counter == fromsize) {
			int outcount;
			if (Control == ENCODE) {
				outcount = Base64_Encode(from, fromsize, to, tosize);
			} else {
				outcount = Base64_Decode(from, fromsize, to, tosize);
			}
			total += Pipe::Put(to, outcount);
			Counter = 0;
		}
	}

	while (slen >= fromsize) {
		int outcount;
		if (Control == ENCODE) {
			outcount = Base64_Encode(source, fromsize, to, tosize);
		} else {
			outcount = Base64_Decode(source, fromsize, to, tosize);
		}
		source = ((char *)source) + fromsize;
		total += Pipe::Put(to, outcount);
		slen -= fromsize;
	}

	if (slen > 0) {
		memmove(from, source, slen);
		Counter = slen;
	}

	return(total);
}


int Base64Pipe::Flush(void)
{
	int len = 0;

	if (Counter) {
		if (Control == ENCODE) {
			int chars = Base64_Encode(PBuffer, Counter, CBuffer, sizeof(CBuffer));
			len += Pipe::Put(CBuffer, chars);
		} else {
			int chars = Base64_Decode(CBuffer, Counter, PBuffer, sizeof(PBuffer));
			len += Pipe::Put(PBuffer, chars);
		}
		Counter = 0;
	}
	len += Pipe::Flush();
	return(len);
}
