#include "..\headers\ComponentsMappingDTO.h"

ComponentsMappingDTO::ComponentsMappingDTO()
{
	this->_modelerComponentName = "";
	this->_ifcComponentName = "";
	this->_ifcTypeComponentName = "";
}

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

string ComponentsMappingDTO::getIfcComponentTypeName()
{
	return this->_ifcTypeComponentName;
}

void ComponentsMappingDTO::setIfcComponentTypeName(string ifcComponentTypeName)
{
	this->_ifcTypeComponentName = ifcComponentTypeName;
}
