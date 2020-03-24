#include "../headers/DictionaryProperties.h"

DictionaryProperties::DictionaryProperties()
{
	this->pGeneralProperties = new GeneralProperties();
	this->pReaderProperties = new ReaderProperties();
	this->pGraphicProperties = new GraphicProperties();
	this->areReaderPropertiesFound = true;
}

GeneralProperties * DictionaryProperties::getGeneralProperties()
{
	return this->pGeneralProperties;
}

ReaderProperties * DictionaryProperties::getReaderProperties()
{
	return this->pReaderProperties;
}

GraphicProperties * DictionaryProperties::getGraphicProperties()
{
	return this->pGraphicProperties;
}

bool DictionaryProperties::getAreReaderPropertiesFound()
{
	return this->areReaderPropertiesFound;
}

void DictionaryProperties::setAreReaderPropertiesFound(bool newAreReaderPropertiesFound)
{
	this->areReaderPropertiesFound = newAreReaderPropertiesFound;
}
