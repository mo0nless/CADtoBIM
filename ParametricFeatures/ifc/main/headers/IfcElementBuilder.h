#pragma once

#include "../../../data_base/services/headers/ComponentsMappingService.h"
#include "../../bundle/headers/IfcElementBundle.h"

using namespace Ifc::Bundle;

namespace Ifc
{
	namespace Main
	{
		class IfcElementBuilder
		{
		public:
			IfcElementBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory, Ifc4::IfcObjectPlacement* objectPlacement);

			void processIfcElement(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file, map<LevelId, IfcEntityList*> levelFileEntities);
		private:
			Ifc4::IfcElement* handleIfcElementCreation(ComponentsMappingDTO* mappedValue, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcBuildingElement* handleIfcBuildingElement(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcCivilElement* handleIfcCivilElement(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcDistributionElement* handleIfcDistributionElement(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcElementAssembly* handleIfcElementAssembly(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcElementComponent* handleIfcElementComponent(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcFeatureElement* handleIfcFeatureElement(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcFurnishingElement* handleIfcFurnishingElement(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcGeographicElement* handleIfcGeographicElement(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcTransportElement* handleIfcTransportElement(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcVirtualElement* handleIfcVirtualElement(string ifcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			Ifc4::IfcElement* buildIfcElement(IfcElementBundle*& ifcElementBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file);

			ComponentsMappingDTO* getIfcElement(vector<ComponentsMappingDTO*>componentsMapping, string elementDescription);

			typedef Ifc4::IfcGloballyUniqueId guid;

			Ifc4::IfcGeometricRepresentationContext* geometricRepresentationContext = nullptr;
			Ifc4::IfcOwnerHistory* ownerHistory = nullptr;
			Ifc4::IfcObjectPlacement* objectPlacement = nullptr;

			ComponentsMappingService* _componentsMappingService;

			Logs::Logger* _logger = Logs::Logger::getLogger();
		};
	}
}