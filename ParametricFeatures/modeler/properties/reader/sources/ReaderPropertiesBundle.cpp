#include "../headers/ReaderPropertiesBundle.h"

ReaderPropertiesBundle::ReaderPropertiesBundle(string newClassName, int newLocalId)
{
	this->className = newClassName;
	this->localId = newLocalId;
}

string ReaderPropertiesBundle::getCassName()
{
	return this->className;
}

int ReaderPropertiesBundle::getLocalId()
{
	return this->localId;
}

vector<ReaderPropertyDefinition*> ReaderPropertiesBundle::getProperties()
{
	return this->properties;
}

void ReaderPropertiesBundle::addProperty(ReaderPropertyDefinition* readerPropertyDefinition)
{
	this->properties.push_back(readerPropertyDefinition);
}
