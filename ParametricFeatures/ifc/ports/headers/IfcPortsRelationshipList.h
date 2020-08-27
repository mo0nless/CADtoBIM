#pragma once

#include "../../main/headers/IfcElementBundle.h"

#include "../../../common/models/headers/SessionManager.h"
#include "../../../common/utils/headers/Comparator.h"

struct PortElement
{
	//Data 
	Ifc4::IfcCartesianPoint* cartesianPointPort;
	Ifc4::IfcDistributionPort* distributionPort;
	Ifc4::IfcDistributionElement* ifcDistributionElement;
	long elementIdNumber ;

	//Next port
	PortElement* nextPortElement;
	//Previous Port
	PortElement* previousPortElement;

	bool isElementConnected;
};

class IfcPortsRelationshipList
{
private:
	PortElement *mHead;

	bool isEqual(std::vector<double> v1, std::vector<double> v2);
	bool isDoubleEqual(double x, double y);
	bool connectPortAtLocation(PortElement*& newPortElement);

public:
	IfcPortsRelationshipList();	
	
	PortElement* getHead();
	void insertIfcPortElement(Ifc4::IfcCartesianPoint* point, Ifc4::IfcDistributionPort* dPort, IfcElementBundle*& ifcElementBundle);
	void display();
};
