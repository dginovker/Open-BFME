#pragma once
#ifndef SWEEP_WINSOCK_H
#define SWEEP_WINSOCK_H

#include <windows.h>

typedef unsigned int SOCKET;

struct in_addr {
    union {
        struct { unsigned char s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { unsigned short s_w1, s_w2; } S_un_w;
        unsigned long S_addr;
    } S_un;
#define s_addr S_un.S_addr
};

struct sockaddr {
    unsigned short sa_family;
    char sa_data[14];
};

struct sockaddr_in {
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

struct hostent {
    char *h_name;
    char **h_aliases;
    short h_addrtype;
    short h_length;
    char **h_addr_list;
#define h_addr h_addr_list[0]
};
typedef struct hostent HOSTENT, *PHOSTENT;

struct WSADATA {
    WORD wVersion;
    WORD wHighVersion;
    char szDescription[257];
    char szSystemStatus[129];
    unsigned short iMaxSockets;
    unsigned short iMaxUdpDg;
    char *lpVendorInfo;
};

#define AF_INET 2
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define IPPROTO_UDP 17
#define SOL_SOCKET 0xffff
#define SO_BROADCAST 0x0020
#define SO_RCVBUF 0x1002
#define SO_SNDBUF 0x1001
#define FIONBIO 0x8004667e
#define INADDR_ANY 0x00000000
#define INADDR_BROADCAST 0xffffffff
#define INVALID_SOCKET ((SOCKET)~0)
#define SOCKET_ERROR (-1)

#define WSABASEERR 10000
#define WSAEINTR 10004
#define WSAEBADF 10009
#define WSAEACCES 10013
#define WSAEFAULT 10014
#define WSAEINVAL 10022
#define WSAEMFILE 10024
#define WSAEWOULDBLOCK 10035
#define WSAEINPROGRESS 10036
#define WSAEALREADY 10037
#define WSAENOTSOCK 10038
#define WSAEDESTADDRREQ 10039
#define WSAEMSGSIZE 10040
#define WSAEPROTOTYPE 10041
#define WSAENOPROTOOPT 10042
#define WSAEPROTONOSUPPORT 10043
#define WSAESOCKTNOSUPPORT 10044
#define WSAEOPNOTSUPP 10045
#define WSAEPFNOSUPPORT 10046
#define WSAEAFNOSUPPORT 10047
#define WSAEADDRINUSE 10048
#define WSAEADDRNOTAVAIL 10049
#define WSAENETDOWN 10050
#define WSAENETUNREACH 10051
#define WSAENETRESET 10052
#define WSAECONNABORTED 10053
#define WSAECONNRESET 10054
#define WSAENOBUFS 10055
#define WSAEISCONN 10056
#define WSAENOTCONN 10057
#define WSAESHUTDOWN 10058
#define WSAETOOMANYREFS 10059
#define WSAETIMEDOUT 10060
#define WSAECONNREFUSED 10061
#define WSAELOOP 10062
#define WSAENAMETOOLONG 10063
#define WSAEHOSTDOWN 10064
#define WSAEHOSTUNREACH 10065
#define WSAENOTEMPTY 10066
#define WSAEPROCLIM 10067
#define WSAEUSERS 10068
#define WSAEDQUOT 10069
#define WSAESTALE 10070
#define WSAEREMOTE 10071
#define WSAEDISCON 10101
#define WSASYSNOTREADY 10091
#define WSAVERNOTSUPPORTED 10092
#define WSANOTINITIALISED 10093
#define WSAHOST_NOT_FOUND 11001
#define WSATRY_AGAIN 11002
#define WSANO_RECOVERY 11003
#define WSANO_DATA 11004

extern "C" {
__declspec(dllimport) int __stdcall WSAStartup(WORD, WSADATA *);
__declspec(dllimport) int __stdcall WSACleanup(void);
__declspec(dllimport) int __stdcall WSAGetLastError(void);
__declspec(dllimport) SOCKET __stdcall socket(int, int, int);
__declspec(dllimport) int __stdcall closesocket(SOCKET);
__declspec(dllimport) int __stdcall bind(SOCKET, const struct sockaddr *, int);
__declspec(dllimport) int __stdcall connect(SOCKET, const struct sockaddr *, int);
__declspec(dllimport) int __stdcall getsockname(SOCKET, struct sockaddr *, int *);
__declspec(dllimport) int __stdcall ioctlsocket(SOCKET, long, unsigned long *);
__declspec(dllimport) int __stdcall send(SOCKET, const char *, int, int);
__declspec(dllimport) int __stdcall sendto(SOCKET, const char *, int, int, const struct sockaddr *, int);
__declspec(dllimport) int __stdcall recvfrom(SOCKET, char *, int, int, struct sockaddr *, int *);
__declspec(dllimport) int __stdcall setsockopt(SOCKET, int, int, const char *, int);
__declspec(dllimport) int __stdcall getsockopt(SOCKET, int, int, char *, int *);
__declspec(dllimport) unsigned short __stdcall htons(unsigned short);
__declspec(dllimport) unsigned short __stdcall ntohs(unsigned short);
__declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
__declspec(dllimport) unsigned long __stdcall ntohl(unsigned long);
__declspec(dllimport) unsigned long __stdcall inet_addr(const char *);
__declspec(dllimport) char * __stdcall inet_ntoa(struct in_addr);
__declspec(dllimport) struct hostent * __stdcall gethostbyname(const char *);
__declspec(dllimport) int __stdcall gethostname(char *, int);
}

#endif
