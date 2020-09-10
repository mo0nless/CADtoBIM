#include "../headers/InitializationHelper.h"


InitializationHelper::InitializationHelper()
{	

	createFilesStructure();

	this->mDgnModel = ISessionMgr::GetActiveDgnModelP();
	this->mDgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName();//.AppendUtf8(".txt");
	this->pGraElement = mDgnModel->GetGraphicElementsP();


	Logs::Logger* logger = Logs::Logger::getLogger();
	logger->logInfo(__FILE__,__LINE__, __FUNCTION__,"info");
	logger->logDebug(__FILE__, __LINE__, __FUNCTION__, "debug");
	logger->logWarning(__FILE__, __LINE__, __FUNCTION__, "warning");
	logger->logError(__FILE__, __LINE__, __FUNCTION__, "error");
	logger->logFatal(__FILE__, __LINE__, __FUNCTION__, "fatal");


	
	//try
	//{
	//	// Create a text file sink
	//	typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
	//	boost::shared_ptr<file_sink> sink(new file_sink(
	//		keywords::file_name = "file_%Y-%m-%d_%H-%M-%S.%N.log",      // file name pattern
	//		keywords::rotation_size = 16384                     // rotation size, in characters
	//	));

	//	// Set up where the rotated files will be stored
	//	sink->locked_backend()->set_file_collector(sinks::file::make_collector(
	//		keywords::target = "logs",                          // where to store rotated files
	//		keywords::max_size = 16 * 1024 * 1024,              // maximum total size of the stored files, in bytes
	//		keywords::min_free_space = 100 * 1024 * 1024        // minimum free space on the drive, in bytes
	//	));

	//	// Upon restart, scan the target directory for files matching the file_name pattern
	//	sink->locked_backend()->scan_for_files();

	//	sink->set_formatter
	//	(
	//		expr::format("%1%: [%2%] - %3%")
	//		% expr::attr< unsigned int >("RecordID")
	//		% expr::attr< boost::posix_time::ptime >("TimeStamp")
	//		% expr::smessage
	//	);

	//	// Add it to the core
	//	logging::core::get()->add_sink(sink);

	//	// Add some attributes too
	//	logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
	//	logging::core::get()->add_global_attribute("RecordID", attrs::counter< unsigned int >());

	//	// Do some logging
	//	src::logger lg;
	//	for (unsigned int i = 0; i < LOG_RECORDS_TO_WRITE; ++i)
	//	{
	//		BOOST_LOG(lg) << "Some log record";
	//	}

	//	/*return 0;*/
	//}
	//catch (std::exception& e)
	//{
	//	std::cout << "FAILURE: " << e.what() << std::endl;
	//	/*return 1;*/
	//}



	//BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
	//BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
	//BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
	//BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
	//BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
	//BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";
}

SmartFeatureContainer * InitializationHelper::createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec)
{
	ofstream outfile;

	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer(currentElem.GetElementId());
	long newLocalNodeId = -1, newParentLocalNodeId = -1, newGlobalNodeId = -1;

	SmartFeatureElement::ExtractTree(sFeatNode, currentElem);

	sFeatNode->GetAllChildrenRecursively(sFeatVec);

	for (size_t i = 0; i < sFeatVec.size(); i++)
	{
		outfile.open(filePath, ios_base::app);
		outfile << "start==================" << endl;
		outfile.close();
		if (sFeatVec.at(i)->GetParent() != nullptr)
		{
			outfile.open(filePath, ios_base::app);
			outfile << "Parent Ref Count: " << sFeatVec.at(i)->GetParent()->GetRefCount() << endl;
			outfile << "Parent ID: " << sFeatVec.at(i)->GetParent()->GetNodeId() << endl;
			outfile.close();

			newParentLocalNodeId = sFeatVec.at(i)->GetParent()->GetNodeId();
		}

		newLocalNodeId = sFeatVec.at(i)->GetNodeId();

		outfile.open(filePath, ios_base::app);
		outfile << "Node ID: " << newLocalNodeId << endl;
		outfile.close();

		sFeatVec.at(i)->GetLeaf(leafNode);

		if (leafNode.IsValid()) {

			newGlobalNodeId = leafNode.GetElementId();
			
			outfile.open(filePath, ios_base::app);
			outfile << "Leaf ID:  " << leafNode.GetElementId() << endl;
			outfile.close();

		}

		outfile.open(filePath, ios_base::app);
		outfile << "finish==================" << endl;
		outfile.close();

		
		smartFeatureContainer->insertNodeInTree(newLocalNodeId, newParentLocalNodeId, newGlobalNodeId);

	}

	outfile.open(filePath, ios_base::app);
	outfile << "Smart Feat Element Node ID: " << sFeatNode->GetNodeId() << endl;
	outfile << "Number of Child: " << sFeatNode->GetChildCount() << endl;
	outfile.close();


	return smartFeatureContainer;
}

