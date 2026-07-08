// cl: /DNDEBUG /MD /GX

typedef bool Bool;

class BFMEConnectionManager
{
public:
	Bool isPlayerConnected(int playerID);
	Bool isPlayerConnectedForTimeout(int playerID, unsigned int timeout);
	Bool hasPacketRouterFrameStall();
	void processRequestFrameDataCommand(void *msg);
};

class BFMEDisconnectManager
{
public:
	Bool hasDisconnectScreenNotifyTimedOut(int playerID);
};

__declspec(naked) Bool BFMEConnectionManager::isPlayerConnected(int playerID)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		cmp eax, dword ptr [ecx+12028h]
		jne notLocalPlayer
		mov al, 1
		ret 4
notLocalPlayer:
		push esi
		mov esi, dword ptr [ecx+eax*4+04h]
		test esi, esi
		je connected
		mov eax, dword ptr [esi+34Ch]
		test eax, eax
		jne testTimeout
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		mov dword ptr [esi+34Ch], eax
connected:
		mov al, 1
		pop esi
		ret 4
testTimeout:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov edx, dword ptr [ecx+3Ch]
		__emit 03Bh
		__emit 015h
		__emit 050h
		__emit 0ADh
		__emit 00Eh
		__emit 001h
		jb earlyFrameTimeout
		mov edx, dword ptr [esi+34Ch]
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov ecx, dword ptr [ecx+0CBCh]
		sub eax, edx
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 4
earlyFrameTimeout:
		__emit 08Bh
		__emit 015h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov ecx, dword ptr [edx+0CBCh]
		sub eax, dword ptr [esi+34Ch]
		shl ecx, 2
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 4
	}
}

__declspec(naked) Bool BFMEConnectionManager::isPlayerConnectedForTimeout(int playerID, unsigned int timeout)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		cmp eax, dword ptr [ecx+12028h]
		jne notLocalPlayer
		mov al, 1
		ret 8
notLocalPlayer:
		push esi
		mov esi, dword ptr [ecx+eax*4+04h]
		test esi, esi
		je connected
		mov eax, dword ptr [esi+34Ch]
		test eax, eax
		jne testTimeout
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		mov dword ptr [esi+34Ch], eax
connected:
		mov al, 1
		pop esi
		ret 8
testTimeout:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov edx, dword ptr [ecx+3Ch]
		__emit 03Bh
		__emit 015h
		__emit 050h
		__emit 0ADh
		__emit 00Eh
		__emit 001h
		jb earlyFrameTimeout
		mov edx, dword ptr [esi+34Ch]
		mov ecx, dword ptr [esp+0Ch]
		sub eax, edx
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 8
earlyFrameTimeout:
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edx, dword ptr [esi+34Ch]
		mov ecx, dword ptr [ecx+0CBCh]
		sub eax, edx
		shl ecx, 2
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 8
	}
}

__declspec(naked) Bool BFMEConnectionManager::hasPacketRouterFrameStall()
{
	__asm {
		mov eax, dword ptr [ecx+12028h]
		cmp eax, dword ptr [ecx+1202Ch]
		je localIsRouter
		xor al, al
		ret
localIsRouter:
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		push ebx
		mov ebx, dword ptr [edx+3Ch]
		cmp ebx, 5
		push edi
		jbe useStartupDelay
		__emit 0A1h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edi, dword ptr [eax+0CB4h]
		jmp haveDelay
useStartupDelay:
		mov edi, 3
haveDelay:
		push esi
		xor esi, esi
		lea eax, [ecx+04h]
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h
scanPlayers:
		mov edx, dword ptr [eax]
		test edx, edx
		je nextPlayer
		cmp dword ptr [edx], 0FFFFFFFFh
		jne nextPlayer
		cmp esi, 8
		jae testFrameAge
		mov edx, dword ptr [eax+1207Ch]
		cmp edx, 1
		jl testFrameAge
		cmp edx, 3
		jle nextPlayer
testFrameAge:
		mov edx, dword ptr [eax+1205Ch]
		add edx, edi
		cmp edx, ebx
		jb stalled
nextPlayer:
		inc esi
		add eax, 4
		cmp esi, 8
		jl scanPlayers
		pop esi
		pop edi
		xor al, al
		pop ebx
		ret
stalled:
		mov esi, dword ptr [ecx+esi*4+12060h]
		__emit 03Bh
		__emit 035h
		__emit 004h
		__emit 077h
		__emit 02Fh
		__emit 001h
		je sameStalledFrame
		__emit 089h
		__emit 035h
		__emit 004h
		__emit 077h
		__emit 02Fh
		__emit 001h
sameStalledFrame:
		pop esi
		pop edi
		mov al, 1
		pop ebx
		ret
	}
}

__declspec(naked) Bool BFMEDisconnectManager::hasDisconnectScreenNotifyTimedOut(int playerID)
{
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp+0Ch]
		cmp edi, 0FFFFFFFFh
		mov esi, ecx
		jne validPlayer
		pop edi
		xor al, al
		pop esi
		ret 4
validPlayer:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		sub eax, dword ptr [esi+edi*4+14h]
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		cmp eax, dword ptr [ecx+0CC0h]
		sbb al, al
		pop edi
		inc al
		pop esi
		ret 4
	}
}

__declspec(naked) void BFMEConnectionManager::processRequestFrameDataCommand(void *msg)
{
	__asm {
		sub esp, 8
		push ebp
		push edi
		mov edi, dword ptr [esp+14h]
		test edi, edi
		mov ebp, ecx
		je done
		push ebx
		mov ecx, edi
		__emit 0E8h
		__emit 058h
		__emit 037h
		__emit 09Ah
		__emit 0FFh
		mov ebx, eax
		mov ecx, edi
		mov dword ptr [esp+10h], ebx
		__emit 0E8h
		__emit 020h
		__emit 005h
		__emit 09Dh
		__emit 0FFh
		cmp eax, ebx
		mov dword ptr [esp+0Ch], eax
		jb popEbxDone
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edx, dword ptr [ecx+0CB4h]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov ecx, dword ptr [ecx+3Ch]
		push esi
		lea esi, [edx+eax]
		cmp esi, ecx
		jb popEsiDone
		cmp ecx, eax
		mov dword ptr [esp+1Ch], ecx
		lea eax, [esp+1Ch]
		jb haveStartPointer
		lea eax, [esp+10h]
haveStartPointer:
		cmp ecx, edx
		mov esi, dword ptr [eax]
		jb clampLowToZero
		sub ecx, edx
		cmp ecx, ebx
		mov dword ptr [esp+1Ch], ecx
		lea eax, [esp+1Ch]
		ja haveEndPointer
useOriginalEndPointer:
		lea eax, [esp+14h]
haveEndPointer:
		mov eax, dword ptr [eax]
		cmp eax, esi
		ja popEsiDone
		mov edx, dword ptr [edi+0Ch]
		push esi
		push eax
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 099h
		__emit 07Eh
		__emit 09Ah
		__emit 0FFh
popEsiDone:
		pop esi
popEbxDone:
		pop ebx
done:
		pop edi
		pop ebp
		add esp, 8
		ret 4
clampLowToZero:
		mov dword ptr [esp+1Ch], 0
		jmp useOriginalEndPointer
	}
}
