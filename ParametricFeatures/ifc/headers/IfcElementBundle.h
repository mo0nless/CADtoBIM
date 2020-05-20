#pragma once


#include <vector>
#include <string>
#include "IfcGraphicPropertiesBundle.h"
#include "IfcReaderPropertiesBundle.h"
#include "../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../enhancer/headers/IfcOperationsEnhancer.h"


class IfcElementBundle {

private:
	long modelerElementId;
	std::string modelerElementDescriptor;

	std::vector<IfcReaderPropertiesBundle*> ifcReaderPropertiesBundleVector;
	std::vector<IfcGraphicPropertiesBundle*> ifcGraphicPropertiesBundleVector;

	std::vector<Ifc4::IfcCartesianPoint*> ifcPointsPortsVector;
	std::vector<Ifc4::IfcDistributionPort*> ifcDistributionPortVector;

	std::vector<SolidEdge*> smartSolidEdgesCollection;

	Ifc4::IfcElement* ifcElement;

	bool hasConnections;
	bool isSmartSolid;

	SmartFeatureContainer* smartFeatureContainer;
	std::string representationType;

public:
	IfcElementBundle(long newModelerElementId,std::string newModelerElementName);

	std::string getRepresentationType();
	void setRepresentationType(std::string type);

	void addIfcDistributionPorts(Ifc4::IfcDistributionPort* newDistPort);
	void addIfcPortsPoints(Ifc4::IfcCartesianPoint* newIfcPoint);
	void addIfcReaderPropertiesBundle(IfcReaderPropertiesBundle* newIfcReaderPropertiesBundle);
	void addIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle* newIfcGraphicPropertiesBundle);

	void addSolidEdgesCollection(std::vector<SolidEdge*> solidEdges);

	std::vector<IfcReaderPropertiesBundle*> getIfcReaderPropertiesBundleVector();

	std::vector<IfcGraphicPropertiesBundle*> getIfcGraphicPropertiesBundleVector();

	std::vector<Ifc4::IfcCartesianPoint*> getIfcPortsPointsVector();
	std::vector<Ifc4::IfcDistributionPort*> getIfcDistributionPortsVector();

	std::vector<SolidEdge*> getSolidEdgesCollection();

	Ifc4::IfcElement* getIfcElement();
	void setIfcElement(Ifc4::IfcElement* newIfcElement);

	bool getHasElementConnection();
	long getModelerElementId();
	std::string getModelerElementDescriptor();

	bool getIsSmartFeature();
	void setSmartFeatureContainer(SmartFeatureContainer* newSmartFeatureContainer);
	SmartFeatureContainer* getSmartFeatureContainer();

	void setIsSmartSolid(bool value);
	bool getIsSmartSolid();
};