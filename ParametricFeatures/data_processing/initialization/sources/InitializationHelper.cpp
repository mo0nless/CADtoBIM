#include "../headers/InitializationHelper.h"

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning (disable:4311 4302 4312 4100 )

InitializationHelper::InitializationHelper(vector<PersistentElementRefP> pGraElement, bool onlySelected)
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

	ofstream outfile;
	string filePath = SessionManager::getInstance()->getDataOutputFilePath();

	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer(currentElem.GetElementId());
	long newLocalNodeId = -1, newParentLocalNodeId = -1, newGlobalNodeId = -1;

	SmartFeatureElement::ExtractTree(sFeatNode, currentElem);

	sFeatNode->GetAllChildrenRecursively(sFeatVec);

	outfile.open(filePath, std::ios_base::app);
	outfile << std::endl;	
	outfile << "----- SMART FEATURE -----" << endl;


	for (size_t i = 0; i < sFeatVec.size(); i++)
	{
		outfile << std::endl;
		outfile << "*** Tree Nodes ***" << endl;
		if (sFeatVec.at(i)->GetParent() != nullptr)
		{
			newParentLocalNodeId = sFeatVec.at(i)->GetParent()->GetNodeId();
			outfile << "Parent Node ID: " << newParentLocalNodeId << endl;
		}

		newLocalNodeId = sFeatVec.at(i)->GetNodeId();
		sFeatVec.at(i)->GetLeaf(leafNode);

		outfile << "Local Node ID: " << newLocalNodeId << endl;

		if (leafNode.IsValid()) {

			newGlobalNodeId = leafNode.GetElementId();

			outfile << "Global Node ID: " << newGlobalNodeId << endl;
		}
		smartFeatureContainer->insertNodeInTree(newLocalNodeId, newParentLocalNodeId, newGlobalNodeId);

	}

	outfile << std::endl;
	outfile << "----- END SMART FEATURE -----" << endl;
	outfile.close();

	return smartFeatureContainer;
}

StatusInt InitializationHelper::iterateSubElements(ElementRefP elementRefP, DictionaryProperties*& dictionaryProperties)
{		
	_logger->logDebug(__FILE__, __LINE__, __func__);

	ElementHandle elementHandle(elementRefP);	 //	Can also construct an ElemHandle from an MSElementDescr*
	
	// Since we have an elementRef from the DgnModel, we know that FileLevelCache is never NULL.
	FileLevelCache* fileLevelCache = mDgnModel->GetFileLevelCacheP();

	int index = 0;

	//TODO[SB] if (el->GetElementType() == MSElementTypes::CELL_HEADER_ELM) MSElementTypes:: https://communities.bentley.com/products/programming/microstation_programming/f/microstation-programming---forum/202544/net-sdk-get-selected-elements

	for (ChildElemIter child(elementHandle); child.IsValid(); child = child.ToNext())
	{
		//ElementHandle elm(child.GetElementRef());
		iterateSubElements(child.GetElementRef(), dictionaryProperties);// , propertiesReaderProcessor);
		++index;
	}
	if(index==0){

		LevelHandle level = fileLevelCache->GetLevel(elementRefP->GetLevel());

		IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle = new IfcGraphicPropertiesBundle(elementHandle, level);

		GraphicsProcessor* graphicsProcessor = new GraphicsProcessor();
		GraphicsProcessorHelper* graphicsProcessorHelper = graphicsProcessor->getGraphicsProcessorHelper();

		graphicsProcessorHelper->setElementHandle(elementHandle);
		graphicsProcessorHelper->setIfcGraphicPropertiesBundle(*ifcGraphicPropertiesBundle);
		graphicsProcessorHelper->setDictionaryProperties(*dictionaryProperties);
				
		ElementGraphicsOutput::Process(elementHandle, *graphicsProcessor);

		dictionaryProperties->addGraphicGeomBundle(ifcGraphicPropertiesBundle);

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
	/*ReachableElementCollection rCollection = mDgnModel->GetReachableElements();*/

	//for (PersistentElementRefP elemRef : *pGraElement)
	for (PersistentElementRefP elemRef : pGraElement)
	{	
		try
		{
			ElementHandle currentElem(elemRef);

			WString elDescr, myString;

			currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
			this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

			DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getNormalizedString(elDescr.GetWCharCP()));

			vector<ReaderPropertiesBundle*> readerPropertiesBundleVector = this->_propertiesReaderProcessor->processElementReaderProperties(currentElem);
			propertiesDictionary->setElementReaderPropertiesBundleVector(readerPropertiesBundleVector);
			propertiesDictionary->setElementClassName(this->_propertiesReaderProcessor->getElementClassName());
			
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
			else
			{
				iterateSubElements(elemRef, propertiesDictionary);
			}


			propsDictVec.push_back(propertiesDictionary);

			this->_modelerDataWriterManager->writeElementInfoDataToFile(currentElem.GetElementId(), elDescr);

			//ProgressBar
			this->_progressBar->IncrementIndex();
			myString.Sprintf(L"Processing Elements... [%d/%d]  (%s)", this->_progressBar->GetIndex(), this->_progressBar->numGraphicElement, elDescr);
			this->_progressBar->Update(myString);
		}
		catch (exception& ex) {
			_logger->logError(__FILE__, __LINE__, __FUNCTION__, ex, "An error occured while iterating and processing pGraElement");
		}
		catch (...) {
			_logger->logError(__FILE__, __LINE__, __FUNCTION__, "An error occured while iterating and processing pGraElement");

		}
	}

	//Close ProgressBar
	this->_progressBar->Close();

	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Ended elements processing -!");
}

#pragma warning( pop ) 
