#include <string>
#include <thread>
#include "boost/thread.hpp"
#include "boost/bind.hpp"
#include "ListenSocket.h"
#include "WorldSession.h"

using boost::asio::ip::tcp;

void ServerRun(tcp::socket& _socket)
{
	std::cout << "accept a new socket" << std::endl;
	while (true)
	{
		// TODO
		char data[max_length];
		memset(data, 0, sizeof(data));

		boost::system::error_code error;
		size_t length = _socket.read_some(boost::asio::buffer(data), error);
		if (error == boost::asio::error::eof)
		{
			std::cout << "Connection closed cleanly by peer." << std::endl;
		}
		else if (error)
		{
			std::cout << "Other error" << std::endl;
			break;
		}

		if (length > 0)
		{
			std::cout << "message: " << data << std::endl;
		}
	}

	std::cout << "out of thread" << std::endl;
}

boost::asio::io_service ioService;
boost::asio::io_service::work tWork(ioService);

void ShutDownNetThreat(std::vector<std::shared_ptr<std::thread>>& rThread)
{
	//ioService.stop();
	for (std::size_t i = 0; i < rThread.size(); i++)
	{
		rThread[i]->join();
	}
}

int main()
{
	std::string binIp("0.0.0.0");


// 	ListenWork<Socket> listenWork(ioService);
// 	bool isOk = listenWork.Start(ioService, binIp, 8086);

	ListenWork<WorldSession> listenServerWork(ioService);
	bool isOk = listenServerWork.Start(ioService, binIp, 8087);

//	WorldSession* testSession = ConnectTCPSocket<WorldSession>(ioService, "127.0.0.1", "8087");

	std::vector<std::shared_ptr<std::thread>> mThreadList;
	if (isOk)
	{
		for (uint32 i = 0; i < 8; i++)
		{
			 std::shared_ptr<std::thread> pTh(new std::thread(
				boost::bind(&boost::asio::io_service::run,&ioService)));

			mThreadList.push_back(pTh);
		}

		 ShutDownNetThreat(mThreadList);
	}

	system("pause");
	return 0;
}