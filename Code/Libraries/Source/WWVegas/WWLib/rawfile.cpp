// cl: /MD /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// WWLib RawFileClass, verbatim from the Generals Zero Hour reference
// (GeneralsMD/.../WWVegas/WWLib/rawfile.cpp) -- BFME uses the Zero Hour variant of
// the file classes (StringClass filename, Create/Delete/Get_Date_Time in the base).
// always.h is omitted (nothing here needs it); win.h is a minimal stand-in declaring
// the kernel32 imports (see src/w3d/win.h).
#include	"rawfile.h"
#include	<direct.h>
#include	<stddef.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include "win.h"
#include	<limits.h>
#include	<errno.h>


RawFileClass::RawFileClass(void) :
	Rights(READ),
	BiasStart(0),
	BiasLength(-1),
	Handle(NULL_HANDLE),
	Filename(""),
	Date(0),
	Time(0)
{
}



bool RawFileClass::Is_Open(void) const
{
	return(Handle != NULL_HANDLE);
}

RawFileClass::RawFileClass(char const * filename) :
	Rights(0),
	BiasStart(0),
	BiasLength(-1),
	Handle(NULL_HANDLE),
	Filename(filename),
	Date(0),
	Time(0)
{
}

RawFileClass::~RawFileClass(void)
{
	Reset ();
}

void RawFileClass::Reset(void)
{
	Close();
	Filename = "";
}

char const * RawFileClass::Set_Name(char const * filename)
{
	Bias(0);

	Filename=filename;

	/*
	** If this is a UNIX build, fix the filename from the DOS-like name passed in
	*/
	#ifdef _UNIX
		for (int i=0; i<Filename.Get_Length(); i++)
		{
			if (Filename[i]=='\\')
				Filename[i]='/';
			Filename[i]=tolower(Filename[i]);  // don't preserve case
		}
	#endif

	return(Filename);
}


int RawFileClass::Open(char const * filename, int rights)
{
	Set_Name(filename);
	return(Open(rights));
}


