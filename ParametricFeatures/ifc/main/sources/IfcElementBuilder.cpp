#include "../headers/IfcElementBuilder.h"

IfcElementBuilder::IfcElementBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory, Ifc4::IfcObjectPlacement* objectPlacement)
{
	this->geometricRepresentationContext = geomContext;
	this->ownerHistory = ownerHistory;
	this->objectPlacement = objectPlacement;

	this->_componentsMappingService = new ComponentsMappingService(Logs::Logger::getLogger());
}

void IfcElementBuilder::processIfcElement(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{

	vector<ComponentsMappingDTO*> componentsMappings = this->_componentsMappingService->getAll();

	
	//Create the vector for the distribution element 
	//vector<IfcElementBundle*>ifcDistributionBundleVector;
	for (auto& ifcElementBundle : ifcBundleVector) //const& removed
	{
		string ifcElementType = getIfcElement(componentsMappings, ifcElementBundle->getModelerElementDescriptor());

		Ifc4::IfcRepresentationItem::list::ptr ifcRepresentationItemList(new Ifc4::IfcRepresentationItem::list());

		for (auto const& ifcGraphicPropertiesBundle : ifcElementBundle->getIfcGraphicPropertiesBundleVector()) {

			if (ifcGraphicPropertiesBundle->getIfcRepresentationItem() != nullptr && ifcGraphicPropertiesBundle->getShow()) {
				ifcRepresentationItemList->push(ifcGraphicPropertiesBundle->getIfcRepresentationItem());
			}
		}

		string representationType = "";
		string representationIdentifier = "";
		//TODO: Needs to be set up correctly the 3rd input parameter following:
		//https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcrepresentationresource/lexical/ifcshaperepresentation.htm
		if (ifcElementBundle->solidModel)
		{
			representationType = "SolidModel";
			representationIdentifier = "Body";
		}
		else
		{
			representationType = "Axis";
			representationIdentifier = "Curve";
		}

		//NOTE  The provision of a model view (IfcGeometricRepresentationContext.ContextType = 'Model') is mandatory. Instances of IfcGeometricRepresentationSubContext relate to it as its ParentContext.
		Ifc4::IfcGeometricRepresentationSubContext* geometricSubContext = new Ifc4::IfcGeometricRepresentationSubContext(
			representationIdentifier,
			geometricRepresentationContext->ContextType(),
			geometricRepresentationContext,
			boost::none,
			Ifc4::IfcGeometricProjectionEnum::IfcGeometricProjection_MODEL_VIEW,
			string("$")
		);

				
		Ifc4::IfcShapeRepresentation* ifcRepresentation = new Ifc4::Ifc4::IfcShapeRepresentation(
			geometricSubContext,
			//file.getSingle<Ifc4::IfcGeometricRepresentationContext>(),
			representationIdentifier,
			representationType,
			ifcRepresentationItemList
		);

		Ifc4::IfcRepresentation::list::ptr ifcRepresentationList(new Ifc4::IfcRepresentation::list());
		ifcRepresentationList->push(ifcRepresentation);

		Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(
			string("$"),
			string("$"),
			ifcRepresentationList
		);

		file.addEntity(shape);
	

		handleIfcElementCreation(ifcElementType, file, shape, ifcElementBundle);

	}
}


void IfcElementBuilder::handleIfcElementCreation(string ifcElementType, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProductDefinitionShape* shape, 
	IfcElementBundle* ifcElementBundle)
{
	if (boost::iequals(ifcElementType, "IfcBeam")) {
			Ifc4::IfcBeam* beam = new Ifc4::IfcBeam(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
				ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
				file.addLocalPlacement(), shape, string("$"), Ifc4::IfcBeamTypeEnum::IfcBeamType_NOTDEFINED);

			file.addBuildingProduct(beam);
			ifcElementBundle->setIfcElement(beam);
	}
	else if (boost::iequals(ifcElementType, "IfcBuildingElementProxy")) {
		Ifc4::IfcBuildingElementProxy* buildingElementProxy = new Ifc4::IfcBuildingElementProxy(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcBuildingElementProxyTypeEnum::IfcBuildingElementProxyType_NOTDEFINED);

		file.addBuildingProduct(buildingElementProxy);
		ifcElementBundle->setIfcElement(buildingElementProxy);
	}
	else if (boost::iequals(ifcElementType, "IfcChimney")) {
		Ifc4::IfcChimney* chimney = new Ifc4::IfcChimney(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcChimneyTypeEnum::IfcChimneyType_NOTDEFINED);

		file.addBuildingProduct(chimney);
		ifcElementBundle->setIfcElement(chimney);
	}
	else if (boost::iequals(ifcElementType, "IfcColumn")) {
		Ifc4::IfcColumn* column = new Ifc4::IfcColumn(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcColumnTypeEnum::IfcColumnType_NOTDEFINED);

		file.addBuildingProduct(column);
		ifcElementBundle->setIfcElement(column);
	}
	else if (boost::iequals(ifcElementType, "IfcCovering")) {
		Ifc4::IfcCovering* covering = new Ifc4::IfcCovering(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcCoveringTypeEnum::IfcCoveringType_NOTDEFINED);

		file.addBuildingProduct(covering);
		ifcElementBundle->setIfcElement(covering);
	}
	else if (boost::iequals(ifcElementType, "IfcCurtainWall")) {
		Ifc4::IfcCurtainWall* curtainWall = new Ifc4::IfcCurtainWall(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcCurtainWallTypeEnum::IfcCurtainWallType_NOTDEFINED);

		file.addBuildingProduct(curtainWall);
		ifcElementBundle->setIfcElement(curtainWall);
	}
	else if (boost::iequals(ifcElementType, "IfcDoor")) {
		Ifc4::IfcDoor* door = new Ifc4::IfcDoor(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), 2, 3, Ifc4::IfcDoorTypeEnum::IfcDoorType_NOTDEFINED,
			Ifc4::IfcDoorTypeOperationEnum::IfcDoorTypeOperation_NOTDEFINED, string("$"));

		file.addBuildingProduct(door);
		ifcElementBundle->setIfcElement(door);
	}
	else if (boost::iequals(ifcElementType, "IfcFooting")) {
		Ifc4::IfcFooting* footing = new Ifc4::IfcFooting(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcFootingTypeEnum::IfcFootingType_NOTDEFINED);

		file.addBuildingProduct(footing);
		ifcElementBundle->setIfcElement(footing);
	}
	else if (boost::iequals(ifcElementType, "IfcMember")) {
		Ifc4::IfcMember* member = new Ifc4::IfcMember(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcMemberTypeEnum::IfcMemberType_NOTDEFINED);

		file.addBuildingProduct(member);
		ifcElementBundle->setIfcElement(member);
	}
	else if (boost::iequals(ifcElementType, "IfcPile")) {
		Ifc4::IfcPile* pile = new Ifc4::IfcPile(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcPileTypeEnum::IfcPileType_NOTDEFINED, 
			Ifc4::IfcPileConstructionEnum::IfcPileConstruction_NOTDEFINED);

		file.addBuildingProduct(pile);
		ifcElementBundle->setIfcElement(pile);
	}
	else if (boost::iequals(ifcElementType, "IfcPlate")) {
		Ifc4::IfcPlate* pile = new Ifc4::IfcPlate(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcPlateTypeEnum::IfcPlateType_NOTDEFINED);

		file.addBuildingProduct(pile);
		ifcElementBundle->setIfcElement(pile);
	}
	else if (boost::iequals(ifcElementType, "IfcRailing")) {
		Ifc4::IfcRailing* railing = new Ifc4::IfcRailing(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcRailingTypeEnum::IfcRailingType_NOTDEFINED);

		file.addBuildingProduct(railing);
		ifcElementBundle->setIfcElement(railing);
	}
	else if (boost::iequals(ifcElementType, "IfcRamp")) {
		Ifc4::IfcRamp* ramp = new Ifc4::IfcRamp(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcRampTypeEnum::IfcRampType_NOTDEFINED);

		file.addBuildingProduct(ramp);
		ifcElementBundle->setIfcElement(ramp);
	}
	else if (boost::iequals(ifcElementType, "IfcRampFlight")) {
		Ifc4::IfcRampFlight* rampFlight = new Ifc4::IfcRampFlight(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcRampFlightTypeEnum::IfcRampFlightType_NOTDEFINED);

		file.addBuildingProduct(rampFlight);
		ifcElementBundle->setIfcElement(rampFlight);
	}
	else if (boost::iequals(ifcElementType, "IfcPipeSegment")) {
		Ifc4::IfcPipeSegment* pipeSegment = new Ifc4::IfcPipeSegment(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcPipeSegmentTypeEnum::IfcPipeSegmentType_NOTDEFINED);

		file.addBuildingProduct(pipeSegment);
		ifcElementBundle->setIfcElement(pipeSegment);
	}
	else if (boost::iequals(ifcElementType,"IfcSlab")) {
		Ifc4::IfcSlab* slab = new Ifc4::IfcSlab(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcSlabTypeEnum::IfcSlabType_NOTDEFINED);


		file.addBuildingProduct(slab);
		ifcElementBundle->setIfcElement(slab);

	}


	else if (boost::iequals(ifcElementType, "IfcWall")) {
		Ifc4::IfcWall* wall = new Ifc4::IfcWall(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcWallTypeEnum::IfcWallType_NOTDEFINED);

		file.addBuildingProduct(wall);
		ifcElementBundle->setIfcElement(wall);
	}
	else if (boost::iequals(ifcElementType, "IfcStair")) {
		Ifc4::IfcStair* stair = new Ifc4::IfcStair(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
			ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"),
			file.addLocalPlacement(), shape, string("$"), Ifc4::IfcStairTypeEnum::IfcStairType_NOTDEFINED);

		file.addBuildingProduct(stair);
		ifcElementBundle->setIfcElement(stair);
	}


	else {
		if (ifcElementBundle->getHasElementConnection())
		{
			Ifc4::IfcDistributionElement * ifcDistributionElem = buildIfcDistributionElement(ifcElementBundle, shape, file);
			file.addBuildingProduct(ifcDistributionElem);

			ifcElementBundle->setIfcElement(ifcDistributionElem);
		}
		else {
			Ifc4::IfcElement* ifcElement = buildIfcElement(ifcElementBundle, shape, file);
			file.addBuildingProduct(ifcElement);

			ifcElementBundle->setIfcElement(ifcElement);
		}
	}
}

