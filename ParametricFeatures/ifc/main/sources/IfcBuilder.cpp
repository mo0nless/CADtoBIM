#include "../headers/IfcBuilder.h"

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning( disable : 4101)

IfcBuilder::IfcBuilder()
{
	this->_ifcPrimitivesEnhancer = new IfcPrimitivesEnhancer();
	this->_ifcShapesEnhancer = new IfcShapesEnhancer();
	this->_ifcBRepSolidsEnhancer = new IfcBRepSolidsEnhancer();
	this->_ifcPropertiesEnhancer = new IfcPropertiesEnhancer();
	this->_IfcColorMaterialEnhancer = new IfcColorMaterialEnhancer();
	this->_ifcSurfaceEnhancer = new IfcSurfaceEnhancer();
	this->_progressBar = new PBAR::DialogCompletionBar();
	this->_smartFeatureHandler = new SmartFeatureHandler();
	this->_ifcTextEnhancer = new IfcTextEnhancer();
}

map<LevelId, IfcEntityList*> IfcBuilder::getLevelFileCache()
{
	if (!_levelFileEntities.empty())
		return _levelFileEntities;

	DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();
	FileLevelCache* fileLevelCache = dgnModelRef->GetFileLevelCacheP();

	for (LevelHandle lHndl : *fileLevelCache)
	{
		_levelFileEntities.insert(pair<LevelId, IfcEntityList*>{lHndl.GetLevelId(),new IfcEntityList()});
		_fileLevelHandle.push_back(lHndl);
	}

	return _levelFileEntities;
}

void IfcBuilder::generateIfcLevelsCache(IfcHierarchyHelper<Ifc4>& file)
{
	for (auto lHdl : _fileLevelHandle)
	{
		IfcEntityList* entList = getLevelFileCache().at(lHdl->GetLevelId());
		boost::shared_ptr<IfcEntityList> layer(entList);

		Ifc4::IfcPresentationLayerAssignment* presLayer = new Ifc4::IfcPresentationLayerAssignment(
			StringUtils::getNormalizedString(lHdl->GetName()),
			StringUtils::getNormalizedString(lHdl->GetDescription()),
			layer,
			to_string(lHdl->GetLevelId())
		);
		
		file.addEntity(presLayer);
	}
}

