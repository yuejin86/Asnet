#ifndef _SOCKET_MGR_H
#define _SOCKET_MGR_H

#include "Common.h"
#include <set>
#include <memory>
#include <mutex>
#include <atomic>

class Socket;
class NetSession;

typedef std::set<std::shared_ptr<Socket>> SocketSet;
typedef std::set<std::shared_ptr<NetSession>> GameSocketSet;

class SocketMgr
{
public:
	SocketMgr();
	~SocketMgr();

	static SocketMgr& Instance()
	{
		static SocketMgr socketMgr;
		return socketMgr;
	}

	void AddSocket(std::shared_ptr<Socket>& newSocket);
	void RemoveSocket(std::shared_ptr<Socket>& removeSocket);

	void AddNetSession(std::shared_ptr<NetSession>& newSession);
	void RemoveNetSession(std::shared_ptr<NetSession>& removeSession);

private:
	SocketSet m_SocketList;
	GameSocketSet m_NetSessionList;
	uint32 m_MaxmPos;
	std::list<uint32> m_InvalidPos;
	std::mutex m_socketLock;
	std::mutex m_sessionLock;
	std::atomic<uint32> m_socketCount; 
};

#define sSocketMgr SocketMgr::Instance()

#endif