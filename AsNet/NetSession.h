#ifndef _NET_SESSION_H
#define _NET_SESSION_H

#include "Socket.h"

struct NetPktHeader
{
	uint32 cmd;
	uint32 size;
};

typedef bool (*_handler)(const char* pMsg, int n32MsgLength, NetSession* vthis, int n32MsgID);

struct MsgNode
{
	_handler mHandle;
	bool mIsInitMsg;
	MsgNode() { mIsInitMsg=false; mHandle=NULL; }
};

class MsgHandler
{
public:
	MsgHandler(int base,int max);
	virtual ~MsgHandler();
public:
	void RegisterMsgFunc(int type, _handler fuc_handle,bool isInitMsg=false);
	void SetUnKnownMsgHandle(_handler fuc_handle);
	MsgNode* mNodes;
	_handler mUnknownHandle;
	int mMax;
	int mBase;
};

class NetSession : public Socket
{
public:
	NetSession(tcp::socket&& tSocket);
	virtual ~NetSession();

	void OnRead();
	void OnConnect();
	void OnDisconnect();

	inline void SetId(uint32 id) { m_Id = id;}
	inline uint32 GetID() { return m_Id;}

	inline void SetType(uint32 type) { m_Type = type;}
	inline uint32 GetType() { return m_Type;} 

	void SetMsgHandler(MsgHandler* pHandler);

private:
	uint32 m_Id;           // 外部
	uint32 m_Type;         // 进程内部
	uint32 m_Remaining;
	uint32 m_Opcode;
	uint32 m_Size;
	MsgHandler* m_MsgHandler;
};

#endif