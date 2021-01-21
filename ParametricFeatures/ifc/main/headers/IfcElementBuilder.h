#pragma once

/**
 * @file IfcElementBuilder.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../data_base/services/headers/ComponentsMappingService.h"
#include "../../bundle/headers/IfcElementBundle.h"

using namespace Ifc::Bundle;
using namespace DataBase::Services;

namespace Ifc
{
	namespace Main
	{
		/**
		 * @brief Ifc Element Builder Class. Process all IfcElementBundle to build correspondent IfcElement representation
		 * 
		 * @remark the function is called by the class IfcBuilder
		 * @see IfcBuilder
		 */
		class IfcElementBuilder
		{
		public:
			/**
			 * @brief Construct a new Ifc Element Builder object
			 * 
			 * @param geomContext 
			 * @param ownerHistory 
			 * @param objectPlacement 
			 */
			IfcElementBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory, Ifc4::IfcObjectPlacement* objectPlacement);

			/**
			 * @brief Start processing and building the correct IfcElement with its Level Id cache
			 * 
			 * @param ifcBundleVector 
			 * @param file 
			 * @param levelFileEntities 
			 */
			void processIfcElement(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file, map<LevelId, IfcEntityList*> levelFileEntities);
		private:
			/**
			 * @brief Handle IfcElement Creation using the mapped value from the database
			 * 
			 * @param mappedValue the mapped value from the database
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcElement* 
			 */
			Ifc4::IfcElement* handleIfcElementCreation(ComponentsMappingDTO* mappedValue, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcBuildingElement and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcBuildingElement* 
			 */
			Ifc4::IfcBuildingElement* handleIfcBuildingElement(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcCivilElement and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcCivilElement* 
			 */
			Ifc4::IfcCivilElement* handleIfcCivilElement(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcDistributionElement and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcDistributionElement* 
			 */
			Ifc4::IfcDistributionElement* handleIfcDistributionElement(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcElementAssembly and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcElementAssembly* 
			 */
			Ifc4::IfcElementAssembly* handleIfcElementAssembly(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcElementComponent and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcElementComponent* 
			 */
			Ifc4::IfcElementComponent* handleIfcElementComponent(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcFeatureElement and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcFeatureElement* 
			 */
			Ifc4::IfcFeatureElement* handleIfcFeatureElement(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcFurnishingElement and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcFurnishingElement* 
			 */
			Ifc4::IfcFurnishingElement* handleIfcFurnishingElement(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcGeographicElement and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcGeographicElement* 
			 */
			Ifc4::IfcGeographicElement* handleIfcGeographicElement(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcTransportElement and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcTransportElement* 
			 */
			Ifc4::IfcTransportElement* handleIfcTransportElement(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Handle IfcVirtualElement and sub categories 
			 * 
			 * @param nameIfcElement 
			 * @param shape 
			 * @param ifcElementBundle 
			 * @param file 
			 * @return Ifc4::IfcVirtualElement* 
			 */
			Ifc4::IfcVirtualElement* handleIfcVirtualElement(string nameIfcElement, Ifc4::IfcProductDefinitionShape* shape, IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);
			
			/**
			 * @brief Handle IfcElement and sub categories 
			 * 
			 * @param ifcElementBundle 
			 * @param elemShape 
			 * @param file 
			 * @return Ifc4::IfcElement* 
			 */
			Ifc4::IfcElement* buildIfcElement(IfcElementBundle*& ifcElementBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Get the ComponentsMappingDTO related to the ifcElementBundle object with its description string
			 * 
			 * @param elementDescription the ifcElementBundle modeler description
			 * @return ComponentsMappingDTO* 
			 */
			ComponentsMappingDTO* getIfcElement(vector<ComponentsMappingDTO*>componentsMapping, string elementDescription);

			typedef Ifc4::IfcGloballyUniqueId guid;

			Ifc4::IfcGeometricRepresentationContext* geometricRepresentationContext = nullptr;
			Ifc4::IfcOwnerHistory* ownerHistory = nullptr;
			Ifc4::IfcObjectPlacement* objectPlacement = nullptr;

			ComponentsMappingService* _componentsMappingService;

			Logging::Logger* _logger = Logging::Logger::getLogger();
		};
	}
}