StatusInt InitializationHelper::iterateSubElements(ElementRefP elementRefP, DictionaryProperties* dictionaryProperties)
{
	ElementHandle eh(elementRefP);	 //	Can also construct an ElemHandle from an MSElementDescr*

	ofstream outfile;
	outfile.open(filePath, ios_base::app);
	int index = 0;


	outfile << "eh id = " << eh.GetElementId() << endl;
	outfile << "eh type = " << eh.GetElementType() << endl;
	outfile << "index1 = " << index << endl;

	outfile.close();

	for (ChildElemIter child(eh); child.IsValid(); child = child.ToNext())
	{
		iterateSubElements(child.GetElementRef(), dictionaryProperties);
		++index;
	}
	if(index==0){

		outfile.open(filePath, ios_base::app);

		outfile << "eh2 id" << eh.GetElementId() << endl;
		outfile << "eh2 type" << eh.GetElementType() << endl;
		outfile << "index2 = " << index << endl;


		outfile.close();

		ElementBundle* elementBundle = new ElementBundle();
		elementBundle->setElementHandle(eh);

		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();
		ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(eh, elementBundle);
		elementBundle->setReaderPropertiesBundle(*readerPropertiesBundle);

		GraphicsProcessor graphicsProcessor = GraphicsProcessor();
		GraphicsProcessorHelper* GraphicsProcessorHelper = graphicsProcessor.getGraphicsProcessorHelper();

		GraphicsProcessorHelper->setElementHandle(eh);
		GraphicsProcessorHelper->setElementBundle(*elementBundle);
		GraphicsProcessorHelper->setDictionaryProperties(*dictionaryProperties);
		ElementGraphicsOutput::Process(eh, graphicsProcessor);

		dictionaryProperties->addElementBundle(elementBundle);

		return SUCCESS;
	}

	return SUCCESS;
}

