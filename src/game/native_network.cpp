// cl: /DNDEBUG /MD /GX

typedef bool Bool;

class BFMENetworkBackend
{
public:
	virtual ~BFMENetworkBackend();
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
	Bool backendHasLiveHandle();
	void destroyBackend();
	void pushQueue0(BFMENetworkQueueItem *item);
	Bool popQueue0(BFMENetworkQueueItem *item);
	void pushQueue1(BFMENetworkQueueItem1 *item);
	Bool popQueue1(BFMENetworkQueueItem1 *item);
	void pushList90(BFMENetworkListPayload payload);
	void *findList90(void *key, void *payload);

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

__declspec(noinline) BFMEAutoLockRef::~BFMEAutoLockRef()
{
	if (!m_failed) {
		BFMENetworkLock *lock = m_lock;
		--lock->m_refCount;
		ReleaseMutex(lock->m_handle);
	}
}
