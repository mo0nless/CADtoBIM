#include "../headers/DictionaryProperties.h"



DictionaryProperties::DictionaryProperties(long newElementId, std::string newElementName)
{
	this->elementId = newElementId;
	this->elementName = newElementName;

	this->pReaderProperties = new ReaderProperties();
	this->pGraphicProperties = new GraphicProperties();
	this->smartFeatureContainer = new SmartFeatureContainer(newElementId);
}

ReaderProperties * DictionaryProperties::getReaderProperties()
{
	return this->pReaderProperties;
}

GraphicProperties * DictionaryProperties::getGraphicProperties()
{
	return this->pGraphicProperties;
}

SmartFeatureContainer * DictionaryProperties::getSmartFeatureContainer()
{
	return this->smartFeatureContainer;
}

std::string DictionaryProperties::getElementName()
{
	return this->elementName;
}
