#pragma once

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

		class IfcPortsRelationshipList
		{
		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			PortElement *mHead;
			bool connectPortAtLocation(PortElement*& newPortElement);

		public:
			IfcPortsRelationshipList();

			PortElement* getHead();
			void insertIfcPortElement(Ifc4::IfcCartesianPoint* point, Ifc4::IfcDistributionPort* dPort, IfcElementBundle*& ifcElementBundle);
			void display();
		};
	}
}