// cl: /DNDEBUG /MD /GX

class BFMENetRequestPlayerLeaveCommandMsg
{
public:
	void *construct();
	void destruct();
	void setRequestedPlayerID(int playerID);
	int getRequestedPlayerID();
};

// BFME command type 7 is NETCOMMANDTYPE_REQUESTPLAYERLEAVE, not ZH run-ahead.
void *BFMENetRequestPlayerLeaveCommandMsg::construct()
{
	char *base = reinterpret_cast<char *>(this);
	*reinterpret_cast<unsigned int *>(base + 0x08) = 0xffffffff;
	*reinterpret_cast<unsigned short *>(base + 0x10) = 0;
	*reinterpret_cast<unsigned int *>(base + 0x0c) = 0;
	*reinterpret_cast<unsigned int *>(base + 0x04) = 0;
	*reinterpret_cast<unsigned int *>(base + 0x18) = 1;
	*reinterpret_cast<unsigned int *>(base) = 0x0111a5a0;
	*reinterpret_cast<unsigned int *>(base + 0x14) = 7;
	*reinterpret_cast<unsigned int *>(base + 0x1c) = 0xffffffff;
	return this;
}

void BFMENetRequestPlayerLeaveCommandMsg::destruct()
{
	*reinterpret_cast<unsigned int *>(this) = 0x0111a20c;
}

void BFMENetRequestPlayerLeaveCommandMsg::setRequestedPlayerID(int playerID)
{
	*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x1c) = playerID;
}

int BFMENetRequestPlayerLeaveCommandMsg::getRequestedPlayerID()
{
	return *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x1c);
}
