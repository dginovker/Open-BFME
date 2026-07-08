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
__declspec(naked) void *BFMENetRequestPlayerLeaveCommandMsg::construct()
{
	__asm {
		mov eax, ecx
		xor ecx, ecx
		or edx, 0FFFFFFFFh
		mov dword ptr [eax+08h], edx
		mov word ptr [eax+10h], cx
		mov dword ptr [eax+0Ch], ecx
		mov dword ptr [eax+04h], ecx
		mov dword ptr [eax+18h], 1
		mov dword ptr [eax], 0111A5A0h
		mov dword ptr [eax+14h], 7
		mov dword ptr [eax+1Ch], edx
		ret
	}
}

__declspec(naked) void BFMENetRequestPlayerLeaveCommandMsg::destruct()
{
	__asm {
		mov dword ptr [ecx], 0111A20Ch
		ret
	}
}

__declspec(naked) void BFMENetRequestPlayerLeaveCommandMsg::setRequestedPlayerID(int playerID)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		mov dword ptr [ecx+1Ch], eax
		ret 4
	}
}

__declspec(naked) int BFMENetRequestPlayerLeaveCommandMsg::getRequestedPlayerID()
{
	__asm {
		mov eax, dword ptr [ecx+1Ch]
		ret
	}
}
