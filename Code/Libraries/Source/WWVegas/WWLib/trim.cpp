// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep


#include	"always.h"
#include	"trim.h"
#include	<string.h>

#ifdef _UNIX
#include	<wctype.h>
#endif // _UNIX


char* strtrim(char* buffer)
{
	if (buffer) {
		/* Strip leading white space from the string. */
		char* source = buffer;

		while ((*source != 0) && ((unsigned char)*source <= 32)) {
			++source;
		}

		if (source != buffer) {
			strcpy(buffer, source);
		}

		/* Clip trailing white space from the string. */
		for (int index = strlen(buffer) - 1; index >= 0; --index) {
			if ((*source != 0) && ((unsigned char)buffer[index] <= 32)) {
				buffer[index] = '\0';
			} else {
				break;
			}
		}
	}

	return buffer;
}


wchar_t* wcstrim(wchar_t* buffer)
{
	if (buffer) {
		/* Strip leading white space from the string. */
		wchar_t* source = buffer;

		while ((*source != 0) && ((unsigned int)*source <= 32)) {
			++source;
		}

		if (source != buffer) {
			wcscpy(buffer, source);
		}

		/* Clip trailing white space from the string. */
		for (int index = wcslen(buffer) - 1; index >= 0; --index) {
			if ((*source != 0) && ((unsigned int)buffer[index] <= 32)) {
				buffer[index] = L'\0';
			} else {
				break;
			}
		}
	}

	return buffer;
}
