#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <memory>
#include <boost/asio.hpp>
#include "CircularBuffer.h"
#include <iostream>
#include "SocketMgr.h"
#include <mutex>

template<class T>
T* ConnectTCPSocket(boost::asio::io_service &io, const char* addstr, const char* port)
{
	try
	{
		tcp::socket tSocket(io);
		tcp::resolver resolver(io);
		tcp::resolver::query query(tcp::v4(), addstr, port);
		boost::asio::connect(tSocket, resolver.resolve(query));

		T * s = new T(std::move(tSocket));

		std::shared_ptr<T> newSocket(s);
		newSocket->_Connect();

		return s;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
		return 0;
	}

	return 0;	
}

#define max_length 12048

using boost::asio::ip::tcp;

class Socket : public std::enable_shared_from_this<Socket>
{
public:
	Socket(tcp::socket&& tSocket);
	virtual ~Socket();

	void SetSocket(tcp::socket&& tSocket);
	void Disconnect();
	void Accept();
	void _Connect();

	virtual void OnRead() {}
	virtual void OnConnect() {}
	virtual void OnDisconnect() {}

	void _AsyncRead();
	void AsyncReadCallBack(std::size_t&& length);

	void _AsyncWrite();
	void AsyncWriteCallBack(std::size_t&& length);

	bool Send(const uint8 * bytes, uint32 len);
	bool IsOpen() const { return !_closed && !_closing; }

protected:
	char writeData[max_length];
	CircularBuffer readBuffer;
	CircularBuffer writeBuffer;
	std::mutex  mWriteLock;

	std::atomic<bool> _closed;     // 写和读关闭
	std::atomic<bool> _closing;    // 写完才关闭

    bool _isWritingAsync;

private:
	tcp::socket _socket;
};

#endif