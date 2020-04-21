#pragma once


#include <vector>
#include <string>
#include "IfcGraphicPropertiesBundle.h"
#include "IfcReaderPropertiesBundle.h"


class IfcBundle {

private:
	long modelerElementId;
	std::string modelerElementName;

	//std::vector<IfcReaderPropertiesBundle*> ifcReaderPropertiesBundleVector;
	std::vector<IfcGraphicPropertiesBundle*> ifcGraphicPropertiesBundleVector;

	Ifc4::IfcElement* ifcElement;

public:
	IfcBundle(long newModelerElementId,std::string newModelerElementName);

	//void addIfcReaderPropertiesBundle(IfcReaderPropertiesBundle* newIfcReaderPropertiesBundle);
	void addIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle* newIfcGraphicPropertiesBundle);

	//std::vector<IfcReaderPropertiesBundle*> getIfcReaderPropertiesBundleVector();
	std::vector<IfcGraphicPropertiesBundle*> getIfcGraphicPropertiesBundleVector();

	Ifc4::IfcElement* getIfcElement();
	void setIfcElement(Ifc4::IfcElement* newIfcElement);

	long getModelerElementId();
	std::string getModelerElementName();

};