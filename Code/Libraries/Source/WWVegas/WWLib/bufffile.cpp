// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// WWLib BufferedFileClass, verbatim from the Generals Zero Hour reference
// (GeneralsMD/.../WWVegas/WWLib/bufffile.cpp). Derives from RawFileClass; the
// BFME FileClass vtable drift lives in wwfile.h. always.h supplies W3DNEWARRAY
// (plain new under NDEBUG); wwdebug.h makes WWASSERT a no-op under release.
#include	"always.h"
#include	"bufffile.h"
#include	"wwdebug.h"
#include	<string.h>

int		BufferedFileClass::_DesiredBufferSize	=	1024*16;

BufferedFileClass::BufferedFileClass(void) :
	RawFileClass(),
	Buffer( NULL ),
	BufferSize( 0 ),
	BufferAvailable( 0 ),
	BufferOffset( 0 )
{
}

BufferedFileClass::BufferedFileClass(char const * filename) :
	RawFileClass( filename ),
	Buffer( NULL ),
	BufferSize( 0 ),
	BufferAvailable( 0 ),
	BufferOffset( 0 )
{
}

BufferedFileClass::~BufferedFileClass(void)
{
	Reset_Buffer();
}

void BufferedFileClass::Close(void)
{
	BASECLASS::Close();

	Reset_Buffer();
}


int BufferedFileClass::Read(void * buffer, int size)
{
	int read = 0;

	// If there is anything in the buffer, copy it in.
	if ( BufferAvailable > 0 ) {
		int amount = min( size, BufferAvailable );
		::memcpy( buffer, &Buffer[BufferOffset], amount );
		BufferAvailable -= amount;
		BufferOffset += amount;
		size -= amount;
		buffer = (char *)buffer + amount;
		read += amount;
	}

	if ( size == 0 ) {
		return read;
	}

	// We need to get a copy of the _DesiredBufferSize into
	// a local variable to protect us from modifications
	// from another thread. Otherwise, we could pass the test
	// (size > amount) below, only to allocate a buffer that's
	// too small in the next block. (DRM, 04/20/01)
	int desired_buffer_size = _DesiredBufferSize;

	// If we need more than the buffer will hold, just read it
	int amount = BufferSize;
	if ( amount == 0 ) {
		amount = desired_buffer_size;
	}
	if ( size > amount ) {
		return BASECLASS::Read( buffer, size ) + read;
	}

	// If we dont have a buffer, get one
	if ( BufferSize == 0 ) {
		BufferSize = desired_buffer_size;
		Buffer = W3DNEWARRAY unsigned char [BufferSize];
		BufferAvailable = 0;
		BufferOffset = 0;
	}

	// Fill the buffer
	if ( BufferAvailable == 0 ) {
		BufferAvailable = BASECLASS::Read( Buffer, BufferSize );
		BufferOffset = 0;
	}

	// If there is anything in the buffer, copy it in.
	if ( BufferAvailable > 0 ) {
		int amount = min( size, BufferAvailable );
		::memcpy( buffer, &Buffer[BufferOffset], amount );
		BufferAvailable -= amount;
		BufferOffset += amount;
		read += amount;
	}

	return read;
}


int BufferedFileClass::Write(void const * buffer, int size)
{
	if ( BufferSize != 0 ) {
		WWASSERT( 0 );
	}

	return BASECLASS::Write( buffer, size );
}


int BufferedFileClass::Seek(int pos, int dir)
{
	if ( (dir != SEEK_CUR) || (pos < 0) ) {
		Reset_Buffer();
	}

	// If not buffered, pass through
	if ( BufferAvailable == 0 ) {
		return BASECLASS::Seek( pos, dir );
	}

	// use up what we can of the buffer
	int amount = min( pos, BufferAvailable );
	pos -= amount;
	BufferAvailable -= amount;
	BufferOffset += amount;

	return BASECLASS::Seek( pos, dir ) - BufferAvailable;
}

void	BufferedFileClass::Reset_Buffer( void )
{
	if ( Buffer != NULL ) {
		delete [] Buffer;
		Buffer = NULL;
		BufferSize = 0;
		BufferAvailable = 0;
		BufferOffset = 0;
	}
}
