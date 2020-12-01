#include "../headers/IfcPortsBuilder.h"


IfcPortsBuilder::IfcPortsBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory)
{
	this->geometricRepresentationContext = geomContext;
	this->ownerHistory = ownerHistory;
}

void IfcPortsBuilder::processIfcPorts(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Starting enhancing the IFC ports -!");

	ifcPortsRelationshipList = new IfcPortsRelationshipList();
	
	for (auto& ifcElementBundle : ifcBundleVector) 
	{
		if (ifcElementBundle->getHasElementConnection() && !ifcElementBundle->getBadIfcClassBuild())
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
				string representationType = "Point";
				string representationIdentifier = "Reference";

				//NOTE: The provision of a model view (IfcGeometricRepresentationContext.ContextType = 'Model') is mandatory. 
				//Instances of IfcGeometricRepresentationSubContext relate to it as its ParentContext.
				Ifc4::IfcGeometricRepresentationSubContext* geometricSubContext = new Ifc4::IfcGeometricRepresentationSubContext(
					representationIdentifier,
					geometricRepresentationContext->ContextType(),
					geometricRepresentationContext,
					boost::none,
					Ifc4::IfcGeometricProjectionEnum::IfcGeometricProjection_MODEL_VIEW,
					boost::none
				);
				
				Ifc4::IfcShapeRepresentation* ifcPortsRepresentation = new Ifc4::Ifc4::IfcShapeRepresentation(
					geometricSubContext,
					representationIdentifier,
					representationType,
					ifcPortsRepItemList
				);
				ifcPortsRepList->push(ifcPortsRepresentation);

				Ifc4::IfcProductDefinitionShape* portShape = new Ifc4::IfcProductDefinitionShape(
					boost::none,
					boost::none,
					ifcPortsRepList
				);

				file.addEntity(portShape);

				Ifc4::IfcObjectPlacement* objPlacement = ifcElementBundle->getIfcElement()->ObjectPlacement();

				//Need to be used the subtype because otherwise the flow , distribution type, distribution system cqnnot be specified
				Ifc4::IfcDistributionPort* port = new Ifc4::IfcDistributionPort(
					guid::IfcGloballyUniqueId("Port: " + to_string(portSequence) + string(" Element: ") + to_string(ifcElementBundle->getModelerElementId())),
					//file.getSingle<Ifc4::IfcOwnerHistory>(),
					ownerHistory,
					string("Port ") + to_string(portSequence) + string(" Element: ") + ifcElementBundle->getModelerElementDescriptor(),
					ifcElementBundle->getModelerElementDescriptor(),
					string("PORT"),
					objPlacement,
					//ifcElementBundle->getIfcElement()->ObjectPlacement(),
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

				if (portSequence <= 2)
					portSequence++;
			}

			//create the shared_ptr with the object definition list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>> objectDefinition(tempEntityList);

			//Create the nested relationship between the element and ports
			Ifc4::IfcRelNests* relNests = buildIfcRelNests(objectDefinition, ifcElementBundle);

			file.addEntity(relNests);
		}
		else
		{
			_logger->logError(__FILE__, __LINE__, __func__, ifcElementBundle->getModelerElementDescriptor() + " " + to_string(ifcElementBundle->getModelerElementId()) + " IFC Element is Nullptr, ElementBundle bad flag");
		}
	}

	buildIfcReletionshipConnectionPorts(file);

	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Ended enhancing the IFC ports -!");

}

Ifc4::IfcRelNests* IfcPortsBuilder::buildIfcRelNests(boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>> objectDefinition, IfcElementBundle *& ifcElementBundle)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	//Create the nested relationship between the element and ports
	Ifc4::IfcRelNests * relNests = new Ifc4::IfcRelNests(
		guid::IfcGloballyUniqueId(string("RelNests: ") + to_string(ifcElementBundle->getModelerElementId()) + string(" Ports")),
		//file.getSingle<Ifc4::IfcOwnerHistory>(),
		ownerHistory,
		string("RelNests: ") + ifcElementBundle->getModelerElementDescriptor() + string(" Ports"),
		string("RelNests: ") + ifcElementBundle->getModelerElementDescriptor() + string(" Ports"),
		ifcElementBundle->getIfcElement(),
		objectDefinition
	);

	return relNests;
	
}

void IfcPortsBuilder::buildIfcReletionshipConnectionPorts(IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	PortElement* temp = ifcPortsRelationshipList->getHead();

	string _dataOutputFilePath = SessionManager::getInstance()->getDataOutputFilePath();
	ofstream _outFile;

	while(temp != NULL)
	{
		if (temp->isElementConnected && temp->ifcDistributionElement != nullptr)
		{

			/*_outFile.open(_dataOutputFilePath, ios_base::app, sizeof(string));
			_outFile << "------------------- " << temp->elementIdNumber << " -------------------" << temp->elementName << endl;
			_outFile.close();*/

			if (temp->ifcDistributionElement->declaration().supertype()->is(Ifc4::IfcDistributionElement::Class()))
			{
				_outFile.open(_dataOutputFilePath, ios_base::app, sizeof(string));
				_outFile << "------------------- " << temp->elementName << endl;
				_outFile.close();
			}
			if (temp->ifcDistributionElement->declaration().is(Ifc4::IfcDistributionElement::Class()))
			{
				_outFile.open(_dataOutputFilePath, ios_base::app, sizeof(string));
				_outFile << "------------------- " << temp->elementIdNumber << endl;
				_outFile.close();
			}

			Ifc4::IfcRelConnectsPorts* connectsPorts = new Ifc4::IfcRelConnectsPorts(
				guid::IfcGloballyUniqueId("Element: " + temp->ifcDistributionElement->Name() + " Connection Port: " + to_string(temp->distributionPort->FlowDirection())),
				//file.getSingle<Ifc4::IfcOwnerHistory>(),
				ownerHistory,
				string("Connection: ") + temp->ifcDistributionElement->Name() + string(" To: ") + temp->nextPortElement->ifcDistributionElement->Name(),
				string("Connection: ") + temp->ifcDistributionElement->Name() + string(" To: ") + temp->nextPortElement->ifcDistributionElement->Name(),
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

	//ifcPortsRelationshipList->display();
}
