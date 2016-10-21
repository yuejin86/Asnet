#include "NetSession.h"
#include "Socket.h"

MsgHandler::MsgHandler(int base,int max)
{
	mBase = base;
	mMax = max;
	mNodes = new MsgNode[max];
	memset(mNodes,0,sizeof(MsgNode)*max);
	mUnknownHandle = NULL;
}

MsgHandler::~MsgHandler()
{
	delete [] mNodes;
}

void MsgHandler::RegisterMsgFunc(int type, _handler fuc_handle, bool isInitMsg/*=false*/)
{
	type -= mBase;
	if (type<0) { char* p = NULL; *p = '\0'; }
	MsgNode* pNode = mNodes+type;
	pNode->mIsInitMsg = isInitMsg;
	pNode->mHandle = fuc_handle;
}

void MsgHandler::SetUnKnownMsgHandle(_handler fuc_handle)
{
	mUnknownHandle = fuc_handle;
}

NetSession::NetSession(tcp::socket&& tSocket) 
	: Socket(std::move(tSocket)),
	m_Id(0),
	m_Type(0),
	m_Opcode(0),
	m_Size(0),
	m_Remaining(0),
	m_MsgHandler(NULL)
{

}

NetSession::~NetSession()
{

}

void NetSession::OnRead()
{
	if (m_MsgHandler==NULL) 
		return;

	while (true)
	{
		if (m_Remaining == 0)
		{
			if (readBuffer.GetSize() < sizeof(NetPktHeader))
			{
				// 长度少于包头
				return;
			}

			// 读包头
			NetPktHeader tHeader;
			readBuffer.Read((uint8*)&tHeader, sizeof(NetPktHeader));

			// 包长
			m_Remaining = m_Size = tHeader.size - sizeof(NetPktHeader);
			m_Opcode = tHeader.cmd;
		}

		if (m_Remaining > 0)
		{
			if (readBuffer.GetSize() < m_Remaining)
			{
				// 不够包长
				return;
			}
		}

		char* pMsgData = new char[m_Remaining];
		if (m_Remaining > 0)
		{
			readBuffer.Read(pMsgData, m_Remaining);
		}

		int32 nMsgLen = m_Remaining;
		int32 nMsgType = m_Opcode;
		int32 nMsgId = m_Opcode - m_MsgHandler->mBase;
		m_Remaining = m_Opcode = m_Size = 0;

		if (nMsgId >= 0 && nMsgId < m_MsgHandler->mMax)
		{
			MsgNode* pNode = m_MsgHandler->mNodes + nMsgId;
			if (pNode->mHandle)
			{
				bool bRet = pNode->mHandle(pMsgData, nMsgLen, this, nMsgType);
			}
			else
			{
				m_MsgHandler->mUnknownHandle(pMsgData, nMsgLen, this, nMsgType);
			}
		}
		else if(m_MsgHandler->mUnknownHandle)
		{
			m_MsgHandler->mUnknownHandle(pMsgData, nMsgLen, this, nMsgType);
		}
	}
}

void NetSession::OnConnect() 
{
	sSocketMgr.AddNetSession(std::dynamic_pointer_cast<NetSession>(shared_from_this()));
}

void NetSession::OnDisconnect() 
{
	sSocketMgr.RemoveNetSession(std::dynamic_pointer_cast<NetSession>(shared_from_this()));
}

void NetSession::SetMsgHandler(MsgHandler* pHandler)
{
	m_MsgHandler = pHandler;
}