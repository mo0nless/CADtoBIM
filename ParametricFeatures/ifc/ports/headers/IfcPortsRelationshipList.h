#pragma once

/**
 * @file IfcPortsRelationshipList.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../bundle/headers/IfcElementBundle.h"

#include "../../../common/models/headers/SessionManager.h"
#include "../../../common/utils/headers/Comparator.h"

using namespace Ifc::Bundle;
using namespace Common::Utilities;
using namespace Common::Models;

namespace Ifc
{
	namespace Ports
	{
		/**
		 * @brief PortElement structure used as container and linked element
		 * 
		 * @remark Used as a linked list object
		 */
		struct PortElement
		{
			//Data 
			Ifc4::IfcCartesianPoint* cartesianPointPort;
			Ifc4::IfcDistributionPort* distributionPort;
			Ifc4::IfcDistributionElement* ifcDistributionElement;
			long elementIdNumber;
			string elementName;

			//Next port
			PortElement* nextPortElement;
			//Previous Port
			PortElement* previousPortElement;

			bool isElementConnected;
		};

		/**
		 * @brief Class that operates to establish the relationship and connection between one port or the other
		 * 
		 */
		class IfcPortsRelationshipList
		{
		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			PortElement *mHead;

			/**
			 * @brief Connect and check the relationship of the input PortElement
			 * 
			 * @param newPortElement 
			 * @return true 
			 * @return false 
			 */
			bool connectPortAtLocation(PortElement*& newPortElement);

		public:
			IfcPortsRelationshipList();

			/**
			 * @brief Get the Head object
			 * 
			 * @return PortElement* 
			 */
			PortElement* getHead();

			/**
			 * @brief Insert a new port element that belongs to an IfcElementBundle
			 * 
			 * @param point 
			 * @param dPort 
			 * @param ifcElementBundle 
			 */
			void insertIfcPortElement(Ifc4::IfcCartesianPoint* point, Ifc4::IfcDistributionPort* dPort, IfcElementBundle*& ifcElementBundle);
			
			void display();
		};
	}
}