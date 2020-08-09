#include "../headers/InitializationEnhancer.h"


InitializationEnhancer::InitializationEnhancer()
{	
	this->mDgnModel = ISessionMgr::GetActiveDgnModelP();
	this->mDgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName();//.AppendUtf8(".txt");

	this->pGraElement = mDgnModel->GetGraphicElementsP();

	this->filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	//this->filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
}

SmartFeatureContainer * InitializationEnhancer::createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec)
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

//#pragma warning( push )
//#pragma warning( disable : 4700)
//#pragma warning( disable : 4189)
//void InitializationEnhancer::testFunction(PersistentElementRefP elemRef)
//{
//	std::ofstream outfile;
//	ElementRefP* referenceDependents;
//	ElementRefP parentRef = elemRef->GetParentElementRef();
//
//	// Handles persistance of ECInstances
//	DgnECManagerR ecMgr = DgnECManager::GetManager();
//	RelationshipEntryVector relationshipVec;
//	ecMgr.FindRelationshipEntriesOnElement(elemRef, relationshipVec);
//
//	outfile.open(filePath, std::ios_base::app);
//	outfile << "Level Position of the current element: " << elemRef->GetLevel() << std::endl;
//	outfile << "Dependences of the element request: " << elemRef->GetDependents(referenceDependents, 3) << std::endl;
//	outfile << "Is Complex Component: " << elemRef->IsComplexComponent() << std::endl;
//	outfile << std::endl;
//	outfile.close();
//
//	if (parentRef != nullptr)
//	{
//		ElementHandle p(parentRef);
//		outfile.open(filePath, std::ios_base::app);
//		outfile << "Parent element : " << p.GetElementId() << std::endl;
//		outfile << std::endl;
//		outfile.close();
//	}
//
//	for (size_t i = 0; i < 3; i++)
//	{
//		if (referenceDependents[i] != nullptr) {
//			ElementHandle df(*referenceDependents);
//			WString eDescr;
//			df.GetHandler().GetDescription(df, eDescr, 100);
//
//			outfile.open(filePath, std::ios_base::app);
//			outfile << "Dependences element: " << df.GetElementId() << std::endl;
//			outfile << "Element Description: " << static_cast<Utf8String>(eDescr.GetWCharCP()) << std::endl;
//			outfile << "------" << std::endl;
//			outfile << std::endl;
//			outfile.close();
//		}
//	}
//
//
//
//	for (auto rel : relationshipVec)
//	{
//		outfile.open(filePath, std::ios_base::app);
//		outfile << "Relationship " << std::endl;
//		outfile << "Class Name: " << StringUtils::getString(rel.RelationshipClassName) << std::endl;
//		outfile << "Schema Name: " << StringUtils::getString(rel.RelationshipSchemaName) << std::endl;
//		outfile << "Source Name: " << StringUtils::getString(rel.SourceClassName) << std::endl;
//		outfile << "Source Schema Name: " << StringUtils::getString(rel.SourceSchemaName) << std::endl;
//		outfile << "Source InstanceId: " << StringUtils::getString(rel.SourceInstanceId) << std::endl;
//		outfile << "Target Class Name: " << StringUtils::getString(rel.TargetClassName) << std::endl;
//		outfile << "Target Schema Name: " << StringUtils::getString(rel.TargetSchemaName) << std::endl;
//		outfile << "Target InstanceId: " << StringUtils::getString(rel.TargetInstanceId) << std::endl;
//		outfile << std::endl;
//		outfile.close();
//	}
//
//}

