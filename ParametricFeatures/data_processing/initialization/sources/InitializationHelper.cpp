#include "../headers/InitializationHelper.h"


InitializationHelper::InitializationHelper()
{	
	this->mDgnModel = ISessionMgr::GetActiveDgnModelP();
	this->mDgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName();//.AppendUtf8(".txt");

	this->pGraElement = mDgnModel->GetGraphicElementsP();

	//this->filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	this->filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::string ifcOutputFileName = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/IfcCustomName.ifc";
	
	SessionManager* sm = sm->getInstance();
	sm->setDataOutputFilePath(filePath);
	sm->setIfcOutputFilePath(ifcOutputFileName);
}

SmartFeatureContainer * InitializationHelper::createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec)
{
	std::ofstream outfile;

	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer(currentElem.GetElementId());
	long newLocalNodeId = -1, newParentLocalNodeId = -1, newGlobalNodeId = -1;

	SmartFeatureElement::ExtractTree(sFeatNode, currentElem);

	sFeatNode->GetAllChildrenRecursively(sFeatVec);

	for (size_t i = 0; i < sFeatVec.size(); i++)
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << "start==================" << std::endl;
		outfile.close();
		if (sFeatVec.at(i)->GetParent() != nullptr)
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "Parent Ref Count: " << sFeatVec.at(i)->GetParent()->GetRefCount() << std::endl;
			outfile << "Parent ID: " << sFeatVec.at(i)->GetParent()->GetNodeId() << std::endl;
			outfile.close();

			newParentLocalNodeId = sFeatVec.at(i)->GetParent()->GetNodeId();
		}

		newLocalNodeId = sFeatVec.at(i)->GetNodeId();

		outfile.open(filePath, std::ios_base::app);
		outfile << "Node ID: " << newLocalNodeId << std::endl;
		outfile.close();

		sFeatVec.at(i)->GetLeaf(leafNode);

		if (leafNode.IsValid()) {

			newGlobalNodeId = leafNode.GetElementId();
			
			outfile.open(filePath, std::ios_base::app);
			outfile << "Leaf ID:  " << leafNode.GetElementId() << std::endl;
			outfile.close();

		}

		outfile.open(filePath, std::ios_base::app);
		outfile << "finish==================" << std::endl;
		outfile.close();

		
		smartFeatureContainer->insertNodeInTree(newLocalNodeId, newParentLocalNodeId, newGlobalNodeId);

	}

	outfile.open(filePath, std::ios_base::app);
	outfile << "Smart Feat Element Node ID: " << sFeatNode->GetNodeId() << std::endl;
	outfile << "Number of Child: " << sFeatNode->GetChildCount() << std::endl;
	outfile.close();


	return smartFeatureContainer;
}

