﻿#pragma once


// 21 이상부터 시작해야 한다!!!
enum class PACKET_ID : short
{		
	PK_LOGIN_IN_REQ = 21,
	PK_LOGIN_IN_RES = 22,
		
	PK_ENTER_ROOM_REQ = 61,
	PK_ENTER_ROOM_RES = 62,
	PK_NEW_USER_ENTER_ROOM_NTF = 63,

	PK_LEAVE_ROOM_REQ = 66,
	PK_LEAVE_ROOM_RES = 67,
	PK_USER_LEAVE_ROOM_NTF = 68,

	PK_CHAT_ROOM_REQ = 76,
	PK_CHAT_ROOM_RES = 77,
	PK_CHAT_ROOM_NTF = 78,

	PK_READY_GAME_ROOM_REQ = 81,
	PK_READY_GAME_ROOM_RES = 82,
	PK_READY_GAME_ROOM_NTF = 83,

	PK_CANCEL_READY_GAME_ROOM_REQ = 86,
	PK_CANCEL_READY_GAME_ROOM_RES = 87, 
	PK_CANCEL_READY_GAME_ROOM_NTF = 88,

	PK_START_GAME_ROOM_NTF = 91, 

	PK_PUT_AL_ROOM_REQ = 96, 
	PK_PUT_AL_ROOM_RES = 97,
	PK_END_GAME_ROOM_NTF = 98,



	MAX = 256
};

