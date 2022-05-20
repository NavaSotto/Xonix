#pragma once
#include "Object.h"

class StaticObject :public Object
{
public:
	StaticObject(sf::Vector2f = { 0,0 });
	virtual void foo() {};
	virtual ~StaticObject();
};