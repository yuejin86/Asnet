#include "HttpSession.h"

HttpSession::HttpSession(tcp::socket&& tSocket)
	: NetSession(std::move(tSocket))
{

}

HttpSession::~HttpSession()
{

}


void HttpSession::OnRead()
{
	bool ended = false;
	uint8 c;
	size_t n = readBuffer.GetSize();
	while (n-- > 0) {
		readBuffer.Read(&c, 1);
		if (m_Response.read(c) != 0) {
			ended = true;
			break;
		}
	}

	if (ended) 
	{
		std::string info;              // ÄÚÈÝ
		if (m_Response.chunked()) 
		{
			c = 0;
			int i = 0;
			const std::string& data = m_Response.data();
			std::string cache;
			size_t n = data.size();
			size_t size = 0;
			for (size_t i = 0; i < n; i++)
			{
				switch (c)
				{
				case 0:
					{
						if (data[i] == '\n') { //chunk size
							c = size ? 1 : 2;
							break;
						}

						if (isxdigit(data[i])) {
							size = (size << 4) + XDIGIT_TO_NUM(data[i]);
						}
					}
					break;
				case 1:
					{
						if (size)
						{
							info += data[i];
							size--;
						}
						if (data[i] == '\n') {
							c = 0;
							break;
						}
					}
					break;
				case 2:
					break;
				}
			}
		}
		else
		{
			info = m_Response.data();
		}

		Disconnect();
	}
}

void HttpSession::OnConnect()
{
	NetSession::OnConnect();
}

void HttpSession::OnDisconnect()
{
	NetSession::OnDisconnect();
}

void HttpSession::Get(const char* body, uint32 len)
{
	char buffSend[512] = {0};
	uint32 n = snprintf(buffSend, sizeof buffSend, "GET %s HTTP/1.1\r\nHost: %s\r\nAccept: text/html\r\n\r\n", body, m_host);

	Send((const uint8 *)&buffSend, n);
}

void HttpSession::Post(const char* body, uint32 len)
{
	char buffSend[512] = {0};
	uint32 n = snprintf(buffSend, sizeof buffSend, "POST /account?tunnel-command=2852126760 HTTP/1.1\r\nHost: %s\r\nContent-Length: %u\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s", m_host, len, body);

	Send((const uint8*)&buffSend, n);
}

void HttpSession::SetHost(std::string&& host)
{
	m_host = std::move(host);
}

HttpSession* HttpSession::ConnectHttp(boost::asio::io_service &io, const char* addstr, const char* port)
{
	HttpSession* pHttpSession = ConnectTCPSocket<HttpSession>(io, addstr, port);

	if (pHttpSession != NULL)
	{
		char host[50] = {0};
		sprintf_s(host, "%s:%s", addstr, port);
		pHttpSession->SetHost(std::move(std::string(host)));
	}

	return pHttpSession;
}