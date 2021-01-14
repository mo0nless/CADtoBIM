#include "..\headers\ComponentsMapping.h"

using namespace DataBase::Models;

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

string ComponentsMapping::getIfcComponentTypeName()
{
	return this->_ifcTypeComponentName;;
}

void ComponentsMapping::setIfcComponentTypeName(string ifcComponentTypeName)
{
	this->_ifcTypeComponentName = ifcComponentTypeName;
}
