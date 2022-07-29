#pragma once

#include <memory>

#include "Packet.h"
#include "ErrorCode.h"
#include "NetLib/Define.h"


namespace NServerNetLib
{
	class ITcpNetwork;
	class ILog;
}

	
class UserManager;
class RoomManager;


class PacketProcess
{
	using PacketInfo = NServerNetLib::RecvPacketInfo;
	
	using TcpNet = NServerNetLib::ITcpNetwork;
	using ILog = NServerNetLib::ILog;

public:
	PacketProcess();
	~PacketProcess();

	void Init(TcpNet* pNetwork, UserManager* pUserMgr, RoomManager* pRoomMgr, NServerNetLib::ServerConfig* pConfig, ILog* pLogger);

	void Process(PacketInfo packetInfo);

	
private:
	ILog* m_pRefLogger;
	TcpNet* m_pRefNetwork;
				
	UserManager* m_pRefUserMgr;
	RoomManager* m_pRefRoomMgr;
						
private:
	ERROR_CODE NtfSysConnctSession(PacketInfo packetInfo);
	ERROR_CODE NtfSysCloseSession(PacketInfo packetInfo);
		
	ERROR_CODE Login(PacketInfo packetInfo);

	ERROR_CODE EnterRoom(PacketInfo packetInfo);
	ERROR_CODE LeaveRoom(PacketInfo packetInfo);
	ERROR_CODE ChatRoom(PacketInfo packetInfo);
};
