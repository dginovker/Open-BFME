// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

#include "Common/GameEngine.h"
#include "Common/MessageStream.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "GameClient/Shell.h"
#include "GameClient/MessageBox.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameNetwork/NetworkInterface.h"
#include "GameNetwork/Transport.h"
#include "GameNetwork/Udp.h"

class Network : public NetworkInterface
{
public:
	Network();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);
	virtual void liteupdate(void);
	Bool deinit(void);

	virtual void setLocalAddress(UnsignedInt ip, UnsignedInt port);
	virtual UnsignedInt getRunAhead(void) { return m_runAhead; }
	virtual UnsignedInt getFrameRate(void) { return m_frameRate; }
	virtual UnsignedInt getPacketArrivalCushion(void);
	virtual Bool isFrameDataReady(void);
	virtual void parseUserList(const GameInfo *game);
	virtual void startGame(void);

	virtual void sendChat(UnicodeString text, Int playerMask);
	virtual void sendDisconnectChat(UnicodeString text);

	virtual void sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
	virtual UnsignedShort sendFileAnnounce(AsciiString path, UnsignedByte playerMask);
	virtual Int getFileTransferProgress(Int playerID, AsciiString path);
	virtual Bool areAllQueuesEmpty(void);

	virtual void quitGame();
	virtual void selfDestructPlayer(Int index);

	virtual void voteForPlayerDisconnect(Int slot);
	virtual Bool isPacketRouter(void);

	virtual Real getIncomingBytesPerSecond(void);
	virtual Real getIncomingPacketsPerSecond(void);
	virtual Real getOutgoingBytesPerSecond(void);
	virtual Real getOutgoingPacketsPerSecond(void);
	virtual Real getUnknownBytesPerSecond(void);
	virtual Real getUnknownPacketsPerSecond(void);

	virtual void updateLoadProgress(Int percent);
	virtual void loadProgressComplete(void);
	virtual void sendTimeOutGameStart(void);

#if defined(_INTERNAL) || defined(_DEBUG)
	virtual void toggleNetworkOn();
#endif

	virtual UnsignedInt getLocalPlayerID(void);
	virtual UnicodeString getPlayerName(Int playerNum);
	virtual Int getNumPlayers(void);

	virtual Int getAverageFPS() { return m_conMgr->getAverageFPS(); }
	virtual Int getSlotAverageFPS(Int slot);

	virtual void attachTransport(Transport *transport);
	virtual void initTransport();

	virtual void setSawCRCMismatch(void);
	virtual Bool sawCRCMismatch(void) { return m_sawCRCMismatch; }
	virtual Bool isPlayerConnected(Int playerID);

	virtual void notifyOthersOfCurrentFrame(void);
	virtual void notifyOthersOfNewFrame(UnsignedInt frame);

	virtual Int getExecutionFrame(void);

	virtual UnsignedInt getPingFrame();
	virtual Int getPingsSent();
	virtual Int getPingsRecieved();

protected:
	void GetCommandsFromCommandList(void);
	void SendCommandsToConnectionManager(void);
	Bool AllCommandsReady(UnsignedInt frame);
	void RelayCommandsToCommandList(UnsignedInt frame);
	Bool isTransferCommand(GameMessage *msg);
	Bool processCommand(GameMessage *msg);
	void processFrameSynchronizedNetCommand(NetCommandRef *msg);
	void processRunAheadCommand(NetRunAheadCommandMsg *msg);
	void processDestroyPlayerCommand(NetDestroyPlayerCommandMsg *msg);
	void endOfGameCheck(void);
	Bool timeForNewFrame(void);

	ConnectionManager *m_conMgr;
	UnsignedInt m_lastFrame;
	NetLocalStatus m_localStatus;
	Int m_runAhead;
	Int m_frameRate;
	Int m_lastExecutionFrame;
	Int m_lastFrameCompleted;
	Bool m_didSelfSlug;
	__int64 m_perfCountFreq;
	__int64 m_nextFrameTime;
	Bool m_frameDataReady;
	Bool m_checkCRCsThisFrame;
	Bool m_sawCRCMismatch;
	std::vector<UnsignedInt> m_CRC[MAX_SLOTS];
	std::list<Int> m_playersToDisconnect;
	GameWindow *m_messageWindow;

#if defined(_DEBUG) || defined(_INTERNAL)
	Bool m_networkOn;
#endif
};

NetworkInterface *NetworkInterface::createNetwork()
{
	return NEW Network;
}

Bool Network::isPacketRouter(void)
{
	return m_conMgr && m_conMgr->isPacketRouter();
}
