#include "..\headers\ComponentsMappingDTO.h"

string ComponentsMappingDTO::getModelerComponentName()
{
	return _modelerComponentName;
}

void ComponentsMappingDTO::setModelerComponentName(string modelerComponentName)
{
	this->_modelerComponentName = modelerComponentName;
}

string ComponentsMappingDTO::getIfcComponentName()
{
	return this->_ifcComponentName;
}

void ComponentsMappingDTO::setIfcComponentName(string ifcComponentName)
{
	this->_ifcComponentName = ifcComponentName;
}
