#include "../headers/IfcBuilder.h"


void IfcBuilder::buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{	
	typedef Ifc4::IfcGloballyUniqueId guid;
	
	std::string name = "Test-" + dictionaryPropertiesVector[0]->getElementDescriptor();
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	std::string filename = SessionManager::getInstance()->getIfcOutputFilePath();
	
	//DEV CREDIT
	Ifc4::IfcActorRole* appActorRole1 = new Ifc4::IfcActorRole(
		Ifc4::IfcRoleEnum::IfcRole_ENGINEER,
		std::string("Software Developer"),
		std::string("Stefano Beccaletto")
	);

	Ifc4::IfcActorRole* appActorRole2 = new Ifc4::IfcActorRole(
		Ifc4::IfcRoleEnum::IfcRole_ENGINEER,
		std::string("Software Developer"),
		std::string("Mario Pirau")
	);

	IfcTemplatedEntityList<Ifc4::IfcActorRole>* appListOfActor = new IfcTemplatedEntityList<Ifc4::IfcActorRole>();
	appListOfActor->push(appActorRole1);
	appListOfActor->push(appActorRole2);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcActorRole>> appActorList(appListOfActor);

	Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
	Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);

	// TODO [MP] review unit assigment
	IfcEntityList* entityList = new IfcEntityList();
	entityList->push(ifcUnitLength);
	entityList->push(ifcUnitAngle);
	boost::shared_ptr<IfcEntityList> unitEntity(entityList);

	Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);

	//NOTE The inherited attribute ContextType shall have one of the following recognized values: 'Sketch', 'Outline', 'Design', 'Detail', 'Model', 'Plan', 'NotDefined'.
	std::string representationIdentifier = "*";
	std::string representationContextType = "Model"; //This is related to the specification of the context
	
	Ifc4::IfcDirection* trueNorthDirection = new Ifc4::IfcDirection(std::vector<double>{ 0.0, 1.0}); //This describe a plane and is 2D

	Ifc4::IfcAxis2Placement3D* originAndAxisPlacement = new Ifc4::IfcAxis2Placement3D(
		file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0),
		file.addTriplet<Ifc4::IfcDirection>(0, 0, 1), // Z direction
		file.addTriplet<Ifc4::IfcDirection>(1, 0, 0) 
	);

	//http://standards.buildingsmart.org/MVD/RELEASE/IFC4/ADD2_TC1/RV1_2/HTML/schema/ifcrepresentationresource/lexical/ifcgeometricrepresentationcontext.htm
	Ifc4::IfcGeometricRepresentationContext* geometricContext = new Ifc4::IfcGeometricRepresentationContext(
		representationIdentifier,
		representationContextType,
		3,
		1.0E-03, //1.0E-05
		//file.addTriplet<Ifc4::IfcAxis2Placement3D>(4,4,4),
		originAndAxisPlacement,
		trueNorthDirection
	);

	IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>* listContext = new IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>();
	listContext->push(geometricContext);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>> representationContextList(listContext);
	
	//TODO[SB] Set up owner History
	Ifc4::IfcAddress* address = new Ifc4::IfcAddress(
		Ifc4::IfcAddressTypeEnum::IfcAddressType_OFFICE,
		std::string("$"),
		std::string("$")
	);

	IfcTemplatedEntityList<Ifc4::IfcAddress>* listOfAddresses = new IfcTemplatedEntityList<Ifc4::IfcAddress>();
	listOfAddresses->push(address);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcAddress>> addressList(listOfAddresses);

	Ifc4::IfcPerson* person = new Ifc4::IfcPerson(
		std::string("Software Developer"),
		std::string("Soft"),
		std::string("Deve"),
		std::vector<std::string>{"Loper"},
		std::vector<std::string>{"$"},
		std::vector<std::string>{"$"},
		appActorList,
		addressList
	);

	Ifc4::IfcOrganization* organization = new Ifc4::IfcOrganization(
		std::string("Tractebel Belgium"),
		std::string("Tractebel Belgium - ENGIE group"),
		std::string("$"),
		appActorList,
		addressList
	);

	Ifc4::IfcPersonAndOrganization* personAndOrganization = new Ifc4::IfcPersonAndOrganization(
		person,
		organization,
		appActorList
	);
	
	Ifc4::IfcApplication* application = new Ifc4::IfcApplication(
		organization,
		std::string("Beta 1.0"),
		std::string("Bentley IFC Exporter"),
		std::string("Bentley-IFC-Exp")
	);

	// Current date/time based on current system
	time_t currentTimeNow = time(0);

	Ifc4::IfcOwnerHistory* ownerHistory = new Ifc4::IfcOwnerHistory(
		personAndOrganization,
		application,
		Ifc4::IfcStateEnum::IfcState_READWRITE,
		Ifc4::IfcChangeActionEnum::IfcChangeAction_NOCHANGE,
		currentTimeNow, //last mod
		personAndOrganization,
		application,
		currentTimeNow //creation date
	);

	Ifc4::IfcProject* project = new Ifc4::IfcProject(
		guid::IfcGloballyUniqueId(name), 
		ownerHistory,
		//file.getSingle<Ifc4::IfcOwnerHistory>(), 
		std::string("OpenPlant IFC Exporter"), 
		std::string("$"),
		std::string("$"),
		std::string("$"),
		std::string("$"),
		representationContextList,
		unitAssigment
	);

	Ifc4::IfcObjectPlacement* objectPlacement = file.addLocalPlacement();

	/*Ifc4::IfcBuildingStorey* buildingStorey = new Ifc4::IfcBuildingStorey(
		guid::IfcGloballyUniqueId("Test Building Storey"),
		ownerHistory,
		std::string(name),
		std::string("$"),
		std::string("$"),
		objectPlacement,

	);*/

	//Ifc4::IfcBuilding* building = new Ifc4::IfcBuilding()

	file.addEntity(project);

	// initialize ifc bundle vector
	std::vector<IfcElementBundle*>ifcElementBundleVector;
	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			IfcElementBundle* ifcElementBundle = new IfcElementBundle(dictionaryProperties.getElementId(), dictionaryProperties.getElementDescriptor());

			ifcElementBundle->setIsSmartSolid(dictionaryProperties.getIsSmartSolid());

			if (dictionaryProperties.getIsSmartSolid() || dictionaryProperties.getIsPrimitiveSolid()) {
				ifcElementBundle->solidModel = true;
			}

			ifcElementBundle->setSmartFeatureContainer(dictionaryProperties.getSmartFeatureContainer());
			// TODO [MP] to be replaced with a copy contructor or delete dicionary properties and only keep ifc element bundle
			for (auto const& readerProperty : dictionaryProperties.getElementReaderPropertiesBundleVector()) {
				ReaderPropertiesBundle* readerPropertiesBundle = new ReaderPropertiesBundle(readerProperty->getCassName(), readerProperty->getLocalId());
				for (auto const& property1 : readerProperty->getProperties()) {
					ReaderPropertyDefinition* readerPropertyDefinition = new ReaderPropertyDefinition(property1->getPropertyName(), property1->getPropertyTypeName()
						, property1->getPropertyValue(), property1->getPropertyValueAsString());
					readerPropertiesBundle->addProperty(readerPropertyDefinition);

				}
				ifcElementBundle->addIfcElementReaderPropertiesBundle(new IfcReaderPropertiesBundle(readerPropertiesBundle));


			}
			ifcElementBundleVector.push_back(ifcElementBundle);
		}
	}

	IfcPrimitivesEnhancer* ifcPrimitivesEnhancer = new IfcPrimitivesEnhancer();
	ifcPrimitivesEnhancer->enhanceIfcPrimitives(dictionaryPropertiesVector,ifcElementBundleVector, file);

	IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
	ifcShapesEnhancer->enhanceIfcShapesPrimitives(dictionaryPropertiesVector, ifcElementBundleVector, file);

	//TODO [MP] solve the issue
	//SmartFeatureHandler* smartFeatureHandler = new SmartFeatureHandler();
	//smartFeatureHandler->handleSmartFeature(ifcElementBundleVector,file);

	IfcBRepSolidsEnhancer* ifcBRepSolidsEnhancer = new IfcBRepSolidsEnhancer();
	ifcBRepSolidsEnhancer->enhanceIfcBRepSolidsEnhancer(dictionaryPropertiesVector, ifcElementBundleVector, file);
	
	IfcElementBuilder* ifcElementBuilder = new IfcElementBuilder(geometricContext, ownerHistory, objectPlacement);
	ifcElementBuilder->processIfcElement(ifcElementBundleVector, file);
		
	IfcPropertiesEnhancer* ifcPropertiesEnhancer = new IfcPropertiesEnhancer();
	ifcPropertiesEnhancer->enhanceIfcProperties(dictionaryPropertiesVector, ifcElementBundleVector, file);

	IfcColorEnhancer* ifcColorEnhancer = new IfcColorEnhancer();
	ifcColorEnhancer->enhanceColors(ifcElementBundleVector, file);

	IfcPortsBuilder* ifcPortsBuilder = new IfcPortsBuilder(geometricContext, ownerHistory);
	ifcPortsBuilder->processIfcPorts(ifcElementBundleVector, file);
				
	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();

}
