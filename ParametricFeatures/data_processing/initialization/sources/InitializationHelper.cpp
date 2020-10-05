#include "../headers/InitializationHelper.h"


InitializationHelper::InitializationHelper()
{	

	this->filePath = SessionManager::getInstance()->getDataOutputFilePath();
	this->mDgnModel = ISessionMgr::GetActiveDgnModelP();
	this->mDgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName();//.AppendUtf8(".txt");
	this->pGraElement = mDgnModel->GetGraphicElementsP();
	this->_progressBar = new PBAR::DialogCompletionBar();
	this->_modelerDataWriterManager = ModelerDataWriterManager::getInstance(); //new ModelerDataWriterManager(true);
	this->_propertiesReaderProcessor = PropertiesReaderProcessor::getInstance();
}

SmartFeatureContainer * InitializationHelper::createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);


	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer(currentElem.GetElementId());
	long newLocalNodeId = -1, newParentLocalNodeId = -1, newGlobalNodeId = -1;

	SmartFeatureElement::ExtractTree(sFeatNode, currentElem);

	sFeatNode->GetAllChildrenRecursively(sFeatVec);

	for (size_t i = 0; i < sFeatVec.size(); i++)
	{
		/*outfile.open(filePath, ios_base::app);
		outfile << "start==================" << endl;
		outfile.close();*/
		if (sFeatVec.at(i)->GetParent() != nullptr)
		{
			/*outfile.open(filePath, ios_base::app);
			outfile << "Parent Ref Count: " << sFeatVec.at(i)->GetParent()->GetRefCount() << endl;
			outfile << "Parent ID: " << sFeatVec.at(i)->GetParent()->GetNodeId() << endl;
			outfile.close();*/

			newParentLocalNodeId = sFeatVec.at(i)->GetParent()->GetNodeId();
		}

		newLocalNodeId = sFeatVec.at(i)->GetNodeId();
/*
		outfile.open(filePath, ios_base::app);
		outfile << "Node ID: " << newLocalNodeId << endl;
		outfile.close();
*/
		sFeatVec.at(i)->GetLeaf(leafNode);

		if (leafNode.IsValid()) {

			newGlobalNodeId = leafNode.GetElementId();
			
			/*outfile.open(filePath, ios_base::app);
			outfile << "Leaf ID:  " << leafNode.GetElementId() << endl;
			outfile.close();*/

		}

		/*outfile.open(filePath, ios_base::app);
		outfile << "finish==================" << endl;
		outfile.close();*/

		
		smartFeatureContainer->insertNodeInTree(newLocalNodeId, newParentLocalNodeId, newGlobalNodeId);

	}

	/*outfile.open(filePath, ios_base::app);
	outfile << "Smart Feat Element Node ID: " << sFeatNode->GetNodeId() << endl;
	outfile << "Number of Child: " << sFeatNode->GetChildCount() << endl;
	outfile.close();*/


	return smartFeatureContainer;
}

#pragma warning( pop ) 

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning (disable:4311 4302 4312 4100)
StatusInt InitializationHelper::iterateSubElements(ElementRefP elementRefP, DictionaryProperties*& dictionaryProperties)
{		
	_logger->logDebug(__FILE__, __LINE__, __func__);

	ElementHandle eh(elementRefP);	 //	Can also construct an ElemHandle from an MSElementDescr*

	int index = 0;

	for (ChildElemIter child(eh); child.IsValid(); child = child.ToNext())
	{
		iterateSubElements(child.GetElementRef(), dictionaryProperties);// , propertiesReaderProcessor);
		++index;
	}
	if(index==0){

		ElementBundle* elementBundle = new ElementBundle();
		elementBundle->setElementHandle(eh);

		ReaderPropertiesBundle* readerPropertiesBundle = _propertiesReaderProcessor->processElementReaderProperties(eh, elementBundle);
		elementBundle->setReaderPropertiesBundle(*readerPropertiesBundle);		

		GraphicsProcessor* graphicsProcessor = new GraphicsProcessor();
		GraphicsProcessorHelper* graphicsProcessorHelper = graphicsProcessor->getGraphicsProcessorHelper();

		graphicsProcessorHelper->setElementHandle(eh);
		graphicsProcessorHelper->setElementBundle(*elementBundle);
		graphicsProcessorHelper->setDictionaryProperties(*dictionaryProperties);
				
		ElementGraphicsOutput::Process(eh, *graphicsProcessor);

		dictionaryProperties->addElementBundle(elementBundle);

		return SUCCESS;
	}

	return SUCCESS;
}

