#pragma once
#include <map>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include <cmath>
#include <functional>
#include "Object.h"
#include "StaticObject.h"
#include <iostream>

//enum  GameObjectIndex
//{
//	Player2,
//	Enemy1,
//	MAX1
//};
class StaticFactory
{
public:

	~StaticFactory();
	StaticFactory() {};
	std::unique_ptr<StaticObject> createObject(const std::string& name);
	void registerit(const std::string& name, std::function< std::unique_ptr<StaticObject>()>f);
protected:
	std::map<std::string, std::function< std::unique_ptr<StaticObject>()>> m_map;
};
