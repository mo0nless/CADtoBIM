#include "../headers/DictionaryProperties.h"



DictionaryProperties::DictionaryProperties(long newElementId, std::string newEmentDescriptor)
{
	this->elementId = newElementId;
	this->elementDescriptor = newEmentDescriptor;
	this->isSmartSolid = false;
	this->smartFeatureContainer = new SmartFeatureContainer(newElementId);
	this->isPrimitiveSolid = false;
	this->isSmartSolid = false;
}

//std::vector<ReaderPropertiesBundle*> DictionaryProperties::getGraphicsReaderPropertiesBundleVector()
//{
//	return this->graphicsReaderPropertiesBundleVector;
//}
//
//void DictionaryProperties::addGraphicsReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle)
//{
//	this->graphicsReaderPropertiesBundleVector.push_back(readerPropertiesBundle);
//}

std::vector<ElementBundle*> DictionaryProperties::getElementBundle()
{
	return this->subElements;
}

void DictionaryProperties::addElementBundle(ElementBundle * elementBundle)
{
	this->subElements.push_back(elementBundle);
}

std::vector<ReaderPropertiesBundle*> DictionaryProperties::getElementReaderPropertiesBundleVector()
{
	return this->elementReaderPropertiesBundleVector;
}

void DictionaryProperties::addElementReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle)
{
	this->elementReaderPropertiesBundleVector.push_back(readerPropertiesBundle);
}

//std::vector<GraphicProperties*> DictionaryProperties::getGraphicPropertiesVector()
//{
//	return this->graphicPropertiesVector;
//}
//
//void DictionaryProperties::addGraphicProperties(GraphicProperties * graphicProperties)
//{
//	this->graphicPropertiesVector.push_back(graphicProperties);
//}

void DictionaryProperties::setSmartFeatureContainer(SmartFeatureContainer * newSmartFeatureContainer)
{
	this->smartFeatureContainer = newSmartFeatureContainer;
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

void DictionaryProperties::setIsSmartSolid(bool value)
{
	this->isSmartSolid = value;
}

bool DictionaryProperties::getIsSmartSolid()
{
	return this->isSmartSolid;
}

void DictionaryProperties::setIsPrimitiveSolid(bool value)
{
	this->isPrimitiveSolid = value;
}

bool DictionaryProperties::getIsPrimitiveSolid()
{
	return this->isPrimitiveSolid;
}
