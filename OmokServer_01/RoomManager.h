#pragma once

#include <vector>
#include <unordered_map>


namespace NServerNetLib
{
	class ITcpNetwork;
}

namespace NServerNetLib
{
	class ILog;
}



using TcpNet = NServerNetLib::ITcpNetwork;
using ILog = NServerNetLib::ILog;

class User;
class Room;

class RoomManager
{
public:
	RoomManager() = default;
	virtual ~RoomManager() = default;

	void Init(const int maxRoomCountByLobby, const int maxRoomUserCount);
		
	void Release();

	void SetNetwork(TcpNet* pNetwork, ILog* pLogger);
	
	short GetUserCount();
	
	Room* GetRoom(const short roomIndex);
				
	auto MaxUserCount() { return (short)m_MaxUserCount; }

	auto MaxRoomCount() { return (short)m_RoomList.size(); }
		

protected:
	ILog* m_pRefLogger;
	TcpNet* m_pRefNetwork;

	short m_MaxUserCount = 0;
	std::unordered_map<int, User*> m_UserIndexDic;
	std::unordered_map<const char*, User*> m_UserIDDic;

	std::vector<Room*> m_RoomList;
};