#pragma warning( pop ) 

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning (disable:4311 4302 4312)
void InitializationHelper::processDgnGraphicsElements(vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	ofstream outfile;	
	outfile.open(filePath);
	outfile << "------------------------" << endl;
	outfile.close();
			
	GraphicsProcessor graphicsProcessor = GraphicsProcessor();
	GraphicsProcessorHelper* GraphicsProcessorHelper = graphicsProcessor.getGraphicsProcessorHelper();
	PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();

	DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();
	ModelInfoCP modelInfo = dgnModelRef->GetModelInfoCP();
	
	DPoint3d globalOrigin = modelInfo->GetGlobalOrigin();

	UnitDefinitionCR masterUnit = modelInfo->GetMasterUnit();
	UnitDefinitionCR subUnit = modelInfo->GetSubUnit();

	UnitDefinitionCR storageUnit = modelInfo->GetStorageUnit();
	double uorPerUnit = modelInfo->GetUorPerStorage();
	//mdlColorPal_getElemColorDescrByModelRef()

	//mdlElement_getFillColor

	outfile.open(filePath, ios_base::app);
	outfile << "------------------------" << endl;
	outfile << "DgnModelRefP Unit System" << endl;
	outfile << fixed;
	outfile << endl;

	outfile << "UnitSystem::English 1" << endl;
	outfile << "UnitSystem::Metric 2" << endl;
	outfile << "UnitSystem::USSurvey 3" << endl;
	outfile << endl;
	
	outfile << "UnitBase::Meter 1" << endl;
	outfile << "UnitBase::Degree 2" << endl;
	outfile << endl;
	
	outfile << "Master unit: " << StringUtils::getNormalizedString(masterUnit.GetLabel()) << endl;
	outfile << "masterUnit System" << (int)masterUnit.GetSystem() << endl;
	outfile << "masterUnit Base" << (int)masterUnit.GetBase() << endl;
	outfile << "masterUnit Numerator" << masterUnit.GetNumerator() << endl;
	outfile << "masterUnit Denominator" << masterUnit.GetDenominator() << endl;
	outfile << "Division Ratio" << (masterUnit.GetNumerator() / masterUnit.GetDenominator()) << endl;
	outfile << endl;

	outfile << "Sub unit: " << StringUtils::getNormalizedString(subUnit.GetLabel()) << endl;
	outfile << "subUnit System" << (int)subUnit.GetSystem() << endl;
	outfile << "subUnit Base" << (int)subUnit.GetBase() << endl;
	outfile << "subUnit Numerator" << subUnit.GetNumerator() << endl;
	outfile << "subUnit Denominator" << subUnit.GetDenominator() << endl;
	outfile << "Division Ratio" << (subUnit.GetNumerator() / subUnit.GetDenominator()) << endl;
	outfile << endl;

	outfile << "Storage unit: " << StringUtils::getNormalizedString(storageUnit.GetLabel()) << endl;
	outfile << "storageUnit System" << (int)storageUnit.GetSystem() << endl;
	outfile << "storageUnit Base" << (int)storageUnit.GetBase() << endl;
	outfile << "storageUnit Numerator" << storageUnit.GetNumerator() << endl;
	outfile << "storageUnit Denominator" << storageUnit.GetDenominator() << endl;
	outfile << "Division Ratio" << (storageUnit.GetNumerator() / storageUnit.GetDenominator()) << endl;
	outfile << endl;

	outfile << "UOR per storage" << uorPerUnit << endl;
	outfile << "AnnotationScaleFactor" << modelInfo->GetAnnotationScaleFactor() << endl;
	outfile << "Global Origin [x,y,z]= " << globalOrigin.x << ", " << globalOrigin.y << ", " << globalOrigin.z << endl;
	
	outfile << "------------------------" << endl;
	outfile.close();

	auto dgnRefActive = ISessionMgr::GetActiveDgnModelP();
	

	for (PersistentElementRefP elemRef : *pGraElement)
	{	
		
		DgnModelP c = elemRef->GetDgnModelP();
		ElementHandle currentElem(elemRef);

		WString elDescr;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

		SmartFeatureContainer* smartFeatureContainer = nullptr;
		DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));
		GraphicsProcessorHelper->setDictionaryProperties(*propertiesDictionary);

		iterateSubElements(elemRef, propertiesDictionary);

		if (SmartFeatureElement::IsSmartFeature(currentElem))
		{
			ElementHandle leafNode;
			SmartFeatureNodePtr sFeatNode;
			T_SmartFeatureVector sFeatVec;

			smartFeatureContainer = createSmartFeatureContainer(currentElem, sFeatNode, leafNode, sFeatVec);
			if (smartFeatureContainer != nullptr) {
				smartFeatureContainerVector.push_back(smartFeatureContainer);
				propertiesDictionary->setSmartFeatureContainer(smartFeatureContainer);
			}
		}
					


		outfile.open(filePath, ios_base::app);
		outfile << "===================================================" << endl;
		outfile << "===================================================" << endl;
		outfile << "Element Description: " << static_cast<Utf8String>(elDescr.GetWCharCP()) << endl;
		outfile << "Element ID: " << currentElem.GetElementId() << endl;
		outfile << "===================================================" << endl;
		outfile << "===================================================" << endl;
		outfile << endl;
		outfile.close();

		ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(currentElem);
		propertiesDictionary->addElementReaderPropertiesBundle(readerPropertiesBundle);
		GraphicsProcessorHelper->getCurrentElementHandle() = currentElem; 
		
		propsDictVec.push_back(propertiesDictionary);


		outfile.open(filePath, ios_base::app);
		outfile << endl;
		outfile << "===================================================" << endl;
		outfile << "===================================================" << endl;
		outfile << "Element Description: " << static_cast<Utf8String>(elDescr.GetWCharCP()) << endl;
		outfile << "Element: ID " << currentElem.GetElementId() << endl;
		outfile << "===================================================" << endl;
		outfile << "===================================================" << endl;
		outfile << endl;
		outfile.close();

	}
}
void InitializationHelper::createFilesStructure()
{
	//this->filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	this->filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

	SessionManager::getInstance()->setDataOutputFilePath(filePath);


	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK) {
		cout << "Error: " << result << "\n";
	}
	else {
		cout << "Path: " << my_documents << "\n";
	}

	string documentsPath = my_documents;

	string mainFolderPath = documentsPath + "\\IfcModels";
	// create main folder
	createFolder(mainFolderPath);

	SessionManager::getInstance()->setOutputFolderPath(mainFolderPath);

	string logFolderPath = mainFolderPath + "\\logs";
	// create logs folder
	createFolder(logFolderPath);

	// get date to create logs by day
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1; 
	int year = aTime->tm_year + 1900;

	string currentDayLogFolderPath = logFolderPath + "\\" + to_string(day)+"-"+to_string(month)+"-"+to_string(year);
	// create log folder
	createFolder(currentDayLogFolderPath);
	SessionManager::getInstance()->setCurrentDayLogsFolderPath(currentDayLogFolderPath);


	string re = StringUtils::getNormalizedString(ISessionMgr::GetActiveDgnFile()->GetFileName());


	// get dgn file name
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(re.c_str(), drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);


	//string ifcOutputFileName1 = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/IfcCustomName.ifc";
	string ifcOutputFileName = mainFolderPath + "\\" + fname + ".ifc";
	
	SessionManager::getInstance()->setIfcOutputFilePath(ifcOutputFileName);

}
void InitializationHelper::createFolder(string folderPath)
{

	// create main folder
	if (CreateDirectory(folderPath.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		// do something. status/boolean
	}
	else
	{
		// Failed to create directory. return status/boolean and log
	}
}
#pragma warning( pop ) 
