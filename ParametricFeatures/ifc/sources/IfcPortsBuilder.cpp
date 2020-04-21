#include "../headers/IfcPortsBuilder.h"


IfcPortsBuilder::IfcPortsBuilder()
{
}

void IfcPortsBuilder::processIfcPorts(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	for (auto& ifcElementBundle : ifcBundleVector) 
	{
		if (ifcElementBundle->getHasElementConnection())
		{
			//TODO [SB] find a better implementation especially for handling Source and Sink ports
			IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>();

			int portSequence = 0;
			for (Ifc4::IfcPoint* point : ifcElementBundle->getIfcPortsPointsVector())
			{
				Ifc4::IfcRepresentationItem::list::ptr ifcPortsRepItemList(new Ifc4::IfcRepresentationItem::list());
				Ifc4::IfcRepresentation::list::ptr ifcPortsRepList(new Ifc4::IfcRepresentation::list());

				Ifc4::IfcGeometricRepresentationItem* pointGeom(point);
				ifcPortsRepItemList->push(pointGeom);


				Ifc4::IfcRepresentation* ifcPortsRepresentation = new Ifc4::Ifc4::IfcRepresentation(
					file.getSingle<Ifc4::IfcGeometricRepresentationContext>(),
					std::string("Point Port"),
					std::string("Point Port"),
					ifcPortsRepItemList
				);

				ifcPortsRepList->push(ifcPortsRepresentation);

				Ifc4::IfcProductDefinitionShape* portShape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, ifcPortsRepList);

				file.addEntity(portShape);

				//Need to be used the subtype because otherwise the flow , distribution type, distribution system you can specify it
				Ifc4::IfcDistributionPort* port = new Ifc4::IfcDistributionPort(
					std::string("Port test"),
					file.getSingle<Ifc4::IfcOwnerHistory>(),
					ifcElementBundle->getModelerElementName(),
					ifcElementBundle->getModelerElementName(),
					std::string("Port test"),
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

				portSequence++;
			}

			//create the shared_ptr with the object definition list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>> objectDefinition(tempEntityList);

			//Create the nested relationship between the element and ports
			buildIfcRelNests(objectDefinition, ifcElementBundle, file);
		}
	}
}

void IfcPortsBuilder::buildIfcRelNests(boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>>& objectDefinition, IfcElementBundle *& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	//Create the nested relationship between the element and ports
	Ifc4::IfcRelNests * relNests = new Ifc4::IfcRelNests(
		guid::IfcGloballyUniqueId(""),
		file.getSingle<Ifc4::IfcOwnerHistory>(),
		ifcElementBundle->getModelerElementName(),
		ifcElementBundle->getModelerElementName(),
		ifcElementBundle->getIfcElement(),
		objectDefinition
	);

	file.addEntity(relNests);
}

