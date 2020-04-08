#include "../headers/ReaderPropertiesBundle.h"

ReaderPropertiesBundle::ReaderPropertiesBundle(std::string newClassName, int newLocalId)
{
	this->className = newClassName;
	this->localId = newLocalId;
}

std::string ReaderPropertiesBundle::getCassName()
{
	return this->className;
}

int ReaderPropertiesBundle::getLocalId()
{
	return this->localId;
}

std::vector<ReaderPropertyDefinition> ReaderPropertiesBundle::getProperties()
{
	return this->properties;
}

void ReaderPropertiesBundle::addProperty(ReaderPropertyDefinition readerPropertyDefinition)
{
	this->properties.push_back(readerPropertyDefinition);
}
