#include "../headers/IfcBuilder.h"


IfcBuilder::IfcBuilder()
{
	this->_ifcPrimitivesEnhancer = new IfcPrimitivesEnhancer();
	this->_ifcShapesEnhancer = new IfcShapesEnhancer();
	this->_ifcBRepSolidsEnhancer = new IfcBRepSolidsEnhancer();
	this->_ifcPropertiesEnhancer = new IfcPropertiesEnhancer();
	this->_IfcColorMaterialEnhancer = new IfcColorMaterialEnhancer();
	this->_ifcSurfaceEnhancer = new IfcSurfaceEnhancer();
	this->_progressBar = new PBAR::DialogCompletionBar();
}

void IfcBuilder::buildIfc(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{	

	_logger->logInfo(__FILE__, __LINE__, __func__,"!- Starting IFC conversion -!");
	typedef Ifc4::IfcGloballyUniqueId guid;
	
	//string name = "Test-" + dictionaryPropertiesVector[0]->getElementDescriptor();
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
		guid::IfcGloballyUniqueId(filename),
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
	try {
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
					readerPropertiesBundle->setName(readerProperty->getName());

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
	}
	catch (exception& ex) {
		_logger->logFatal(__FILE__, __LINE__, __func__, ex, "Error at initializing the ifcElementBundleVector");
		throw ex;
	}
	catch (...) {
		_logger->logFatal(__FILE__, __LINE__, __func__, "Error at initializing the ifcElementBundleVector. Unhandled exception type");
		throw;
	}

	//TODO [MP] solve the issue
	//SmartFeatureHandler* smartFeatureHandler = new SmartFeatureHandler();
	//smartFeatureHandler->handleSmartFeature(ifcElementBundleVector,file);	

	_ifcElementBuilder = new IfcElementBuilder(geometricContext, ownerHistory, objectPlacement);

	int numThreads = boost::thread::hardware_concurrency();

	auto dictionaryPropertiesSections = splitVector<DictionaryProperties*>(dictionaryPropertiesVector, numThreads);
	auto elementBundleSections = splitVector<IfcElementBundle*>(ifcElementBundleVector, numThreads);

	//Open ProgressBar
	_progressBar->Open(L"Working...");
	_progressBar->numGraphicElement = (int)dictionaryPropertiesVector.size();

	try {
		vector<boost::thread*> bthread;
		for (int i = 0; i < dictionaryPropertiesSections.size(); i++)
		{
			bthread.push_back(
				new boost::thread(
					&IfcBuilder::processElementVector,
					this,
					dictionaryPropertiesSections.at(i),
					elementBundleSections.at(i),
					boost::ref(file)
				)
			);
		}

		for (auto& t: bthread)
		{
			t->join();
		}
	}
	catch (exception& ex) {
		_logger->logFatal(__FILE__, __LINE__, __FUNCTION__, ex, "Fatal error at creating boost::thread Multithreading");
		processElementVector(dictionaryPropertiesVector, ifcElementBundleVector, file);
		throw ex;
	}
	catch (...) {
		_logger->logFatal(__FILE__, __LINE__, __FUNCTION__, "Fatal error at creating boost::thread Multithreading");
		processElementVector(dictionaryPropertiesVector, ifcElementBundleVector, file);
		throw;
	}
	
	this->_ifcPortsBuilder = new IfcPortsBuilder(geometricContext, ownerHistory);
	_ifcPortsBuilder->processIfcPorts(ifcElementBundleVector, file);		

	//Close ProgressBar
	_progressBar->Close();

				
	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Finished IFC conversion -!");

	try {
		_logger->logInfo(__FILE__, __LINE__, __func__, "!- Starting writing to the IFC file -!");

		ofstream f;
		f.open(filename);
		f << file;
		f.close();

		_logger->logInfo(__FILE__, __LINE__, __func__, "!- Ended writing to the IFC file -!");
	}
	catch (exception& ex) {
		_logger->logFatal(__FILE__, __LINE__, __func__, ex, "Error at writing the IFC file");
		throw ex;
	}
	catch (...) {
		_logger->logFatal(__FILE__, __LINE__, __func__, "Error at writing the IFC file");
		throw;
	}
}

void IfcBuilder::processElementVector(vector<DictionaryProperties*> dictionaryPropertiesVector, vector<IfcElementBundle*> ifcElementBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	WString myString;
	myString.Sprintf(L"Generating IFC file...");

	for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
	{
		DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

		// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
		IfcElementBundle*& ifcElementBundle = ifcElementBundleVector.at(i);

		for (auto element : dictionaryProperties.getElementBundle())
		{
			try
			{
				SolidPrimitiveProperties* solidPrimitiveProperties = dynamic_cast<SolidPrimitiveProperties*>(element->getGraphicProperties());
				if (solidPrimitiveProperties != nullptr) {
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcPrimitivesEnhancer->enhance(file, solidPrimitiveProperties, ifcElementBundle, element);
					continue;
				}

				ShapesGraphicProperties* shapeGraphicProperties = dynamic_cast<ShapesGraphicProperties*>(element->getGraphicProperties());
				if (shapeGraphicProperties != nullptr)
				{
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcShapesEnhancer->enhance(file, shapeGraphicProperties, ifcElementBundle, element);
					continue;
				}

				MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = dynamic_cast<MSBsplineSurfaceGraphicProperties*>(element->getGraphicProperties());
				if (msBsplineSurfaceGraphicProperties != nullptr)
				{
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcSurfaceEnhancer->enhance(file, msBsplineSurfaceGraphicProperties, ifcElementBundle, element);
					continue;
				}

				SolidEntityGraphicProperties* solidEntityGraphicProperties = dynamic_cast<SolidEntityGraphicProperties*>(element->getGraphicProperties());
				if (solidEntityGraphicProperties != nullptr)
				{
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcBRepSolidsEnhancer->enhance(file, solidEntityGraphicProperties, ifcElementBundle, element);
					continue;
				}			

				//ProgressBar
				_progressBar->IncrementIndex();
				_progressBar->Update(myString);
			}
			catch (exception& ex) {
				_logger->logError(__FILE__, __LINE__, __FUNCTION__, ex, "Error at creating IFC primitives/shapes/bsplines/solid entities");
				continue;
			}
			catch (...) {
				_logger->logError(__FILE__, __LINE__, __FUNCTION__, "Error at creating IFC primitives/shapes/bsplines/solid entities");
				continue;
			}
		}
	}
	try	
	{
		boost::unique_lock<boost::shared_mutex> guard(_mutex);
		_ifcElementBuilder->processIfcElement(ifcElementBundleVector, file);

		_ifcPropertiesEnhancer->enhanceIfcProperties(dictionaryPropertiesVector, ifcElementBundleVector, file);

		_IfcColorMaterialEnhancer->enhance(ifcElementBundleVector, file);
	}
	catch (exception& ex) {
		_logger->logError(__FILE__, __LINE__, __FUNCTION__, ex, "Error at creating IFC Element/Property/Material");
	}
	catch (...) {
		_logger->logError(__FILE__, __LINE__, __FUNCTION__, "Error at creating IFC Element/Property/Material");
	}
}