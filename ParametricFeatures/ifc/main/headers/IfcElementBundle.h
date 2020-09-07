#pragma once


#include <vector>
#include <string>
#include "IfcGraphicPropertiesBundle.h"
#include "IfcReaderPropertiesBundle.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../../ifc/operations_helper/headers/IfcOperationsHelper.h"


class IfcElementBundle {

private:
	long modelerElementId;
	string modelerElementDescriptor;

	vector<IfcReaderPropertiesBundle*> ifcElementReaderPropertiesBundleVector;
	vector<IfcGraphicPropertiesBundle*> ifcGraphicPropertiesBundleVector;

	vector<Ifc4::IfcCartesianPoint*> ifcPointsPortsVector;
	vector<Ifc4::IfcDistributionPort*> ifcDistributionPortVector;

	vector<SolidEdge*> smartSolidEdgesCollection;

	Ifc4::IfcElement* ifcElement;

	bool hasConnections;
	bool isSmartSolid;

	SmartFeatureContainer* smartFeatureContainer;
	string representationType;

public:
	IfcElementBundle(long newModelerElementId,string newModelerElementName);

	string getRepresentationType();
	void setRepresentationType(string type);

	void addIfcDistributionPorts(Ifc4::IfcDistributionPort* newDistPort);
	void addIfcPortsPoints(Ifc4::IfcCartesianPoint* newIfcPoint);
	void addIfcElementReaderPropertiesBundle(IfcReaderPropertiesBundle* newIfcReaderPropertiesBundle);
	void addIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle* newIfcGraphicPropertiesBundle);

	void addSolidEdgesCollection(vector<SolidEdge*> solidEdges);

	vector<IfcReaderPropertiesBundle*> getIfcElementReaderPropertiesBundleVector();

	vector<IfcGraphicPropertiesBundle*> getIfcGraphicPropertiesBundleVector();

	vector<Ifc4::IfcCartesianPoint*> getIfcPortsPointsVector();
	vector<Ifc4::IfcDistributionPort*> getIfcDistributionPortsVector();

	vector<SolidEdge*> getSolidEdgesCollection();

	Ifc4::IfcElement* getIfcElement();
	void setIfcElement(Ifc4::IfcElement* newIfcElement);

	bool getHasElementConnection();
	long getModelerElementId();
	string getModelerElementDescriptor();

	bool getIsSmartFeature();
	void setSmartFeatureContainer(SmartFeatureContainer* newSmartFeatureContainer);
	SmartFeatureContainer* getSmartFeatureContainer();

	void setIsSmartSolid(bool value);
	bool getIsSmartSolid();

	bool solidModel = false;
};