Ifc4::IfcElement * IfcElementBuilder::buildIfcElement(IfcElementBundle *& ifcElementBundle, Ifc4::IfcProductDefinitionShape * elemShape, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcElement* ifcElement = new Ifc4::IfcElement(
		guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
		//file.getSingle<Ifc4::IfcOwnerHistory>(),
		ownerHistory,
		ifcElementBundle->getModelerElementDescriptor(),
		ifcElementBundle->getModelerElementDescriptor(),
		//boost::none,
		string("$"),
		file.addLocalPlacement(),
		elemShape, 
		//boost::none
		string("$")
	);

	return ifcElement;
}

Ifc4::IfcDistributionElement * IfcElementBuilder::buildIfcDistributionElement(IfcElementBundle *& ifcElementBundle, Ifc4::IfcProductDefinitionShape * elemShape, IfcHierarchyHelper<Ifc4>& file)
{
	//Create the pipe as IfcDistributionElement
	Ifc4::IfcDistributionElement* ifcDistributionElem = new Ifc4::IfcDistributionElement(
		guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
		//file.getSingle<Ifc4::IfcOwnerHistory>(),
		ownerHistory,
		ifcElementBundle->getModelerElementDescriptor(),
		ifcElementBundle->getModelerElementDescriptor(),
		//boost::none,
		string("$"),
		file.addLocalPlacement(),
		elemShape,
		//boost::none
		string("$")
	);	

	return ifcDistributionElem;
}

string IfcElementBuilder::getIfcElement(vector<ComponentsMappingDTO*> componentsMapping, string elementDescription)
{
	istringstream iss(elementDescription);
	vector<string> elementWords{ istream_iterator<string>{iss}, istream_iterator<string>{} };

	for each (string element in elementWords)
	{
		for each (ComponentsMappingDTO* mapping in componentsMapping)
		{
			if (boost::iequals(element, mapping->getModelerComponentName())) {
				return mapping->getIfcComponentName();
			}
		}
	}
	return string();
}
