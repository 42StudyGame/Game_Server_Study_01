#pragma once
#include <memory>

#include "Packet.h"
#include "ErrorCode.h"


namespace NServerNetLib
{
	struct ServerConfig;
	class ILog;
	class ITcpNetwork;
}


class UserManager;
class RoomManager;
class PacketProcess;

class Server
{
public:
	Server();
	~Server();

	ERROR_CODE Init();

	void Run();

	void Stop();


private:
	ERROR_CODE LoadConfig();

	void Release();


private:
	bool m_IsRun = false;

	std::unique_ptr<NServerNetLib::ServerConfig> m_pServerConfig;
	std::unique_ptr<NServerNetLib::ILog> m_pLogger;

	std::unique_ptr<NServerNetLib::ITcpNetwork> m_pNetwork;
	
	std::unique_ptr<PacketProcess> m_pPacketProc;
	
	std::unique_ptr<UserManager> m_pUserMgr;
	
	std::unique_ptr<RoomManager> m_pRoomMgr;
		
};

