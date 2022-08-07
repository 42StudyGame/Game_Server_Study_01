#include <algorithm>
#include <cstring>
#include <wchar.h>

#include "NetLib/ILog.h"
#include "NetLib/TcpNetwork.h"
#include "Packet.h"
#include "ErrorCode.h"
#include "User.h"
#include "Room.h"



Room::Room() {}

Room::~Room()
{
}
	
void Room::Init(const short index, const short maxUserCount)
{
	m_Index = index;
	m_MaxUserCount = maxUserCount;
}

void Room::SetNetwork(TcpNet* pNetwork, ILog* pLogger)
{
	m_pRefLogger = pLogger;
	m_pRefNetwork = pNetwork;
}

void Room::Clear()
{
	m_IsUsed = false;
	m_UserList.clear();
}

ERROR_CODE Room::EnterUser(User* pUser)
{
	if (m_IsUsed == false) {
		return ERROR_CODE::ROOM_ENTER_NOT_CREATED;
	}

	if (m_UserList.size() == m_MaxUserCount) {
		return ERROR_CODE::ROOM_ENTER_MEMBER_FULL;
	}

	m_UserList.push_back(pUser);
	return ERROR_CODE::NONE;
}

void Room::SendToAllUser(const short packetId, const short dataSize, char* pData, const int excludedUserIndex)
{
	for (auto pUser : m_UserList)
	{
		if (pUser->GetIndex() == excludedUserIndex) {
			continue;
		}

		m_pRefNetwork->SendData(pUser->GetSessioIndex(), packetId, dataSize, pData);
	}
}

void Room::NotifyEnterUserInfo(const int excludedUserIndex, const char* pszUserID)
{
	PktNewUserEnterRoomNtf pkt;
	strncpy_s(pkt.UserID, MAX_USER_ID_SIZE, pszUserID, MAX_USER_ID_SIZE);
	SendToAllUser((short)PACKET_ID::PK_NEW_USER_ENTER_ROOM_NTF, sizeof(pkt), (char*)&pkt, excludedUserIndex);
}

void Room::LeaveUserForAbnormal(const short userIndex, const char* pszUserID)
{
	if (LeaveUser(userIndex) != ERROR_CODE::NONE) 
	{
		return;
	}

	NotifyLeaveUserInfo(pszUserID);
}

ERROR_CODE Room::LeaveUser(const short userIndex)
{
	if (m_IsUsed == false) {
		return ERROR_CODE::ROOM_ENTER_NOT_CREATED;
	}

	auto iter = std::find_if(std::begin(m_UserList), std::end(m_UserList), [userIndex](auto pUser) { return pUser->GetIndex() == userIndex; });
	if (iter == std::end(m_UserList)) {
		return ERROR_CODE::ROOM_LEAVE_NOT_MEMBER;
	}

	m_UserList.erase(iter);

	if (m_UserList.empty())
	{
		Clear();
	}

	return ERROR_CODE::NONE;
}

void Room::NotifyLeaveUserInfo(const char* pszUserID)
{
	if (m_IsUsed == false) {
		return;
	}

	PktUserLeaveRoomNtf pkt;
	strncpy_s(pkt.UserID, MAX_USER_ID_SIZE, pszUserID, MAX_USER_ID_SIZE);
	SendToAllUser((short)PACKET_ID::PK_USER_LEAVE_ROOM_NTF, sizeof(pkt), (char*)&pkt, -1);
}

void Room::NotifyChat(const int excludedUserIndex, const char* pszUserID, const char* pszMsg)
{
	PktChatRoomNtf pkt;
	strncpy_s(pkt.UserID, MAX_USER_ID_SIZE, pszUserID, MAX_USER_ID_SIZE);
	strncpy_s(pkt.Msg, MAX_ROOM_CHAT_MSG_SIZE, pszMsg, MAX_ROOM_CHAT_MSG_SIZE);
	SendToAllUser((short)PACKET_ID::PK_CHAT_ROOM_NTF, sizeof(pkt), (char*)&pkt, excludedUserIndex);
}