void IfcBuilder::buildIfc(vector<IfcElementBundle*>& ifcElementBundleVector)
{	

	_logger->logInfo(__FILE__, __LINE__, __func__,"!- Starting IFC conversion -!");

	string filename = SessionManager::getInstance()->getIfcOutputFilePath();
	
	IfcGeneralInformation::getInstance()->buildIfcGeneralInfo();
	Ifc4::IfcGeometricRepresentationContext* geometricContext = IfcGeneralInformation::getInstance()->getGeometricContext();
	Ifc4::IfcOwnerHistory* ownerHistory = IfcGeneralInformation::getInstance()->getOwnerHistory();
	Ifc4::IfcObjectPlacement* objectPlacement = IfcGeneralInformation::getInstance()->getObjectPlacement();
	IfcHierarchyHelper<Ifc4>& file = IfcGeneralInformation::getInstance()->getIfcHierarchyHelper();

	
	try {

#if false
		// initialize ifc bundle vector
		vector<IfcElementBundle*>ifcElementBundleVector;
		if (!dictionaryPropertiesVector.empty())
		{
			for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
			{
				DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

				IfcElementBundle* ifcElementBundle = new IfcElementBundle(dictionaryProperties.getElementId(), dictionaryProperties.getElementDescriptor());
				ifcElementBundle->setElementClassName(dictionaryProperties.getElementClassName());
				ifcElementBundle->setGraphicGeomBundle(dictionaryProperties.getIfcGraphicPropertiesBundleVector());

				//ifcElementBundle->setIsSmartSolid(dictionaryProperties.getIsSmartSolid());

				/*if (dictionaryProperties.getIsSmartSolid() || dictionaryProperties.getIsPrimitiveSolid()) {
					ifcElementBundle->solidModel = true;
				}*/

				ifcElementBundle->setSmartFeatureContainer(dictionaryProperties.getSmartFeatureContainer());
				// TODO [MP] to be replaced with a copy contructor or delete dicionary properties and only keep ifc element bundle
				for (auto const& readerProperty : dictionaryProperties.getElementReaderPropertiesBundleVector()) {
					ReaderPropertiesBundle* readerPropertiesBundle = new ReaderPropertiesBundle(readerProperty->getClassName(), readerProperty->getLocalId());
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
#endif
		if (!ifcElementBundleVector.empty())
		{
			for (auto const& ifcElementBundle : ifcElementBundleVector)
			{
				for (auto const& readerProperty : ifcElementBundle->getElementReaderPropertiesBundleVector()) {
					ReaderPropertiesBundle* readerPropertiesBundle = new ReaderPropertiesBundle(readerProperty->getClassName(), readerProperty->getLocalId());
					readerPropertiesBundle->setName(readerProperty->getName());

					for (auto const& property1 : readerProperty->getProperties()) {
						ReaderPropertyDefinition* readerPropertyDefinition = new ReaderPropertyDefinition(property1->getPropertyName(), property1->getPropertyTypeName()
							, property1->getPropertyValue(), property1->getPropertyValueAsString());
						readerPropertiesBundle->addProperty(readerPropertyDefinition);

					}
					ifcElementBundle->addIfcElementReaderPropertiesBundle(new IfcReaderPropertiesBundle(readerPropertiesBundle));
				}
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

	_ifcPortsBuilder = new IfcPortsBuilder(geometricContext, ownerHistory);
	_ifcElementBuilder = new IfcElementBuilder(geometricContext, ownerHistory, objectPlacement);

	int numThreads = boost::thread::hardware_concurrency();

	//auto dictionaryPropertiesSections = splitVector<DictionaryProperties*>(dictionaryPropertiesVector, numThreads);
	auto elementBundleSections = splitVector<IfcElementBundle*>(ifcElementBundleVector, numThreads);

	//Open ProgressBar
	_progressBar->Open(L"Working...");
	_progressBar->numGraphicElement = (int)ifcElementBundleVector.size();


	try {

		vector<boost::thread*> bthread;
		for (int i = 0; i < elementBundleSections.size(); i++)
		{
			bthread.push_back(
				new boost::thread(
					&IfcBuilder::processElementVector,
					this,
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
		processElementVector(ifcElementBundleVector, file);
		throw ex;
	}
	catch (...) {
		_logger->logFatal(__FILE__, __LINE__, __FUNCTION__, "Fatal error at creating boost::thread Multithreading");
		processElementVector(ifcElementBundleVector, file);
		throw;
	}

	_smartFeatureHandler->handleSmartFeature(ifcElementBundleVector, file);

	_ifcElementBuilder->processIfcElement(ifcElementBundleVector, file, getLevelFileCache());

	_ifcPropertiesEnhancer->enhance(ifcElementBundleVector, file, ownerHistory);

	_IfcColorMaterialEnhancer->enhance(ifcElementBundleVector, file, ownerHistory);

	_ifcPortsBuilder->processIfcPorts(ifcElementBundleVector, file);		

	this->generateIfcLevelsCache(file);

	//Close ProgressBar
	_progressBar->Close();

				
	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Finished IFC conversion -!");

	try {
		_logger->logInfo(__FILE__, __LINE__, __func__, "!- Starting writing to the IFC file -!");

		bool g = file.good();
		bool d = file.parsing_complete();

		/*ofstream f;
		f.open(filename);
		f << file;
		f.close();*/

		auto myfile = std::fstream(filename, std::ios::out);// | std::ios::binary);
		myfile << file;
		myfile.flush();
		myfile.close();

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

void IfcBuilder::processElementVector(vector<IfcElementBundle*> ifcElementBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	WString myString;
	myString.Sprintf(L"Generating IFC file...");

	for (int i = 0; i < ifcElementBundleVector.size(); i++)
	{
		//DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

		// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
		IfcElementBundle*& ifcElementBundle = ifcElementBundleVector.at(i);
		
		for (IfcGraphicPropertiesBundle* graphicPropertiesBundle : ifcElementBundle->getIfcGraphicPropertiesBundleVector())
		{
			try
			{
				SolidPrimitiveProperties* solidPrimitiveProperties = dynamic_cast<SolidPrimitiveProperties*>(graphicPropertiesBundle->getGraphicProperties());
				if (solidPrimitiveProperties != nullptr) {
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcPrimitivesEnhancer->enhance(file, solidPrimitiveProperties, ifcElementBundle, graphicPropertiesBundle);
					continue;
				}

				ShapesGraphicProperties* shapeGraphicProperties = dynamic_cast<ShapesGraphicProperties*>(graphicPropertiesBundle->getGraphicProperties());
				if (shapeGraphicProperties != nullptr)
				{
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcShapesEnhancer->enhance(file, shapeGraphicProperties, ifcElementBundle, graphicPropertiesBundle);
					continue;
				}

				MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = dynamic_cast<MSBsplineSurfaceGraphicProperties*>(graphicPropertiesBundle->getGraphicProperties());
				if (msBsplineSurfaceGraphicProperties != nullptr)
				{
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcSurfaceEnhancer->enhance(file, msBsplineSurfaceGraphicProperties, ifcElementBundle, graphicPropertiesBundle);
					continue;
				}

				SolidEntityGraphicProperties* solidEntityGraphicProperties = dynamic_cast<SolidEntityGraphicProperties*>(graphicPropertiesBundle->getGraphicProperties());
				if (solidEntityGraphicProperties != nullptr)
				{
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcBRepSolidsEnhancer->enhance(file, solidEntityGraphicProperties, ifcElementBundle, graphicPropertiesBundle);
					continue;
				}	

				TextGraphicProperties* textGraphicProperties = dynamic_cast<TextGraphicProperties*>(graphicPropertiesBundle->getGraphicProperties());
				if (textGraphicProperties != nullptr)
				{
					boost::unique_lock<boost::shared_mutex> guard(_mutex);
					_ifcTextEnhancer->enhance(file, textGraphicProperties, ifcElementBundle, graphicPropertiesBundle);
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
}