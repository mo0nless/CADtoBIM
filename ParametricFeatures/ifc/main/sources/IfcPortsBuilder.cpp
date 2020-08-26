#include "../headers/IfcPortsBuilder.h"


IfcPortsBuilder::IfcPortsBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory)
{
	this->geometricRepresentationContext = geomContext;
	this->ownerHistory = ownerHistory;
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

				//TODO: Needs to be set up correctly the 3rd input parameter following:
				//https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcrepresentationresource/lexical/ifcshaperepresentation.htm
				std::string representationType = "Point";
				std::string representationIdentifier = "Reference";

				//NOTE  The provision of a model view (IfcGeometricRepresentationContext.ContextType = 'Model') is mandatory. Instances of IfcGeometricRepresentationSubContext relate to it as its ParentContext.
				Ifc4::IfcGeometricRepresentationSubContext* geometricSubContext = new Ifc4::IfcGeometricRepresentationSubContext(
					representationIdentifier,
					geometricRepresentationContext->ContextType(),
					geometricRepresentationContext,
					boost::none,
					Ifc4::IfcGeometricProjectionEnum::IfcGeometricProjection_MODEL_VIEW,
					std::string("$")
				);
				
				Ifc4::IfcShapeRepresentation* ifcPortsRepresentation = new Ifc4::Ifc4::IfcShapeRepresentation(
					geometricSubContext,
					representationIdentifier,
					representationType,
					ifcPortsRepItemList
				);
				ifcPortsRepList->push(ifcPortsRepresentation);

				Ifc4::IfcProductDefinitionShape* portShape = new Ifc4::IfcProductDefinitionShape(
					std::string("$"),
					std::string("$"), 
					ifcPortsRepList
				);

				file.addEntity(portShape);

				//Need to be used the subtype because otherwise the flow , distribution type, distribution system cqnnot be specified
				Ifc4::IfcDistributionPort* port = new Ifc4::IfcDistributionPort(
					guid::IfcGloballyUniqueId("Port: " + std::to_string(portSequence) + std::string(" Element: ") + ifcElementBundle->getModelerElementDescriptor()),
					//file.getSingle<Ifc4::IfcOwnerHistory>(),
					ownerHistory,
					std::string("Port ") + std::to_string(portSequence) + std::string(" Element: ") + ifcElementBundle->getModelerElementDescriptor(),
					ifcElementBundle->getModelerElementDescriptor(),
					std::string("PORT"),
					ifcElementBundle->getIfcElement()->ObjectPlacement(),
					//file.getSingle<Ifc4::IfcObjectPlacement>(),
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
		//file.getSingle<Ifc4::IfcOwnerHistory>(),
		ownerHistory,
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
				//file.getSingle<Ifc4::IfcOwnerHistory>(),
				ownerHistory,
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
