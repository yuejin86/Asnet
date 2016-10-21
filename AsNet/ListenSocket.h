#ifndef _LISTEN_SOCKET_H
#define _LISTEN_SOCKET_H

#include <boost/asio.hpp>
#include <iostream>
#include <set>

using boost::asio::ip::tcp;

template<class T>
class ListenWork
{
public:
	ListenWork::ListenWork(boost::asio::io_service& ioService) 
		: _acceptor(nullptr), aSocket(ioService)
	{
	}

	ListenWork::~ListenWork()
	{
		delete _acceptor;
		_acceptor = nullptr;
	}

	bool Start(boost::asio::io_service& ioService, std::string const& bindIp, unsigned short&& port)
	{
		try
		{
			_acceptor = new tcp::acceptor(ioService, tcp::endpoint(boost::asio::ip::address::from_string(bindIp), port), false);
		}
		catch(boost::system::system_error const& err)
		{
			std::cout << "error code: " << err.what() << std::endl;
			return false;
		}

		//std::cout << "now start async accept socket" << std::endl;
		AsyncAccept();

		return true;
	}

	void AsyncAccept()
	{
		_acceptor->async_accept(aSocket, 
			[this](boost::system::error_code ec)
		{
			if (!ec)
			{
				//std::make_shared<T>(std::move(aSocket))->Accept();
				
				mSocket = new T(std::move(aSocket));
				std::shared_ptr<T> newSocket(mSocket);
				newSocket->Accept();
			}
			else
			{
				std::cout << "Failed to initialize client's socket " << boost::system::system_error(ec).what() << std::endl;
			}

			AsyncAccept();
		});
	}

private:
	tcp::acceptor* _acceptor;
	tcp::socket aSocket;
	T* mSocket;
};

#endif

