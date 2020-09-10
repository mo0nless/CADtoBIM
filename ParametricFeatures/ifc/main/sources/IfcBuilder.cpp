#include "../headers/IfcBuilder.h"


IfcBuilder::IfcBuilder()
{
	this->_ifcPrimitivesEnhancer = new IfcPrimitivesEnhancer();
	this->_ifcShapesEnhancer = new IfcShapesEnhancer();
	this->_ifcBRepSolidsEnhancer = new IfcBRepSolidsEnhancer();
	this->_ifcPropertiesEnhancer = new IfcPropertiesEnhancer();
	this->_IfcColorMaterialEnhancer = new IfcColorMaterialEnhancer();
	this->_ifcSurfaceEnhancer = new IfcSurfaceEnhancer();

}

void IfcBuilder::buildIfc(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{	
	typedef Ifc4::IfcGloballyUniqueId guid;
	
	string name = "Test-" + dictionaryPropertiesVector[0]->getElementDescriptor();
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	string filename = SessionManager::getInstance()->getIfcOutputFilePath();
	
	//DEV CREDIT
	Ifc4::IfcActorRole* appActorRole1 = new Ifc4::IfcActorRole(
		Ifc4::IfcRoleEnum::IfcRole_ENGINEER,
		string("Software Developer"),
		string("Stefano Beccaletto")
	);

	Ifc4::IfcActorRole* appActorRole2 = new Ifc4::IfcActorRole(
		Ifc4::IfcRoleEnum::IfcRole_ENGINEER,
		string("Software Developer"),
		string("Mario Pirau")
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
	string representationIdentifier = "*";
	string representationContextType = "Model"; //This is related to the specification of the context
	
	Ifc4::IfcDirection* trueNorthDirection = new Ifc4::IfcDirection(vector<double>{ 0.0, 1.0}); //This describe a plane and is 2D

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
		string("$"),
		string("$")
	);

	IfcTemplatedEntityList<Ifc4::IfcAddress>* listOfAddresses = new IfcTemplatedEntityList<Ifc4::IfcAddress>();
	listOfAddresses->push(address);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcAddress>> addressList(listOfAddresses);

	Ifc4::IfcPerson* person = new Ifc4::IfcPerson(
		string("Software Developer"),
		string("Soft"),
		string("Deve"),
		vector<string>{"Loper"},
		vector<string>{"$"},
		vector<string>{"$"},
		appActorList,
		addressList
	);

	Ifc4::IfcOrganization* organization = new Ifc4::IfcOrganization(
		string("Tractebel Belgium"),
		string("Tractebel Belgium - ENGIE group"),
		string("$"),
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
		string("Beta 1.0"),
		string("Bentley IFC Exporter"),
		string("Bentley-IFC-Exp")
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
		string("OpenPlant IFC Exporter"), 
		string("$"),
		string("$"),
		string("$"),
		string("$"),
		representationContextList,
		unitAssigment
	);

	Ifc4::IfcObjectPlacement* objectPlacement = file.addLocalPlacement();

	/*Ifc4::IfcBuildingStorey* buildingStorey = new Ifc4::IfcBuildingStorey(
		guid::IfcGloballyUniqueId("Test Building Storey"),
		ownerHistory,
		string(name),
		string("$"),
		string("$"),
		objectPlacement,

	);*/

	//Ifc4::IfcBuilding* building = new Ifc4::IfcBuilding()

	file.addEntity(project);

	// initialize ifc bundle vector
	vector<IfcElementBundle*>ifcElementBundleVector;
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

	//TODO [MP] solve the issue
	//SmartFeatureHandler* smartFeatureHandler = new SmartFeatureHandler();
	//smartFeatureHandler->handleSmartFeature(ifcElementBundleVector,file);

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcElementBundle*& ifcElementBundle = ifcElementBundleVector.at(i);

			//Ifc4::IfcRepresentationItem::list::ptr ifcTemplatedEntityList(new Ifc4::IfcRepresentationItem::list());

			for (auto element : dictionaryProperties.getElementBundle())
			{
				SolidPrimitiveProperties* solidPrimitiveProperties = dynamic_cast<SolidPrimitiveProperties*>(element->getGraphicProperties());
				if (solidPrimitiveProperties != nullptr) {
					_ifcPrimitivesEnhancer->enhance(file, solidPrimitiveProperties, ifcElementBundle, element);
					continue;
				}

				ShapesGraphicProperties* shapeGraphicProperties = dynamic_cast<ShapesGraphicProperties*>(element->getGraphicProperties());
				if (shapeGraphicProperties != nullptr)
				{
					_ifcShapesEnhancer->enhance(file,shapeGraphicProperties, ifcElementBundle, element);
					continue;
				}

				MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = dynamic_cast<MSBsplineSurfaceGraphicProperties*>(element->getGraphicProperties());
				if (msBsplineSurfaceGraphicProperties != nullptr)
				{
					_ifcSurfaceEnhancer->enhance(file, msBsplineSurfaceGraphicProperties, ifcElementBundle, element);
					continue;
				}

				SolidEntityGraphicProperties* solidEntityGraphicProperties = dynamic_cast<SolidEntityGraphicProperties*>(element->getGraphicProperties());
				if (solidEntityGraphicProperties != nullptr)
				{
					_ifcBRepSolidsEnhancer->enhance(file, solidEntityGraphicProperties, ifcElementBundle, element);
					continue;
				}
			}
		}
	}
	
	IfcElementBuilder* ifcElementBuilder = new IfcElementBuilder(geometricContext, ownerHistory, objectPlacement);
	ifcElementBuilder->processIfcElement(ifcElementBundleVector, file);

	_ifcPropertiesEnhancer->enhanceIfcProperties(dictionaryPropertiesVector, ifcElementBundleVector, file);

	_IfcColorMaterialEnhancer->enhance(ifcElementBundleVector, file);

	this->_ifcPortsBuilder = new IfcPortsBuilder(geometricContext, ownerHistory);
	_ifcPortsBuilder->processIfcPorts(ifcElementBundleVector, file);
				
	ofstream f;
	f.open(filename);
	f << file;
	f.close();

}
