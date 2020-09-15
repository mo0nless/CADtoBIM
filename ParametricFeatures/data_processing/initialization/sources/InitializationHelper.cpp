#include "../headers/InitializationHelper.h"


InitializationHelper::InitializationHelper()
{	

	this->filePath = SessionManager::getInstance()->getDataOutputFilePath();
	this->mDgnModel = ISessionMgr::GetActiveDgnModelP();
	this->mDgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName();//.AppendUtf8(".txt");
	this->pGraElement = mDgnModel->GetGraphicElementsP();
	this->_progressBar = DialogCompletionBar();
	this->_modelerDataWriterManager = new ModelerDataWriterManager(true);
}

SmartFeatureContainer * InitializationHelper::createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);


	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer(currentElem.GetElementId());
	long newLocalNodeId = -1, newParentLocalNodeId = -1, newGlobalNodeId = -1;

	SmartFeatureElement::ExtractTree(sFeatNode, currentElem);

	sFeatNode->GetAllChildrenRecursively(sFeatVec);

	for (size_t i = 0; i < sFeatVec.size(); i++)
	{
		if (sFeatVec.at(i)->GetParent() != nullptr)
		{
			newParentLocalNodeId = sFeatVec.at(i)->GetParent()->GetNodeId();
		}

		newLocalNodeId = sFeatVec.at(i)->GetNodeId();
		sFeatVec.at(i)->GetLeaf(leafNode);

		if (leafNode.IsValid()) {

			newGlobalNodeId = leafNode.GetElementId();
		}
		smartFeatureContainer->insertNodeInTree(newLocalNodeId, newParentLocalNodeId, newGlobalNodeId);

	}

	return smartFeatureContainer;
}

StatusInt InitializationHelper::iterateSubElements(ElementRefP elementRefP, DictionaryProperties* dictionaryProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	mutex g_display_mutex;
	ElementHandle eh(elementRefP);	 //	Can also construct an ElemHandle from an MSElementDescr*

	int index = 0;

	for (ChildElemIter child(eh); child.IsValid(); child = child.ToNext())
	{
		iterateSubElements(child.GetElementRef(), dictionaryProperties);
		++index;
	}
	if(index==0){

		ElementBundle* elementBundle = new ElementBundle();
		elementBundle->setElementHandle(eh);

		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();
		ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(eh, elementBundle);
		elementBundle->setReaderPropertiesBundle(*readerPropertiesBundle);

		lock_guard<mutex> guard(g_display_mutex);
		GraphicsProcessor graphicsProcessor = GraphicsProcessor();
		GraphicsProcessorHelper* graphicsProcessorHelper = graphicsProcessor.getGraphicsProcessorHelper();

		graphicsProcessorHelper->setElementHandle(eh);
		graphicsProcessorHelper->setElementBundle(*elementBundle);
		graphicsProcessorHelper->setDictionaryProperties(*dictionaryProperties);
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
#pragma warning (disable:4311 4302 4312 4100)
void InitializationHelper::processDgnGraphicsElements(vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	_logger->logInfo(__FILE__, __LINE__, __FUNCTION__, "!- Starting elements processing -!");
	//Open ProgressBar
	DialogCompletionBar progressBar = DialogCompletionBar();
	progressBar.Open(L"Processing DGN elements...");

			
	GraphicsProcessor graphicsProcessor = GraphicsProcessor();
	GraphicsProcessorHelper* graphicsProcessorHelper = graphicsProcessor.getGraphicsProcessorHelper();
	PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();

	DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();
	ModelInfoCP modelInfo = dgnModelRef->GetModelInfoCP();

	this->_modelerDataWriterManager->writeInitializationDataToFile(modelInfo);

	auto dgnRefActive = ISessionMgr::GetActiveDgnModelP();
	
	WString myString;	
	
	//Open ProgressBar	
	this->_progressBar.numGraphicElement = dgnRefActive->GetElementCount(DgnModelSections::GraphicElements); //Count the element (this function gets also the deleted ones??)
	this->_progressBar.Open(L"Working...");

#if false
	vector<PersistentElementRefP> vecGraphicElements;
	for (PersistentElementRefP elemRef : *pGraElement)
	{
		vecGraphicElements.push_back(elemRef);
	}

	int numThreads = thread::hardware_concurrency();
	vector<vector<PersistentElementRefP>> elementThreadCollection = splitVector<PersistentElementRefP>(vecGraphicElements, numThreads);
	ctpl::thread_pool pool(numThreads);

	vector<thread> threadVector;
	for (auto elmVec : elementThreadCollection)
	{
		/*pool.push([](int id) {
			string f = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
			ofstream outfile;
			outfile.open(f, ios_base::app);
			outfile << "------------- THREAD ------------- " << id << endl;
			outfile.close();
		});*/
		//for (...) some_threads.push_back(std::thread(&foo::foo_func, this));

		
		threadVector.push_back(thread (&InitializationHelper::processSubElemVector, this, elmVec, ref(propsDictVec), ref(smartFeatureContainerVector)));
	}

	for (auto& t : threadVector)
	{
		t.join();
	}
#endif

#if true
	for (PersistentElementRefP elemRef : *pGraElement)
	{	
		DgnModelP c = elemRef->GetDgnModelP();
		ElementHandle currentElem(elemRef);

		WString elDescr;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

		SmartFeatureContainer* smartFeatureContainer = nullptr;
		DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));

		//ProgressBar
		this->_progressBar.globalIndex += 1;
		myString.Sprintf(L"Processing Elements... [%d/%d]  (%s)", this->_progressBar.globalIndex, this->_progressBar.numGraphicElement, elDescr);
		this->_progressBar.Update(myString);		

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

		this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

		ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(currentElem);
		propertiesDictionary->addElementReaderPropertiesBundle(readerPropertiesBundle);
		
		propsDictVec.push_back(propertiesDictionary);

		this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);
	}
#endif

	//Close ProgressBar
	this->_progressBar.Close();

	_logger->logInfo(__FILE__, __LINE__, __FUNCTION__, "!- Ended elements processing -!");
}

void InitializationHelper::processSubElemVector(vector<PersistentElementRefP> vecGraphicElement, vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	WString myString;
	mutex g_display_mutex;

	//PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();

	string errorMessageAtElementsProcessing = "An error occured while iterating and processing pGraElement";


	for (PersistentElementRefP elemRef : *pGraElement)
	{
		try {

			DgnModelP c = elemRef->GetDgnModelP();
			ElementHandle currentElem(elemRef);

			WString elDescr;

			currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

			SmartFeatureContainer* smartFeatureContainer = nullptr;
			DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));

			//ProgressBar
			this->_progressBar.globalIndex += 1;
			myString.Sprintf(L"Processing Elements... [%d/%d]  (%s)", this->_progressBar.globalIndex, this->_progressBar.numGraphicElement, elDescr);
			this->_progressBar.Update(myString);

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


			this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

			PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();
			ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(currentElem);
			propertiesDictionary->addElementReaderPropertiesBundle(readerPropertiesBundle);

			lock_guard<mutex> guard(g_display_mutex);
			propsDictVec.push_back(propertiesDictionary);

			this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

		}
		catch (exception& ex) {
			_logger->logError(__FILE__, __LINE__, __FUNCTION__, ex, errorMessageAtElementsProcessing);
		}
		catch (...) {
			_logger->logError(__FILE__, __LINE__, __FUNCTION__, errorMessageAtElementsProcessing);

		}
	}

}
#pragma warning( pop ) 
