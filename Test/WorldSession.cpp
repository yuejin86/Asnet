#include "WorldSession.h"
#include "ParseProto.h"


WorldMsgHandler::WorldMsgHandler()
	: MsgHandler(1, 1)
{
	InitMsgHandlerTable();
}

WorldMsgHandler::~WorldMsgHandler()
{

}

void WorldMsgHandler::InitMsgHandlerTable()
{
	RegisterMsgFunc(1, WorldSession::TestMsgHandler,true);
	SetUnKnownMsgHandle(WorldSession::TestMsgHandler);
}

WorldSession::WorldSession(tcp::socket&& tSocket)
	:NetSession(std::move(tSocket))
{
	SetId(SESSION_TYPE_WORLD);

	static MsgHandler* sMsgHandler = new WorldMsgHandler();
	SetMsgHandler(sMsgHandler);
}

WorldSession::~WorldSession()
{

}

void WorldSession::OnRead()
{
	NetSession::OnRead();
}

void WorldSession::OnConnect()
{
	NetSession::OnConnect();
}

void WorldSession::OnDisconnect()
{
	NetSession::OnDisconnect();
}

void WorldSession::SendMsg(google::protobuf::Message& sMsg, uint32 nMsgID)
{
	uint32 nMsgSize = sMsg.ByteSize();

	NetPktHeader tHeader;
	tHeader.cmd = nMsgID;
	tHeader.size = nMsgSize + sizeof(NetPktHeader);

	char* pBuffer = new char[tHeader.size];
	memcpy(pBuffer, (char*)&tHeader, sizeof(NetPktHeader));

	bool res = sMsg.SerializeToArray(pBuffer+sizeof(NetPktHeader), nMsgSize);
	assert(res);

	Send((uint8*)&pBuffer, tHeader.size);
	delete []pBuffer;
}
bool WorldSession::TestMsgHandler(const char* pMsg, int n32MsgLength, NetSession* vthis, int n3MsgID)
{
	std::cout << "Rec str size is " <<  n32MsgLength << std::endl;
	std::cout.write(pMsg, n32MsgLength) << std::endl;

	char writeData[max_length] = {0};
	memset(writeData, 0, sizeof(writeData));
	sprintf_s(writeData, "%s", pMsg);

	vthis->Send((uint8*)&writeData, strlen(writeData)+1);

	return true;
}