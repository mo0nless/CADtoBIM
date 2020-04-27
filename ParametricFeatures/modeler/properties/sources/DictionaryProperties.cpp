#include "../headers/DictionaryProperties.h"



DictionaryProperties::DictionaryProperties(long newElementId, std::string newEmentDescriptor)
{
	this->elementId = newElementId;
	this->elementDescriptor = newEmentDescriptor;

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

SmartFeatureContainer * DictionaryProperties::getSmartFeatureContainer()
{
	return this->smartFeatureContainer;
}

std::string DictionaryProperties::getElementDescriptor()
{
	return this->elementDescriptor;
}

long DictionaryProperties::getElementId()
{
	return this->elementId;
}
