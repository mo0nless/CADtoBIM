#pragma once


#include "IfcPortsRelationshipList.h"

class IfcPortsBuilder
{
public:
	IfcPortsBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory);

	void processIfcPorts(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
private:
	Logs::Logger* _logger = Logs::Logger::getLogger();

	void buildIfcRelNests(boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>>& objectDefinition, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);
	void buildIfcReletionshipConnectionPorts(IfcHierarchyHelper<Ifc4>& file);
	typedef Ifc4::IfcGloballyUniqueId guid;

	IfcPortsRelationshipList* ifcPortsRelationshipList;
	Ifc4::IfcGeometricRepresentationContext* geometricRepresentationContext = nullptr;
	Ifc4::IfcOwnerHistory* ownerHistory = nullptr;
};


