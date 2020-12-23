#include "../headers/IfcElementBuilder.h"

#if true
IfcElementBuilder::IfcElementBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory, Ifc4::IfcObjectPlacement* objectPlacement)
{
	this->geometricRepresentationContext = geomContext;
	this->ownerHistory = ownerHistory;
	this->objectPlacement = objectPlacement;

	this->_componentsMappingService = new ComponentsMappingService(Logs::Logger::getLogger());
}

void IfcElementBuilder::processIfcElement(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file, map<LevelId, IfcEntityList*> levelFileEntities)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	vector<ComponentsMappingDTO*> componentsMappings = this->_componentsMappingService->getAll();
			
	//Create the vector for the distribution element 
	//vector<IfcElementBundle*>ifcDistributionBundleVector;
	for (auto& ifcElementBundle : ifcBundleVector) //const& removed
	{
		if (ifcElementBundle->getBadIfcClassBuild())
		{
			_logger->logError(__FILE__, __LINE__, __func__, ifcElementBundle->getElementDescriptor() + " " + to_string(ifcElementBundle->getElementId()) + " IFC Element is Nullptr, ElementBundle bad flag");
			continue;
		}
		ComponentsMappingDTO* mappedValue = getIfcElement(componentsMappings, ifcElementBundle->getElementDescriptor());
		
		Ifc4::IfcRepresentation::list::ptr ifcShapeRepresentationList(new Ifc4::IfcRepresentation::list());

		for (auto const& ifcGraphicPropertiesBundle : ifcElementBundle->getIfcGraphicPropertiesBundleVector()) 
		{

			Ifc4::IfcRepresentationItem::list::ptr ifcRepresentationItemList(new Ifc4::IfcRepresentationItem::list());

			//if (ifcGraphicPropertiesBundle->getIfcRepresentationItem() != nullptr && ifcGraphicPropertiesBundle->getShow())
			if (ifcGraphicPropertiesBundle->isValid() && ifcGraphicPropertiesBundle->getShow())
			{
				
				ifcRepresentationItemList->push(ifcGraphicPropertiesBundle->getIfcRepresentationItem());

				//TODO: Needs to be set up correctly the 3rd input parameter following:
				//https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcrepresentationresource/lexical/ifcshaperepresentation.htm
				string representationType = ifcGraphicPropertiesBundle->getRepresentationType();
				string representationIdentifier = ifcGraphicPropertiesBundle->getRepresentationIdentifier();
				
				//NOTE  The provision of a model view (IfcGeometricRepresentationContext.ContextType = 'Model') is mandatory. Instances of IfcGeometricRepresentationSubContext relate to it as its ParentContext.
				Ifc4::IfcGeometricRepresentationSubContext* geometricSubContext = new Ifc4::IfcGeometricRepresentationSubContext(
					representationIdentifier,
					geometricRepresentationContext->ContextType(),
					geometricRepresentationContext,
					boost::none,
					Ifc4::IfcGeometricProjectionEnum::IfcGeometricProjection_MODEL_VIEW,
					boost::none
				);


				Ifc4::IfcShapeRepresentation* ifcShapeRepresentation = new Ifc4::Ifc4::IfcShapeRepresentation(
					geometricSubContext,
					representationIdentifier,
					representationType,
					ifcRepresentationItemList
				);

				ifcShapeRepresentationList->push(ifcShapeRepresentation);

				try
				{
					if (ifcGraphicPropertiesBundle->getLevelHandle().IsValid())
					{
						IfcEntityList* entityLevel = levelFileEntities.at(ifcGraphicPropertiesBundle->getLevelHandle()->GetLevelId());

						entityLevel->push(ifcShapeRepresentation);
					}
					else
						_logger->logInfo(__FILE__, __LINE__, __func__, "Level Not Valid");
				}
				catch (exception& ex) {
					_logger->logError(__FILE__, __LINE__, __func__, ex, "Error Layer Entity " + string(ex.what()));
				}
			}
			else
			{
				_logger->logWarning(__FILE__, __LINE__, __func__, ifcElementBundle->getElementDescriptor() + " " + to_string(ifcElementBundle->getElementId()) + " ifcGraphicPropertiesBundle is Not Valid - Show: " + to_string(ifcGraphicPropertiesBundle->getShow()));
			}
		}
		if (ifcShapeRepresentationList->size() == 0) {
			_logger->logWarning(__FILE__, __LINE__, __func__, ifcElementBundle->getElementDescriptor() + " " + to_string(ifcElementBundle->getElementId()) + " IFC ifcShapeRepresentationList is Empty, ElementBundle bad flag");
			//ifcElementBundle->setBadIfcClassBuild(true);
			//continue;
		}
			

		Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(
			boost::none,
			boost::none,
			ifcShapeRepresentationList
		);

		Ifc4::IfcElement* ifcElement = handleIfcElementCreation(mappedValue, shape, ifcElementBundle, file);

		if (ifcElement == nullptr)
		{
			_logger->logError(__FILE__, __LINE__, __func__, ifcElementBundle->getElementDescriptor() + " " + to_string(ifcElementBundle->getElementId()) + " IFC Element is Nullptr, ElementBundle bad flag");
			
			ifcElementBundle->setBadIfcClassBuild(true);
			ifcElementBundle->setIfcElement(ifcElement);
		}
		else
		{
			file.addEntity(shape);

			file.addEntity(ifcElement);

			ifcElementBundle->setIfcElement(ifcElement);
		}
	}
	
}


