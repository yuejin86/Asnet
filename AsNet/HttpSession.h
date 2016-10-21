#ifndef _HTTP_SESSION_H
#define _HTTP_SESSION_H

#include "NetSession.h"
#include "HttpResponse.h"

class HttpSession : public NetSession
{
public:
	HttpSession(tcp::socket&& tSocket);
	~HttpSession();

	void OnRead();
	void OnConnect();
	void OnDisconnect();

	void Get(const char* body, uint32 len);
	void Post(const char* body, uint32 len);
	void SetHost(std::string&& host);

	static HttpSession* ConnectHttp(boost::asio::io_service &io, const char* addstr, const char* port);

private:
	HttpResponse m_Response;
	std::string m_host;
};

#endif