#pragma once

#include "../../enhancer/headers/IfcOperationsEnhancer.h"
#include "../headers/IfcElementBundle.h"

#include <vector>


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
