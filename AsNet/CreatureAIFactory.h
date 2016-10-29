#ifndef CREATURE_AI_FACTORY_H
#define CREATURE_AI_FACTORY_H

//π÷ŒÔIA¿‡
template <class T>
class CreatureAIFactory : public BFactory<IFactoryHolder>
{
public:
	CreatureAIFactory() {};
	~CreatureAIFactory() {};
	IFactoryHolder* Create() const;
};

template <class T>
inline IFactoryHolder* CreatureAIFactory<T>::Create() const
{
	return (new T());
}

class CreatureAIMgr : public IFactoryMgr<IFactoryHolder>
{
public:
	static CreatureAIMgr& Instance()
	{
		static CreatureAIMgr creatureAIMgr;
		return creatureAIMgr;
	}

	void RegistryFactorys()
	{
		RegFactory("CA", new CreatureAIFactory<CreatureAI>());
		RegFactory("PA", new CreatureAIFactory<PetAI>());
		RegFactory("SA", new CreatureAIFactory<SmartAI>());
	}
};

#define sCreatureAIMgr CreatureAIMgr::Instance()

#endif