StatusInt InitializationEnhancer::findElementByType(ElementRefP elementRefP, DictionaryProperties* dictionaryProperties)
{
	ElementHandle eh(elementRefP);	 //	Can also construct an ElemHandle from an MSElementDescr*

	if (MSElementTypes::LINE_ELM == eh.GetElementType()|| MSElementTypes::LINE_STRING_ELM == eh.GetElementType() || MSElementTypes::SHAPE_ELM == eh.GetElementType() || 
		MSElementTypes::CURVE_ELM == eh.GetElementType() || MSElementTypes::ELLIPSE_ELM == eh.GetElementType() || MSElementTypes::ARC_ELM == eh.GetElementType() || 
		MSElementTypes::TEXT_ELM == eh.GetElementType() || MSElementTypes::SURFACE_ELM == eh.GetElementType() || MSElementTypes::SOLID_ELM == eh.GetElementType() || 
		MSElementTypes::BSPLINE_POLE_ELM == eh.GetElementType() || MSElementTypes::POINT_STRING_ELM == eh.GetElementType() || MSElementTypes::CONE_ELM == eh.GetElementType() || 
		MSElementTypes::BSPLINE_SURFACE_ELM == eh.GetElementType() || MSElementTypes::BSURF_BOUNDARY_ELM == eh.GetElementType() || MSElementTypes::BSPLINE_KNOT_ELM == eh.GetElementType() || 
		MSElementTypes::BSPLINE_CURVE_ELM == eh.GetElementType() || MSElementTypes::BSPLINE_WEIGHT_ELM == eh.GetElementType() || MSElementTypes::DIMENSION_ELM == eh.GetElementType() || 
		MSElementTypes::MULTILINE_ELM == eh.GetElementType() || MSElementTypes::ATTRIBUTE_ELM == eh.GetElementType() || MSElementTypes::LINE_ELM == eh.GetElementType())
	{

		//outfile << std::endl;
		//outfile << "Child3 id" << child3.GetElementId() << std::endl;
		//outfile << "Child3 type" << child3.GetElementType() << std::endl;

		//ElementHandle childEl3(child3);

		ElementBundle* elementBundle = new ElementBundle();
		elementBundle->setElementHandle(eh);

		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();
		ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(eh);
		elementBundle->setReaderPropertiesBundle(*readerPropertiesBundle);

		GraphicsProcessor graphicsProcessor = GraphicsProcessor();
		GraphicsProcessorEnhancer* graphicsProcessorEnhancer = graphicsProcessor.getGraphicsProcessorEnhancer();

		graphicsProcessorEnhancer->mCurrentElementHandle = eh;
		graphicsProcessorEnhancer->setElementBundle(*elementBundle);
		ElementGraphicsOutput::Process(eh, graphicsProcessor);

		dictionaryProperties->addElementBundle(elementBundle);

		return SUCCESS;
	}

	for (ChildElemIter child(eh); child.IsValid(); child = child.ToNext())
	{
		findElementByType(child.GetElementRef(), dictionaryProperties);
	}

	return SUCCESS;
}

#pragma warning( pop ) 

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning (disable:4311 4302 4312)
void InitializationEnhancer::processDgnGraphicsElements(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	std::ofstream outfile;	
	outfile.open(filePath);
	outfile << "------------------------" << std::endl;
	outfile.close();
			
	GraphicsProcessor graphicsProcessor = GraphicsProcessor();
	GraphicsProcessorEnhancer* graphicsProcessorEnhancer = graphicsProcessor.getGraphicsProcessorEnhancer();
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

	//Helpful for nested dgn attacchments
	//auto dgnRefActive = ISessionMgr::GetActiveDgnModelRefP();
	auto dgnRefActive = ISessionMgr::GetActiveDgnModelP();
	
	//dgnRefActive->GetReachableElements()

	for (PersistentElementRefP elemRef : *pGraElement)
	{	
		
		DgnModelP c = elemRef->GetDgnModelP();
		ElementHandle currentElem(elemRef);


		// TODO might be useful

		//ElementId elemIdPrev(-1);

		//DictionaryProperties* d1 = new DictionaryProperties(-1, "");

		WString elDescr;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

		SmartFeatureContainer* smartFeatureContainer = nullptr;
		DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));
		graphicsProcessorEnhancer->setDictionaryProperties(*propertiesDictionary);

		findElementByType(elemRef, propertiesDictionary);


		//outfile.open(filePath, std::ios_base::app);


		//for (ChildElemIter child(currentElem, ExposeChildrenReason::Edit); child.IsValid(); child = child.ToNext())
		//{
		//	outfile << std::endl;
		//	outfile << "Child id" << child.GetElementId() << std::endl;
		//	outfile << "Child type" << child.GetElementType() << std::endl;
		//	ElementHandle childEl(child);

		//	if (MSElementTypes::CELL_HEADER_ELM == child.GetElementType()) {


		//		//propertiesReaderProcessor->processElementReaderProperties(childEl, *d, *s);

		//		//graphicsProcessorEnhancer->setDictionaryProperties(*d);
		//		//graphicsProcessorEnhancer->mCurrentElementHandle = childEl;	

		//		//Handler::ExposeChildren(currentElem,ExposeChildrenReason::Query);

		//		outfile << "is CELL_HEADER_ELM" << std::endl;

		//		//ElementGraphicsOutput::Process(childEl, graphicsProcessor);
		//	}
		//	if (MSElementTypes::SHAREDCELL_DEF_ELM == child.GetElementType()) {
		//		outfile << "is SHAREDCELL_DEF_ELM" << std::endl;
		//	}
		//	if (MSElementTypes::SHARED_CELL_ELM == child.GetElementType()) {
		//		outfile << "is SHARED_CELL_ELM" << std::endl;
		//	}

		//	for (ChildElemIter child2(childEl, ExposeChildrenReason::Query); child2.IsValid(); child2 = child2.ToNext())
		//	{
		//		outfile << std::endl;
		//		outfile << "Child2 id" << child2.GetElementId() << std::endl;
		//		outfile << "Child2 type" << child2.GetElementType() << std::endl;
		//		ElementHandle childEl2(child2);
		//		//propertiesReaderProcessor->processElementReaderProperties(childEl2, *d, *s);

		//		for (ChildElemIter child3(childEl2, ExposeChildrenReason::Query); child3.IsValid(); child3 = child3.ToNext())
		//		{
		//			outfile << std::endl;
		//			outfile << "Child3 id" << child3.GetElementId() << std::endl;
		//			outfile << "Child3 type" << child3.GetElementType() << std::endl;

		//			ElementHandle childEl3(child3);

		//			ElementBundle* elementBundle = new ElementBundle();
		//			elementBundle->setElementHandle(childEl3);

		//			ReaderPropertiesBundle* readerPropertiesBundle = propertiesReaderProcessor->processElementReaderProperties(childEl3);
		//			elementBundle->setReaderPropertiesBundle(*readerPropertiesBundle);

		//			graphicsProcessorEnhancer->mCurrentElementHandle = childEl3;
		//			graphicsProcessorEnhancer->setElementBundle(*elementBundle);
		//			ElementGraphicsOutput::Process(childEl3, graphicsProcessor);

		//			propertiesDictionary->addElementBundle(elementBundle);


		//			
		//		}
		//	}


		//}
		//outfile.close();



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
		graphicsProcessorEnhancer->mCurrentElementHandle = currentElem; //store the element in graphic processor enhancer
		

		//ElementGraphicsOutput::Process(currentElem, graphicsProcessor);

		//Add as BRep after finishing processing
		if (graphicsProcessorEnhancer->mBRepGraphicProperties != nullptr)
		{
			if (graphicsProcessorEnhancer->mBRepGraphicProperties->getSolidEntityVector().size() > 0) {
				//propertiesDictionary->addGraphicProperties(graphicsProcessorEnhancer->mBRepGraphicProperties);
				//TODO [MP] check this shit
			}

			graphicsProcessorEnhancer->mBRepGraphicProperties = nullptr;
			graphicsProcessorEnhancer->mNumberSolidEntity = 0;
		}


		propsDictVec.push_back(propertiesDictionary);

		//testFunction(elemRef);

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



