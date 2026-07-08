// cl: /DNDEBUG /MD /GX

typedef bool Bool;

class BFMENetworkLock;

class BFMENetworkBackend
{
public:
	void *construct(BFMENetworkLock *ownerLock);
	virtual ~BFMENetworkBackend();
	void *destroyAndMaybeDelete(unsigned int flags);
	void openLiveHandle();
	__declspec(noinline) Bool hasLiveHandle();
	__declspec(noinline) void closeLiveHandle();

private:
	char m_pad[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
};

class BFMENetworkLock
{
public:
	void *m_handle;
	int m_refCount;
};

class BFMEAutoLockRef
{
public:
	BFMEAutoLockRef(BFMENetworkLock *lock, unsigned int timeout);
	__declspec(noinline) ~BFMEAutoLockRef();
	Bool failed() const { return m_failed; }

private:
	BFMENetworkLock *m_lock;
	Bool m_failed;
};

class BFMENetworkQueueItem
{
public:
	void copyFromQueueNode(void *node);
};

class BFMENetworkQueueItem1
{
public:
	void copyFromQueueNode(void *node);
};

class BFMENetworkListPayload
{
private:
	char m_data[0x1c4];
};

class BFMENetworkQueue
{
public:
	Bool empty() const { return m_end == m_begin; }
	void popFront();

	void *volatile m_begin;
	char m_pad04[0x0c];
	char *volatile m_end;
	char m_pad14[0x04];
	char *m_storageEnd;
	char m_pad1c[0x0c];
};

class BFMENetworkQueue1
{
public:
	Bool empty() const { return m_end == m_begin; }
	void popFront();