void InitializationHelper::processDgnGraphicsElements(vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Starting elements processing -!");

	DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();
	ModelInfoCP modelInfo = dgnModelRef->GetModelInfoCP();

	this->_modelerDataWriterManager->writeInitializationDataToFile(modelInfo);

	auto dgnRefActive = ISessionMgr::GetActiveDgnModelP();
	int numElements = dgnRefActive->GetElementCount(DgnModelSections::GraphicElements);
		
	//Open ProgressBar	
	this->_progressBar->numGraphicElement = numElements; //Count the element (this function gets also the deleted ones??)
	this->_progressBar->Open(L"Working...");

#if false	
	int numThreads = boost::thread::hardware_concurrency();
	vector<ElementHandle> elementsVec;
	for (PersistentElementRefP elemRef : *pGraElement)
	{
		ElementHandle currentElem(elemRef);
		elementsVec.push_back(currentElem);
	}
	auto elementsVecSections = splitVector<ElementHandle>(elementsVec, numThreads);

	vector<boost::thread*> bthread;
	for (int i = 0; i < elementsVecSections.size(); i++)
	{
		bthread.push_back(
			new boost::thread(
				&InitializationHelper::threadFunction,
				this,
				elementsVecSections.at(i),
				boost::ref(propsDictVec),
				boost::ref(smartFeatureContainerVector)
			)
		);
	}

	for (auto& t : bthread)
	{
		t->join();
	}
#endif
#if true
	for (PersistentElementRefP elemRef : *pGraElement)
	{	
		ElementHandle currentElem(elemRef);

		WString elDescr, myString;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
		this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

		DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));

		ReaderPropertiesBundle* readerPropertiesBundle = this->_propertiesReaderProcessor->processElementReaderProperties(currentElem);
		propertiesDictionary->addElementReaderPropertiesBundle(readerPropertiesBundle);

		iterateSubElements(elemRef, propertiesDictionary);

		if (SmartFeatureElement::IsSmartFeature(currentElem))
		{
			ElementHandle leafNode;
			SmartFeatureNodePtr sFeatNode;
			T_SmartFeatureVector sFeatVec;

			SmartFeatureContainer* smartFeatureContainer = createSmartFeatureContainer(currentElem, sFeatNode, leafNode, sFeatVec);

			if (smartFeatureContainer != nullptr) {
				smartFeatureContainerVector.push_back(smartFeatureContainer);
				propertiesDictionary->setSmartFeatureContainer(smartFeatureContainer);
			}
		}

		propsDictVec.push_back(propertiesDictionary);

		this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

		//ProgressBar
		this->_progressBar->IncrementIndex();
		myString.Sprintf(L"Processing Elements... [%d/%d]  (%s)", this->_progressBar->GetIndex(), this->_progressBar->numGraphicElement, elDescr);
		this->_progressBar->Update(myString);
	}
#endif
	//Close ProgressBar
	this->_progressBar->Close();

	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Ended elements processing -!");
}

void InitializationHelper::threadFunction(vector<ElementHandle> vecElemen, vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	//boost::unique_lock<boost::shared_mutex> guard(_mutex);

	for (ElementHandle currentElem : vecElemen)
	{
		//ElementHandle currentElem(elemRef);

		WString elDescr, myString;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
		this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

		DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));

		ReaderPropertiesBundle* readerPropertiesBundle = this->_propertiesReaderProcessor->processElementReaderProperties(currentElem);
		propertiesDictionary->addElementReaderPropertiesBundle(readerPropertiesBundle);
		{
			boost::unique_lock<boost::shared_mutex> guard(_mutex);

			_iteration->iterateSubElements(currentElem, propertiesDictionary);
		}

		if (SmartFeatureElement::IsSmartFeature(currentElem))
		{
			ElementHandle leafNode;
			SmartFeatureNodePtr sFeatNode;
			T_SmartFeatureVector sFeatVec;

			SmartFeatureContainer* smartFeatureContainer = createSmartFeatureContainer(currentElem, sFeatNode, leafNode, sFeatVec);

			if (smartFeatureContainer != nullptr) {
				smartFeatureContainerVector.push_back(smartFeatureContainer);
				propertiesDictionary->setSmartFeatureContainer(smartFeatureContainer);
			}
		}

		{
			boost::unique_lock<boost::shared_mutex> guard(_mutex);
			propsDictVec.push_back(propertiesDictionary);

			this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);
		}
		//ProgressBar
		this->_progressBar->IncrementIndex();
		myString.Sprintf(L"Processing Elements... [%d/%d]  (%s)", this->_progressBar->GetIndex(), this->_progressBar->numGraphicElement, elDescr);
		this->_progressBar->Update(myString);
		
	}
}
#pragma warning( pop ) 
