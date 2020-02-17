#include "../headers/DictionaryProperties.h"

DictionaryProperties::DictionaryProperties()
{
	this->readerProperties = new ReaderProperties();
	this->graphicProperties = new GraphicProperties();
}

ReaderProperties * DictionaryProperties::getReaderProperties()
{
	return this->readerProperties;
}

GraphicProperties * DictionaryProperties::getGraphicProperties()
{
	return this->graphicProperties;
}

bool DictionaryProperties::getIsSmartFeature()
{
	return this->isSmartFeature;
}

void DictionaryProperties::setIsSmartFeature(bool newIsSmartFeature)
{
	this->isSmartFeature = newIsSmartFeature;
}

std::string DictionaryProperties::getClassName()
{
	return this->className;
}

void DictionaryProperties::setClassName(std::string newClassName)
{
	this->className = newClassName;
}

bool DictionaryProperties::getAreReaderPropertiesFound()
{
	return this->areReaderPropertiesFound;
}

void DictionaryProperties::setAreReaderPropertiesFound(bool newAreReaderPropertiesFound)
{
	this->areReaderPropertiesFound = newAreReaderPropertiesFound;
}
