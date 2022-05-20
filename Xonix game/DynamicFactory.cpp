#include "DynamicFactory.h"



DynamicFactory::~DynamicFactory()
{
}

void DynamicFactory::registerit(const std::string & name, std::function< std::unique_ptr<DynamicObject>()>f)
{
	m_map.emplace(name, f);
}

std::unique_ptr<DynamicObject> DynamicFactory::createObject(const std::string& name)
{
	auto it = m_map.find(name);
	if (it == m_map.end())
		return nullptr;
	return it->second();
}



