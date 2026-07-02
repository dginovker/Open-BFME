// cl: /DNDEBUG /MD


#include	"cstraw.h"
#include	<string.h>


int CacheStraw::Get(void * source, int slen)
{
	int total = 0;

	if (Is_Valid() && source != NULL && slen > 0) {

		/*
		**	Keep processing the data request until there is no more data to supply or the request
		**	has been fulfilled.
		*/
		while (slen > 0) {

			/*
			**	First try to fetch the data from data previously loaded into the buffer.
			*/
			if (Length > 0) {
				int tocopy = (Length < slen) ? Length : slen;
				memmove(source, ((char *)BufferPtr.Get_Buffer()) + Index, tocopy);
				slen -= tocopy;
				Index += tocopy;
				total += tocopy;
				Length -= tocopy;
				source = (char*)source + tocopy;
			}
			if (slen == 0) break;

			/*
			**	Since there is more to be fulfilled yet the holding buffer is empty,
			**	refill the buffer with a fresh block of data from the source.
			*/
			Length = Straw::Get(BufferPtr, BufferPtr.Get_Size());
			Index = 0;
			if (Length == 0) break;
		}
	}
	return(total);
}
