#include "../headers/IfcPortsBuilder.h"


IfcPortsBuilder::IfcPortsBuilder()
{
}

void IfcPortsBuilder::processIfcPorts(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	ifcPortsRelationshipList = new IfcPortsRelationshipList();

	for (auto& ifcElementBundle : ifcBundleVector) 
	{
		if (ifcElementBundle->getHasElementConnection())
		{
			//TODO [SB] find a better implementation especially for handling Source and Sink ports
			IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>();

			int portSequence = 0;
			for (Ifc4::IfcCartesianPoint* point : ifcElementBundle->getIfcPortsPointsVector())
			{
				Ifc4::IfcRepresentationItem::list::ptr ifcPortsRepItemList(new Ifc4::IfcRepresentationItem::list());
				Ifc4::IfcRepresentation::list::ptr ifcPortsRepList(new Ifc4::IfcRepresentation::list());

				Ifc4::IfcGeometricRepresentationItem* pointGeom(point);
				ifcPortsRepItemList->push(pointGeom);


				Ifc4::IfcRepresentation* ifcPortsRepresentation = new Ifc4::Ifc4::IfcRepresentation(
					file.getSingle<Ifc4::IfcGeometricRepresentationContext>(),
					std::string("Point"),
					std::string("Point"),
					ifcPortsRepItemList
				);

				ifcPortsRepList->push(ifcPortsRepresentation);

				Ifc4::IfcProductDefinitionShape* portShape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, ifcPortsRepList);

				file.addEntity(portShape);

				//Need to be used the subtype because otherwise the flow , distribution type, distribution system cqnnot be specified
				Ifc4::IfcDistributionPort* port = new Ifc4::IfcDistributionPort(
					guid::IfcGloballyUniqueId("Port: " + std::to_string(portSequence) + std::string(" Element: ") + ifcElementBundle->getModelerElementDescriptor()),
					file.getSingle<Ifc4::IfcOwnerHistory>(),
					std::string("Port ") + std::to_string(portSequence) + std::string(" Element: ") + ifcElementBundle->getModelerElementDescriptor(),
					ifcElementBundle->getModelerElementDescriptor(),
					std::string("PORT"),
					file.getSingle<Ifc4::IfcObjectPlacement>(),
					portShape,
					Ifc4::IfcFlowDirectionEnum::Value(portSequence), //TODO [SB] Handle in case of multiple ports on element
					Ifc4::IfcDistributionPortTypeEnum::IfcDistributionPortType_PIPE,
					Ifc4::IfcDistributionSystemEnum::IfcDistributionSystem_NOTDEFINED
				);


				//insert the object inside the object definition list list
				tempEntityList->push(port);

				//Add the IfcDistributionPort to the IfcBundleElement
				ifcElementBundle->addIfcDistributionPorts(port);

				//The ports belongs to the Ifc under Product category
				file.addBuildingProduct(port);

				//Insert the port to the list
				ifcPortsRelationshipList->insertIfcPortElement(point, port, ifcElementBundle);

				portSequence++;
			}

			//create the shared_ptr with the object definition list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>> objectDefinition(tempEntityList);

			//Create the nested relationship between the element and ports
			buildIfcRelNests(objectDefinition, ifcElementBundle, file);
		}
	}

	buildIfcReletionshipConnectionPorts(file);
}

void IfcPortsBuilder::buildIfcRelNests(boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>>& objectDefinition, IfcElementBundle *& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	//Create the nested relationship between the element and ports
	Ifc4::IfcRelNests * relNests = new Ifc4::IfcRelNests(
		guid::IfcGloballyUniqueId("RelNests: " + ifcElementBundle->getModelerElementDescriptor() + " Ports"),
		file.getSingle<Ifc4::IfcOwnerHistory>(),
		std::string("RelNests: ") + ifcElementBundle->getModelerElementDescriptor() + std::string(" Ports"),
		std::string("RelNests: ") + ifcElementBundle->getModelerElementDescriptor() + std::string(" Ports"),
		ifcElementBundle->getIfcElement(),
		objectDefinition
	);
	
	file.addEntity(relNests);
}

void IfcPortsBuilder::buildIfcReletionshipConnectionPorts(IfcHierarchyHelper<Ifc4>& file)
{
	PortElement* temp = ifcPortsRelationshipList->getHead();

	while(temp != NULL)
	{
		if (temp->isElementConnected)
		{
			Ifc4::IfcRelConnectsPorts* connectsPorts = new Ifc4::IfcRelConnectsPorts(
				guid::IfcGloballyUniqueId("Element: " + temp->ifcDistributionElement->Name() + " Connection Port: " + std::to_string(temp->distributionPort->FlowDirection())),
				file.getSingle<Ifc4::IfcOwnerHistory>(),				
				std::string("Connection: ") + temp->ifcDistributionElement->Name() + std::string(" To: ") + temp->nextPortElement->ifcDistributionElement->Name(),
				std::string("Connection: ") + temp->ifcDistributionElement->Name() + std::string(" To: ") + temp->nextPortElement->ifcDistributionElement->Name(),
				temp->distributionPort,
				temp->nextPortElement->distributionPort,
				temp->ifcDistributionElement
			);
			
			file.addEntity(connectsPorts);

			temp = temp->nextPortElement;
		}	
		else
			temp = temp->nextPortElement;
	}

	ifcPortsRelationshipList->display();
}
