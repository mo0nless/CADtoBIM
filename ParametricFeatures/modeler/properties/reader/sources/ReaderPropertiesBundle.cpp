#include "../headers/ReaderPropertiesBundle.h"

ReaderPropertiesBundle::ReaderPropertiesBundle(string newClassName, int newLocalId)
{
	this->className = newClassName;
	this->localId = newLocalId;
}

string ReaderPropertiesBundle::getClassName()
{
	return this->className;
}

int ReaderPropertiesBundle::getLocalId()
{
	return this->localId;
}

void ReaderPropertiesBundle::setLocalId(int newLocalId)
{
	this->localId = newLocalId;
}

string ReaderPropertiesBundle::getName()
{
	return this->_name;
}

void ReaderPropertiesBundle::setName(string name)
{
	this->_name = name;
}

vector<ReaderPropertyDefinition*> ReaderPropertiesBundle::getProperties()
{
	return this->properties;
}

void ReaderPropertiesBundle::addProperty(ReaderPropertyDefinition* readerPropertyDefinition)
{
	this->properties.push_back(readerPropertyDefinition);
}
