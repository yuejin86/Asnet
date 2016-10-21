#ifndef _WORLD_SESSION_H
#define _WORLD_SESSION_H

#include "NetSession.h"
#include "WorldSession.pb.h"

#define SESSION_TYPE_WORLD 1

class WorldMsgHandler : public MsgHandler
{
public:
	WorldMsgHandler();
	~WorldMsgHandler();

private:
	void InitMsgHandlerTable();
};

class WorldSession : public NetSession
{
public:
	WorldSession(tcp::socket&& tSocket);
	~WorldSession();

	void OnRead();
	void OnConnect();
	void OnDisconnect();
	
	void SendMsg(google::protobuf::Message& sMsg, uint32 nMsgID);
	static bool TestMsgHandler(const char* pMsg, int nMsgLength, NetSession* vthis, int n32MsgID);
};

#endif