Ifc4::IfcElement* IfcElementBuilder::handleIfcElementCreation(ComponentsMappingDTO* mappedValue,Ifc4::IfcProductDefinitionShape* shape,	IfcElementBundle* ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__, ifcElementBundle->getElementDescriptor() + " " + to_string(ifcElementBundle->getElementId()));

	//if (ifcElementBundle->getModelerElementId() == 60897)
	//	_logger->logInfo(__FILE__, __LINE__, __func__, "!- BAD elements processing -!");

	Ifc4::IfcElement* ifcElement = nullptr;
	if (mappedValue->getIfcComponentTypeName().empty()) {
		ifcElement = buildIfcElement(ifcElementBundle, shape, file);
	}

	else {
		if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::IfcDistributionElement).name())) || ifcElementBundle->getHasElementConnection())
		{
			ifcElement = handleIfcDistributionElement(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::IfcBuildingElement).name())))
		{
			ifcElement = handleIfcBuildingElement(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::Ifc4::IfcCivilElement).name()))) 
		{
			ifcElement = handleIfcCivilElement(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::Ifc4::IfcElementAssembly).name())))
		{
			ifcElement = handleIfcElementAssembly(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::Ifc4::IfcElementComponent).name())))
		{
			ifcElement = handleIfcElementComponent(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::Ifc4::IfcFeatureElement).name())))
		{
			ifcElement = handleIfcFeatureElement(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::Ifc4::IfcFurnishingElement).name())))
		{
			ifcElement = handleIfcFurnishingElement(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::Ifc4::IfcGeographicElement).name())))
		{
			ifcElement = handleIfcGeographicElement(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::Ifc4::IfcTransportElement).name())))
		{
			ifcElement = handleIfcTransportElement(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}
		else if (boost::iequals(mappedValue->getIfcComponentTypeName(), StringUtils::getIfcClassName(typeid(Ifc4::Ifc4::IfcVirtualElement).name())))
		{
			ifcElement = handleIfcVirtualElement(mappedValue->getIfcComponentName(), shape, ifcElementBundle, file);
		}

		else {
			ifcElement = buildIfcElement(ifcElementBundle, shape, file);
		}
	}

	return ifcElement;
}

