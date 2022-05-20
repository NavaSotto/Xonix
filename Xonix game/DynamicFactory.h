#pragma once
#include <map>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include <cmath>
#include <functional>
#include "Object.h"
#include "DynamicObject.h"
#include <iostream>


class DynamicFactory
{
public:

	~DynamicFactory();
	DynamicFactory() {};
	std::unique_ptr<DynamicObject> createObject(const std::string& name);
	void registerit(const std::string& name, std::function< std::unique_ptr<DynamicObject>()>f);
protected:
	std::map<std::string, std::function< std::unique_ptr<DynamicObject>()>> m_map;
};
