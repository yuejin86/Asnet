#ifndef CREATURE_AI_H
#define CREATURE_AI_H

#include "Factory.h"
#include <iostream>

// CreatureAI
class CreatureAI : public IFactoryHolder
{
public:
	void Print() const { std::cout << "CreatureAI\n";}

};

// PetAI
class PetAI : public CreatureAI
{
public:
	void Print() const { std::cout << "PetAI\n"; }
};

//SmartAI
class SmartAI : public CreatureAI
{
public:
	void Print() const { std::cout << "SmartAI\n";}
};

#endif