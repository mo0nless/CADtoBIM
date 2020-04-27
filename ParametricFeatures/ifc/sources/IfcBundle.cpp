#include "../headers/IfcBundle.h"
#include "..\headers\IfcBundle.h"

IfcBundle::IfcBundle(long newModelerElementId, std::string newModelerElementName)
{
	this->modelerElementId = newModelerElementId;
	this->modelerElementName = newModelerElementName;
	this->hasConnections = false;
}

void IfcBundle::addIfcDistributionPorts(Ifc4::IfcDistributionPort * newDistPort)
{
	this->ifcDistributionPortVector.push_back(newDistPort);
}

void IfcBundle::addIfcPortsPoints(Ifc4::IfcPoint * newIfcPoint)
{
	this->hasConnections = true;
	this->ifcPointsPortsVector.push_back(newIfcPoint);
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

bool IfcBundle::getHasElementConnection()
{
	return this->hasConnections;
}

long IfcBundle::getModelerElementId()
{
	return this->modelerElementId;
}

std::string IfcBundle::getModelerElementName()
{
	return this->modelerElementName;
}

bool IfcBundle::getIsSmartFeature()
{
	return this->smartFeatureContainer->getRoot()!=nullptr;
}

void IfcBundle::setSmartFeatureContainer(SmartFeatureContainer * newSmartFeatureContainer)
{
	this->smartFeatureContainer = newSmartFeatureContainer;
}

SmartFeatureContainer * IfcBundle::getSmartFeatureContainer()
{
	return this->smartFeatureContainer;
}


std::vector<IfcReaderPropertiesBundle*> IfcBundle::getIfcReaderPropertiesBundleVector()
{
	return this->ifcReaderPropertiesBundleVector;
}

std::vector<IfcGraphicPropertiesBundle*> IfcBundle::getIfcGraphicPropertiesBundleVector()
{
	return this->ifcGraphicPropertiesBundleVector;
}

std::vector<Ifc4::IfcPoint*> IfcBundle::getIfcPortsPointsVector()
{
	return this->ifcPointsPortsVector;
}

std::vector<Ifc4::IfcDistributionPort*> IfcBundle::getIfcDistributionPortsVector()
{
	return this->ifcDistributionPortVector;
}
