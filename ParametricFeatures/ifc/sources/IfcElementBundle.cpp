#include "../headers/IfcElementBundle.h"

IfcElementBundle::IfcElementBundle(long newModelerElementId, std::string newModelerElementName)
{
	this->modelerElementId = newModelerElementId;
	this->modelerElementName = newModelerElementName;
	this->hasConnections = false;
}

void IfcElementBundle::addIfcDistributionPorts(Ifc4::IfcDistributionPort * newDistPort)
{
	this->ifcDistributionPortVector.push_back(newDistPort);
}

void IfcElementBundle::addIfcPortsPoints(Ifc4::IfcPoint * newIfcPoint)
{
	this->hasConnections = true;
	this->ifcPointsPortsVector.push_back(newIfcPoint);
}

//void IfcElementBundle::addIfcReaderPropertiesBundle(IfcReaderPropertiesBundle * newIfcReaderPropertiesBundle)
//{
//	this->ifcReaderPropertiesBundleVector.push_back(newIfcReaderPropertiesBundle);
//}

void IfcElementBundle::addIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle * newIfcGraphicPropertiesBundle)
{
	this->ifcGraphicPropertiesBundleVector.push_back(newIfcGraphicPropertiesBundle);
}

Ifc4::IfcElement * IfcElementBundle::getIfcElement()
{
	return this->ifcElement;
}

void IfcElementBundle::setIfcElement(Ifc4::IfcElement * newIfcElement)
{
	this->ifcElement = newIfcElement;
}

bool IfcElementBundle::getHasElementConnection()
{
	return this->hasConnections;
}

long IfcElementBundle::getModelerElementId()
{
	return this->modelerElementId;
}

std::string IfcElementBundle::getModelerElementName()
{
	return this->modelerElementName;
}

//std::vector<IfcReaderPropertiesBundle*> IfcElementBundle::getIfcReaderPropertiesBundleVector()
//{
//	return this->ifcReaderPropertiesBundleVector;
//}

std::vector<IfcGraphicPropertiesBundle*> IfcElementBundle::getIfcGraphicPropertiesBundleVector()
{
	return this->ifcGraphicPropertiesBundleVector;
}

std::vector<Ifc4::IfcPoint*> IfcElementBundle::getIfcPortsPointsVector()
{
	return this->ifcPointsPortsVector;
}

std::vector<Ifc4::IfcDistributionPort*> IfcElementBundle::getIfcDistributionPortsVector()
{
	return this->ifcDistributionPortVector;
}
