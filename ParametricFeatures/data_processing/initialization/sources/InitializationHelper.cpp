#include "../headers/InitializationHelper.h"

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning (disable:4311 4302 4312 4100)

InitializationHelper::InitializationHelper(vector<ElementHandle> pGraElement, bool onlySelected)
{	
	this->mDgnModel = ISessionMgr::GetActiveDgnModelP();
	//this->pGraElement = mDgnModel->GetGraphicElementsP();
	this->pGraElement = pGraElement;
	this->onlySelected = onlySelected;
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

StatusInt InitializationHelper::iterateSubElements(ElementHandle eh, DictionaryProperties*& dictionaryProperties)
{		
	_logger->logDebug(__FILE__, __LINE__, __func__);

	//ElementHandle eh(elementRefP);	 //	Can also construct an ElemHandle from an MSElementDescr*

	int index = 0;

	//TODO[SB] if (el->GetElementType() == MSElementTypes::CELL_HEADER_ELM) MSElementTypes:: https://communities.bentley.com/products/programming/microstation_programming/f/microstation-programming---forum/202544/net-sdk-get-selected-elements

	for (ChildElemIter child(eh); child.IsValid(); child = child.ToNext())
	{
		ElementHandle elm(child.GetElementRef());
		iterateSubElements(elm, dictionaryProperties);// , propertiesReaderProcessor);
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
	int numElements = dgnRefActive->GetElementCount(DgnModelSections::GraphicElements); //Count the element (this function gets also the deleted ones??)
		
	//Open ProgressBar	
	this->_progressBar->numGraphicElement = numElements; 
	this->_progressBar->Open(L"Working...");

	//TODO[SB] for nested dgn attached dgnModelRef->GetReachableElements();	
	/*ReachableElementCollection rCollection = mDgnModel->GetReachableElements();
	for (auto a : rCollection)
	{
		
	}*/
	if (onlySelected)
	{
		size_t numSelected = SelectionSetManager::GetManager().NumSelected();

		for (size_t i = 0; i < numSelected; i++)
		{
			ElementRefP elemRef = NULL;
			StatusInt status = SelectionSetManager::GetManager().GetElement(i, &elemRef, &dgnModelRef);

			ElementHandle currentElem(elemRef);

			pGraElement.clear();
			pGraElement.push_back(currentElem);
		}
	}

	string errorMessageAtElementsProcessing = "An error occured while iterating and processing pGraElement";
	//for (PersistentElementRefP elemRef : *pGraElement)
	for (ElementHandle currentElem : pGraElement)
	{	
		try
		{
			//ElementHandle currentElem(elemRef);

			WString elDescr, myString;

			currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
			this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

			DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));

			ReaderPropertiesBundle* readerPropertiesBundle = this->_propertiesReaderProcessor->processElementReaderProperties(currentElem);
			propertiesDictionary->addElementReaderPropertiesBundle(readerPropertiesBundle);

			iterateSubElements(currentElem, propertiesDictionary);

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
		catch (exception& ex) {
			_logger->logError(__FILE__, __LINE__, __FUNCTION__, ex, errorMessageAtElementsProcessing);
		}
		catch (...) {
			_logger->logError(__FILE__, __LINE__, __FUNCTION__, errorMessageAtElementsProcessing);

		}
	}

	//Close ProgressBar
	this->_progressBar->Close();

	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Ended elements processing -!");
}

#pragma warning( pop ) 