StatusInt InitializationHelper::iterateSubElements(ElementRefP elementRefP, DictionaryProperties* dictionaryProperties)
{
	ElementHandle eh(elementRefP);	 //	Can also construct an ElemHandle from an MSElementDescr*

	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	int index = 0;


	outfile << "eh id = " << eh.GetElementId() << std::endl;
	outfile << "eh type = " << eh.GetElementType() << std::endl;
	outfile << "index1 = " << index << std::endl;

	outfile.close();

	for (ChildElemIter child(eh); child.IsValid(); child = child.ToNext())
	{
		iterateSubElements(child.GetElementRef(), dictionaryProperties);
		++index;
	}
	if(index==0){

		outfile.open(filePath, std::ios_base::app);

		outfile << "eh2 id" << eh.GetElementId() << std::endl;
		outfile << "eh2 type" << eh.GetElementType() << std::endl;
		outfile << "index2 = " << index << std::endl;


		outfile.close();

		ElementBundle* elementBundle = new ElementBundle();
		elementBundle->setElementHandle(eh);

		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();
		ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(eh, elementBundle);
		elementBundle->setReaderPropertiesBundle(*readerPropertiesBundle);

		GraphicsProcessor graphicsProcessor = GraphicsProcessor();
		GraphicsProcessorHelper* GraphicsProcessorHelper = graphicsProcessor.getGraphicsProcessorHelper();

		GraphicsProcessorHelper->mCurrentElementHandle = eh;
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
void InitializationHelper::processDgnGraphicsElements(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	std::ofstream outfile;	
	outfile.open(filePath);
	outfile << "------------------------" << std::endl;
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

	outfile.open(filePath, std::ios_base::app);
	outfile << "------------------------" << std::endl;
	outfile << "DgnModelRefP Unit System" << std::endl;
	outfile << std::fixed;
	outfile << std::endl;

	outfile << "UnitSystem::English 1" << std::endl;
	outfile << "UnitSystem::Metric 2" << std::endl;
	outfile << "UnitSystem::USSurvey 3" << std::endl;
	outfile << std::endl;
	
	outfile << "UnitBase::Meter 1" << std::endl;
	outfile << "UnitBase::Degree 2" << std::endl;
	outfile << std::endl;
	
	outfile << "Master unit: " << StringUtils::getNormalizedString(masterUnit.GetLabel()) << std::endl;
	outfile << "masterUnit System" << (int)masterUnit.GetSystem() << std::endl;
	outfile << "masterUnit Base" << (int)masterUnit.GetBase() << std::endl;
	outfile << "masterUnit Numerator" << masterUnit.GetNumerator() << std::endl;
	outfile << "masterUnit Denominator" << masterUnit.GetDenominator() << std::endl;
	outfile << "Division Ratio" << (masterUnit.GetNumerator() / masterUnit.GetDenominator()) << std::endl;
	outfile << std::endl;

	outfile << "Sub unit: " << StringUtils::getNormalizedString(subUnit.GetLabel()) << std::endl;
	outfile << "subUnit System" << (int)subUnit.GetSystem() << std::endl;
	outfile << "subUnit Base" << (int)subUnit.GetBase() << std::endl;
	outfile << "subUnit Numerator" << subUnit.GetNumerator() << std::endl;
	outfile << "subUnit Denominator" << subUnit.GetDenominator() << std::endl;
	outfile << "Division Ratio" << (subUnit.GetNumerator() / subUnit.GetDenominator()) << std::endl;
	outfile << std::endl;

	outfile << "Storage unit: " << StringUtils::getNormalizedString(storageUnit.GetLabel()) << std::endl;
	outfile << "storageUnit System" << (int)storageUnit.GetSystem() << std::endl;
	outfile << "storageUnit Base" << (int)storageUnit.GetBase() << std::endl;
	outfile << "storageUnit Numerator" << storageUnit.GetNumerator() << std::endl;
	outfile << "storageUnit Denominator" << storageUnit.GetDenominator() << std::endl;
	outfile << "Division Ratio" << (storageUnit.GetNumerator() / storageUnit.GetDenominator()) << std::endl;
	outfile << std::endl;

	outfile << "UOR per storage" << uorPerUnit << std::endl;
	outfile << "AnnotationScaleFactor" << modelInfo->GetAnnotationScaleFactor() << std::endl;
	outfile << "Global Origin [x,y,z]= " << globalOrigin.x << ", " << globalOrigin.y << ", " << globalOrigin.z << std::endl;
	
	outfile << "------------------------" << std::endl;
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
					


		outfile.open(filePath, std::ios_base::app);
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "Element Description: " << static_cast<Utf8String>(elDescr.GetWCharCP()) << std::endl;
		outfile << "Element ID: " << currentElem.GetElementId() << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << std::endl;
		outfile.close();

		ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(currentElem);
		propertiesDictionary->addElementReaderPropertiesBundle(readerPropertiesBundle);
		GraphicsProcessorHelper->mCurrentElementHandle = currentElem; 
		
		if (GraphicsProcessorHelper->mBRepGraphicProperties != nullptr)
		{
			if (GraphicsProcessorHelper->mBRepGraphicProperties->getSolidEntityVector().size() > 0) {
				//propertiesDictionary->addGraphicProperties(GraphicsProcessorHelper->mBRepGraphicProperties);
				//TODO [MP] check this shit
			}

			GraphicsProcessorHelper->mBRepGraphicProperties = nullptr;
			GraphicsProcessorHelper->mNumberSolidEntity = 0;
		}


		propsDictVec.push_back(propertiesDictionary);


		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "Element Description: " << static_cast<Utf8String>(elDescr.GetWCharCP()) << std::endl;
		outfile << "Element: ID " << currentElem.GetElementId() << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << std::endl;
		outfile.close();

	}
}
#pragma warning( pop ) 
