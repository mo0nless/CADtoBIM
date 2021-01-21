#pragma once

/**
 * @file IfcPortsBuilder.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "IfcPortsRelationshipList.h"

namespace Ifc
{
	namespace Ports
	{
		/**
		 * @brief Ifc Ports Builder Class. Process all IfcElementBundle to build correspondent IfcPorts representation
		 * 
		 * @remark the function is called by the class IfcBuilder
		 * @see IfcBuilder
		 */
		class IfcPortsBuilder
		{
		public:
			/**
			 * @brief Construct a new Ifc Ports Builder object
			 * 
			 * @param geomContext 
			 * @param ownerHistory 
			 */
			IfcPortsBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory);

			/**
			 * @brief Process the IfcElementBundle vector and check each element if contains ports and build them
			 * 
			 * @param ifcBundleVector 
			 * @param file 
			 */
			void processIfcPorts(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			/**
			 * @brief Create the IfcRelNests relationship between ports and IfcElement
			 * 
			 * @param objectDefinition 
			 * @param ifcElementBundle 
			 * @return Ifc4::IfcRelNests* 
			 */
			Ifc4::IfcRelNests* buildIfcRelNests(boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>> objectDefinition, IfcElementBundle*& ifcElementBundle);
			
			/**
			 * @brief Build the connection and relationship between differents ports
			 * 
			 * @param file 
			 */
			void buildIfcReletionshipConnectionPorts(IfcHierarchyHelper<Ifc4>& file);
			typedef Ifc4::IfcGloballyUniqueId guid;

			IfcPortsRelationshipList* ifcPortsRelationshipList;
			Ifc4::IfcGeometricRepresentationContext* geometricRepresentationContext = nullptr;
			Ifc4::IfcOwnerHistory* ownerHistory = nullptr;

		};
	}
}
