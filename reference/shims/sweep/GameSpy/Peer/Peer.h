/*
**	GameSpy Peer SDK shim — minimal declarations for sweep compilation
**	The real Peer SDK headers are not available; this supplies the types
**	that ZH's headers reference so the sweep build can proceed.
*/

#pragma once

#ifndef __PEER_H__
#define __PEER_H__

typedef int PEERBool;
#define PEERTrue  1
#define PEERFalse 0

typedef void* PEER;

typedef enum {
	TitleRoom,
	GroupRoom,
	StagingRoom,
} RoomType;

typedef enum {
	PEERJoinNoError,
	PEERJoinSuccess,
	PEERFullRoom,
	PEERAlreadyInRoom,
	PEERInviteOnlyRoom,
	PEERInUse,
	PEERBannedFromRoom,
	PEERBadPassword,
	PEERNoConnection,
} PEERJoinResult;

typedef enum {
	NormalMessage,
	ActionMessage,
} MessageType;

// PEER connection constants
enum {
	PEER_ADD,
	PEER_UPDATE,
	PEER_REMOVE,
	PEER_CLEAR,
	PEER_STOP_REPORTING,
	PEER_FLAG_OP = 0x01,
};

typedef void (*peerEnumPlayersCallback)(PEER peer, PEERBool success,
	const char* nick, int flags, void* param);

typedef void (*peerListingGamesCallback)(PEER peer, PEERBool success,
	const char* ip, unsigned short port,
	const char* keys, const char* values,
	void* param);

class GServer
{
};

#endif // __PEER_H__