Ifc4::IfcBuildingElement* IfcElementBuilder::handleIfcBuildingElement(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcBuildingElement* buildingElement = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcBeam).name()))) {
		buildingElement = new Ifc4::IfcBeam(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcBeamTypeEnum::IfcBeamType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcBuildingElementProxy).name()))) {
		buildingElement = new Ifc4::IfcBuildingElementProxy(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcBuildingElementProxyTypeEnum::IfcBuildingElementProxyType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcChimney).name()))) {
		buildingElement = new Ifc4::IfcChimney(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcChimneyTypeEnum::IfcChimneyType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcColumn).name()))) {
		buildingElement = new Ifc4::IfcColumn(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcColumnTypeEnum::IfcColumnType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCovering).name()))) {
		buildingElement = new Ifc4::IfcCovering(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCoveringTypeEnum::IfcCoveringType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCurtainWall).name()))) {
		buildingElement = new Ifc4::IfcCurtainWall(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCurtainWallTypeEnum::IfcCurtainWallType_NOTDEFINED);

	}
	// TODO add door measurements
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDoor).name()))) {
		buildingElement = new Ifc4::IfcDoor(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, 2, 3, Ifc4::IfcDoorTypeEnum::IfcDoorType_NOTDEFINED,
			Ifc4::IfcDoorTypeOperationEnum::IfcDoorTypeOperation_NOTDEFINED, boost::none);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFooting).name()))) {
		buildingElement = new Ifc4::IfcFooting(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcFootingTypeEnum::IfcFootingType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcMember).name()))) {
		buildingElement = new Ifc4::IfcMember(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcMemberTypeEnum::IfcMemberType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcPile).name()))) {
		buildingElement = new Ifc4::IfcPile(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcPileTypeEnum::IfcPileType_NOTDEFINED,
			Ifc4::IfcPileConstructionEnum::IfcPileConstruction_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcPlate).name()))) {
		buildingElement = new Ifc4::IfcPlate(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcPlateTypeEnum::IfcPlateType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcRailing).name()))) {
		buildingElement = new Ifc4::IfcRailing(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcRailingTypeEnum::IfcRailingType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcRamp).name()))) {
		buildingElement = new Ifc4::IfcRamp(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcRampTypeEnum::IfcRampType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcRampFlight).name()))) {
		buildingElement = new Ifc4::IfcRampFlight(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcRampFlightTypeEnum::IfcRampFlightType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcRoof).name()))) {
		buildingElement = new Ifc4::IfcRoof(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcRoofTypeEnum::IfcRoofType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcShadingDevice).name()))) {
		buildingElement = new Ifc4::IfcShadingDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcShadingDeviceTypeEnum::IfcShadingDeviceType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcSlab).name()))) {
		buildingElement = new Ifc4::IfcSlab(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcSlabTypeEnum::IfcSlabType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcStair).name()))) {
		buildingElement = new Ifc4::IfcStair(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcStairTypeEnum::IfcStairType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcStairFlight).name()))) {
		// TODO get lenght measures and replace the dummies
		buildingElement = new Ifc4::IfcStairFlight(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, 1, 1, 1.0, 1.0, Ifc4::IfcStairFlightTypeEnum::IfcStairFlightType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcWall).name()))) {
		buildingElement = new Ifc4::IfcWall(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none,  Ifc4::IfcWallTypeEnum::IfcWallType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcWindow).name()))) {
		// TODO get lenght measures and replace the dummies
		buildingElement = new Ifc4::IfcWindow(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none,1,1, Ifc4::IfcWindowTypeEnum::IfcWindowType_NOTDEFINED, 
			Ifc4::IfcWindowTypePartitioningEnum::IfcWindowTypePartitioning_NOTDEFINED, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcBuildingElement).name()))) {
		// TODO get lenght measures and replace the dummies
		buildingElement = new Ifc4::IfcBuildingElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}

	return buildingElement;


}

Ifc4::IfcCivilElement * IfcElementBuilder::handleIfcCivilElement(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcCivilElement* civilElement = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCivilElement).name()))) {
		civilElement = new Ifc4::IfcCivilElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);

	}

	return civilElement;
}

