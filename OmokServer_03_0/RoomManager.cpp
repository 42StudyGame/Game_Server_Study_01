#include <algorithm>

#include "NetLib/ILog.h"
#include "NetLib/TcpNetwork.h"
#include "Packet.h"
#include "ErrorCode.h"
#include "User.h"
#include "Room.h"
#include "RoomManager.h"

void RoomManager::Init(const int maxRoomCountByLobby, const int maxRoomUserCount)
{		
	for (int i = 0; i < maxRoomCountByLobby; ++i)
	{
		m_RoomList.emplace_back(new Room());
		m_RoomList[i]->Init((short)i, (short)maxRoomUserCount);
	}
}

void RoomManager::Release()
{
	for (int i = 0; i < (int)m_RoomList.size(); ++i)
	{
		delete m_RoomList[i];
	}

	m_RoomList.clear();
}

void RoomManager::SetNetwork(TcpNet* pNetwork, ILog* pLogger)
{
	m_pRefLogger = pLogger;
	m_pRefNetwork = pNetwork;

	for (auto pRoom : m_RoomList)
	{
		pRoom->SetNetwork(pNetwork, pLogger);
	}
}

Room* RoomManager::GetRoom(const short roomIndex)
{
	if (roomIndex < 0 || roomIndex >= m_RoomList.size()) {
		return nullptr;
	}

	return m_RoomList[roomIndex];
}

Room* RoomManager::NewRoom()
{
	for (int i = 0; i < (int)m_RoomList.size(); ++i)
	{
		if (m_RoomList[i]->IsUsed() == false) {
			return m_RoomList[i];
		}
	}

	return nullptr;
}

void RoomManager::UpdateAllRoom()
{
	// 모든 방의 상태를 체크하고, 상황에 맞은 행동을 한다.

	//TODO: 이전에 체크했을 때의 시간과 지금 시간을 비교해서 1초 미만이면 체크 하지 않는다

	/*
	for(auto pRoom : m_RoomList)
	{
		if(pRoom->현재 유저 수() < 1)
		{
			continue;
		}

		if(pRoom->게임중())
		{
			if(턴 시간이 넘겼다면)
			{
			}
		}
		else if(pRoom->게임종료후 대기중())
		{
			if(게임종료 후 대기 시간이 지났다)
			{
				게임 시작 요청 가능한 상태로 변경
				방에 있는 모든 유저들에게 알려준다
			}
		}
	}
	
	*/
}

