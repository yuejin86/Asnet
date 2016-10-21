#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "Common.h"

#define XDIGIT_TO_NUM(h) ((h) < 'A' ? (h) - '0' : toupper (h) - 'A' + 10)
#define X2DIGITS_TO_NUM(h1, h2) ((XDIGIT_TO_NUM (h1) << 4) + XDIGIT_TO_NUM (h2))

#define XNUM_TO_DIGIT(x) ("0123456789ABCDEF"[x] + 0)
#define XNUM_TO_digit(x) ("0123456789abcdef"[x] + 0)

class HttpResponse
{
public:
	HttpResponse();
	~HttpResponse();

	int read(uint8 c);
	bool chunked(void) { return m_chunked; }
	const std::string& data(void) const { return m_data; }

private:
	int m_status;
	std::string m_data;
	bool m_chunked;
	size_t m_content_length;
	uint8 m_stage;
	std::string m_line;
	uint8 m_cache;
};
#endif