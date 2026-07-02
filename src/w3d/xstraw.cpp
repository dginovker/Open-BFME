// cl: /DNDEBUG /MD


#include	"always.h"
#include	"xstraw.h"
#include	<stddef.h>
#include	<string.h>


int BufferStraw::Get(void * source, int slen)
{
	int total = 0;

	if (Is_Valid() && source != NULL && slen > 0) {
		int len = slen;
		if (BufferPtr.Get_Size() != 0) {
			int theoretical_max = BufferPtr.Get_Size() - Index;
			len = (slen < theoretical_max) ? slen : theoretical_max;
		}

		if (len > 0) {
			memmove(source, ((char*)BufferPtr.Get_Buffer()) + Index, len);
		}

		Index += len;
		total += len;
	}
	return(total);
}


int FileStraw::Get(void * source, int slen)
{
	if (Valid_File() && source != NULL && slen > 0) {
		if (!File->Is_Open()) {
			HasOpened = true;
			if (!File->Is_Available()) return(0);
			if (!File->Open(FileClass::READ)) return(0);
		}

		return(File->Read(source, slen));
	}
	return(0);
}


FileStraw::~FileStraw(void)
{
	if (Valid_File() && HasOpened) {
		File->Close();
		HasOpened = false;
		File = NULL;
	}
}
