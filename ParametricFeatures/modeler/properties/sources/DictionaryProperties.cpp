#include "../headers/DictionaryProperties.h"

DictionaryProperties::DictionaryProperties()
{
	this->generalProperties = new GeneralProperties();
	this->readerProperties = new ReaderProperties();
	this->graphicProperties = new GraphicProperties();
}

GeneralProperties * DictionaryProperties::getGeneralProperties()
{
	return this->generalProperties;
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

bool DictionaryProperties::getAreReaderPropertiesFound()
{
	return this->areReaderPropertiesFound;
}

void DictionaryProperties::setAreReaderPropertiesFound(bool newAreReaderPropertiesFound)
{
	this->areReaderPropertiesFound = newAreReaderPropertiesFound;
}
