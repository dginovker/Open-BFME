// StringClass, matching the layout and inline bodies of the Generals Zero Hour
// reference (Libraries/Source/WWVegas/WWLib/wwstring.h). StringClass has no vtable
// and a single member (m_Buffer), so this reproduces the object layout exactly.
// RawFileClass only touches the inline members near the top (operator=, ctor, dtor,
// Get_Length, operator[], operator const TCHAR *). The temp-string pool, mutex and
// private helpers below are declared so the out-of-line bodies in wwstring.cpp
// compile and byte-match; the heavyweight WWLib includes (win.h/mutex.h/wwmemlog.h)
// are folded in here as the minimal stand-ins the decomp toolchain can build.
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __WWSTRING_H
#define __WWSTRING_H

#include <string.h>
#include <tchar.h>
#include <stdarg.h>

#ifndef WWASSERT
#define WWASSERT(exp)
#endif

// The reference allocates string buffers with W3DNEWARRAY; with no _DEBUG/_INTERNAL
// (release build) it collapses to a plain operator new[], which is what the game emitted.
#ifndef W3DNEWARRAY
#define W3DNEWARRAY new
#endif

// Minimal stand-in for the WWLib mutex.h primitive that Get_String/Free_String lock
// with. In the reference, LockClass's ctor holds an inline asm spin whose labels stop
// MSVC inlining it, so the compiler emits the spin out-of-line and inlines away the
// lock object itself -- every call site becomes `mov ecx,&mutex; call spin`, and the
// dtor a direct `mov [&mutex],0`. Modelling the spin as a fastcall prototype (resolved
// through reverse/symbols.csv to that shared out-of-line body) reproduces exactly that
// codegen; a verbatim asm ctor instead materialises the object and does not match.
class FastCriticalSectionClass
{
	unsigned Flag;

public:
	FastCriticalSectionClass() : Flag(0) {}

	class LockClass
	{
		FastCriticalSectionClass& cs;
		static void __fastcall spin(unsigned* flag);
	public:
		__forceinline LockClass(FastCriticalSectionClass& critical_section) : cs(critical_section)
		{
			spin(&cs.Flag);
		}

		~LockClass()
		{
			cs.Flag=0;
		}

	private:
		LockClass &operator=(const LockClass&);
		LockClass(const LockClass&);
	};

	friend class LockClass;
};

class StringClass
{
public:

	StringClass (bool hint_temporary);
	StringClass (const StringClass &string, bool hint_temporary = false);
	StringClass (const TCHAR *string, bool hint_temporary = false);
	~StringClass (void);

	inline const StringClass &operator= (const StringClass &string);
	inline const StringClass &operator= (const TCHAR *string);

	const StringClass &operator+= (const StringClass &string);
	const StringClass &operator+= (const TCHAR *string);
	const StringClass &operator+= (TCHAR ch);

	friend StringClass operator+ (const StringClass &string1, const StringClass &string2);
	friend StringClass operator+ (const TCHAR *string1, const StringClass &string2);
	friend StringClass operator+ (const StringClass &string1, const TCHAR *string2);

	const TCHAR & operator[] (int index) const;
	TCHAR & operator[] (int index);
	inline operator const TCHAR * (void) const;

	inline int	Get_Length (void) const;
	bool			Is_Empty (void) const;

	int _cdecl  Format (const TCHAR *format, ...);
	int _cdecl  Format_Args (const TCHAR *format, const va_list & arg_list );

	TCHAR *		Get_Buffer (int new_length);
	TCHAR *		Peek_Buffer (void);
	const TCHAR * Peek_Buffer (void) const;

	void	Release_Resources (void);

private:

	typedef struct _HEADER
	{
		int	allocated_length;
		int	length;
	} HEADER;

	// Note: Don't change these enums without withs checking the Get_String() and Free_String() function!
	enum
	{
		MAX_TEMP_STRING	= 8,
		MAX_TEMP_LEN		= 256-sizeof(_HEADER),
		MAX_TEMP_BYTES		= (MAX_TEMP_LEN * sizeof (TCHAR)) + sizeof (HEADER),
		ALL_TEMP_STRINGS_USED_MASK = 0xff
	};

	void			Get_String (int length, bool is_temp);
	TCHAR *		Allocate_Buffer (int length);
	void			Resize (int size);
	void			Uninitialised_Grow (int length);
	void			Free_String (void);

