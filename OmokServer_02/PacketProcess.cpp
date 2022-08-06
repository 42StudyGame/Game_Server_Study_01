#include <cstring>

#include "NetLib/ILog.h"
#include "NetLib/TcpNetwork.h"
#include "User.h"
#include "UserManager.h"
#include "Room.h"
#include "RoomManager.h"
#include "PacketProcess.h"

using LOG_TYPE = NServerNetLib::LOG_TYPE;
using ServerConfig = NServerNetLib::ServerConfig;

	
PacketProcess::PacketProcess() {}
PacketProcess::~PacketProcess() {}

void PacketProcess::Init(TcpNet* pNetwork, UserManager* pUserMgr, RoomManager* pLobbyMgr, ServerConfig* pConfig, ILog* pLogger)
{
	m_pRefLogger = pLogger;
	m_pRefNetwork = pNetwork;
	m_pRefUserMgr = pUserMgr;
	m_pRefRoomMgr = pLobbyMgr;
}
	
void PacketProcess::Process(PacketInfo packetInfo)
{
	using netLibPacketId = NServerNetLib::PACKET_ID;
	using commonPacketId = PACKET_ID;

	auto packetId = packetInfo.PacketId;
		
	switch (packetId)
	{
	case (int)netLibPacketId::NTF_SYS_CONNECT_SESSION:
		NtfSysConnctSession(packetInfo);
		break;
	case (int)netLibPacketId::NTF_SYS_CLOSE_SESSION:
		NtfSysCloseSession(packetInfo);
		break;
	case (int)commonPacketId::PK_LOGIN_IN_REQ:
		Login(packetInfo);
		break;
	case (int)commonPacketId::PK_ENTER_ROOM_REQ:
		EnterRoom(packetInfo);
		break;
	case (int)commonPacketId::PK_LEAVE_ROOM_REQ:
		LeaveRoom(packetInfo);
		break;
	case (int)commonPacketId::PK_CHAT_ROOM_REQ:
		ChatRoom(packetInfo);
		break;
	}
	
}


ERROR_CODE PacketProcess::NtfSysConnctSession(PacketInfo packetInfo)
{
	m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | NtfSysConnctSession. sessionIndex(%d)", __FUNCTION__, packetInfo.SessionIndex);

	//TODO: 유저가 방에 들어간 상태이면 방에서 빼고, 방에 아직 유저가 있다면 있는 유저에게 PK_USER_LEAVE_ROOM_NTF을 보낸다

	return ERROR_CODE::NONE;
}

ERROR_CODE PacketProcess::NtfSysCloseSession(PacketInfo packetInfo)
{
	auto pUser = std::get<1>(m_pRefUserMgr->GetUser(packetInfo.SessionIndex));

	if (pUser) {		
		m_pRefUserMgr->RemoveUser(packetInfo.SessionIndex);		
	}
			
	m_pRefLogger->Write(LOG_TYPE::L_INFO, "%s | NtfSysCloseSesson. sessionIndex(%d)", __FUNCTION__, packetInfo.SessionIndex);
	return ERROR_CODE::NONE;
}


ERROR_CODE PacketProcess::Login(PacketInfo packetInfo)
{
	// 패스워드는 무조건 pass 해준다.
	// ID 중복이라면 에러 처리한다.
	PktLogInRes resPkt;
	auto reqPkt = (PktLogInReq*)packetInfo.pRefData;

	auto addRet = m_pRefUserMgr->AddUser(packetInfo.SessionIndex, reqPkt->szID);

	if (addRet != ERROR_CODE::NONE) {
		resPkt.SetError(addRet);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_LOGIN_IN_RES, sizeof(PktLogInRes), (char*)&resPkt);
		return addRet;
	}
		
	resPkt.ErrorCode = (short)addRet;
	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_LOGIN_IN_RES, sizeof(PktLogInRes), (char*)&resPkt);

	return ERROR_CODE::NONE;
}

