#include "../headers/IfcBundle.h"

IfcBundle::IfcBundle(long newModelerElementId, std::string newModelerElementName)
{
	this->modelerElementId = newModelerElementId;
	this->modelerElementName = newModelerElementName;
}

void IfcBundle::addIfcReaderPropertiesBundle(IfcReaderPropertiesBundle * newIfcReaderPropertiesBundle)
{
	this->ifcReaderPropertiesBundleVector.push_back(newIfcReaderPropertiesBundle);
}

void IfcBundle::addIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle * newIfcGraphicPropertiesBundle)
{
	this->ifcGraphicPropertiesBundleVector.push_back(newIfcGraphicPropertiesBundle);
}

Ifc4::IfcElement * IfcBundle::getIfcElement()
{
	return this->ifcElement;
}

void IfcBundle::setIfcElement(Ifc4::IfcElement * newIfcElement)
{
	this->ifcElement = newIfcElement;
}

long IfcBundle::getModelerElementId()
{
	return this->modelerElementId;
}

std::string IfcBundle::getModelerElementName()
{
	return this->modelerElementName;
}

std::vector<IfcReaderPropertiesBundle*> IfcBundle::getIfcReaderPropertiesBundleVector()
{
	return this->ifcReaderPropertiesBundleVector;
}

std::vector<IfcGraphicPropertiesBundle*> IfcBundle::getIfcGraphicPropertiesBundleVector()
{
	return this->ifcGraphicPropertiesBundleVector;
}