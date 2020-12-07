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
}

void IfcBuilder::buildIfc(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{	

	_logger->logInfo(__FILE__, __LINE__, __func__,"!- Starting IFC conversion -!");

	string filename = SessionManager::getInstance()->getIfcOutputFilePath();
	
	IfcGeneralInformation::getInstance()->buildIfcGeneralInfo();
	Ifc4::IfcGeometricRepresentationContext* geometricContext = IfcGeneralInformation::getInstance()->getGeometricContext();
	Ifc4::IfcOwnerHistory* ownerHistory = IfcGeneralInformation::getInstance()->getOwnerHistory();
	Ifc4::IfcObjectPlacement* objectPlacement = IfcGeneralInformation::getInstance()->getObjectPlacement();
	IfcHierarchyHelper<Ifc4>& file = IfcGeneralInformation::getInstance()->getIfcHierarchyHelper();

	// initialize ifc bundle vector
	vector<IfcElementBundle*>ifcElementBundleVector;
	try {
		if (!dictionaryPropertiesVector.empty())
		{
			for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
			{
				DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

				IfcElementBundle* ifcElementBundle = new IfcElementBundle(dictionaryProperties.getElementId(), dictionaryProperties.getElementDescriptor());
				ifcElementBundle->setElementClassName(dictionaryProperties.getElementClassName());

				ifcElementBundle->setIsSmartSolid(dictionaryProperties.getIsSmartSolid());

				if (dictionaryProperties.getIsSmartSolid() || dictionaryProperties.getIsPrimitiveSolid()) {
					ifcElementBundle->solidModel = true;
				}

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

	_smartFeatureHandler->handleSmartFeature(ifcElementBundleVector, file);

	_ifcElementBuilder->processIfcElement(ifcElementBundleVector, file);

	_ifcPropertiesEnhancer->enhance(dictionaryPropertiesVector, ifcElementBundleVector, file, ownerHistory);

	_IfcColorMaterialEnhancer->enhance(ifcElementBundleVector, file, ownerHistory);

	_ifcPortsBuilder->processIfcPorts(ifcElementBundleVector, file);		

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
}