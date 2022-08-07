#pragma once

#include "PacketID.h"
#include "ErrorCode.h"

#pragma pack(push, 1)
struct PktHeader
{
	short TotalSize;
	short Id;
	unsigned char Reserve;
};

struct PktBase
{
	short ErrorCode = (short)ERROR_CODE::NONE;
	void SetError(ERROR_CODE error) { ErrorCode = (short)error; }
};

//- 로그인 요청
const int MAX_USER_ID_SIZE = 16;
const int MAX_USER_PASSWORD_SIZE = 16;
struct PktLogInReq
{
	char szID[MAX_USER_ID_SIZE] = { 0, };
	char szPW[MAX_USER_PASSWORD_SIZE] = { 0, };
};

struct PktLogInRes : PktBase
{
};


//- 룸에 들어가기 요청
struct PktEnterRoomReq
{
	short RoomNumber;
};

struct PktEnterRoomRes : PktBase
{
};

		
//- 룸에 있는 유저에게 새로 들어온 유저 정보 통보
struct PktNewUserEnterRoomNtf
{
	char UserID[MAX_USER_ID_SIZE] = { 0, };
};


//- 룸 나가기 요청
struct PktLeaveRoomReq {};

struct PktLeaveRoomRes : PktBase
{
};

//- 룸에서 나가는 유저 통보(로비에 있는 유저에게)
struct PktUserLeaveRoomNtf
{
	char UserID[MAX_USER_ID_SIZE] = { 0, };
};
		

//- 룸 채팅
const int MAX_ROOM_CHAT_MSG_SIZE = 256;
struct PktChatRoomReq
{
	char Msg[MAX_ROOM_CHAT_MSG_SIZE] = { 0, };
};

struct PktChatRoomRes : PktBase
{
};

struct PktChatRoomNtf
{
	char UserID[MAX_USER_ID_SIZE] = { 0, };
	char Msg[MAX_ROOM_CHAT_MSG_SIZE] = { 0, };
};


//- 게임 시작 요청(준비완료 통보)
struct PktReadyGameRoomReq {};

struct PktReadyGameRoomRes : PktBase
{
};

struct PktReadyGameRoomNtf
{
	char UserID[MAX_USER_ID_SIZE] = { 0, };
};


//- 게임 시작 취소 요청
struct PktCancelReadyGameRoomReq {};

struct PktCancelReadyGameRoomRes : PktBase
{
};

struct PktCancelReadyGameRoomNtf
{
	char UserID[MAX_USER_ID_SIZE] = { 0, };
};


//서버의 게임 시작 통보
struct PktStartGameRoomNtf
{
	char TurnUserID[MAX_USER_ID_SIZE] = { 0, };
};


// 알 두기
struct PktPutALGameRoomReq 
{
	short XPos;
	short YPos;
};

struct PktPutALGameRoomRes : PktBase
{
};

struct PktPutALGameRoomNtf
{
	short XPos;
	short YPos;
	char NextTurnUserID[MAX_USER_ID_SIZE] = { 0, };
};


// 게임 종료 통보
struct PktEndGameRoomNtf
{
	char WinUserID[MAX_USER_ID_SIZE] = { 0, }; // 아이디 정보가 없으면 무승부
};

#pragma pack(pop)


	
