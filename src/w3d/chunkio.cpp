// cl: /DNDEBUG
// WWLib chunk file writer, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWLib/chunkio.cpp). Compiled with NDEBUG because
// the retail binary strips the asserts. Only the ChunkSaveClass side is here:
// BFME's ChunkLoadClass drifted from this reference (it carries an extra pointer
// member and reads through a two-way virtual dispatch), so none of its methods
// match these verbatim bodies. The ChunkHeader/MicroChunkHeader inline accessors
// still emit out-of-line copies that match.
#include "chunkio.h"
#include <string.h>
#include <assert.h>


ChunkSaveClass::ChunkSaveClass(FileClass * file) :
	File(file),
	StackIndex(0),
	InMicroChunk(false),
	MicroChunkPosition(0)
{
	memset(PositionStack,0,sizeof(PositionStack));
	memset(HeaderStack,0,sizeof(HeaderStack));
	memset(&MCHeader,0,sizeof(MCHeader));
}


bool ChunkSaveClass::Begin_Chunk(uint32 id)
{
	ChunkHeader	chunkh;
	int 			filepos;

	// If we have a parent chunk, set its 'Contains_Chunks' flag
	if (StackIndex > 0) {
		HeaderStack[StackIndex-1].Set_Sub_Chunk_Flag(true);
	}

	// Save the current file position and chunk header
	// for the call to End_Chunk.
	chunkh.Set_Type(id);
	chunkh.Set_Size(0);
	filepos = File->Seek(0);

	PositionStack[StackIndex] = filepos;
	HeaderStack[StackIndex] = chunkh;
	StackIndex++;

	// write a temporary chunk header (size = 0)
	if (File->Write(&chunkh,sizeof(chunkh)) != sizeof(chunkh)) {
		return false;
	}
	return true;
}


bool ChunkSaveClass::End_Chunk(void)
{
	// If the user didn't close his micro chunks bad things are gonna happen
	assert(!InMicroChunk);

	// Save the current position
	int curpos = File->Seek(0);

	// Pop the position and chunk header off the stacks
	StackIndex--;
	int chunkpos = PositionStack[StackIndex];
	ChunkHeader chunkh = HeaderStack[StackIndex];

	// write the completed header
	File->Seek(chunkpos,SEEK_SET);
	if (File->Write(&chunkh,sizeof(chunkh)) != sizeof(chunkh)) {
		return false;
	}

	// Add the total bytes written to any encompasing chunk
	if (StackIndex != 0) {
		HeaderStack[StackIndex-1].Add_Size(chunkh.Get_Size() + sizeof(chunkh));
	}

	// Go back to the end of the file
	File->Seek(curpos,SEEK_SET);

	return true;
}


bool ChunkSaveClass::Begin_Micro_Chunk(uint32 id)
{
	assert(id < 256);
	assert(!InMicroChunk);

	// Save the current file position and chunk header
	// for the call to End_Micro_Chunk.
	MCHeader.Set_Type(id);
	MCHeader.Set_Size(0);
	MicroChunkPosition = File->Seek(0);

	// Write a temporary chunk header
	// NOTE: I'm calling the ChunkSaveClass::Write method so that the bytes for
	// this header are tracked in the wrapping chunk.  This is because micro-chunks
	// are simply data inside the normal chunks...
	if (Write(&MCHeader,sizeof(MCHeader)) != sizeof(MCHeader)) {
		return false;
	}

	InMicroChunk = true;
	return true;
}


bool ChunkSaveClass::End_Micro_Chunk(void)
{
	assert(InMicroChunk);

	// Save the current position
	int curpos = File->Seek(0);

	// Seek back and write the micro chunk header
	File->Seek(MicroChunkPosition,SEEK_SET);
	if (File->Write(&MCHeader,sizeof(MCHeader)) != sizeof(MCHeader)) {
		return false;
	}

	// Go back to the end of the file
	File->Seek(curpos,SEEK_SET);
	InMicroChunk = false;
	return true;
}


uint32 ChunkSaveClass::Write(const void * buf, uint32 nbytes)
{
	// If this assert hits, you mixed data and chunks within the same chunk NO NO!
	assert(HeaderStack[StackIndex-1].Get_Sub_Chunk_Flag() == 0);

	// If this assert hits, you didnt open any chunks yet
	assert(StackIndex > 0);

	// write the bytes into the file
	if (File->Write(buf,nbytes) != (int)nbytes) return 0;

	// track them in the wrapping chunk
	HeaderStack[StackIndex-1].Add_Size(nbytes);

	// track them if you are using a micro-chunk too.
	if (InMicroChunk) {
		assert(MCHeader.Get_Size() < 255 - nbytes);	// micro chunks can only be 255 bytes
		MCHeader.Add_Size(nbytes);
	}

	return nbytes;
}


uint32 ChunkSaveClass::Write(const IOVector2Struct & v)
{
	return Write(&v,sizeof(v));
}


uint32 ChunkSaveClass::Write(const IOVector3Struct & v)
{
	return Write(&v,sizeof(v));
}
