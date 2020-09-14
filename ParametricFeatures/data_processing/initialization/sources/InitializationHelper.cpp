#include "../headers/InitializationHelper.h"


InitializationHelper::InitializationHelper()
{	

	this->filePath = SessionManager::getInstance()->getDataOutputFilePath();
	this->mDgnModel = ISessionMgr::GetActiveDgnModelP();
	this->mDgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName();//.AppendUtf8(".txt");
	this->pGraElement = mDgnModel->GetGraphicElementsP();
}

SmartFeatureContainer * InitializationHelper::createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);


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
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

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
#pragma warning (disable:4311 4302 4312)
void InitializationHelper::processDgnGraphicsElements(vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	_logger->logInfo(__FILE__, __LINE__, __FUNCTION__, "!- Starting elements processing -!");

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
	
	//Open ProgressBar
	DialogCompletionBar progressBar = DialogCompletionBar(); 
	progressBar.Open(L"Working...");

	//Count the element (this function gets also the deleted ones??)
	int numGraphicElement = dgnRefActive->GetElementCount(DgnModelSections::GraphicElements);
	int percentage = 0;
	int index = 0;
	WString myString;	

	for (PersistentElementRefP elemRef : *pGraElement)
	{	
		DgnModelP c = elemRef->GetDgnModelP();
		ElementHandle currentElem(elemRef);

		WString elDescr;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

		SmartFeatureContainer* smartFeatureContainer = nullptr;
		DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));
		GraphicsProcessorHelper->setDictionaryProperties(*propertiesDictionary);

		//ProgressBar
		myString.Sprintf(L"Processing Elements... [%d/%d]  (%s)", index, numGraphicElement, elDescr);
		percentage = 100 * index / numGraphicElement;

		if (percentage > 100)
			percentage = 100;

		progressBar.Update(myString, percentage);
		index++;

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
		//Close ProgressBar
		progressBar.Close();

		_logger->logInfo(__FILE__, __LINE__, __FUNCTION__, "!- Ended elements processing -!");
	}
}
#pragma warning( pop ) 
