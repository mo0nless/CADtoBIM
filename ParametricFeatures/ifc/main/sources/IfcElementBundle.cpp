#include "../headers/IfcElementBundle.h"

using namespace Ifc::Main;

IfcElementBundle::IfcElementBundle(long newModelerElementId, string newModelerElementDescriptor)
{
	this->modelerElementId = newModelerElementId;
	this->modelerElementDescriptor = newModelerElementDescriptor;
	this->hasConnections = false;
	this->smartFeatureContainer = new SmartFeatureContainer(newModelerElementId);
	this->ifcGraphicPropertiesBundleVector = vector<IfcGraphicPropertiesBundle*>();
	this->elementReaderPropertiesBundleVector = vector<ReaderPropertiesBundle*>();
}

string IfcElementBundle::getRepresentationType()
{
	return this->representationType;
}

void IfcElementBundle::setRepresentationType(string type)
{
	this->representationType = type;
}

void IfcElementBundle::setBadIfcClassBuild(bool value)
{
	badIfcElemetBuild = value;
}

bool IfcElementBundle::getBadIfcClassBuild()
{
	return badIfcElemetBuild;
}

void IfcElementBundle::addIfcDistributionPorts(Ifc4::IfcDistributionPort * newDistPort)
{
	this->ifcDistributionPortVector.push_back(newDistPort);
}

void IfcElementBundle::addIfcPortsPoints(Ifc4::IfcCartesianPoint * newIfcPoint)
{
	this->hasConnections = true;
	this->ifcPointsPortsVector.push_back(newIfcPoint);
}

void IfcElementBundle::addIfcElementReaderPropertiesBundle(IfcReaderPropertiesBundle * newIfcReaderPropertiesBundle)
{
	this->ifcElementReaderPropertiesBundleVector.push_back(newIfcReaderPropertiesBundle);
}

void IfcElementBundle::addIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle * newIfcGraphicPropertiesBundle)
{
	this->ifcGraphicPropertiesBundleVector.push_back(newIfcGraphicPropertiesBundle);
}

void IfcElementBundle::addSolidEdgesCollection(vector<SolidEdge*> solidEdges)
{
	this->smartSolidEdgesCollection = solidEdges;
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

long IfcElementBundle::getElementId()
{
	return this->modelerElementId;
}

string IfcElementBundle::getElementDescriptor()
{
	return this->modelerElementDescriptor;
}

bool IfcElementBundle::getIsSmartFeature()
{
	return this->smartFeatureContainer->getRoot()!=nullptr;
}

void IfcElementBundle::setSmartFeatureContainer(SmartFeatureContainer*& newSmartFeatureContainer)
{
	this->smartFeatureContainer = newSmartFeatureContainer;
}

SmartFeatureContainer * IfcElementBundle::getSmartFeatureContainer()
{
	return this->smartFeatureContainer;
}

vector<ReaderPropertiesBundle*> IfcElementBundle::getElementReaderPropertiesBundleVector()
{
	return this->elementReaderPropertiesBundleVector;
}

void IfcElementBundle::setElementReaderPropertiesBundleVector(vector<ReaderPropertiesBundle*> newReaderPropertiesBundleVector)
{
	this->elementReaderPropertiesBundleVector = newReaderPropertiesBundleVector;
}

vector<IfcReaderPropertiesBundle*> IfcElementBundle::getIfcElementReaderPropertiesBundleVector()
{
	return this->ifcElementReaderPropertiesBundleVector;
}

vector<IfcGraphicPropertiesBundle*> IfcElementBundle::getIfcGraphicPropertiesBundleVector()
{
	return this->ifcGraphicPropertiesBundleVector;
}

vector<Ifc4::IfcCartesianPoint*> IfcElementBundle::getIfcPortsPointsVector()
{
	return this->ifcPointsPortsVector;
}

vector<Ifc4::IfcDistributionPort*> IfcElementBundle::getIfcDistributionPortsVector()
{
	return this->ifcDistributionPortVector;
}

vector<SolidEdge*> IfcElementBundle::getSolidEdgesCollection()
{
	return this->smartSolidEdgesCollection;
}

string IfcElementBundle::getElementClassName()
{
	return this->mElemClassName;
}

void IfcElementBundle::setElementClassName(string name)
{
	this->mElemClassName = name;
}
