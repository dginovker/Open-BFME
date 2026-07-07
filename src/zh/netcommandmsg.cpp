// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

void NetFileCommandMsg::setFileData(UnsignedByte *data, UnsignedInt dataLength)
{
	m_dataLength = dataLength;
	m_data = NEW UnsignedByte[dataLength];
	memcpy(m_data, data, dataLength);
}
