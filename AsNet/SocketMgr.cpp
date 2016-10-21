#include "SocketMgr.h"
#include "NetSession.h"

SocketMgr::SocketMgr()
	: m_socketCount(0)
{
}

SocketMgr::~SocketMgr()
{
}

void SocketMgr::AddSocket(std::shared_ptr<Socket>& newSocket)
{
	std::lock_guard<std::mutex> lock(m_socketLock);

	auto iter = m_SocketList.find(newSocket);
	if (iter == m_SocketList.end())
	{
		m_SocketList.insert(newSocket);

		++m_socketCount;
		if (m_socketCount%2 == 0)
		{
			std::cout << "Socket Count is " << m_socketCount << std::endl;
		}
	}
	else
	{
		assert(false);
	}
}

void SocketMgr::RemoveSocket(std::shared_ptr<Socket>& removeSocket)
{
	std::lock_guard<std::mutex> lock(m_socketLock);

	auto iter = m_SocketList.find(removeSocket);
	if (iter != m_SocketList.end())
	{
		m_SocketList.erase(iter);

		--m_socketCount;
	}
	else
	{
		assert(false);
	}
}

void SocketMgr::AddNetSession(std::shared_ptr<NetSession>& newSession)
{
	std::lock_guard<std::mutex> lock(m_sessionLock);

	auto iter = m_NetSessionList.find(newSession);
	if (iter == m_NetSessionList.end())
	{
		m_NetSessionList.insert(newSession);

		if (newSession->GetType() == 0)
		{
			// Íâ²¿
			uint32 pos = 0;
			if (m_InvalidPos.size() > 0)
			{
				pos = m_InvalidPos.front();
				m_InvalidPos.pop_front();
			}
			else
			{
				pos = ++m_MaxmPos;
			}

			newSession->SetId(pos);
		}
	}
	else
	{
		assert(false);
	}
}

void SocketMgr::RemoveNetSession(std::shared_ptr<NetSession>& removeSession)
{
	std::lock_guard<std::mutex> lock(m_sessionLock);

	auto iter = m_NetSessionList.find(removeSession);
	if (iter != m_NetSessionList.end())
	{
		if (removeSession->GetType() == 0)
		{
			m_InvalidPos.push_back(removeSession->GetID());
		}
		
		m_NetSessionList.erase(removeSession);	
	}
	else
	{
		assert(false);
	}
}