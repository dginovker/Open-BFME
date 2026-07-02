// cl: /DNDEBUG /MD


#include	"always.h"
#include	"readline.h"
#include	"trim.h"
#include	"wwfile.h"
#include	"xstraw.h"
#include	<string.h>


#if !defined(__BORLANDC__) && !defined(_MSC_VER)
// Disable the "temporary object used to initialize a non-constant reference" warning.
#pragma warning 665 9
#endif


int Read_Line(FileClass & file, char * buffer, int len, bool & eof)
{
	FileStraw fs(file);
	return(Read_Line(fs, buffer, len, eof));
}


int Read_Line(Straw & file, char * buffer, int len, bool & eof)
{
	if (len == 0 || buffer == NULL) return(0);

	int count = 0;
	for (;;) {
		char c;
		if (file.Get(&c, sizeof(c)) != sizeof(c)) {
			eof = true;
			buffer[count] = '\0';
			break;
		}

		if (c == '\x0A') break;
		if (c != '\x0D' && count+1 < len) {
			buffer[count++] = c;
		}
	}
	buffer[count] = '\0';

	strtrim(buffer);
	return(strlen(buffer));
}

int Read_Line(Straw & file, wchar_t * buffer, int len, bool & eof)
{
	if (len == 0 || buffer == NULL) return(0);

	int count = 0;
	for (;;) {
		wchar_t c;
		if (file.Get(&c, sizeof(c)) != sizeof(c)) {
			eof = true;
			buffer[count] = L'\0';
			break;
		}

		if (c == L'\x0A') break;
		if (c != L'\x0D' && count+1 < len) {
			buffer[count++] = c;
		}
	}
	buffer[count] = '\0';

	wcstrim(buffer);
	return(wcslen(buffer));
}
