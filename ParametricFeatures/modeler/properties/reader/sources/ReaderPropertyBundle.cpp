#include "../headers/ReaderPropertyBundle.h"

ReaderPropertyBundle::ReaderPropertyBundle(std::string newClassName, int newLocalId)
{
	this->className = newClassName;
	this->localId = newLocalId;
}

std::string ReaderPropertyBundle::getCassName()
{
	return this->className;
}

int ReaderPropertyBundle::getLocalId()
{
	return this->localId;
}

std::vector<ReaderPropertyDefinition> ReaderPropertyBundle::getProperties()
{
	return this->properties;
}

void ReaderPropertyBundle::addProperty(ReaderPropertyDefinition readerPropertyDefinition)
{
	this->properties.push_back(readerPropertyDefinition);
}
