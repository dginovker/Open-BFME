// cl: /MD /EHsc /DNDEBUG
// WWLib StringClass out-of-line bodies, verbatim from the Generals Zero Hour reference
// (GeneralsMD/.../WWVegas/WWLib/wwstring.cpp). BFME uses the Zero Hour variant of the
// file classes (see rawfile.cpp). The heavyweight WWLib includes are folded into
// wwstring.h as minimal stand-ins; WWMEMLOG expanded to nothing in the shipped build
// (USE_MEMLOG undefined), and Copy_Wide is omitted (it would drag in the wide Win32
// codepage imports the decomp toolchain has no headers for).
#include "wwstring.h"
#include <stdio.h>

#define WWMEMLOG(category)


///////////////////////////////////////////////////////////////////
//	Static member initialzation
///////////////////////////////////////////////////////////////////

FastCriticalSectionClass StringClass::m_Mutex;

TCHAR		StringClass::m_NullChar					= 0;
TCHAR *	StringClass::m_EmptyString				= &m_NullChar;

//
// A trick to optimize strings that are allocated from the stack and used only temporarily
//
// For alignment reasons we need twice as large block...
char StringClass::m_TempStrings[(StringClass::MAX_TEMP_STRING*2)*StringClass::MAX_TEMP_BYTES];

unsigned StringClass::ReservedMask=0;

///////////////////////////////////////////////////////////////////
//
//	Get_String
//
///////////////////////////////////////////////////////////////////
void
StringClass::Get_String (int length, bool is_temp)
{
	WWMEMLOG(MEM_STRINGS);

	if (!is_temp && length == 0) {
		m_Buffer = m_EmptyString;
		return;
	}

	TCHAR *string = NULL;

	//
	//	Should we attempt to use a temp buffer for this string?
	//
	if (is_temp && length <= MAX_TEMP_LEN && ReservedMask!=ALL_TEMP_STRINGS_USED_MASK) {

		//
		//	Make sure no one else is requesting a temp pointer
		// at the same time we are. There is a slight possibility that another
		// thread stole the last available buffer in between the if sentence and
		// the mutex lock, but that is a feature by design and doesn't cause
		// anything bad to happen.
		//
		FastCriticalSectionClass::LockClass m(m_Mutex);

		//
		//	Try to find an available temporary buffer
		//
		// TODO: Don't loop, there are better ways
		unsigned mask=1;
		for (int index = 0; index < MAX_TEMP_STRING; index ++, mask<<=1) {
			unsigned mask=1<<index;
			if (!(ReservedMask&mask)) {
				ReservedMask|=mask;

				//
				//	Grab this unused buffer for our string
				//
				unsigned temp_string=reinterpret_cast<unsigned>(m_TempStrings);
				temp_string+=MAX_TEMP_BYTES*MAX_TEMP_STRING;
				temp_string&=~(MAX_TEMP_BYTES*MAX_TEMP_STRING-1);
				temp_string+=index*MAX_TEMP_BYTES;
				temp_string+=sizeof(_HEADER);	// The buffer contains header as well, and it needs to be at the start
				string=reinterpret_cast<char*>(temp_string);

				Set_Buffer_And_Allocated_Length (string, MAX_TEMP_LEN);
				break;
			}
		}
	}

	if (string == NULL) {

		//
		//	Allocate a new string as necessary
		//
		if (length > 0) {
			Set_Buffer_And_Allocated_Length (Allocate_Buffer (length), length);
		} else {
			Free_String ();
		}
	}
}


///////////////////////////////////////////////////////////////////
//
//	Resize
//
///////////////////////////////////////////////////////////////////
void
StringClass::Resize (int new_len)
{
	WWMEMLOG(MEM_STRINGS);

	int allocated_len = Get_Allocated_Length ();
	if (new_len > allocated_len) {

		//
		//	Allocate the new buffer and copy the contents of our current
		// string.
		//
		TCHAR *new_buffer = Allocate_Buffer (new_len);
		_tcscpy (new_buffer, m_Buffer);

		//
		//	Switch to the new buffer
		//
		Set_Buffer_And_Allocated_Length (new_buffer, new_len);
	}

	return ;
}