Ifc4::IfcDistributionElement* IfcElementBuilder::handleIfcDistributionElement(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcDistributionElement* distributionElement = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcActuator).name()))) {
		distributionElement = new Ifc4::IfcActuator(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcActuatorTypeEnum::IfcActuatorType_NOTDEFINED);

	} 
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcAirTerminal).name()))) {
		distributionElement = new Ifc4::IfcAirTerminal(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcAirTerminalTypeEnum::IfcAirTerminalType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcAirTerminalBox).name()))) {
		distributionElement = new Ifc4::IfcAirTerminalBox(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcAirToAirHeatRecovery).name()))) {
		distributionElement = new Ifc4::IfcAirToAirHeatRecovery(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcAirToAirHeatRecoveryTypeEnum::IfcAirToAirHeatRecoveryType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcAlarm).name()))) {
		distributionElement = new Ifc4::IfcAlarm(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcAlarmTypeEnum::IfcAlarmType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcAudioVisualAppliance).name()))) {
		distributionElement = new Ifc4::IfcAudioVisualAppliance(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcAudioVisualApplianceTypeEnum::IfcAudioVisualApplianceType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcBoiler).name()))) {
		distributionElement = new Ifc4::IfcBoiler(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcBoilerTypeEnum::IfcBoilerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcBurner).name()))) {
		distributionElement = new Ifc4::IfcBurner(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcBurnerTypeEnum::IfcBurnerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCableCarrierFitting).name()))) {
		distributionElement = new Ifc4::IfcCableCarrierFitting(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCableCarrierFittingTypeEnum::IfcCableCarrierFittingType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCableCarrierSegment).name()))) {
		distributionElement = new Ifc4::IfcCableCarrierSegment(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCableCarrierSegmentTypeEnum::IfcCableCarrierSegmentType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCableFitting).name()))) {
		distributionElement = new Ifc4::IfcCableFitting(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCableFittingTypeEnum::IfcCableFittingType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCableSegment).name()))) {
		distributionElement = new Ifc4::IfcCableSegment(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCableSegmentTypeEnum::IfcCableSegmentType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcChiller).name()))) {
		distributionElement = new Ifc4::IfcChiller(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcChillerTypeEnum::IfcChillerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCoil).name()))) {
		distributionElement = new Ifc4::IfcCoil(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCoilTypeEnum::IfcCoilType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCommunicationsAppliance).name()))) {
		distributionElement = new Ifc4::IfcCommunicationsAppliance(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCompressor).name()))) {
		distributionElement = new Ifc4::IfcCompressor(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCompressorTypeEnum::IfcCompressorType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCondenser).name()))) {
		distributionElement = new Ifc4::IfcCondenser(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCondenserTypeEnum::IfcCondenserType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcController).name()))) {
		distributionElement = new Ifc4::IfcController(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcControllerTypeEnum::IfcControllerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCooledBeam).name()))) {
		distributionElement = new Ifc4::IfcCooledBeam(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCooledBeamTypeEnum::IfcCooledBeamType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcCoolingTower).name()))) {
		distributionElement = new Ifc4::IfcCoolingTower(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcCoolingTowerTypeEnum::IfcCoolingTowerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDamper).name()))) {
		distributionElement = new Ifc4::IfcDamper(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcDamperTypeEnum::IfcDamperType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDamper).name()))) {
		distributionElement = new Ifc4::IfcDamper(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcDamperTypeEnum::IfcDamperType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDistributionChamberElement).name()))) {
		distributionElement = new Ifc4::IfcDistributionChamberElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcDistributionChamberElementTypeEnum::IfcDistributionChamberElementType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDistributionControlElement).name()))) {
		distributionElement = new Ifc4::IfcDistributionControlElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDistributionFlowElement).name()))) {
		distributionElement = new Ifc4::IfcDistributionFlowElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDuctFitting).name()))) {
		distributionElement = new Ifc4::IfcDuctFitting(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcDuctFittingTypeEnum::IfcDuctFittingType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDuctSilencer).name()))) {
		distributionElement = new Ifc4::IfcDuctSilencer(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcDuctSilencerTypeEnum::IfcDuctSilencerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcElectricAppliance).name()))) {
		distributionElement = new Ifc4::IfcElectricAppliance(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcElectricApplianceTypeEnum::IfcElectricApplianceType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcElectricDistributionBoard).name()))) {
		distributionElement = new Ifc4::IfcElectricDistributionBoard(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcElectricFlowStorageDevice).name()))) {
		distributionElement = new Ifc4::IfcElectricFlowStorageDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcElectricGenerator).name()))) {
		distributionElement = new Ifc4::IfcElectricGenerator(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcElectricGeneratorTypeEnum::IfcElectricGeneratorType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcElectricMotor).name()))) {
		distributionElement = new Ifc4::IfcElectricMotor(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcElectricMotorTypeEnum::IfcElectricMotorType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcElectricTimeControl).name()))) {
		distributionElement = new Ifc4::IfcElectricTimeControl(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcElectricTimeControlTypeEnum::IfcElectricTimeControlType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcEnergyConversionDevice).name()))) {
		distributionElement = new Ifc4::IfcEnergyConversionDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcEngine).name()))) {
		distributionElement = new Ifc4::IfcEngine(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none,Ifc4::IfcEngineTypeEnum::IfcEngineType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcEvaporativeCooler).name()))) {
		distributionElement = new Ifc4::IfcEvaporativeCooler(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcEvaporativeCoolerTypeEnum::IfcEvaporativeCoolerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcEvaporator).name()))) {
		distributionElement = new Ifc4::IfcEvaporator(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcEvaporatorTypeEnum::IfcEvaporatorType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFan).name()))) {
		distributionElement = new Ifc4::IfcFan(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcFanTypeEnum::IfcFanType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFilter).name()))) {
		distributionElement = new Ifc4::IfcFilter(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcFilterTypeEnum::IfcFilterType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFireSuppressionTerminal).name()))) {
		distributionElement = new Ifc4::IfcFireSuppressionTerminal(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcFireSuppressionTerminalTypeEnum::IfcFireSuppressionTerminalType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFlowController).name()))) {
		distributionElement = new Ifc4::IfcFlowController(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFlowInstrument).name()))) {
		distributionElement = new Ifc4::IfcFlowInstrument(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcFlowInstrumentTypeEnum::IfcFlowInstrumentType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFlowMeter).name()))) {
		distributionElement = new Ifc4::IfcFlowMeter(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcFlowMeterTypeEnum::IfcFlowMeterType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFlowMovingDevice).name()))) {
		distributionElement = new Ifc4::IfcFlowMovingDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFlowSegment).name()))) {
		distributionElement = new Ifc4::IfcFlowSegment(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFlowStorageDevice).name()))) {
		distributionElement = new Ifc4::IfcFlowStorageDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFlowTerminal).name()))) {
		distributionElement = new Ifc4::IfcFlowTerminal(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFlowTreatmentDevice).name()))) {
		distributionElement = new Ifc4::IfcFlowTreatmentDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcHeatExchanger).name()))) {
		distributionElement = new Ifc4::IfcHeatExchanger(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcHeatExchangerTypeEnum::IfcHeatExchangerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcHumidifier).name()))) {
		distributionElement = new Ifc4::IfcHumidifier(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcHumidifierTypeEnum::IfcHumidifierType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcInterceptor).name()))) {
		distributionElement = new Ifc4::IfcInterceptor(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcInterceptorTypeEnum::IfcInterceptorType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcJunctionBox).name()))) {
		distributionElement = new Ifc4::IfcJunctionBox(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcJunctionBoxTypeEnum::IfcJunctionBoxType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcLamp).name()))) {
		distributionElement = new Ifc4::IfcLamp(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcLampTypeEnum::IfcLampType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcLightFixture).name()))) {
		distributionElement = new Ifc4::IfcLightFixture(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcLightFixtureTypeEnum::IfcLightFixtureType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcMedicalDevice).name()))) {
		distributionElement = new Ifc4::IfcMedicalDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcMedicalDeviceTypeEnum::IfcMedicalDeviceType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcMotorConnection).name()))) {
		distributionElement = new Ifc4::IfcMotorConnection(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcMotorConnectionTypeEnum::IfcMotorConnectionType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcOutlet).name()))) {
		distributionElement = new Ifc4::IfcOutlet(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcOutletTypeEnum::IfcOutletType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcPipeFitting).name()))) {
		distributionElement = new Ifc4::IfcPipeFitting(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcPipeFittingTypeEnum::IfcPipeFittingType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcPipeSegment).name()))) {
		distributionElement = new Ifc4::IfcPipeSegment(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcPipeSegmentTypeEnum::IfcPipeSegmentType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcProtectiveDevice).name()))) {
		distributionElement = new Ifc4::IfcProtectiveDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcProtectiveDeviceTrippingUnit).name()))) {
		distributionElement = new Ifc4::IfcProtectiveDeviceTrippingUnit(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcPump).name()))) {
		distributionElement = new Ifc4::IfcPump(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcPumpTypeEnum::IfcPumpType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcSanitaryTerminal).name()))) {
		distributionElement = new Ifc4::IfcSanitaryTerminal(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcSanitaryTerminalTypeEnum::IfcSanitaryTerminalType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcSensor).name()))) {
		distributionElement = new Ifc4::IfcSensor(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcSensorTypeEnum::IfcSensorType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcSolarDevice).name()))) {
		distributionElement = new Ifc4::IfcSolarDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcSolarDeviceTypeEnum::IfcSolarDeviceType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcSpaceHeater).name()))) {
		distributionElement = new Ifc4::IfcSpaceHeater(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcSpaceHeaterTypeEnum::IfcSpaceHeaterType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcStackTerminal).name()))) {
		distributionElement = new Ifc4::IfcStackTerminal(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcStackTerminalTypeEnum::IfcStackTerminalType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcSwitchingDevice).name()))) {
		distributionElement = new Ifc4::IfcSwitchingDevice(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcTank).name()))) {
		distributionElement = new Ifc4::IfcTank(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcTankTypeEnum::IfcTankType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcTransformer).name()))) {
		distributionElement = new Ifc4::IfcTransformer(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcTransformerTypeEnum::IfcTransformerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcTubeBundle).name()))) {
		distributionElement = new Ifc4::IfcTubeBundle(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcTubeBundleTypeEnum::IfcTubeBundleType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcUnitaryControlElement).name()))) {
		distributionElement = new Ifc4::IfcUnitaryControlElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcUnitaryEquipment).name()))) {
		distributionElement = new Ifc4::IfcUnitaryEquipment(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcUnitaryEquipmentTypeEnum::IfcUnitaryEquipmentType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcValve).name()))) {
		distributionElement = new Ifc4::IfcValve(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcValveTypeEnum::IfcValveType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcWasteTerminal).name()))) {
		distributionElement = new Ifc4::IfcWasteTerminal(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcWasteTerminalTypeEnum::IfcWasteTerminalType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDistributionElement).name()))) {
		distributionElement = new Ifc4::IfcDistributionElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}

	return distributionElement;
	
}

