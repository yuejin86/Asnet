#ifndef _FACTORY_MGR_H
#define _FACTORY_MGR_H

#include <map>

// 产品基类
class IFactoryHolder
{
public:
	IFactoryHolder(){}
	virtual ~IFactoryHolder(){}

	virtual void Print() const = 0;
};

//工厂基类
template <class T>
class BFactory
{
public:
	BFactory(){};
	virtual ~BFactory(){}

	virtual T* Create() const = 0;
};


//工厂管理类
template <class T>
class IFactoryMgr
{
public:
	IFactoryMgr() {};
	~IFactoryMgr(){};

	typedef std::map<const char*, BFactory<T>*> RegistryMapType;

	void RegFactory(const char* key, BFactory<T>* obj)
	{
		RegistryMapType::const_iterator iter = m_Factorys.find(key);
		if (iter != m_Factorys.end())
		{
			delete iter->second;
			m_Factorys.erase(iter);
		}
		
		m_Factorys[key] = obj;
	}

	void RemoveFactory(const char* key)
	{
		RegistryMapType::const_iterator iter = m_Factorys.find(key);
		if (iter != m_Factorys.end())
		{
			delete iter->second;
			m_Factorys.erase(iter);
		}
	}

	BFactory<T>* GetFactory(const char* key) 
	{ 
		RegistryMapType::const_iterator iter = m_Factorys.find(key);
		if (iter != m_Factorys.end())
		{
			return iter->second;
		}
		
		return NULL;
	}

	virtual void RegistryFactorys() = 0;
private:
	RegistryMapType m_Factorys;
};

#endif