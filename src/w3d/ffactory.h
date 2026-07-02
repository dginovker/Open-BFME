// Minimal file-factory declarations for the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WWLib/ffactory.h) that ini.cpp needs. Only the
// abstract FileFactoryClass, the RawFileFactoryClass used for writing, the
// file_auto_ptr helper, and the two global factory pointers are declared here;
// SimpleFileFactoryClass and its mutex/vector/StringClass dependencies are
// omitted because ini.cpp never touches them. All bodies live in the game's
// ffactory.obj, reached by masked REL32 call.
#ifndef FFACTORY_H
#define FFACTORY_H

#include "rawfile.h"

class FileClass;

class FileFactoryClass {
public:
	virtual ~FileFactoryClass(void){};
	virtual FileClass * Get_File( char const *filename ) = 0;
	virtual void Return_File( FileClass *file ) = 0;
};

//
// Handy auto pointer class.  Prevents you from having to call Return_File manually
//
class file_auto_ptr
{
public:
	explicit	file_auto_ptr(FileFactoryClass *fac, const char *filename);
				~file_auto_ptr();

	operator FileClass*(void) const
		{return (get()); }

	FileClass& operator*() const
		{return (*get()); }

	FileClass *operator->() const
		{return (get()); }

	FileClass *get() const
		{return (_Ptr); }

private:
	// prevent these from getting auto-generated or used
						file_auto_ptr(const file_auto_ptr &other);
	file_auto_ptr	&operator=(const file_auto_ptr &other);


	FileClass			*_Ptr;
	FileFactoryClass	*_Fac;
};

/*
** RawFileFactoryClass is a derived FileFactoryClass which
** gives RawFileClass objects
*/
class	RawFileFactoryClass {
public:
	RawFileClass * Get_File( char const *filename );
	void Return_File( FileClass *file );
};

extern FileFactoryClass	*	_TheFileFactory;
extern RawFileFactoryClass	*	_TheWritingFileFactory;

#endif