ERROR_CODE PacketProcess::EnterRoom(PacketInfo packetInfo)
{
	PktEnterRoomRes resPkt;
	auto reqPkt = (PktEnterRoomReq*)packetInfo.pRefData;
		
	auto [errorCode, pUser] = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);

	if (errorCode != ERROR_CODE::NONE) {
		resPkt.SetError(errorCode);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_ENTER_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return errorCode;
	}

	if (pUser->IsCurDomainInRoom() == false) {
		resPkt.SetError(ERROR_CODE::ROOM_ENTER_INVALID_DOMAIN);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_ENTER_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return ERROR_CODE::ROOM_ENTER_INVALID_DOMAIN;
	}
	

	Room* pRoom = nullptr;
	
	if( reqPkt->RoomNumber == -1 )
	{
		pRoom = m_pRefRoomMgr->NewRoom();
		if (pRoom == nullptr) {
			resPkt.SetError(ERROR_CODE::ROOM_ENTER_EMPTY_ROOM);
			m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_ENTER_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
			return ERROR_CODE::ROOM_ENTER_EMPTY_ROOM;
		}	
	}
	else
	{
		pRoom = m_pRefRoomMgr->GetRoom(reqPkt->RoomNumber);
		if (pRoom == nullptr) {
			resPkt.SetError(ERROR_CODE::ROOM_ENTER_INVALID_ROOM_INDEX);
			m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_ENTER_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
			return ERROR_CODE::ROOM_ENTER_INVALID_ROOM_INDEX;
		}
	
		auto enterRet = pRoom->EnterUser(pUser);
		if (enterRet != ERROR_CODE::NONE) {
			resPkt.SetError(enterRet);
			m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_ENTER_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
			return enterRet;
		}
	}
	
	
	pUser->EnterRoom(pRoom->GetIndex());

	pRoom->NotifyEnterUserInfo(pUser->GetIndex(), pUser->GetID().c_str());

	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_ENTER_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
	return ERROR_CODE::NONE;
}

ERROR_CODE PacketProcess::LeaveRoom(PacketInfo packetInfo)
{
	PktLeaveRoomRes resPkt;
	
	auto [errorCode, pUser] = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	if (errorCode != ERROR_CODE::NONE) {
		resPkt.SetError(errorCode);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_LEAVE_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return errorCode;
	}

	auto userIndex = pUser->GetIndex();

	if (pUser->IsCurDomainInRoom() == false) {
		resPkt.SetError(ERROR_CODE::ROOM_LEAVE_INVALID_DOMAIN);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_LEAVE_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return ERROR_CODE::ROOM_LEAVE_INVALID_DOMAIN;
	}
		
	auto pRoom = m_pRefRoomMgr->GetRoom(pUser->GetRoomIndex());
	if (pRoom == nullptr) {
		resPkt.SetError(ERROR_CODE::ROOM_LEAVE_INVALID_ROOM_INDEX);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_LEAVE_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return ERROR_CODE::ROOM_LEAVE_INVALID_ROOM_INDEX;
	}

	auto leaveRet = pRoom->LeaveUser(userIndex);
	if (leaveRet != ERROR_CODE::NONE) {
		resPkt.SetError(leaveRet);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_LEAVE_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return leaveRet;
	}

	
	pUser->LeaveRoom();

	pRoom->NotifyLeaveUserInfo(pUser->GetID().c_str());

	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_LEAVE_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
	return ERROR_CODE::NONE;
}

ERROR_CODE PacketProcess::ChatRoom(PacketInfo packetInfo)
{
	PktChatRoomRes resPkt;
	auto reqPkt = (PktChatRoomReq*)packetInfo.pRefData;
		
	auto [errorCode, pUser] = m_pRefUserMgr->GetUser(packetInfo.SessionIndex);
	if (errorCode != ERROR_CODE::NONE) {
		resPkt.SetError(errorCode);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_CHAT_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return errorCode;
	}

	if (pUser->IsCurDomainInRoom() == false) {
		resPkt.SetError(ERROR_CODE::ROOM_CHAT_INVALID_DOMAIN);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_CHAT_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return ERROR_CODE::ROOM_CHAT_INVALID_DOMAIN;
	}
		
	auto pRoom = m_pRefRoomMgr->GetRoom(pUser->GetRoomIndex());
	if (pRoom == nullptr) {
		resPkt.SetError(ERROR_CODE::ROOM_CHAT_INVALID_ROOM_INDEX);
		m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_CHAT_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
		return ERROR_CODE::ROOM_CHAT_INVALID_ROOM_INDEX;
	}

	pRoom->NotifyChat(pUser->GetSessioIndex(), pUser->GetID().c_str(), reqPkt->Msg);

	m_pRefNetwork->SendData(packetInfo.SessionIndex, (short)PACKET_ID::PK_CHAT_ROOM_RES, sizeof(resPkt), (char*)&resPkt);
	return ERROR_CODE::NONE;
}
