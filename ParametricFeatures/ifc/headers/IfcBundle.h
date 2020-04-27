#pragma once


#include <vector>
#include <string>
#include "IfcGraphicPropertiesBundle.h"
#include "IfcReaderPropertiesBundle.h"
#include "../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"


class IfcBundle {

private:
	long modelerElementId;
	std::string modelerElementName;

	std::vector<IfcReaderPropertiesBundle*> ifcReaderPropertiesBundleVector;
	std::vector<IfcGraphicPropertiesBundle*> ifcGraphicPropertiesBundleVector;

	std::vector<Ifc4::IfcPoint*> ifcPointsPortsVector;
	std::vector<Ifc4::IfcDistributionPort*> ifcDistributionPortVector;

	Ifc4::IfcElement* ifcElement;

	bool hasConnections;
	
	SmartFeatureContainer* smartFeatureContainer;

public:
	IfcBundle(long newModelerElementId,std::string newModelerElementName);

	void addIfcDistributionPorts(Ifc4::IfcDistributionPort* newDistPort);
	void addIfcPortsPoints(Ifc4::IfcPoint* newIfcPoint);
	void addIfcReaderPropertiesBundle(IfcReaderPropertiesBundle* newIfcReaderPropertiesBundle);
	void addIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle* newIfcGraphicPropertiesBundle);

	std::vector<IfcReaderPropertiesBundle*> getIfcReaderPropertiesBundleVector();

	std::vector<IfcGraphicPropertiesBundle*> getIfcGraphicPropertiesBundleVector();

	std::vector<Ifc4::IfcPoint*> getIfcPortsPointsVector();
	std::vector<Ifc4::IfcDistributionPort*> getIfcDistributionPortsVector();

	Ifc4::IfcElement* getIfcElement();
	void setIfcElement(Ifc4::IfcElement* newIfcElement);

	bool getHasElementConnection();
	long getModelerElementId();
	std::string getModelerElementName();

	bool getIsSmartFeature();
	void setSmartFeatureContainer(SmartFeatureContainer* newSmartFeatureContainer);
	SmartFeatureContainer* getSmartFeatureContainer();
};