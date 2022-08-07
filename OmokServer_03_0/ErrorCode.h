﻿#pragma once


// 201 부터 시작한다.
enum class ERROR_CODE : short
{
	NONE = 0,

	UNASSIGNED_ERROR = 201,

	MAIN_INIT_NETWORK_INIT_FAIL = 206,

	USER_MGR_ID_DUPLICATION = 211,
	USER_MGR_MAX_USER_COUNT = 212,
	USER_MGR_INVALID_SESSION_INDEX = 213,
	USER_MGR_NOT_CONFIRM_USER = 214,
	USER_MGR_REMOVE_INVALID_SESSION = 221,

	ROOM_ENTER_INVALID_DOMAIN = 251,
	ROOM_ENTER_EMPTY_ROOM = 252,
	ROOM_ENTER_INVALID_ROOM_INDEX = 253,
	ROOM_ENTER_NOT_CREATED = 254,
	ROOM_ENTER_MEMBER_FULL = 255,

	ROOM_LEAVE_INVALID_DOMAIN = 261,
	ROOM_LEAVE_INVALID_ROOM_INDEX = 262,
	ROOM_LEAVE_NOT_MEMBER = 263,

	ROOM_CHAT_INVALID_DOMAIN = 271,
	ROOM_CHAT_INVALID_ROOM_INDEX = 272,
};
