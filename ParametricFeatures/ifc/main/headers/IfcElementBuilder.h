#pragma once

//#include "../../enhancer/headers/IfcOperationsHelper.h"

#include "../../../services/components_mapping/headers/ComponentsMappingService.h"
#include "../headers/IfcElementBundle.h"




class IfcElementBuilder
{
public:
	IfcElementBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory, Ifc4::IfcObjectPlacement* objectPlacement);

	void processIfcElement(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
private:
	Ifc4::IfcElement* handleIfcElementCreation(ComponentsMappingDTO* mappedValue, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcBuildingElement* handleIfcBuildingElement(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcCivilElement* handleIfcCivilElement(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcDistributionElement* handleIfcDistributionElement(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcElementAssembly* handleIfcElementAssembly(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcElementComponent* handleIfcElementComponent(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcFeatureElement* handleIfcFeatureElement(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcFurnishingElement* handleIfcFurnishingElement(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcGeographicElement* handleIfcGeographicElement(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcTransportElement* handleIfcTransportElement(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);

	Ifc4::IfcVirtualElement* handleIfcVirtualElement(string ifcElement, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle);



	Ifc4::IfcElement* buildIfcElement(IfcElementBundle*& ifcElementBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file);

	ComponentsMappingDTO* getIfcElement(vector<ComponentsMappingDTO*>componentsMapping, string elementDescription);

	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcGeometricRepresentationContext* geometricRepresentationContext = nullptr;
	Ifc4::IfcOwnerHistory* ownerHistory = nullptr;
	Ifc4::IfcObjectPlacement* objectPlacement = nullptr;

	ComponentsMappingService* _componentsMappingService;

	Logs::Logger* _logger = Logs::Logger::getLogger();
};
