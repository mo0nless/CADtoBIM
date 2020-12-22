#include "../headers/DictionaryProperties.h"



DictionaryProperties::DictionaryProperties(long newElementId, string newEmentDescriptor)
{
	this->elementId = newElementId;
	this->elementDescriptor = newEmentDescriptor;
	this->isSmartSolid = false;
	this->smartFeatureContainer = new SmartFeatureContainer(newElementId);
	this->isPrimitiveSolid = false;
	this->subElements = vector<IfcGraphicPropertiesBundle*>();
	this->elementReaderPropertiesBundleVector = vector<ReaderPropertiesBundle*>();
}

//vector<ReaderPropertiesBundle*> DictionaryProperties::getGraphicsReaderPropertiesBundleVector()
//{
//	return this->graphicsReaderPropertiesBundleVector;
//}
//
//void DictionaryProperties::addGraphicsReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle)
//{
//	this->graphicsReaderPropertiesBundleVector.push_back(readerPropertiesBundle);
//}

vector<IfcGraphicPropertiesBundle*> DictionaryProperties::getIfcGraphicPropertiesBundleVector()
{
	return this->subElements;
}

void DictionaryProperties::addGraphicGeomBundle(IfcGraphicPropertiesBundle * elementBundle)
{
	
	this->subElements.push_back(elementBundle);
}

vector<ReaderPropertiesBundle*> DictionaryProperties::getElementReaderPropertiesBundleVector()
{
	return this->elementReaderPropertiesBundleVector;
}

void DictionaryProperties::setElementReaderPropertiesBundleVector(vector<ReaderPropertiesBundle*> newReaderPropertiesBundleVector)
{
	this->elementReaderPropertiesBundleVector = newReaderPropertiesBundleVector;
}

void DictionaryProperties::addElementReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle)
{
	
	this->elementReaderPropertiesBundleVector.push_back(readerPropertiesBundle);
}

string DictionaryProperties::getElementClassName()
{
	return this->mElemClassName;
}

void DictionaryProperties::setElementClassName(string name)
{
	this->mElemClassName = name;
}

void DictionaryProperties::setSmartFeatureContainer(SmartFeatureContainer * newSmartFeatureContainer)
{
	
	this->smartFeatureContainer = newSmartFeatureContainer;
}

SmartFeatureContainer * DictionaryProperties::getSmartFeatureContainer()
{
	return this->smartFeatureContainer;
}

string DictionaryProperties::getElementDescriptor()
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

string DictionaryProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(DictionaryProperties).name();
	stringStream << ", elementId = " << elementId;
	stringStream << ", elementDescriptor = " << elementDescriptor;
	stringStream << ", isSmartSolid = " << isSmartSolid;
	stringStream << ", isPrimitiveSolid = " << isPrimitiveSolid;
	stringStream << endl;

	return stringStream.str();
}