	inline void	Store_Length (int length);
	inline void	Store_Allocated_Length (int allocated_length);
	inline HEADER * Get_Header (void) const;
	int			Get_Allocated_Length (void) const;

	void			Set_Buffer_And_Allocated_Length (TCHAR *buffer, int length);

	TCHAR *		m_Buffer;

	static TCHAR	m_NullChar;
	static TCHAR *	m_EmptyString;

	static unsigned ReservedMask;
	static char m_TempStrings[];

	static FastCriticalSectionClass m_Mutex;
};

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator= (const TCHAR *string)
{
	if (string != 0) {

		int len = _tcslen (string);
		Uninitialised_Grow (len+1);
		Store_Length (len);

		::memcpy (m_Buffer, string, (len + 1) * sizeof (TCHAR));
	}

	return (*this);
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline
StringClass::StringClass (const TCHAR *string, bool hint_temporary)
	:	m_Buffer (m_EmptyString)
{
	int len=string ? _tcsclen(string) : 0;
	if (hint_temporary || len>0) {
		Get_String (len+1, hint_temporary);
	}

	(*this) = string;
	return ;
}

///////////////////////////////////////////////////////////////////
//	~StringClass
///////////////////////////////////////////////////////////////////
inline
StringClass::~StringClass (void)
{
	Free_String ();
	return ;
}

///////////////////////////////////////////////////////////////////
//	operator const TCHAR *
///////////////////////////////////////////////////////////////////
inline
StringClass::operator const TCHAR * (void) const
{
	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	Get_Length
///////////////////////////////////////////////////////////////////
inline int
StringClass::Get_Length (void) const
{
	int length = 0;

	if (m_Buffer != m_EmptyString) {

		//
		//	Read the length from the header
		//
		HEADER *header	= Get_Header ();
		length			= header->length;

		//
		//	Hmmm, a zero length was stored in the header,
		// we better manually get the string length.
		//
		if (length == 0) {
			length = _tcslen (m_Buffer);
			((StringClass *)this)->Store_Length (length);
		}
	}

	return length;
}

///////////////////////////////////////////////////////////////////
//	Get_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *
StringClass::Get_Buffer (int new_length)
{
	Uninitialised_Grow (new_length);

	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	Get_Allocated_Length
//
//	Return allocated size of the string buffer
///////////////////////////////////////////////////////////////////
inline int
StringClass::Get_Allocated_Length (void) const
{
	int allocated_length = 0;

	//
	//	Read the allocated length from the header
	//
	if (m_Buffer != m_EmptyString) {
		HEADER *header		= Get_Header ();
		allocated_length	= header->allocated_length;
	}

	return allocated_length;
}

///////////////////////////////////////////////////////////////////
// Get_Header
///////////////////////////////////////////////////////////////////
inline StringClass::HEADER *
StringClass::Get_Header (void) const
{
	return reinterpret_cast<HEADER *>(((char *)m_Buffer) - sizeof (StringClass::_HEADER));
}

///////////////////////////////////////////////////////////////////
// Store_Length
///////////////////////////////////////////////////////////////////
inline void
StringClass::Store_Length (int length)
{
	if (m_Buffer != m_EmptyString) {
		HEADER *header		= Get_Header ();
		header->length		= length;
	} else {
		WWASSERT (length == 0);
	}

	return ;
}

///////////////////////////////////////////////////////////////////
// Store_Allocated_Length
///////////////////////////////////////////////////////////////////
inline void
StringClass::Store_Allocated_Length (int allocated_length)
{
	if (m_Buffer != m_EmptyString) {
		HEADER *header					= Get_Header ();
		header->allocated_length	= allocated_length;
	} else {
		WWASSERT (allocated_length == 0);
	}

	return ;
}

///////////////////////////////////////////////////////////////////
//	Set_Buffer_And_Allocated_Length
//
// Set buffer pointer and init size variable. Length is set to 0
// as the contents of the new buffer are not necessarily defined.
///////////////////////////////////////////////////////////////////
inline void
StringClass::Set_Buffer_And_Allocated_Length (TCHAR *buffer, int length)
{
	Free_String ();
	m_Buffer = buffer;

	//
	//	Update the header (if necessary)
	//
	if (m_Buffer != m_EmptyString) {
		Store_Allocated_Length (length);
		Store_Length (0);
	} else {
		WWASSERT (length == 0);
	}

	return ;
}

///////////////////////////////////////////////////////////////////
// Allocate_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *
StringClass::Allocate_Buffer (int length)
{
	//
	//	Allocate a buffer that is 'length' characters long, plus the
	// bytes required to hold the header.
	//
	char *buffer = W3DNEWARRAY char[(sizeof (TCHAR) * length) + sizeof (StringClass::_HEADER)];

	//
	//	Fill in the fields of the header
	//
	HEADER *header					= reinterpret_cast<HEADER *>(buffer);
	header->length					= 0;
	header->allocated_length	= length;

	//
	//	Return the buffer as if it was a TCHAR pointer
	//
	return reinterpret_cast<TCHAR *>(buffer + sizeof (StringClass::_HEADER));
}

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator= (const StringClass &string)
{
	int len = string.Get_Length();
	Uninitialised_Grow(len+1);
	Store_Length(len);

	::memcpy (m_Buffer, string.m_Buffer, (len+1) * sizeof (TCHAR));
	return (*this);
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline
StringClass::StringClass (bool hint_temporary)
	:	m_Buffer (m_EmptyString)
{
	Get_String (MAX_TEMP_LEN, hint_temporary);
	m_Buffer[0]	= m_NullChar;

	return ;
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline
StringClass::StringClass (const StringClass &string, bool hint_temporary)
 	:	m_Buffer (m_EmptyString)
{
	if (hint_temporary || (string.Get_Length()>0)) {
		Get_String (string.Get_Length()+1, hint_temporary);
	}

	(*this) = string;
	return ;
}

///////////////////////////////////////////////////////////////////
//	Is_Empty
///////////////////////////////////////////////////////////////////
inline bool
StringClass::Is_Empty (void) const
{
	return (m_Buffer[0] == m_NullChar);
}

///////////////////////////////////////////////////////////////////
//	Peek_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *
StringClass::Peek_Buffer (void)
{
	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	Peek_Buffer
///////////////////////////////////////////////////////////////////
inline const TCHAR *
StringClass::Peek_Buffer (void) const
{
	return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator+= (const TCHAR *string)
{
	WWASSERT (string != NULL);

	int cur_len = Get_Length ();
	int src_len = _tcslen (string);
	int new_len = cur_len + src_len;

	//
	//	Make sure our buffer is large enough to hold the new string
	//
	Resize (new_len + 1);
	Store_Length (new_len);

	//
	//	Copy the new string onto our the end of our existing buffer
	//
	::memcpy (&m_Buffer[cur_len], string, (src_len + 1) * sizeof (TCHAR));
	return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator+= (TCHAR ch)
{
	int cur_len = Get_Length ();
	Resize (cur_len + 2);

	m_Buffer[cur_len]			= ch;
	m_Buffer[cur_len + 1]	= m_NullChar;

	if (ch != m_NullChar) {
		Store_Length (cur_len + 1);
	}

	return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &
StringClass::operator+= (const StringClass &string)
{
	int src_len = string.Get_Length();
	if (src_len > 0) {
		int cur_len = Get_Length ();
		int new_len = cur_len + src_len;

		//
		//	Make sure our buffer is large enough to hold the new string
		//
		Resize (new_len + 1);
		Store_Length (new_len);

		//
		//	Copy the new string onto our the end of our existing buffer
		//
		::memcpy (&m_Buffer[cur_len], (const TCHAR *)string, (src_len + 1) * sizeof (TCHAR));
	}

	return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator+
///////////////////////////////////////////////////////////////////
inline StringClass
operator+ (const StringClass &string1, const StringClass &string2)
{
	StringClass new_string(string1, true);
	new_string += string2;
	return new_string;
}

///////////////////////////////////////////////////////////////////
//	operator+
///////////////////////////////////////////////////////////////////
inline StringClass
operator+ (const TCHAR *string1, const StringClass &string2)
{
	StringClass new_string(string1, true);
	new_string += string2;
	return new_string;
}

///////////////////////////////////////////////////////////////////
//	operator+
///////////////////////////////////////////////////////////////////
inline StringClass
operator+ (const StringClass &string1, const TCHAR *string2)
{
	StringClass new_string(string1, true);
	StringClass new_string2(string2, true);
	new_string += new_string2;
	return new_string;
}

#endif //__WWSTRING_H
