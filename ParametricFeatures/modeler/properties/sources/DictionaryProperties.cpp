#include "../headers/DictionaryProperties.h"

DictionaryProperties::DictionaryProperties()
{
	this->mGeneralProperties = new GeneralProperties();
	this->mReaderProperties = new ReaderProperties();
	this->mGraphicProperties = new GraphicProperties();
	this->areReaderPropertiesFound = true;
}

GeneralProperties * DictionaryProperties::getGeneralProperties()
{
	return this->mGeneralProperties;
}

ReaderProperties * DictionaryProperties::getReaderProperties()
{
	return this->mReaderProperties;
}

GraphicProperties * DictionaryProperties::getGraphicProperties()
{
	return this->mGraphicProperties;
}

bool DictionaryProperties::getAreReaderPropertiesFound()
{
	return this->areReaderPropertiesFound;
}

void DictionaryProperties::setAreReaderPropertiesFound(bool newAreReaderPropertiesFound)
{
	this->areReaderPropertiesFound = newAreReaderPropertiesFound;
}
