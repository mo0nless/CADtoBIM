#pragma once

//#include "../../enhancer/headers/IfcOperationsHelper.h"
#include "../headers/IfcElementBundle.h"

class IfcElementBuilder
{
public:
	IfcElementBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory, Ifc4::IfcObjectPlacement* objectPlacement);

	void processIfcElement(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
private:
	Ifc4::IfcElement* buildIfcElement(IfcElementBundle*& ifcElementBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcDistributionElement* buildIfcDistributionElement(IfcElementBundle*& ifcElementBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file);

	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcGeometricRepresentationContext* geometricRepresentationContext = nullptr;
	Ifc4::IfcOwnerHistory* ownerHistory = nullptr;
	Ifc4::IfcObjectPlacement* objectPlacement = nullptr;
};
