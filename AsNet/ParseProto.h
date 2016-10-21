#ifndef _PARSE_PROTO_H
#define _PARSE_PROTO_H

#include <memory>

char* GetStaticBigMemory();
char* GetAnotherStaticBigMemory();
template <class T>
class Deleter  
{  
public:  
	void operator()(T* pointer)  
	{  
		ResetMemory(false);
		pointer->~T();
	}  
}; 

bool CheckMemory();
void ResetMemory(bool flag);
template <class T>
std::shared_ptr<T> ParseProtoMsg(const char* pData, int n32DataLength)
{
	if (CheckMemory())
	{
		std::shared_ptr<T> msg(new T);
		bool res = msg->ParseFromArray(pData, n32DataLength);
		if (!res)
		{
			return NULL;
		}
		return msg;
	}
	else
	{
		std::shared_ptr<T> msg(new(GetStaticBigMemory()) T, Deleter<T>());
		bool res = msg->ParseFromArray(pData, n32DataLength);
		if (!res)
		{
			return NULL;
		}

		ResetMemory(true);
		return msg;
	}
}

template <class T>
bool ParseProtoMsg(const char* pData, int n32DataLength, T& sMsg)
{
	return sMsg.ParseFromArray(pData, n32DataLength);
}

bool CheckThreadMemory();
void ResetThreadMemory(bool flag);
char* GetStaticBigMemoryInThread();
template <class T>
std::shared_ptr<T> ParseProtoMsgInThread(const char* pData, int n32DataLength)
{
	if (CheckThreadMemory())
	{
		std::shared_ptr<T> msg(new T);
		bool res = msg->ParseFromArray(pData, n32DataLength);
		if (!res)
		{
			return NULL;
		}
		return msg;
	}
	else
	{
		std::shared_ptr<T> msg(new(GetStaticBigMemoryInThread()) T, Deleter<T>());
		bool res = msg->ParseFromArray(pData, n32DataLength);
		if (!res)
		{
			return NULL;
		}

		ResetThreadMemory(true);
		return msg;
	}
}

template <class T>
std::shared_ptr<T> ParseProtoMsgWithNewMemory(const char* pData, int n32DataLength)
{
	std::shared_ptr<T> msg(new T);
	bool res = msg->ParseFromArray(pData, n32DataLength);
	if (!res)
	{
		return NULL;
	}
	return msg;
}


#endif
