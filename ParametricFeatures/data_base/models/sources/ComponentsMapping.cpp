#include "..\headers\ComponentsMapping.h"

string ComponentsMapping::getModelerComponentName()
{
	return _modelerComponentName;
}

void ComponentsMapping::setModelerComponentName(string modelerComponentName)
{
	this->_modelerComponentName = modelerComponentName;
}

string ComponentsMapping::getIfcComponentName()
{
	return this->_ifcComponentName;
}

void ComponentsMapping::setIfcComponentName(string ifcComponentName)
{
	this->_ifcComponentName = ifcComponentName;
}
