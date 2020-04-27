#include "../headers/DictionaryProperties.h"



DictionaryProperties::DictionaryProperties(long newElementId, std::string newElementName)
{
	this->elementId = newElementId;
	this->elementName = newElementName;

	this->smartFeatureContainer = new SmartFeatureContainer(newElementId);
}

std::vector<ReaderPropertiesBundle*> DictionaryProperties::getReaderPropertiesBundleVector()
{
	return this->readerPropertiesBundleVector;
}

void DictionaryProperties::addReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle)
{
	this->readerPropertiesBundleVector.push_back(readerPropertiesBundle);
}

std::vector<GraphicProperties*> DictionaryProperties::getGraphicPropertiesVector()
{
	return this->graphicPropertiesVector;
}

void DictionaryProperties::addGraphicProperties(GraphicProperties * graphicProperties)
{
	this->graphicPropertiesVector.push_back(graphicProperties);
}

void DictionaryProperties::setSmartFeatureContainer(SmartFeatureContainer * newSmartFeatureContainer)
{
	this->smartFeatureContainer = newSmartFeatureContainer;
}

SmartFeatureContainer * DictionaryProperties::getSmartFeatureContainer()
{
	return this->smartFeatureContainer;
}

std::string DictionaryProperties::getElementName()
{
	return this->elementName;
}

long DictionaryProperties::getElementId()
{
	return this->elementId;
}
