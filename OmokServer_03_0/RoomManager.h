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

	void Init(const int maxRoomCount, const int maxRoomUserCount);
		
	void Release();

	void SetNetwork(TcpNet* pNetwork, ILog* pLogger);
		
	Room* GetRoom(const short roomIndex);
				
	auto MaxRoomCount() { return (short)m_RoomList.size(); }

	Room* NewRoom();
	
	void UpdateAllRoom();


protected:
	ILog* m_pRefLogger;
	TcpNet* m_pRefNetwork;
		
	std::vector<Room*> m_RoomList;
	
};


