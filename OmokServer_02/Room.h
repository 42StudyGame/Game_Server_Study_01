#pragma once

#include <vector>
#include <string>
#include <memory>

#include "User.h"


namespace NServerNetLib { class ITcpNetwork; }
namespace NServerNetLib { class ILog; }


	
using TcpNet = NServerNetLib::ITcpNetwork;
using ILog = NServerNetLib::ILog;

class Game;

class Room
{
public:
	Room();
	virtual ~Room();

	void Init(const short index, const short maxUserCount);
	
	void SetNetwork(TcpNet* pNetwork, ILog* pLogger);

	void Clear();
		
	short GetIndex() { return m_Index;  }

	bool IsUsed() { return m_IsUsed; }
		
	short MaxUserCount() { return m_MaxUserCount; }

	short GetUserCount() { return (short)m_UserList.size(); }
	
	void SendToAllUser(const short packetId, const short dataSize, char* pData, const int excludedUserIndex);

	ERROR_CODE EnterUser(User* pUser);
	void NotifyEnterUserInfo(const int excludedUserIndex, const char* pszUserID);

	ERROR_CODE LeaveUser(const short userIndex);
	void NotifyLeaveUserInfo(const char* pszUserID);

	void NotifyChat(const int excludedUserIndex, const char* pszUserID, const char* pszMsg);


private:
	ILog* m_pRefLogger;
	TcpNet* m_pRefNetwork;

	short m_Index = -1;
	short m_MaxUserCount;
		
	bool m_IsUsed = false;
	std::vector<User*> m_UserList;

	//Game* m_pGame = nullptr;
};
