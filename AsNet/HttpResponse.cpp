#include "HttpResponse.h"

HttpResponse::HttpResponse() :
	m_stage(0),
	m_status(200),
	m_chunked(false),
	m_content_length(0)
{

}

HttpResponse::~HttpResponse()
{

}

int HttpResponse::read(uint8 c)
{
	if (c == EOF)
		return -1;

	m_line.push_back(c);
	switch (m_stage)
	{
	case 0:
		if (c == '\n')
		{
			int i = 0;
			size_t n = m_line.size();
			while (isspace(m_line[i])) { // skip space
				n--;
				i++;
			}

			while (n > 0 && m_line[i] != ' ') { // skip version
				n--;
				i++;
			}

			while (n > 0 && !isdigit(m_line[i])) {
				n--;
				i++;
			}

			if (n > 3)
			{
				if (m_line[i] == '2' && m_line[i+1] == '0' && m_line[i+2] == '0') { // check status
					m_line.clear();
					m_stage = 1;
					return 0;
				}
			}

			m_line.clear();
			m_stage = 3;
			return -1;
		}
		break;
	case 1: // header
		if (c == '\n')
		{
			size_t n = m_line.length();
			if (n < 3 && (m_line[0] == '\r' || m_line[0] == '\n'))
			{
				m_stage = m_chunked ? 3 : 2;
				break;
			}

			if (m_content_length == 0)
			{
				int i = 0;
				while (isspace(m_line[i])) {
					n--;
					i++;
				}

				size_t pos = i;

				while (n > 0 && m_line[i] != ':') {
					m_line[i] = toupper(m_line[i]);
					n--;
					i++;
				}

				if (m_line.compare(pos, 14, "CONTENT-LENGTH") == 0)
				{
					while (n > 0 && !isdigit(m_line[i])) {
						n--;
						i++;
					}

					if (n > 0)
					{
						while (isdigit(m_line[i])) {
							m_content_length *= 10;
							m_content_length += m_line[i] - '0';
							i++;
						}
					}
				}

				if (m_line.compare(pos, 17, "TRANSFER-ENCODING") == 0)
				{
					while (n > 0 && !isalpha(m_line[i])) {
						n--;
						i++;
					}

					if (n > 0)
					{
						pos = i;
						while (isalpha(m_line[i])) {
							m_line[i] = toupper(m_line[i]);
							n--;
							i++;
						}

						if (m_line.compare(pos, 7, "CHUNKED") == 0)
							m_chunked = true;
					}
				}
			}

			m_line.clear();
		}
		break;
	case 2:
		{
			m_data.push_back(c);
			if (m_content_length != 0 && m_data.size() == m_content_length)
			{
				m_stage = 3;
				return -1;
			}
		}
		break;
	case 3:
		{
			m_data.push_back(c);
			if (c == '\n')
			{
				size_t n = m_line.length();
				if (n < 3 && (m_line[0] == '\r' || m_line[0] == '\n'))
				{
					return -1;
				}

				m_line.clear();
			}
		}
	default:
		break;
	}

	return 0;
}