///////////////////////////////////////////////////////////////////
//
//	Uninitialised_Grow
//
///////////////////////////////////////////////////////////////////
void
StringClass::Uninitialised_Grow (int new_len)
{
	WWMEMLOG(MEM_STRINGS);

	int allocated_len = Get_Allocated_Length ();
	if (new_len > allocated_len) {

		//
		//	Switch to a newly allocated buffer
		//
		TCHAR *new_buffer = Allocate_Buffer (new_len);
		Set_Buffer_And_Allocated_Length (new_buffer, new_len);
	}

	//
	// Whenever this function is called, clear the cached length
	//
	Store_Length (0);
	return ;
}


///////////////////////////////////////////////////////////////////
//
//	Uninitialised_Grow
//
///////////////////////////////////////////////////////////////////
void
StringClass::Free_String (void)
{
	if (m_Buffer != m_EmptyString) {

		unsigned buffer_base=reinterpret_cast<unsigned>(m_Buffer-sizeof (StringClass::_HEADER));
		unsigned temp_base=reinterpret_cast<unsigned>(m_TempStrings+MAX_TEMP_BYTES*MAX_TEMP_STRING);

		if ((buffer_base>>11)==(temp_base>>11)) {
			m_Buffer[0] = 0;

			//
			//	Make sure no one else is changing the reserved mask
			// at the same time we are.
			//
			FastCriticalSectionClass::LockClass m(m_Mutex);

			unsigned index=(buffer_base/MAX_TEMP_BYTES)&(MAX_TEMP_STRING-1);
			unsigned mask=1<<index;
			ReservedMask&=~mask;
		}
		else {

			//
			//	String wasn't temporary, so free the memory
			//
			char *buffer = ((char *)m_Buffer) - sizeof (StringClass::_HEADER);
			delete [] buffer;
		}

		//
		//	Reset the buffer
		//
		m_Buffer = m_EmptyString;
	}

	return ;
}


///////////////////////////////////////////////////////////////////
//
//	Format
//
///////////////////////////////////////////////////////////////////
int _cdecl
StringClass::Format_Args (const TCHAR *format, const va_list & arg_list )
{
	//
	// Make a guess at the maximum length of the resulting string
	//
	TCHAR temp_buffer[512] = { 0 };
	int retval = 0;

	//
	//	Format the string
	//
	#ifdef _UNICODE
		retval = _vsnwprintf (temp_buffer, 512, format, arg_list);
	#else
		retval = _vsnprintf (temp_buffer, 512, format, arg_list);
	#endif

	//
	//	Copy the string into our buffer
	//
	(*this) = temp_buffer;

	return retval;
}


///////////////////////////////////////////////////////////////////
//
//	Format
//
///////////////////////////////////////////////////////////////////
int _cdecl
StringClass::Format (const TCHAR *format, ...)
{
	va_list arg_list;
	va_start (arg_list, format);

	//
	// Make a guess at the maximum length of the resulting string
	//
	TCHAR temp_buffer[512] = { 0 };
	int retval = 0;

	//
	//	Format the string
	//
	#ifdef _UNICODE
		retval = _vsnwprintf (temp_buffer, 512, format, arg_list);
	#else
		retval = _vsnprintf (temp_buffer, 512, format, arg_list);
	#endif

	//
	//	Copy the string into our buffer
	//
	(*this) = temp_buffer;

	va_end (arg_list);
	return retval;
}


///////////////////////////////////////////////////////////////////
//
//	Release_Resources
//
///////////////////////////////////////////////////////////////////
void
// ?Release_Resources@StringClass@@QAEXXZ absent-from-retail
StringClass::Release_Resources (void)
{
	Free_String();
}