Ifc4::IfcElementAssembly * IfcElementBuilder::handleIfcElementAssembly(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcElementAssembly* elementAssembly = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcElementAssembly).name()))) {
		elementAssembly = new Ifc4::IfcElementAssembly(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcAssemblyPlaceEnum::IfcAssemblyPlace_NOTDEFINED,
			Ifc4::IfcElementAssemblyTypeEnum::IfcElementAssemblyType_NOTDEFINED);

	}

	return elementAssembly;
}

Ifc4::IfcElementComponent * IfcElementBuilder::handleIfcElementComponent(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcElementComponent* elementComponent = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcBuildingElementPart).name()))) {
		elementComponent = new Ifc4::IfcBuildingElementPart(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcBuildingElementPartTypeEnum::IfcBuildingElementPartType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcDiscreteAccessory).name()))) {
		elementComponent = new Ifc4::IfcDiscreteAccessory(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcDiscreteAccessoryTypeEnum::IfcDiscreteAccessoryType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFastener).name()))) {
		elementComponent = new Ifc4::IfcFastener(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcFastenerTypeEnum::IfcFastenerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcMechanicalFastener).name()))) {
		// TODO replace the measurement values
		elementComponent = new Ifc4::IfcMechanicalFastener(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none,0,0, Ifc4::IfcMechanicalFastenerTypeEnum::IfcMechanicalFastenerType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcReinforcingBar).name()))) {
		// TODO replace the measurement values
		elementComponent = new Ifc4::IfcReinforcingBar(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, boost::none,0,0,0, Ifc4::IfcReinforcingBarTypeEnum::IfcReinforcingBarType_NOTDEFINED,
			Ifc4::IfcReinforcingBarSurfaceEnum::IfcReinforcingBarSurface_PLAIN);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcReinforcingElement).name()))) {
		elementComponent = new Ifc4::IfcReinforcingElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcReinforcingMesh).name()))) {
		// TODO replace the measurement values
		elementComponent = new Ifc4::IfcReinforcingMesh(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, boost::none,0,0,0,0,0,0,0,0,Ifc4::IfcReinforcingMeshTypeEnum::IfcReinforcingMeshType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcTendon).name()))) {
		// TODO replace the measurement values
		elementComponent = new Ifc4::IfcTendon(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, boost::none, Ifc4::IfcTendonTypeEnum::IfcTendonType_NOTDEFINED,0,0,0,0,0,0,0);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcTendonAnchor).name()))) {
		elementComponent = new Ifc4::IfcTendonAnchor(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, boost::none, Ifc4::IfcTendonAnchorTypeEnum::IfcTendonAnchorType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcVibrationIsolator).name()))) {
		elementComponent = new Ifc4::IfcVibrationIsolator(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcVibrationIsolatorTypeEnum::IfcVibrationIsolatorType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcElementComponent).name()))) {
		elementComponent = new Ifc4::IfcElementComponent(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}

	return elementComponent;
}

