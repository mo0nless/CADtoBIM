#include "../headers/IfcReaderPropertiesBundle.h"

using namespace Ifc::Bundle;

IfcReaderPropertiesBundle::IfcReaderPropertiesBundle(string newClassName, int newLocalId)
{
	this->className = newClassName;
	this->localId = newLocalId;
}

string IfcReaderPropertiesBundle::getClassName()
{
	return this->className;
}

int IfcReaderPropertiesBundle::getLocalId()
{
	return this->localId;
}

void IfcReaderPropertiesBundle::setLocalId(int newLocalId)
{
	this->localId = newLocalId;
}

string IfcReaderPropertiesBundle::getName()
{
	return this->_name;
}

void IfcReaderPropertiesBundle::setName(string name)
{
	this->_name = name;
}

vector<ReaderPropertyDefinition*> IfcReaderPropertiesBundle::getProperties()
{
	return this->properties;
}

void IfcReaderPropertiesBundle::addProperty(ReaderPropertyDefinition* readerPropertyDefinition)
{
	this->properties.push_back(readerPropertyDefinition);
}

void IfcReaderPropertiesBundle::setIfcPropertySet(Ifc4::IfcPropertySet * ifcPropertySetValue)
{
	this->ifcPropertySet = ifcPropertySetValue;
}

Ifc4::IfcPropertySet * IfcReaderPropertiesBundle::getIfcPropertySet()
{
	return this->ifcPropertySet;
}