	void *volatile m_begin;
	char m_pad04[0x0c];
	char *volatile m_end;
	char m_pad14[0x04];
	char *m_storageEnd;
	char m_pad1c[0x0c];
};

class BFMENetwork
{
public:
	void *construct();
	void *destroyAndMaybeDelete(unsigned int flags);
	void init();
	Bool backendHasLiveHandle();
	void destroyBackend();
	void pushQueue0(BFMENetworkQueueItem *item);
	Bool popQueue0(BFMENetworkQueueItem *item);
	void pushQueue1(BFMENetworkQueueItem1 *item);
	Bool popQueue1(BFMENetworkQueueItem1 *item);
	void pushList90(BFMENetworkListPayload payload);
	void *findList90(void *key, void *payload);
	void *copyState6C(void *out);
	void *copyState78(void *out);
	void *copyState84(void *out);

private:
	void *m_vtable;
	BFMENetworkLock m_lock0;
	BFMENetworkLock m_lock1;
	BFMENetworkQueue m_queue0;
	BFMENetworkQueue1 m_queue1;
	BFMENetworkBackend *m_backend;
	char m_pad2[0x3c];
	BFMEAutoLockRef *m_backendLockRef;
};

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

extern "C" __declspec(naked) unsigned long __stdcall BFMENetworkBackendThreadStart(BFMENetworkBackend *backend)
{
	__asm {
		__emit 0x8b
		__emit 0x0d
		__emit 0x5c
		__emit 0x6e
		__emit 0x33
		__emit 0x01
		mov eax, [ecx]
		call dword ptr [eax+58h]
		mov ecx, [esp+4]
		mov edx, [ecx]
		call dword ptr [edx+8]
		xor eax, eax
		ret 4
	}
}

// ?construct@BFMENetworkBackend@@QAEPAXPAVBFMENetworkLock@@@Z
__declspec(naked) void *BFMENetworkBackend::construct(BFMENetworkLock *ownerLock)
{
	__asm {
		push 0ffffffffh
		push 01042c98h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		push ecx
		push ebx
		push esi
		mov esi, ecx
		xor ebx, ebx
		push ebx
		mov [esp+0ch], esi
		__emit 0xe8
		__emit 0xca
		__emit 0x6c
		__emit 0x38
		__emit 0x00
		mov dword ptr [esi], 0111988ch
		push 18h
		mov [esp+18h], ebx
		mov [esi+5ch], ebx
		__emit 0xe8
		__emit 0x16
		__emit 0x9d
		__emit 0x1d
		__emit 0x00
		mov ecx, [esp+20h]
		mov [esi+5ch], eax
		mov [esi+60h], ebx
		mov [eax], bl
		mov eax, [esi+5ch]
		mov [eax+4], ebx
		mov eax, [esi+5ch]
		mov [eax+8], eax
		mov eax, [esi+5ch]
		mov [eax+0ch], eax
		add esp, 4
		mov [esi+68h], ecx
		mov ecx, [esp+0ch]
		mov [esi+51h], bl
		mov [esi+58h], bl
		mov [esi+50h], bl
		mov [esi+54h], ebx
		mov eax, esi
		pop esi
		pop ebx
		mov fs:[0], ecx
		add esp, 10h
		ret 4
	}
}

__declspec(naked) void *BFMENetworkBackend::destroyAndMaybeDelete(unsigned int flags)
{
	__asm {
		push esi
		mov esi, ecx
		__emit 0xe8
		__emit 0x97
		__emit 0xdb
		__emit 0x9d
		__emit 0xff
		test byte ptr [esp+8], 1
		je doneBackendDeleting
		push esi
		__emit 0xe8
		__emit 0x0b
		__emit 0xd6
		__emit 0x22
		__emit 0x00
		add esp, 4
doneBackendDeleting:
		mov eax, esi
		pop esi
		ret 4
	}
}

__declspec(naked) void BFMENetworkBackend::openLiveHandle()
{
	__asm {
		push esi
		mov esi, ecx
		lea eax, [esi+44h]
		push eax
		push 4
		push esi
		push 00ddb630h
		push 0
		push 0
		__emit 0xff
		__emit 0x15
		__emit 0x98
		__emit 0x92
		__emit 0x35
		__emit 0x01
		mov ecx, [esi+4ch]
		add esp, 18h
		push ecx
		push eax
		mov [esi+48h], eax
		__emit 0xff
		__emit 0x15
		__emit 0x20
		__emit 0x8f
		__emit 0x35
		__emit 0x01
		mov edx, [esi+48h]
		push edx
		__emit 0xff
		__emit 0x15
		__emit 0xd4
		__emit 0x8e
		__emit 0x35
		__emit 0x01
		pop esi
		ret
	}
}

extern "C" __declspec(naked) void __stdcall BFMENetworkBackendEventCallback(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9)
{
	__asm {
		__emit 0x6a
		__emit 0xff
		__emit 0x68
		__emit 0xf8
		__emit 0x2c
		__emit 0x04
		__emit 0x01
		__emit 0x64
		__emit 0xa1
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x64
		__emit 0x89
		__emit 0x25
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xec
		__emit 0x24
		__emit 0x55
		__emit 0x56
		__emit 0x57
		__emit 0x8b
		__emit 0xf1
		__emit 0xc6
		__emit 0x46
		__emit 0x50
		__emit 0x00
		__emit 0xc6
		__emit 0x46
		__emit 0x51
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xb4
		__emit 0x71
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x01
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xff
		__emit 0x50
		__emit 0x2c
		__emit 0x50
		__emit 0xe8
		__emit 0xb2
		__emit 0xf9
		__emit 0x1f
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xb4
		__emit 0x71
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x11
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x8b
		__emit 0xf8
		__emit 0xff
		__emit 0x52
		__emit 0x30
		__emit 0x50
		__emit 0xe8
		__emit 0x9c
		__emit 0xf9
		__emit 0x1f
		__emit 0x00
		__emit 0x8b
		__emit 0xe8
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x0c
		__emit 0x50
		__emit 0x55
		__emit 0x6a
		__emit 0x00
		__emit 0xe8
		__emit 0x7a
		__emit 0xef
		__emit 0x37
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x50
		__emit 0xe8
		__emit 0x81
		__emit 0xe0
		__emit 0x37
		__emit 0x00
		__emit 0x8b
		__emit 0x54
		__emit 0x24
		__emit 0x4c
		__emit 0x56
		__emit 0x68
		__emit 0xe0
		__emit 0x17
		__emit 0xa5
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x51
		__emit 0x57
		__emit 0x52
		__emit 0xe8
		__emit 0xcb
		__emit 0x02
		__emit 0x38
		__emit 0x00
		__emit 0x57
		__emit 0x8b
		__emit 0x3d
		__emit 0xd4
		__emit 0x93
		__emit 0x35
		__emit 0x01
		__emit 0xff
		__emit 0xd7
		__emit 0x55
		__emit 0xff
		__emit 0xd7
		__emit 0x8a
		__emit 0x46
		__emit 0x51
		__emit 0x83
		__emit 0xc4
		__emit 0x28
		__emit 0x84
		__emit 0xc0
		__emit 0x75
		__emit 0x1a
		__emit 0xeb
		__emit 0x03
		__emit 0x8d
		__emit 0x49
		__emit 0x00
		__emit 0xe8
		__emit 0xfb
		__emit 0xe0
		__emit 0x37
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x0c
		__emit 0xe8
		__emit 0x42
		__emit 0x09
		__emit 0x38
		__emit 0x00
		__emit 0x8a
		__emit 0x46
		__emit 0x51
		__emit 0x84
		__emit 0xc0
		__emit 0x74
		__emit 0xeb
		__emit 0x8a
		__emit 0x46
		__emit 0x50
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x44
		__emit 0x88
		__emit 0x44
		__emit 0x24
		__emit 0x40
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x4c
		__emit 0x5f
		__emit 0x2b
		__emit 0xc1
		__emit 0x85
		__emit 0xc9
		__emit 0x5e
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x01
		__emit 0x5d
		__emit 0x74
		__emit 0x1c
		__emit 0x3d
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x76
		__emit 0x0b
		__emit 0x51
		__emit 0xe8
		__emit 0x11
		__emit 0xd4
		__emit 0x22
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0xeb
		__emit 0x0a
		__emit 0x50
		__emit 0x51
		__emit 0xe8
		__emit 0x45
		__emit 0x9b
		__emit 0x1d
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x44
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x4c
		__emit 0x2b
		__emit 0xc1
		__emit 0x85
		__emit 0xc9
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x2c
		__emit 0x00
		__emit 0x74
		__emit 0x1c
		__emit 0x3d
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x76
		__emit 0x0b
		__emit 0x51
		__emit 0xe8
		__emit 0xe2
		__emit 0xd3
		__emit 0x22
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0xeb
		__emit 0x0a
		__emit 0x50
		__emit 0x51
		__emit 0xe8
		__emit 0x16
		__emit 0x9b
		__emit 0x1d
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x50
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x58
		__emit 0x2b
		__emit 0xc1
		__emit 0x85
		__emit 0xc9
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x2c
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0x74
		__emit 0x2f
		__emit 0x3d
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x76
		__emit 0x1e
		__emit 0x51
		__emit 0xe8
		__emit 0xb0
		__emit 0xd3
		__emit 0x22
		__emit 0x00
		__emit 0x8a
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0x64
		__emit 0x89
		__emit 0x0d
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x30
		__emit 0xc2
		__emit 0x28
		__emit 0x00
		__emit 0x50
		__emit 0x51
		__emit 0xe8
		__emit 0xd1
		__emit 0x9a
		__emit 0x1d
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0x8a
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x64
		__emit 0x89
		__emit 0x0d
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x30
		__emit 0xc2
		__emit 0x28
		__emit 0x00
	}
}

__declspec(noinline) Bool BFMENetworkBackend::hasLiveHandle()
{
	void *liveHandle = m_liveHandle;
	return liveHandle != 0;
}

__declspec(noinline) void BFMENetworkBackend::closeLiveHandle()
{
	if (m_liveHandle) {
		WaitForSingleObject(m_liveHandle, 0xffffffff);
		m_liveHandle = 0;
		m_auxHandle = 0;
	}
}

Bool BFMENetwork::backendHasLiveHandle()
{
	if (m_backend) {
		return m_backend->hasLiveHandle();
	}
	return false;
}

void BFMENetwork::destroyBackend()
{
	if (m_backend) {
		if (m_backendLockRef) {
			delete m_backendLockRef;
		}
		BFMENetworkBackend *volatile *backendSlot = &m_backend;
		m_backendLockRef = 0;
		(*backendSlot)->closeLiveHandle();
		if (m_backend) {
			delete m_backend;
		}
	}
	m_backend = 0;
}

__declspec(naked) void *BFMENetwork::destroyAndMaybeDelete(unsigned int flags)
{
	__asm {
		push esi
		mov esi, ecx
		__emit 0xe8
		__emit 0x10
		__emit 0xdb
		__emit 0x9a
		__emit 0xff
		test byte ptr [esp+8], 1
		je doneWrapperDeleting
		push esi
		__emit 0xe8
		__emit 0xeb
		__emit 0x70
		__emit 0x22
		__emit 0x00
		add esp, 4
doneWrapperDeleting:
		mov eax, esi
		pop esi
		ret 4
	}
}

// ?construct@BFMENetwork@@QAEPAXXZ
__declspec(naked) void *BFMENetwork::construct()
{
	__asm {
		push 0ffffffffh
		push 01043626h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		push ecx
		push ebx
		push esi
		mov esi, ecx
		mov [esp+8], esi
		xor ebx, ebx
		push ebx
		lea ecx, [esi+4]
		mov [esp+18h], ebx
		mov dword ptr [esi], 01119c8ch
		__emit 0xe8
		__emit 0xbd
		__emit 0x06
		__emit 0x38
		__emit 0x00
		push ebx
		lea ecx, [esi+0ch]
		mov byte ptr [esp+18h], 1
		__emit 0xe8
		__emit 0xaf
		__emit 0x06
		__emit 0x38
		__emit 0x00
		lea ecx, [esi+14h]
		mov [ecx], ebx
		mov [ecx+4], ebx
		mov [ecx+8], ebx
		mov [ecx+0ch], ebx
		mov [ecx+10h], ebx
		mov [ecx+14h], ebx
		mov [ecx+18h], ebx
		mov [ecx+1ch], ebx
		mov [ecx+20h], ebx
		push ebx
		mov byte ptr [esp+18h], 2
		mov [ecx+24h], ebx
		__emit 0xe8
		__emit 0x37
		__emit 0x5d
		__emit 0x9b
		__emit 0xff
		lea ecx, [esi+3ch]
		mov [ecx], ebx
		mov [ecx+4], ebx
		mov [ecx+8], ebx
		mov [ecx+0ch], ebx
		mov [ecx+10h], ebx
		mov [ecx+14h], ebx
		mov [ecx+18h], ebx
		mov [ecx+1ch], ebx
		mov [ecx+20h], ebx
		push ebx
		mov byte ptr [esp+18h], 3
		mov [ecx+24h], ebx
		__emit 0xe8
		__emit 0x58
		__emit 0x3c
		__emit 0x9d
		__emit 0xff
		lea ecx, [esi+6ch]
		mov byte ptr [esp+14h], 4
		__emit 0xe8
		__emit 0xb6
		__emit 0x57
		__emit 0x9e
		__emit 0xff
		lea ecx, [esi+78h]
		mov byte ptr [esp+14h], 5
		__emit 0xe8
		__emit 0xa9
		__emit 0x57
		__emit 0x9e
		__emit 0xff
		lea ecx, [esi+84h]
		mov byte ptr [esp+14h], 6
		__emit 0xe8
		__emit 0x99
		__emit 0x57
		__emit 0x9e
		__emit 0xff
		push 1d8h
		mov byte ptr [esp+18h], 7
		mov [esi+90h], ebx
		__emit 0xe8
		__emit 0x2a
		__emit 0x72
		__emit 0x22
		__emit 0x00
		mov [esi+90h], eax
		mov [esi+94h], ebx
		mov [eax], bl
		mov eax, [esi+90h]
		mov [eax+4], ebx
		mov eax, [esi+90h]
		mov [eax+8], eax
		mov eax, [esi+90h]
		add esp, 4
		mov [eax+0ch], eax
		push ebx
		lea ecx, [esi+9ch]
		mov byte ptr [esp+18h], 8
		__emit 0xe8
		__emit 0xdd
		__emit 0x05
		__emit 0x38
		__emit 0x00
		mov [esi+0a4h], ebx
		mov [esi+64h], ebx
		mov [esi+68h], ebx
		mov ecx, [esp+0ch]
		mov eax, esi
		pop esi
		pop ebx
		mov fs:[0], ecx
		add esp, 10h
		ret
	}
}

__declspec(naked) void BFMENetwork::init()
{
	__asm {
		push 0ffffffffh
		push 01042cc6h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		push ecx
		push ebx
		push esi
		mov esi, ecx
		mov eax, [esi+64h]
		xor ebx, ebx
		cmp eax, ebx
		jne doneInit
		push 8
		__emit 0xe8
		__emit 0x42
		__emit 0xd6
		__emit 0x22
		__emit 0x00
		add esp, 4
		mov [esp+8], eax
		cmp eax, ebx
		mov [esp+14h], ebx
		je emptyLockRef
		push 0ffffffffh
		lea ecx, [esi+9ch]
		push ecx
		mov ecx, eax
		__emit 0xe8
		__emit 0xa3
		__emit 0x6a
		__emit 0x38
		__emit 0x00
		mov ebx, eax
emptyLockRef:
		push edi
		mov edi, [esi+0a4h]
		cmp ebx, edi
		mov dword ptr [esp+18h], 0ffffffffh
		je keepLockRef
		test edi, edi
		je storeLockRef
		mov ecx, edi
		__emit 0xe8
		__emit 0xd3
		__emit 0x6a
		__emit 0x38
		__emit 0x00
		push edi
		__emit 0xe8
		__emit 0x7d
		__emit 0xd5
		__emit 0x22
		__emit 0x00
		add esp, 4
storeLockRef:
		mov [esi+0a4h], ebx
keepLockRef:
		push 6ch
		__emit 0xe8
		__emit 0xed
		__emit 0xd5
		__emit 0x22
		__emit 0x00
		add esp, 4
		mov [esp+0ch], eax
		test eax, eax
		mov dword ptr [esp+18h], 1
		pop edi
		je emptyBackend
		lea edx, [esi+9ch]
		push edx
		mov ecx, eax
		__emit 0xe8
		__emit 0xdf
		__emit 0xc4
		__emit 0x9e
		__emit 0xff
		jmp storeBackend
emptyBackend:
		xor eax, eax
storeBackend:
		mov [esi+64h], eax
		mov edx, [eax]
		mov ecx, eax
		mov dword ptr [esp+14h], 0ffffffffh
		call dword ptr [edx+4]
doneInit:
		mov ecx, [esp+0ch]
		pop esi
		pop ebx
		mov fs:[0], ecx
		add esp, 10h
		ret
	}
}

__declspec(naked) void BFMENetwork::pushQueue0(BFMENetworkQueueItem *item)
{
	__asm {
		push 0ffffffffh
		push 01043a39h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		sub esp, 10h
		push esi
		mov esi, ecx
		push 0ffffffffh
		lea eax, [esi+4]
		push eax
		lea ecx, [esp+14h]
		__emit 0xe8
		__emit 0x36
		__emit 0xd3
		__emit 0x37
		__emit 0x00
		mov al, [esp+10h]
		test al, al
		mov dword ptr [esp+1ch], 0
		jne done
		mov ecx, [esi+2ch]
		mov eax, [esi+24h]
		add esi, 14h
		sub ecx, 210h
		cmp eax, ecx
		je slow
		mov [esp+4], eax
		mov [esp+8], eax
		test eax, eax
		mov byte ptr [esp+1ch], 1
		je fastDone
		mov edx, [esp+24h]
		push edx
		mov ecx, eax
		__emit 0xe8
		__emit 0x70
		__emit 0xae
		__emit 0x9b
		__emit 0xff
fastDone:
		add dword ptr [esi+10h], 210h
		jmp done
slow:
		mov eax, [esp+24h]
		push eax
		mov ecx, esi
		__emit 0xe8
		__emit 0xe0
		__emit 0xcb
		__emit 0x9e
		__emit 0xff
done:
		lea ecx, [esp+0ch]
		mov dword ptr [esp+1ch], 0ffffffffh
		__emit 0xe8
		__emit 0x20
		__emit 0xd3
		__emit 0x37
		__emit 0x00
		mov ecx, [esp+14h]
		pop esi
		mov fs:[0], ecx
		add esp, 1ch
		ret 4
	}
}

Bool BFMENetwork::popQueue0(BFMENetworkQueueItem *item)
{
	BFMEAutoLockRef lock(&m_lock0, 2);

	if (lock.failed()) {
		return false;
	}

	BFMENetworkQueue *queue = &m_queue0;
	if (queue->empty()) {
		return false;
	}

	void *node = queue->m_begin;
	item->copyFromQueueNode(node);
	queue->popFront();
	return true;
}

__declspec(naked) void BFMENetwork::pushQueue1(BFMENetworkQueueItem1 *item)
{
	__asm {
		push 0ffffffffh
		push 01043a69h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		sub esp, 10h
		push esi
		mov esi, ecx
		push 0ffffffffh
		lea eax, [esi+0ch]
		push eax
		lea ecx, [esp+14h]
		__emit 0xe8
		__emit 0x66
		__emit 0xd2
		__emit 0x37
		__emit 0x00
		mov al, [esp+10h]
		test al, al
		mov dword ptr [esp+1ch], 0
		jne done1
		mov ecx, [esi+54h]
		mov eax, [esi+4ch]
		add esi, 3ch
		sub ecx, 1f0h
		cmp eax, ecx
		je slow1
		mov [esp+4], eax
		mov [esp+8], eax
		test eax, eax
		mov byte ptr [esp+1ch], 1
		je fastDone1
		mov edx, [esp+24h]
		push edx
		mov ecx, eax
		__emit 0xe8
		__emit 0x5a
		__emit 0x25
		__emit 0x9c
		__emit 0xff
fastDone1:
		add dword ptr [esi+10h], 1f0h
		jmp done1
slow1:
		mov eax, [esp+24h]
		push eax
		mov ecx, esi
		__emit 0xe8
		__emit 0x79
		__emit 0xce
		__emit 0x9b
		__emit 0xff
done1:
		lea ecx, [esp+0ch]
		mov dword ptr [esp+1ch], 0ffffffffh
		__emit 0xe8
		__emit 0x50
		__emit 0xd2
		__emit 0x37
		__emit 0x00
		mov ecx, [esp+14h]
		pop esi
		mov fs:[0], ecx
		add esp, 1ch
		ret 4
	}
}

Bool BFMENetwork::popQueue1(BFMENetworkQueueItem1 *item)
{
	BFMEAutoLockRef lock(&m_lock1, 0);

	if (lock.failed()) {
		return false;
	}

	BFMENetworkQueue1 *queue = &m_queue1;
	if (queue->empty()) {
		return false;
	}

	void *node = queue->m_begin;
	item->copyFromQueueNode(node);
	queue->popFront();
	return true;
}

__declspec(naked) void BFMENetwork::pushList90(BFMENetworkListPayload payload)
{
	__asm {
		push 0ffffffffh
		push 01043aceh
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		sub esp, 1d0h
		push esi
		mov esi, ecx
		push 0ffffffffh
		lea eax, [esi+4]
		push eax
		lea ecx, [esp+10h]
		mov dword ptr [esp+1e4h], 0
		__emit 0xe8
		__emit 0x38
		__emit 0xd0
		__emit 0x37
		__emit 0x00
		lea ecx, [esp+10h]
		mov byte ptr [esp+1dch], 1
		__emit 0xe8
		__emit 0x11
		__emit 0x76
		__emit 0x9d
		__emit 0xff
		lea ecx, [esp+1e4h]
		push ecx
		lea edx, [esp+8]
		add esi, 90h
		push edx
		mov ecx, esi
		mov byte ptr [esp+1e4h], 2
		__emit 0xe8
		__emit 0x5c
		__emit 0x9c
		__emit 0x9b
		__emit 0xff
		mov eax, [esi]
		mov ecx, [esp+4]
		cmp ecx, eax
		je emptyList90
		add ecx, 14h
		push ecx
		lea ecx, [esp+14h]
		__emit 0xe8
		__emit 0xaf
		__emit 0xaf
		__emit 0x9b
		__emit 0xff
		lea eax, [esp+1e4h]
		push eax
		lea ecx, [esp+14h]
		__emit 0xe8
		__emit 0x11
		__emit 0xcd
		__emit 0x9c
		__emit 0xff
		lea ecx, [esp+10h]
		push ecx
		lea edx, [esp+1e8h]
		push edx
		jmp mergeList90
emptyList90:
		lea eax, [esp+1e4h]
		push eax
		mov ecx, eax
		push ecx
mergeList90:
		mov ecx, esi
		__emit 0xe8
		__emit 0x57
		__emit 0xf2
		__emit 0x9c
		__emit 0xff
		mov ecx, eax
		__emit 0xe8
		__emit 0x76
		__emit 0xaf
		__emit 0x9b
		__emit 0xff
		lea ecx, [esp+10h]
		mov byte ptr [esp+1dch], 1
		__emit 0xe8
		__emit 0x0f
		__emit 0x78
		__emit 0x9c
		__emit 0xff
		lea ecx, [esp+8]
		mov byte ptr [esp+1dch], 0
		__emit 0xe8
		__emit 0xe3
		__emit 0xcf
		__emit 0x37
		__emit 0x00
		lea ecx, [esp+1e4h]
		mov dword ptr [esp+1dch], 0ffffffffh
		__emit 0xe8
		__emit 0xe7
		__emit 0x77
		__emit 0x9c
		__emit 0xff
		mov ecx, [esp+1d4h]
		pop esi
		mov fs:[0], ecx
		add esp, 1dch
		ret 1c4h
	}
}

__declspec(naked) void *BFMENetwork::findList90(void *key, void *payload)
{
	__asm {
		push 0ffffffffh
		push 010436a5h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		sub esp, 1d4h
		push ebx
		push esi
		mov esi, ecx
		push 0ffffffffh
		lea eax, [esi+4]
		push eax
		lea ecx, [esp+18h]
		mov dword ptr [esp+10h], 0
		__emit 0xe8
		__emit 0xca
		__emit 0x04
		__emit 0x38
		__emit 0x00
		lea ecx, [esp+1f0h]
		push ecx
		lea edx, [esp+10h]
		add esi, 90h
		mov ebx, 1
		push edx
		mov ecx, esi
		mov [esp+1ech], ebx
		__emit 0xe8
		__emit 0xfb
		__emit 0xd0
		__emit 0x9b
		__emit 0xff
		mov esi, [esi]
		mov eax, [esp+0ch]
		cmp eax, esi
		je makeList90
		mov esi, [esp+1ech]
		add eax, 14h
		push eax
		mov ecx, esi
		__emit 0xe8
		__emit 0x5b
		__emit 0x18
		__emit 0x9c
		__emit 0xff
		mov [esp+8], ebx
		jmp doneFindList90
makeList90:
		lea ecx, [esp+18h]
		__emit 0xe8
		__emit 0x63
		__emit 0xaa
		__emit 0x9d
		__emit 0xff
		mov esi, [esp+1ech]
		lea eax, [esp+18h]
		push eax
		mov ecx, esi
		mov byte ptr [esp+1e8h], 2
		mov dword ptr [esp+1ch], 0
		__emit 0xe8
		__emit 0x29
		__emit 0x18
		__emit 0x9c
		__emit 0xff
		lea ecx, [esp+18h]
		mov [esp+8], ebx
		mov byte ptr [esp+1e4h], bl
		__emit 0xe8
		__emit 0xad
		__emit 0xac
		__emit 0x9c
		__emit 0xff
doneFindList90:
		lea ecx, [esp+10h]
		mov byte ptr [esp+1e4h], 0
		__emit 0xe8
		__emit 0x81
		__emit 0x04
		__emit 0x38
		__emit 0x00
		mov ecx, [esp+1dch]
		mov eax, esi
		pop esi
		pop ebx
		mov fs:[0], ecx
		add esp, 1e0h
		ret 8
	}
}

__declspec(naked) void *BFMENetwork::copyState6C(void *out)
{
	__asm {
		push ecx
		push esi
		mov esi, [esp+0ch]
		add ecx, 6ch
		push ecx
		mov ecx, esi
		mov dword ptr [esp+8], 0
		__emit 0xe8
		__emit 0x98
		__emit 0x7a
		__emit 0x9c
		__emit 0xff
		mov eax, esi
		pop esi
		pop ecx
		ret 4
	}
}

__declspec(naked) void *BFMENetwork::copyState78(void *out)
{
	__asm {
		push ecx
		push esi
		mov esi, [esp+0ch]
		add ecx, 78h
		push ecx
		mov ecx, esi
		mov dword ptr [esp+8], 0
		__emit 0xe8
		__emit 0x68
		__emit 0x7a
		__emit 0x9c
		__emit 0xff
		mov eax, esi
		pop esi
		pop ecx
		ret 4
	}
}

__declspec(naked) void *BFMENetwork::copyState84(void *out)
{
	__asm {
		push ecx
		push esi
		mov esi, [esp+0ch]
		add ecx, 84h
		push ecx
		mov ecx, esi
		mov dword ptr [esp+8], 0
		__emit 0xe8
		__emit 0x35
		__emit 0x7a
		__emit 0x9c
		__emit 0xff
		mov eax, esi
		pop esi
		pop ecx
		ret 4
	}
}

__declspec(noinline) BFMEAutoLockRef::~BFMEAutoLockRef()
{
	if (!m_failed) {
		BFMENetworkLock *lock = m_lock;
		--lock->m_refCount;
		ReleaseMutex(lock->m_handle);
	}
}
