// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

#include "GameNetwork/NetCommandMsg.h"

NetCommandMsg::~NetCommandMsg()
{
}

NetWrapperCommandMsg::~NetWrapperCommandMsg()
{
	if (m_data != NULL) {
		delete m_data;
		m_data = NULL;
	}
}

void NetWrapperCommandMsg::setData(UnsignedByte *data, UnsignedInt dataLength)
{
	if (m_data != NULL) {
		delete m_data;
		m_data = NULL;
	}

	m_data = NEW UnsignedByte[dataLength];
	memcpy(m_data, data, dataLength);
	m_dataLength = dataLength;
}

UnsignedByte * NetWrapperCommandMsg::getData()
{
	return m_data;
}

UnsignedInt NetWrapperCommandMsg::getDataLength()
{
	return m_dataLength;
}

UnsignedInt NetWrapperCommandMsg::getDataOffset()
{
	return m_dataOffset;
}

void NetWrapperCommandMsg::setDataOffset(UnsignedInt offset)
{
	m_dataOffset = offset;
}

UnsignedInt NetWrapperCommandMsg::getTotalDataLength()
{
	return m_totalDataLength;
}

void NetWrapperCommandMsg::setTotalDataLength(UnsignedInt totalDataLength)
{
	m_totalDataLength = totalDataLength;
}

UnsignedInt NetWrapperCommandMsg::getChunkNumber()
{
	return m_chunkNumber;
}

void NetWrapperCommandMsg::setChunkNumber(UnsignedInt chunkNumber)
{
	m_chunkNumber = chunkNumber;
}

UnsignedInt NetWrapperCommandMsg::getNumChunks()
{
	return m_numChunks;
}

void NetWrapperCommandMsg::setNumChunks(UnsignedInt numChunks)
{
	m_numChunks = numChunks;
}

UnsignedShort NetWrapperCommandMsg::getWrappedCommandID()
{
	return m_wrappedCommandID;
}

void NetWrapperCommandMsg::setWrappedCommandID(UnsignedShort wrappedCommandID)
{
	m_wrappedCommandID = wrappedCommandID;
}

void NetFileCommandMsg::setFileData(UnsignedByte *data, UnsignedInt dataLength)
{
	m_dataLength = dataLength;
	m_data = NEW UnsignedByte[dataLength];
	memcpy(m_data, data, dataLength);
}
