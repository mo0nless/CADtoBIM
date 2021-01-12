#pragma once


#include "IfcPortsRelationshipList.h"

class IfcPortsBuilder
{
public:
	IfcPortsBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory);

	void processIfcPorts(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
private:
	Logging::Logger* _logger = Logging::Logger::getLogger();

	Ifc4::IfcRelNests* buildIfcRelNests(boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>> objectDefinition, IfcElementBundle*& ifcElementBundle);
	void buildIfcReletionshipConnectionPorts(IfcHierarchyHelper<Ifc4>& file);
	typedef Ifc4::IfcGloballyUniqueId guid;

	IfcPortsRelationshipList* ifcPortsRelationshipList;
	Ifc4::IfcGeometricRepresentationContext* geometricRepresentationContext = nullptr;
	Ifc4::IfcOwnerHistory* ownerHistory = nullptr;

};


