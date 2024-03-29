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

};
