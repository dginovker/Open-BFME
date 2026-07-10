/*
**	GameSpy GP (Buddy) SDK shim — minimal declarations for sweep compilation
**	The real GP SDK headers are not available; this supplies the types
**	that ZH's headers reference so the sweep build can proceed.
**
**	Values use distinct ranges since the original SDK uses separate enum types
**	that don't collide across switches, but our flat int typedefs would.
*/

#pragma once

#ifndef __GP_H__
#define __GP_H__

typedef int   GPProfile;
typedef int   GPEnum;
typedef int   GPErrorCode;
typedef int   GPResult;

#define GP_NICK_LEN              64
#define GP_EMAIL_LEN             128
#define GP_PASSWORD_LEN          64
#define GP_COUNTRYCODE_LEN       8
#define GP_REASON_LEN            256
#define GP_LOCATION_STRING_LEN   256
#define GP_STATUS_STRING_LEN     256

// GPEnum status values (0-99)
enum {
	GP_OFFLINE,
	GP_ONLINE,
	GP_PLAYING,
	GP_CHATTING,
	GP_STAGING,
};

// GP callback type indices (100-199)
enum {
	GP_RECV_BUDDY_MESSAGE  = 100,
	GP_RECV_BUDDY_REQUEST,
	GP_RECV_BUDDY_STATUS,
	GP_RECV_GAME_INVITE,
	GP_ERROR,
	GP_BM,
};

// GP connection modes / flags (200-299)
enum {
	GP_BLOCKING = 200,
	GP_FIREWALL,
	GP_NO_FIREWALL,
	GP_NO_ERROR,
	GP_CHECK_CACHE,
	GP_DONT_CHECK_CACHE,
	GP_MASK_NONE,
	GP_DONT_UPDATE,
};

// GP connection state (300-399)
enum {
	GP_NOT_LOGGED_IN = 300,
	GP_CONNECTED,
	GP_DISCONNECTED,
};

// GP error / result codes (400-999)
enum {
	GP_GENERAL = 400,
	GP_PARSE,
	GP_NETWORK,
	GP_DATABASE,
	GP_MEMORY_ERROR,
	GP_PARAMETER_ERROR,
	GP_SERVER_ERROR,
	GP_NETWORK_ERROR,
	GP_BAD_SESSKEY,
	GP_CONNECTION_CLOSED,
	GP_FORCED_DISCONNECT,
	GP_FATAL,
	GP_STATUS,
	GP_LOGIN,
	GP_LOGIN_BAD_NICK,
	GP_LOGIN_BAD_EMAIL,
	GP_LOGIN_BAD_PASSWORD,
	GP_LOGIN_BAD_PROFILE,
	GP_LOGIN_CONNECTION_FAILED,
	GP_LOGIN_SERVER_AUTH_FAILED,
	GP_LOGIN_PROFILE_DELETED,
	GP_LOGIN_TIMEOUT,
	GP_NEWUSER,
	GP_NEWUSER_BAD_NICK,
	GP_NEWUSER_BAD_PASSWORD,
	GP_NEWPROFILE,
	GP_NEWPROFILE_BAD_NICK,
	GP_NEWPROFILE_BAD_OLD_NICK,
	GP_GETPROFILE,
	GP_GETPROFILE_BAD_PROFILE,
	GP_SEARCH,
	GP_SEARCH_CONNECTION_FAILED,
	GP_UPDATEPRO,
	GP_UPDATEPRO_BAD_NICK,
	GP_UPDATEUI,
	GP_UPDATEUI_BAD_EMAIL,
	GP_ADDBUDDY,
	GP_ADDBUDDY_ALREADY_BUDDY,
	GP_ADDBUDDY_BAD_FROM,
	GP_ADDBUDDY_BAD_NEW,
	GP_AUTHADD,
	GP_AUTHADD_BAD_FROM,
	GP_AUTHADD_BAD_SIG,
	GP_BM_NOT_BUDDY,
	GP_DELBUDDY,
	GP_DELBUDDY_NOT_BUDDY,
	GP_DELPROFILE,
	GP_DELPROFILE_LAST_PROFILE,
};

class GPConnection {};

typedef void (*GPCallback)(GPConnection* connection, void* arg, void* param);

struct GPRecvBuddyRequestArg {
	int profile;
	char nick[GP_NICK_LEN];
	char email[GP_EMAIL_LEN];
	char countrycode[GP_COUNTRYCODE_LEN];
	char reason[GP_REASON_LEN];
};
struct GPRecvBuddyMessageArg {
	int profile;
	const char* message;
	unsigned int date;
	char nick[GP_NICK_LEN];
};
struct GPRecvBuddyStatusArg {
	int profile;
	GPEnum status;
	char statusString[GP_STATUS_STRING_LEN];
	char locationString[GP_LOCATION_STRING_LEN];
	int index;
};
struct GPErrorArg {
	GPErrorCode errorCode;
	GPResult result;
	GPEnum fatal;
	char errorString[256];
};
struct GPConnectResponseArg {
	GPResult result;
	GPProfile profile;
};
struct GPGetInfoResponseArg {
	int profile;
	char nick[GP_NICK_LEN];
	char email[GP_EMAIL_LEN];
	char countrycode[GP_COUNTRYCODE_LEN];
};
struct GPBuddyStatus {
	int profile;
	GPEnum status;
	char statusString[GP_STATUS_STRING_LEN];
	char locationString[GP_LOCATION_STRING_LEN];
};

// GP API function declarations (compile-only shim; no implementations needed)
GPResult gpInitialize(GPConnection* connection, int productID);
GPResult gpConnect(GPConnection* connection, const char* nick, const char* email, const char* password, int firewall, int blocking, GPCallback callback, void* param);
GPResult gpConnectNewUser(GPConnection* connection, const char* nick, const char* email, const char* password, int firewall, int blocking, GPCallback callback, void* param);
void gpDisconnect(GPConnection* connection);
void gpDestroy(GPConnection* connection);
GPResult gpIsConnected(GPConnection* connection, int* isConnected);
void gpProcess(GPConnection* connection);
void gpSetCallback(GPConnection* connection, int callbackType, GPCallback callback, void* param);
void gpSetInfoMask(GPConnection* connection, int mask);
void gpSetStatus(GPConnection* connection, GPEnum status, const char* statusString, const char* locationString);
void gpSendBuddyMessage(GPConnection* connection, GPProfile recipient, const char* message);
void gpSendBuddyRequest(GPConnection* connection, GPProfile profile, const char* reason);
void gpDeleteBuddy(GPConnection* connection, GPProfile profile);
void gpDenyBuddyRequest(GPConnection* connection, GPProfile profile);
void gpAuthBuddyRequest(GPConnection* connection, GPProfile profile);
void gpGetInfo(GPConnection* connection, GPProfile profile, int checkCache, int blocking, GPCallback callback, void* param);
void gpDeleteProfile(GPConnection* connection);
void gpGetBuddyStatus(GPConnection* connection, int index, GPBuddyStatus* status);

#endif // __GP_H__