int RawFileClass::Open(int rights)
{
	Close();

	/*
	**	Verify that there is a filename associated with this file object. If not, then this is a
	**	big error condition.
	*/
	if (Filename.Get_Length()==0) {
		Error(ENOENT, false);
	}

	/*
	**	Record the access rights used for this open call. These rights will be used if the
	**	file object is duplicated.
	*/
	Rights = rights;

	/*
	**	Repetitively try to open the file. Abort if a fatal error condition occurs.
	*/
	for (;;) {

		/*
		**	Try to open the file according to the access rights specified.
		*/
		switch (rights) {

			/*
			**	If the access rights are not recognized, then report this as
			**	an invalid access code.
			*/
			default:
				errno = EINVAL;
				break;

			case READ:
				#ifdef _UNIX
					Handle = fopen(Filename, "r");
				#else
					Handle = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ,
								NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				#endif
				break;

			case WRITE:
				#ifdef _UNIX
					Handle = fopen(Filename, "w");
				#else
					Handle = CreateFileA(Filename, GENERIC_WRITE, 0,
								NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				#endif
				break;

			case READ|WRITE:
				#ifdef _UNIX
					Handle = fopen(Filename, "w");
				#else
					// SKB 5/13/99 use OPEN_ALWAYS instead of CREATE_ALWAYS so that files
					//					does not get destroyed.
					Handle = CreateFileA(Filename, GENERIC_READ | GENERIC_WRITE, 0,
								NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				#endif
				break;
		}

		/*
		**	Biased files must be positioned past the bias start position.
		*/
		if (BiasStart != 0 || BiasLength != -1) {
			Seek(0, SEEK_SET);
		}

		/*
		**	If the handle indicates the file is not open, then this is an error condition.
		**	For the case of the file cannot be found, then allow a retry. All other cases
		**	are fatal.
		*/
		if (Handle == NULL_HANDLE) {
			return(false);

//			Error(GetLastError(), false, Filename);
//			continue;
		}
		break;
	}

	return(true);
}


bool RawFileClass::Is_Available(int forced)
{
	if (Filename.Get_Length()==0) return(false);

	/*
	**	If the file is already open, then is must have already passed the availability check.
	**	Return true in this case.
	*/
	if (Is_Open()) return(true);

	/*
	**	If this is a forced check, then go through the normal open channels, since those
	**	channels ensure that the file must exist.
	*/
	if (forced) {
		RawFileClass::Open(READ);
		RawFileClass::Close();
		return(true);
	}

	/*
	**	Perform a raw open of the file. If this open fails for ANY REASON, including a missing
	**	CD-ROM, this routine will return a failure condition. In all but the missing file
	**	condition, go through the normal error recover channels.
	*/
	for (;;) {

		#ifdef _UNIX
			Handle=fopen(Filename,"r");
		#else
			Handle = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ,
							NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		#endif

		if (Handle == NULL_HANDLE) {
			return(false);
		}
		break;
	}

	/*
	**	Since the file could be opened, then close it and return that the file exists.
	*/
	int closeok;
	#ifdef _UNIX
		closeok=((fclose(Handle)==0)?TRUE:FALSE);
	#else
		closeok=CloseHandle(Handle);
	#endif
	if (! closeok) {
		Error(GetLastError(), false, Filename);
	}
	Handle = NULL_HANDLE;

	return(true);
}


void RawFileClass::Close(void)
{
	/*
	**	If the file is open, then close it. If the file is already closed, then just return. This
	**	isn't considered an error condition.
	*/
	if (Is_Open()) {

		/*
		**	Try to close the file. If there was an error (who knows what that could be), then
		**	call the error routine.
		*/
		int closeok;
		#ifdef _UNIX
			closeok=(fclose(Handle)==0)?TRUE:FALSE;
		#else
			closeok=CloseHandle(Handle);
		#endif

		if (!closeok) {
			Error(GetLastError(), false, Filename);
		}

		/*
		**	At this point the file must have been closed. Mark the file as empty and return.
		*/
		Handle = NULL_HANDLE;
	}
}


int RawFileClass::Read(void * buffer, int size)
{
	long	bytesread = 0;			// Running count of the number of bytes read into the buffer.
	int	opened = false;		// Was the file opened by this routine?

	/*
	**	If the file isn't opened, open it. This serves as a convenience
	**	for the programmer.
	*/
	if (!Is_Open()) {

		/*
		**	The error check here is moot. Open will never return unless it succeeded.
		*/
		if (!Open(READ)) {
			return(0);
		}
		opened = true;
	}

	/*
	**	A biased file has the requested read length limited to the bias length of
	**	the file.
	*/
	if (BiasLength != -1) {
		int remainder = BiasLength - Seek(0);
		size = size < remainder ? size : remainder;
	}

	long total = 0;
	while (size > 0) {
		bytesread = 0;

		int readok=TRUE;

		#ifdef _UNIX
			readok=TRUE;
			bytesread=fread(buffer,1,size,Handle);
			if ((bytesread == 0)&&( ! feof(Handle)))
				readok=ferror(Handle);
		#else
			readok=ReadFile(Handle, buffer, size, &(unsigned long&)bytesread, NULL);
		#endif


		if (! readok) {
			size -= bytesread;
			total += bytesread;
			Error(GetLastError(), true, Filename);
			continue;
		}
		size -= bytesread;
		total += bytesread;
		if (bytesread == 0) break;
	}
	bytesread = total;

	/*
	**	Close the file if it was opened by this routine and return
	**	the actual number of bytes read into the buffer.
	*/
	if (opened) Close();
	return(bytesread);
}


int RawFileClass::Write(void const * buffer, int size)
{
	long	byteswritten = 0;
	int	opened = false;		// Was the file manually opened?

	/*
	**	Check to open status of the file. If the file is open, then merely write to
	**	it. Otherwise, open the file for writing and then close the file when the
	**	output is finished.
	*/
	if (!Is_Open()) {
		if (!Open(WRITE)) {
			return(0);
		}
		opened = true;
	}

   int writeok=TRUE;
   #ifdef _UNIX
		byteswritten = fwrite(buffer, 1, size, Handle);
		if (byteswritten != size)
			writeok = FALSE;
	#else
		writeok=WriteFile(Handle, buffer, size, &(unsigned long&)byteswritten, NULL);
	#endif

	if (! writeok) {
		Error(GetLastError(), false, Filename);
	}

	/*
	**	Fixup the bias length if necessary.
	*/
	if (BiasLength != -1) {
		if (Raw_Seek(0) > BiasStart+BiasLength) {
			BiasLength = Raw_Seek(0) - BiasStart;
		}
	}

	/*
	**	If this routine had to open the file, then close it before returning.
	*/
	if (opened) {
		Close();
	}

	/*
	**	Return with the number of bytes written. This will always be the number of bytes
	**	requested, since the case of the disk being full is caught by this routine.
	*/
	return(byteswritten);
}


int RawFileClass::Seek(int pos, int dir)
{

	/*
	**	A file that is biased will have a seek operation modified so that the file appears to
	**	exist only within the bias range. All bytes outside of this range appear to be
	**	non-existant.
	*/
	if (BiasLength != -1) {
		switch (dir) {
			case SEEK_SET:
				if (pos > BiasLength) {
					pos = BiasLength;
				}
				pos += BiasStart;
				break;

			case SEEK_CUR:
				break;

			case SEEK_END:
				dir = SEEK_SET;
				pos += BiasStart + BiasLength;
//				pos = (pos <= BiasStart+BiasLength) ? pos : BiasStart+BiasLength;
//				pos = (pos >= BiasStart) ? pos : BiasStart;
				break;
		}

		/*
		**	Perform the modified raw seek into the file.
		*/
		long newpos = Raw_Seek(pos, dir) - BiasStart;

		/*
		**	Perform a final double check to make sure the file position fits with the bias range.
		*/
		if (newpos < 0) {
			newpos = Raw_Seek(BiasStart, SEEK_SET) - BiasStart;
		}
		if (newpos > BiasLength) {
			newpos = Raw_Seek(BiasStart+BiasLength, SEEK_SET) - BiasStart;
		}
		return(newpos);
	}

	/*
	**	If the file is not biased in any fashion, then the normal seek logic will
	**	work just fine.
	*/
	return(Raw_Seek(pos, dir));
}


int RawFileClass::Size(void)
{
	int size = 0;

	/*
	**	A biased file already has its length determined.
	*/
	if (BiasLength != -1) {
		return(BiasLength);
	}

	/*
	**	If the file is open, then proceed normally.
	*/
	if (Is_Open()) {

      #ifdef _UNIX
			fpos_t curpos,startpos,endpos;
			fgetpos(Handle,&curpos);

			fseek(Handle,0,SEEK_SET);
			fgetpos(Handle,&startpos);

			fseek(Handle,0,SEEK_END);
			fgetpos(Handle,&endpos);

			size=endpos-startpos;
			fsetpos(Handle,&curpos);
		#else
			size = GetFileSize(Handle, NULL);
		#endif

		/*
		**	If there was in internal error, then call the error function.
		*/
		if (size == 0xFFFFFFFF) {
			Error(GetLastError(), false, Filename);
		}

	} else {

		/*
		**	If the file wasn't open, then open the file and call this routine again. Count on
		**	the fact that the open function must succeed.
		*/
		if (Open()) {
			size = Size();

			/*
			**	Since we needed to open the file we must remember to close the file when the
			**	size has been determined.
			*/
			Close();
		}
	}

	BiasLength = size-BiasStart;
	return(BiasLength);
}


int RawFileClass::Create(void)
{
	Close();
	if (Open(WRITE)) {

		/*
		**	A biased file must be at least as long as the bias offset. Seeking to the
		**	appropriate start offset has the effect of lengthening the file to the
		**	correct length.
		*/
		if (BiasLength != -1) {
			Seek(0, SEEK_SET);
		}

		Close();
		return(true);
	}
	return(false);
}


int RawFileClass::Delete(void)
{
	/*
	**	If the file was open, then it must be closed first.
	*/
	Close();

	/*
	**	If there is no filename associated with this object, then this indicates a fatal error
	**	condition. Report this and abort.
	*/
	if (!Filename) {
		Error(ENOENT, false);
	}

	/*
	**	Repetitively try to delete the file if possible. Either return with success, or
	**	abort the program with an error.
	*/
	for (;;) {

		/*
		**	If the file is already missing, then return with this fact. No action is necessary.
		**	This can occur as this section loops if the file exists on a floppy and the floppy
		**	was removed, the file deleted on another machine, and then the floppy was
		**	reinserted. Admittedly, this is a rare case, but is handled here.
		*/
		if (!Is_Available()) {
			return(false);
		}

		int deleteok;
		#ifdef _UNIX
			deleteok=(unlink(Filename)==0)?TRUE:FALSE;
		#else
			deleteok=DeleteFile(Filename);
		#endif

		if (! deleteok) {
			Error(GetLastError(), false, Filename);
			return(false);
		}
		break;
	}

	/*
	**	DOS reports that the file was successfully deleted. Return with this fact.
	*/
	return(true);
}

unsigned long RawFileClass::Get_Date_Time(void)
{
	// Return value
	unsigned long retval = 0;

	// Ensure we will work properly if the file is not open
	if (Is_Open()) {
		// If file is open proceed normally
#ifdef _UNIX
		struct stat statbuf;
		lstat(Filename, &statbuf);
		retval = statbuf.st_mtime;
#else
		BY_HANDLE_FILE_INFORMATION info;

		if (GetFileInformationByHandle(Handle, &info)) {
			WORD dosdate;
			WORD dostime;
			FileTimeToDosDateTime(&info.ftLastWriteTime, &dosdate, &dostime);
			retval = (dosdate << 16) | dostime;
		}
#endif
	} else {
		// If file not open open it, if open succeeded proceed normally and then close to put
		// everything back the way we found it.
		if (Open()) {
#ifdef _UNIX
			struct stat statbuf;
			lstat(Filename, &statbuf);
			retval = statbuf.st_mtime;
#else
			BY_HANDLE_FILE_INFORMATION info;

			if (GetFileInformationByHandle(Handle, &info)) {
				WORD dosdate;
				WORD dostime;
				FileTimeToDosDateTime(&info.ftLastWriteTime, &dosdate, &dostime);
				retval = (dosdate << 16) | dostime;
			}
#endif
			Close();

		}
	}

	return retval;
}


bool RawFileClass::Set_Date_Time(unsigned long datetime)
{
#ifdef _UNIX
	assert(0);
	return(false);
#else
	if (RawFileClass::Is_Open()) {
		BY_HANDLE_FILE_INFORMATION info;

		if (GetFileInformationByHandle(Handle, &info)) {
			FILETIME filetime;
			if (DosDateTimeToFileTime((WORD)(datetime >> 16), (WORD)(datetime & 0x0FFFF), &filetime)) {
				return(SetFileTime(Handle, &info.ftCreationTime, &filetime, &filetime) != 0);
			}
		}
	}
	return(false);
#endif
}


void RawFileClass::Bias(int start, int length)
{
	if (start == 0) {
		BiasStart = 0;
		BiasLength = -1;
		return;
	}

	BiasLength = RawFileClass::Size();
	BiasStart += start;
	if (length != -1) {
		BiasLength = BiasLength < length ? BiasLength : length;
	}
	BiasLength = BiasLength > 0 ? BiasLength : 0;

	/*
	**	Move the current file offset to a legal position if necessary and the
	**	file was open.
	*/
	if (Is_Open()) {
		RawFileClass::Seek(0, SEEK_SET);
	}
}


int RawFileClass::Raw_Seek(int pos, int dir)
{
	/*
	**	If the file isn't opened, then this is a fatal error condition.
	*/
	if (!Is_Open()) {
		Error(EBADF, false, Filename);
	}

   #ifdef _UNIX
      pos=fseek(Handle, pos, dir);
   #else
		switch (dir) {
			case SEEK_SET:
				dir = FILE_BEGIN;
				break;

			case SEEK_CUR:
				dir = FILE_CURRENT;
				break;

			case SEEK_END:
				dir = FILE_END;
				break;
		}
		pos = SetFilePointer(Handle, pos, NULL, dir);
	#endif

	/*
	**	If there was an error in the seek, then bail with an error condition.
	*/
	if (pos == 0xFFFFFFFF) {
		Error(GetLastError(), false, Filename);
	}

	/*
	**	Return with the new position of the file. This will range between zero and the number of
	**	bytes the file contains.
	*/
	return(pos);
}

void RawFileClass::Attach (void *handle, int rights)
{
	Reset ();

	Rights = rights;
	BiasStart = 0;
	BiasLength = -1;
	Date = 0;
	Time = 0;

	#ifdef _UNIX
	  Handle = (FILE *)handle;
	#else
	  Handle = handle;
	#endif
}

void RawFileClass::Detach (void)
{
	Rights = 0;
	BiasStart = 0;
	BiasLength = -1;
	Date = 0;
	Time = 0;
	Handle = NULL_HANDLE;
}
