// cl: /DNDEBUG /MD /GX

class BFMENativeNetwork
{
public:
	void *construct();
	int getFramePacingStatus();
};

__declspec(naked) void *BFMENativeNetwork::construct()
{
	__asm {
		push ebx
		push esi
		mov esi, ecx
		__emit 0E8h
		__emit 077h
		__emit 001h
		__emit 032h
		__emit 000h
		xor ebx, ebx
		lea eax, [esi+10h]
		push eax
		mov dword ptr [esi], 0111A968h
		mov dword ptr [esi+08h], ebx
		mov dword ptr [esi+0Ch], ebx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+24h], ebx
		mov byte ptr [esi+35h], bl
		__emit 0FFh
		__emit 015h
		__emit 0B8h
		__emit 08Eh
		__emit 035h
		__emit 001h
		lea ecx, [esi+18h]
		push ecx
		__emit 0FFh
		__emit 015h
		__emit 0B4h
		__emit 08Eh
		__emit 035h
		__emit 001h
		mov byte ptr [esi+34h], bl
		mov byte ptr [esi+28h], bl
		mov dword ptr [esi+2Ch], ebx
		mov dword ptr [esi+38h], 0FFFFFFFFh
		mov eax, esi
		pop esi
		pop ebx
		ret
	}
}

__declspec(naked) int BFMENativeNetwork::getFramePacingStatus()
{
	__asm {
		sub esp, 10h
		push esi
		mov esi, ecx
		cmp dword ptr [esi+0Ch], 1
		je active
		mov eax, 1
		pop esi
		add esp, 10h
		ret
active:
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+8Ch]
		test al, al
		jne timerPath
		mov ecx, dword ptr [esi+08h]
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov esi, dword ptr [edx+3Ch]
		mov eax, dword ptr [ecx+1205Ch]
		sub eax, esi
		inc eax
		pop esi
		add esp, 10h
		ret
timerPath:
		push ebx
		push edi
		lea eax, [esp+0Ch]
		push eax
		__emit 0FFh
		__emit 015h
		__emit 0B4h
		__emit 08Eh
		__emit 035h
		__emit 001h
		mov eax, dword ptr [esp+0Ch]
		mov ecx, dword ptr [esi+18h]
		mov ebx, dword ptr [esi+1Ch]
		mov edx, eax
		sub edx, ecx
		mov ecx, dword ptr [esp+10h]
		mov edi, ecx
		sbb edi, ebx
		mov ebx, dword ptr [esi+20h]
		push 0
		add ebx, edx
		mov edx, dword ptr [esi+24h]
		mov dword ptr [esi+18h], eax
		mov eax, dword ptr [esi+14h]
		push 5
		mov dword ptr [esi+1Ch], ecx
		mov ecx, dword ptr [esi+10h]
		push eax
		adc edx, edi
		push ecx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+24h], edx
		__emit 0E8h
		__emit 0F8h
		__emit 04Eh
		__emit 037h
		__emit 000h
		mov esi, dword ptr [esi+24h]
		cmp esi, edx
		mov ecx, ebx
		pop edi
		mov dword ptr [esp+10h], eax
		mov dword ptr [esp+14h], edx
		mov dword ptr [esp+08h], ecx
		mov dword ptr [esp+0Ch], esi
		pop ebx
		jg readyEnough
		jl notReady
		cmp ecx, eax
		jae readyEnough
notReady:
		xor eax, eax
		pop esi
		add esp, 10h
		ret
readyEnough:
		fild qword ptr [esp+04h]
		fild qword ptr [esp+0Ch]
		__emit 0D8h
		__emit 00Dh
		__emit 06Ch
		__emit 0B4h
		__emit 009h
		__emit 001h
		fcompp
		fnstsw ax
		test ah, 41h
		mov eax, 1
		je done
		mov eax, 2
done:
		pop esi
		add esp, 10h
		ret
	}
}
