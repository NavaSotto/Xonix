#include "StaticFactory.h"



StaticFactory::~StaticFactory()
{
}

void StaticFactory::registerit(const std::string & name, std::function< std::unique_ptr<StaticObject>()>f)
{
	m_map.emplace(name, f);
}

std::unique_ptr<StaticObject> StaticFactory::createObject(const std::string& name)
{
	auto it = m_map.find(name);
	if (it == m_map.end())
		return nullptr;
	return it->second();
}



