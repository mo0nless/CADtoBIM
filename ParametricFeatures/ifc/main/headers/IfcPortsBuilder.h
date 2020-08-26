#pragma once

//#include "../../enhancer/headers/IfcOperationsHelper.h"
//#include "../headers/IfcElementBundle.h"
#include "IfcPortsRelationshipList.h"

class IfcPortsBuilder
{
public:
	IfcPortsBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory);

	void processIfcPorts(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
private:
	void buildIfcRelNests(boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>>& objectDefinition, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);
	void buildIfcReletionshipConnectionPorts(IfcHierarchyHelper<Ifc4>& file);
	typedef Ifc4::IfcGloballyUniqueId guid;

	IfcPortsRelationshipList* ifcPortsRelationshipList;
	Ifc4::IfcGeometricRepresentationContext* geometricRepresentationContext = nullptr;
	Ifc4::IfcOwnerHistory* ownerHistory = nullptr;
};