Ifc4::IfcFeatureElement * IfcElementBuilder::handleIfcFeatureElement(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcFeatureElement* featureElement = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFeatureElementAddition).name()))) {
		featureElement = new Ifc4::IfcFeatureElementAddition(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFeatureElementSubtraction).name()))) {
		featureElement = new Ifc4::IfcFeatureElementSubtraction(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcOpeningElement).name()))) {
		featureElement = new Ifc4::IfcOpeningElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcOpeningElementTypeEnum::IfcOpeningElementType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcOpeningStandardCase).name()))) {
		featureElement = new Ifc4::IfcOpeningStandardCase(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcOpeningElementTypeEnum::IfcOpeningElementType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcProjectionElement).name()))) {
		featureElement = new Ifc4::IfcProjectionElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcProjectionElementTypeEnum::IfcProjectionElementType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcSurfaceFeature).name()))) {
		featureElement = new Ifc4::IfcSurfaceFeature(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcSurfaceFeatureTypeEnum::IfcSurfaceFeatureType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcVoidingFeature).name()))) {
		featureElement = new Ifc4::IfcVoidingFeature(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcVoidingFeatureTypeEnum::IfcVoidingFeatureType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFeatureElement).name()))) {
		featureElement = new Ifc4::IfcFeatureElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}

	return featureElement;
}

