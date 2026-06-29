#include "xfer.h"

Xfer::Xfer()
{
}

Xfer::~Xfer()
{
}

bool Xfer::IsLoading() const
{
    return false;
}

bool Xfer::IsStoring() const
{
    return false;
}

bool Xfer::IsCRC() const
{
    return false;
}

bool Xfer::IsLightCRC() const
{
    return false;
}

void Xfer::SkipBadBlock(Snapshot &snapshot, unsigned int size)
{
}

__declspec(naked) Xfer &Xfer::operator==(char &c)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x62797465
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned char &c)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x75627974
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(short &s)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 2
        push ecx
        push 0x73687274
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned short &s)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 2
        push ecx
        push 0x75736874
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(int &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x696e74
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned int &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x75696e74
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(float &f)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x7265616c
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(__int64 &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 8
        push ecx
        push 0x693634
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(bool &b)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x626f6f6c
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(Snapshot &snapshot)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [ecx]
        push esi
        call dword ptr [eax + 0x0c]
        mov eax, esi
        pop esi
        ret 4
    }
}
