#pragma once


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

	MAX = 256
};

