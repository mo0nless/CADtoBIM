#pragma once

#include "../../enhancer/headers/IfcOperationsEnhancer.h"
#include "../headers/IfcElementBundle.h"
#include "IfcPortsRelationshipList.h"

class IfcPortsBuilder
{
public:
	IfcPortsBuilder();

	void processIfcPorts(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
private:
	void buildIfcRelNests(boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>>& objectDefinition, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);
	void buildIfcReletionshipConnectionPorts(IfcHierarchyHelper<Ifc4>& file);
	typedef Ifc4::IfcGloballyUniqueId guid;

	IfcPortsRelationshipList* ifcPortsRelationshipList;
};


