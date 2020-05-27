#pragma once

//#include "../../enhancer/headers/IfcOperationsEnhancer.h"
#include "../headers/IfcElementBundle.h"

class IfcElementBuilder
{
public:
	IfcElementBuilder();

	void processIfcElement(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
private:
	Ifc4::IfcElement* buildIfcElement(IfcElementBundle*& ifcElementBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcDistributionElement* buildIfcDistributionElement(IfcElementBundle*& ifcElementBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file);

	typedef Ifc4::IfcGloballyUniqueId guid;
};