//int InitializationEnhancer::ElementRefScanCallback(ElementRef eleR, void *callbackArg, ScanCriteriaP pCriteria) {
//
//	ScanCallBackData*	data = (ScanCallBackData*)callbackArg;
//	DgnModelRefP modelRef = mdlScanCriteria_getModel(pCriteria);
//	DgnModelRefP dgnModelRef = modelRef;
//
//	EditElemHandle eh(eleR, dgnModelRef);
//	MSElement* eleP = eh.GetElementP();
//	UInt32 filePos = elementRef_getFilePos(eleR);
//	ElementID eleId = eleId = mdlElement_getID(eleP);
//	UInt32 level;
//	mdlElement_getProperties(&level, NULL, NULL, NULL, NULL, NULL, NULL, NULL, eleP);
//	MSWChar* pLevelNameOut = new MSWChar[100];
//	mdlLevel_getName(pLevelNameOut, 100, dgnModelRef, level);
//	wstring eleLevelNamew(pLevelNameOut);
//	string eleLevelName = narrowWString(eleLevelNamew);
//	if (mdlElement_isComplexHeader(eleP))
//	{
//		MSElementDescr* elemDescrP;
//		void* params = dgnModelRef;
//		UInt32 worked = mdlElmdscr_getByElemRef(&elemDescrP, eleR, dgnModelRef, TRUE, &filePos);
//		int(*foo)(MSElement *, void *, int, UInt32, MSElementDescr *);
//		foo = &elmFunc;
//		int op = worked = mdlElmdscr_operation(elemDescrP, (MdlFunctionP)foo, params, ELMD_ALL_ONCE);
//		if (op == 3)
//		{
//			mdlSelect_addElement(filePos, dgnModelRef, NULL, TRUE);
//		}
//	}
//	if (eleLevelName.find(levelName) != std::string::npos) {//If the string is contained in the level's name
//		mdlSelect_addElement(filePos, dgnModelRef, NULL, TRUE);
//	}
//
//	return SUCCESS;
//}