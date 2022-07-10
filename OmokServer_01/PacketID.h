#pragma once


// 21 이상부터 시작해야 한다!!!
enum class PACKET_ID : short
{		
	LOGIN_IN_REQ = 21,
	LOGIN_IN_RES = 22,
		
	ROOM_ENTER_REQ = 61,
	ROOM_ENTER_RES = 62,
	ROOM_ENTER_NEW_USER_NTF = 63,

	ROOM_LEAVE_REQ = 66,
	ROOM_LEAVE_RES = 67,
	ROOM_LEAVE_USER_NTF = 68,

	ROOM_CHAT_REQ = 76,
	ROOM_CHAT_RES = 77,
	ROOM_CHAT_NTF = 78,

	MAX = 256
};