Ifc4::IfcFurnishingElement * IfcElementBuilder::handleIfcFurnishingElement(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcFurnishingElement* furnishingElement = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFurniture).name()))) {
		furnishingElement = new Ifc4::IfcFurniture(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcFurnitureTypeEnum::IfcFurnitureType_NOTDEFINED);

	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcSystemFurnitureElement).name()))) {
		furnishingElement = new Ifc4::IfcSystemFurnitureElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcSystemFurnitureElementTypeEnum::IfcSystemFurnitureElementType_NOTDEFINED);
	}
	else if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcFurnishingElement).name()))) {
		furnishingElement = new Ifc4::IfcFurnishingElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);
	}

	return furnishingElement;
}

Ifc4::IfcGeographicElement * IfcElementBuilder::handleIfcGeographicElement(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcGeographicElement* geographicElement = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcGeographicElement).name()))) {
		geographicElement = new Ifc4::IfcGeographicElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcGeographicElementTypeEnum::IfcGeographicElementType_NOTDEFINED);

	}

	return geographicElement;
}

Ifc4::IfcTransportElement * IfcElementBuilder::handleIfcTransportElement(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcTransportElement* transportElement = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcTransportElement).name()))) {
		transportElement = new Ifc4::IfcTransportElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none, Ifc4::IfcTransportElementTypeEnum::IfcTransportElementType_NOTDEFINED);

	}

	return transportElement;
}

Ifc4::IfcVirtualElement * IfcElementBuilder::handleIfcVirtualElement(string ifcElement,Ifc4::IfcProductDefinitionShape * shape, IfcElementBundle * ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcVirtualElement* virtualElement = nullptr;
	if (boost::iequals(ifcElement, StringUtils::getIfcClassName(typeid(Ifc4::IfcVirtualElement).name()))) {
		virtualElement = new Ifc4::IfcVirtualElement(guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
			ownerHistory, elementClassName, elementDescription, boost::none,
			file.addLocalPlacement(objectPlacement), shape, boost::none);

	}

	return virtualElement;
}

Ifc4::IfcElement * IfcElementBuilder::buildIfcElement(IfcElementBundle *& ifcElementBundle, Ifc4::IfcProductDefinitionShape * elemShape, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	string elementDescription = ifcElementBundle->getElementDescriptor();
	string elementClassName = ifcElementBundle->getElementClassName();

	Ifc4::IfcElement* ifcElement = new Ifc4::IfcElement(
		guid::IfcGloballyUniqueId(to_string(ifcElementBundle->getElementId())),
		ownerHistory,
		elementDescription,
		elementDescription,
		boost::none,
		file.addLocalPlacement(objectPlacement),
		elemShape, 
		boost::none
	);

	return ifcElement;
}


ComponentsMappingDTO* IfcElementBuilder::getIfcElement(vector<ComponentsMappingDTO*> componentsMapping, string elementDescription)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	istringstream iss(elementDescription);
	vector<string> elementWords{ istream_iterator<string>{iss}, istream_iterator<string>{} };

	for each (string element in elementWords)
	{
		for each (ComponentsMappingDTO* mapping in componentsMapping)
		{
			if (boost::iequals(element, mapping->getModelerComponentName())) {
				return mapping;
			}
		}
	}
	return new ComponentsMappingDTO();
}
#endif
