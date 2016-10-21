#include "Socket.h"

Socket::Socket(tcp::socket&& tSocket) 
	: _socket(std::move(tSocket)),_isWritingAsync(false),
	_closed(false), _closing(false)
{
	readBuffer.Allocate(4098);
	writeBuffer.Allocate(32768);
}

Socket::~Socket()
{
	_closed = true;
	boost::system::error_code error;
	_socket.close(error);

	if (!error)
	{
		std::cout << "close a socket" << std::endl;
	}
}

void Socket::Disconnect()
{
	if (_closed.exchange(true))
		return;

	boost::system::error_code shutdownError;
	_socket.shutdown(boost::asio::socket_base::shutdown_send, shutdownError);

	if (shutdownError)
		;
	std::cout << "disconnect socket from " << _socket.remote_endpoint().address().to_string() << std::endl;
	sSocketMgr.RemoveSocket(this->shared_from_this());

	OnDisconnect();
}

void Socket::Accept()
{
	std::cout << "new connect from " << _socket.remote_endpoint().address().to_string() << std::endl;
	sSocketMgr.AddSocket(this->shared_from_this());

	OnConnect();

	_AsyncRead();
}

void Socket::_Connect()
{
	std::cout << "new connect to " << _socket.remote_endpoint().address().to_string() << std::endl;
	sSocketMgr.AddSocket(this->shared_from_this());

	OnConnect();
	_AsyncRead();
}

void Socket::_AsyncRead()
{        
	if (!IsOpen())
		return;

	auto self(shared_from_this());
	_socket.async_read_some(boost::asio::buffer(readBuffer.GetBuffer(), readBuffer.GetSpace()),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			this->AsyncReadCallBack(std::move(length));
		}
		else
		{
			this->Disconnect();
		}
	});
}

void Socket::AsyncReadCallBack(std::size_t&& length)
{
	readBuffer.IncrementWritten(length);

// 	OnRead();
// 	_AsyncRead();

	uint8 str[max_length];
	memset(str, 0, sizeof(str));

	size_t yy = readBuffer.GetSize();
	readBuffer.Read(&str, yy);
	//std::cout << str << std::endl;

//    memset(writeData, 0, sizeof(writeData));
//    sprintf_s(writeData, "%s", str);
	Send(str, yy);
	_AsyncWrite();
	_AsyncRead();
}

void Socket::_AsyncWrite()
{
	if (_isWritingAsync || !IsOpen())
	{
		return;
	}

	if (writeBuffer.GetContiguiousBytes())
	{
		_isWritingAsync = true;

		auto self(shared_from_this());
		_socket.async_write_some(boost::asio::buffer(writeBuffer.GetBufferStart(), writeBuffer.GetContiguiousBytes()),
			[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				this->AsyncWriteCallBack(std::move(length));
			}
			else
			{
				this->Disconnect();
			}
		});
	}
}

void Socket::AsyncWriteCallBack(std::size_t&& length)
{
	std::lock_guard<std::mutex> lock(mWriteLock);

// 	std::cout << "send str size is " <<  length << std::endl;
// 	memcpy(writeData, writeBuffer.GetBufferStart(), length);
// 	std::cout.write(writeData, length) << std::endl;

	_isWritingAsync = false;
	writeBuffer.Remove(length);
}

bool Socket::Send(const uint8 * bytes, uint32 len)
{
	std::lock_guard<std::mutex> lock(mWriteLock);

	bool bRet = false;
	if (writeBuffer.GetSpace() < len)
	{
		// 空间不足,需缓存
		return bRet;
	}

	if (len > 0)
	{
		writeBuffer.Write(bytes, len);
		bRet = true;
	}

	if (bRet)
	{
		// 同时只可写一个
		_AsyncWrite();
	}

	return true;
}