#include "../headers/InitializationEnhancer.h"


InitializationEnhancer::InitializationEnhancer()
{	
	this->mDgnModel = ISessionMgr::GetActiveDgnModelP();
	this->mDgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName();//.AppendUtf8(".txt");

	this->pGraElement = mDgnModel->GetGraphicElementsP();

	//this->filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	this->filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
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

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
void InitializationEnhancer::testFunction(PersistentElementRefP elemRef)
{
	std::ofstream outfile;
	ElementRefP* referenceDependents;
	ElementRefP parentRef = elemRef->GetParentElementRef();

	// Handles persistance of ECInstances
	DgnECManagerR ecMgr = DgnECManager::GetManager();
	RelationshipEntryVector relationshipVec;
	ecMgr.FindRelationshipEntriesOnElement(elemRef, relationshipVec);

	outfile.open(filePath, std::ios_base::app);
	outfile << "Level Position of the current element: " << elemRef->GetLevel() << std::endl;
	outfile << "Dependences of the element request: " << elemRef->GetDependents(referenceDependents, 3) << std::endl;
	outfile << "Is Complex Component: " << elemRef->IsComplexComponent() << std::endl;
	outfile << std::endl;
	outfile.close();

	if (parentRef != nullptr)
	{
		ElementHandle p(parentRef);
		outfile.open(filePath, std::ios_base::app);
		outfile << "Parent element : " << p.GetElementId() << std::endl;
		outfile << std::endl;
		outfile.close();
	}

	for (size_t i = 0; i < 3; i++)
	{
		if (referenceDependents[i] != nullptr) {
			ElementHandle df(*referenceDependents);
			WString eDescr;
			df.GetHandler().GetDescription(df, eDescr, 100);

			outfile.open(filePath, std::ios_base::app);
			outfile << "Dependences element: " << df.GetElementId() << std::endl;
			outfile << "Element Description: " << static_cast<Utf8String>(eDescr.GetWCharCP()) << std::endl;
			outfile << "------" << std::endl;
			outfile << std::endl;
			outfile.close();
		}
	}



	for (auto rel : relationshipVec)
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << "Relationship " << std::endl;
		outfile << "Class Name: " << StringUtils::getString(rel.RelationshipClassName) << std::endl;
		outfile << "Schema Name: " << StringUtils::getString(rel.RelationshipSchemaName) << std::endl;
		outfile << "Source Name: " << StringUtils::getString(rel.SourceClassName) << std::endl;
		outfile << "Source Schema Name: " << StringUtils::getString(rel.SourceSchemaName) << std::endl;
		outfile << "Source InstanceId: " << StringUtils::getString(rel.SourceInstanceId) << std::endl;
		outfile << "Target Class Name: " << StringUtils::getString(rel.TargetClassName) << std::endl;
		outfile << "Target Schema Name: " << StringUtils::getString(rel.TargetSchemaName) << std::endl;
		outfile << "Target InstanceId: " << StringUtils::getString(rel.TargetInstanceId) << std::endl;
		outfile << std::endl;
		outfile.close();
	}

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
	outfile << "" << std::endl;
	outfile.close();
			
	GraphicsProcessor graphicsProcessor = GraphicsProcessor();
	GraphicsProcessorEnhancer* graphicsProcessorEnhancer = graphicsProcessor.getGraphicsProcessorEnhancer();
	PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();

	DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();
	//DgnModelRef::inter
	//dgnModelRef->
	//ISessionMgr::get

	//ScanCriteria* s = new ScanCriteria();
	
	
	//dgnModelRef->AsDgnAttachmentCP()->GetFileLevelCacheP()->

	for (PersistentElementRefP elemRef : *pGraElement)
	{	
		
		DgnModelP c = elemRef->GetDgnModelP();

		//ISessionMgr::
		

		//for (auto m : *c->GetGraphicElementsP()) {
		/*for (auto m : *c->GetControlElementsP()) {*/
		//for (auto m : c->GetReachableElements()) {
		//	outfile.open(filePath, std::ios_base::app);
		//	outfile << "cacat0" << std::endl;
		//	outfile << m.GetElementId()<< std::endl;
		//	//outfile << m->IsGraphics() << std::endl;
		//	//outfile << m->GetLevel()<< std::endl;
		//	outfile.close();
		//}

		//for (auto m : c->GetElementsCollection()) {
		//	outfile.open(filePath, std::ios_base::app);
		//	outfile << "cacat1" << std::endl;
		//	outfile << m->GetElementId() << std::endl;
		//	//outfile << m->IsGraphics() << std::endl;
		//	//outfile << m->GetLevel()<< std::endl;
		//	outfile.close();
		//}
		for (auto m : c->GetReachableModelRefs()) {
			outfile.open(filePath, std::ios_base::app);
			outfile << "cacat0" << std::endl;
			//outfile << m->IsGraphics() << std::endl;
			//outfile << m->GetLevel()<< std::endl;
			outfile.close();
		}

		//ElementRefP el;
		//int num = elemRef->GetDependents(&el,100);
		////auto c1 = el->GetFirstDependent();

		//outfile.open(filePath, std::ios_base::app);
		//outfile << "cacat1" << std::endl;
		//outfile << num << std::endl;
		//outfile << elemRef->IsComplexComponent() << std::endl;
		//outfile << elemRef->IsGraphics() << std::endl;
		////outfile << el->GetLevel() << std::endl;
		////outfile << el->GetElementType() << std::endl;
		////outfile << el->GetElementId() << std::endl;
		////outfile <<  << std::endl;
		//outfile.close();
		//DgnECManagerR ecMgr = DgnECManager::GetManager();
		//RelationshipEntryVector relationshipVec;
		//ecMgr.FindRelationshipEntriesOnElement(elemRef, relationshipVec);
		//
		//for (auto something : relationshipVec) {
		//	outfile.open(filePath, std::ios_base::app);
		//	outfile << std::endl;
		//	outfile << something.RelatedInstanceDirection<< std::endl;
		//	outfile << something.RelatedInstanceStrength << std::endl;
		//	outfile <<StringUtils::getString(something.RelationshipClassName) << std::endl;
		//	outfile << std::endl;
		//	outfile.close();
		//}

		//if (ecMgr.FindInstances(*scope, *ecQuery).empty())
		//{
		//	/*outfile.open(filePath, std::ios_base::app);
		//	outfile << std::endl;
		//	outfile << "= Properties Not Found =" << std::endl;
		//	outfile.close();*/
		//	this->mElemClassName = "SmartFeatureSolid";

		//}

		
		ElementHandle currentElem(elemRef);
		
		Elm_hdr hdr;
		currentElem.GetElementHeader(hdr);

				outfile.open(filePath, std::ios_base::app);
				outfile << "hdr" << std::endl;
				outfile << static_cast<int>(hdr.uniqueId) << std::endl;
				outfile.close();
		

		/*EditElementHandle ee(elemRef);
		ee.*/
		//byte* cc1;

		//mdlColor_elementColorFromRGB(elemRef->GetDgnModelP(), cc1);
		//		outfile.open(filePath, std::ios_base::app);
		//		outfile << "cc1" << std::endl;
		//		outfile << static_cast<int>(*cc1) << std::endl;
		//		outfile << cc1 << std::endl;
		//		outfile.close();

		//DgnIndexIteratorP pDgnIndexIterator = mdlModelIterator_create(currentElem.GetDgnFileP());
		//mdlModelIterator_setAcceptCellsOnly(pDgnIndexIterator, true);

		//GuiTreeNode *pNode, *pChildNode;
		//pChildNode = mdlTreeNode_getFirstChild(pNode);
		//MSDialogP       dbP;
		//ListModel       *pList;

		//int                 count = 0;
		//DgnIndexIteratorP   pDgnIndexIterator;
		//DgnFileP            pLibObj;
		//WChar               wCellName[MAX_CELLNAME_LENGTH];//this should be unicode
		//WChar               wCellDescription[MAX_CELLDSCR_LENGTH];
		//bool                isThreeD, isHidden, isLocked;
		//DgnModelType        cellType;
		//DgnIndexItemP       pDgnIndexItem;
		//int                 iStatus, row, col;
		//GuiTreeNode         *pNode, *pChildNode;
		//GuiTreeCell         *pCell;
		//ListRow             *pRow;
		//ListCell            *pListCell;
		//WCharCP             pString;
		//bool                found;


		//ISessionMgr::GetActiveDgnModelP()->
		
		//DialogItem  *pItem = mdlDialog_itemGetByTypeAndId(dbP, RTYPE_Tree, 1, 0);
		//mdlDialog_treeLastCellClicked(&row, &col, pItem->rawItemP);

		//dlDialog_treeGetNextSelection(&found, &row, &col, pItem->rawItemP);

		//currentElem.GetDgnModelP()->item

		//pNode = mdlTreeModel_getDisplayRowAtIndex(mdlDialog_treeGetTreeModelP(pItem->rawItemP), row);
		//pCell = mdlTreeNode_getCellAtIndex(pNode, 0);

		//iStatus = mdlTreeCell_getStringValue(pCell, &pString);

		//iStatus = mdlCell_getLibraryObject(&pLibObj, pString, true);

		//if (pLibObj!=nullptr) {
		//	pDgnIndexIterator = mdlModelIterator_create(pLibObj);

		//	mdlModelIterator_setAcceptCellsOnly(pDgnIndexIterator, true);

		//	pChildNode = mdlTreeNode_getFirstChild(pNode);
		//	//pChildNode->

		//	while (pDgnIndexItem = mdlModelIterator_getNext(pDgnIndexIterator))
		//	{
		//		double      lastSaved;
		//		pRow = mdlListRow_create(pList);
		//		//do the name column
		//		mdlModelItem_getName(pDgnIndexItem, wCellName, MAX_CELLNAME_LENGTH);
		//		pListCell = mdlListRow_getCellAtIndex(pRow, 0);
		//		mdlListCell_setStringValue(pListCell, wCellName, true);
		//		iStatus = mdlListCell_setInfoFieldInt32(pListCell, 0, (long)pChildNode);
		//		long    infoField;
		//		infoField = mdlListCell_getInfoFieldInt32(pListCell, 0, &iStatus);
		//		//do the description column
		//		mdlModelItem_getDescription(pDgnIndexItem, wCellDescription, MAX_CELLDSCR_LENGTH);
		//		pListCell = mdlListRow_getCellAtIndex(pRow, 1);
		//		//mdlListCell_setStringValue(pListCell, wCellDescription, true);
		//		mdlModelItem_getData(pDgnIndexItem, &cellType, &isThreeD, &isLocked, &isHidden, &lastSaved);
		//		CellLibraryType cellLibType = mdlModelItem_getCellType(pDgnIndexItem);
		//	}
		//}

		

		//if (elemRef->IsComplexComponent())

		//{
		//	
		//	//ComplexElement compEl = (Complex)elemRef;

		//	auto compElEnum = elemRef->eleme

		//	Element cEl;

		//	while (compElEnum.MoveNext())

		//	{

		//		cEl = (Element)compElEnum.Current;

		//		int found = elementRef_isHilited(cEl.MdlElementRef(), cEl.ModelReference.MdlModelRefP());

		//		if (found > 0)

		//		{

		//			long xx = cEl.ID;

		//		}

		//	}

		//auto rez = ISessionMgr::GetActiveDgnModelP();
		//
		////for(auto l1 = rez->GetControlElmStart(); l1!=nullptr; l1=r)
		////rez->GetControlElmStart();
		////rez->get
		//for (auto n12 : *rez->GetControlElementsP()) {
		//		outfile.open(filePath, std::ios_base::app);
		//		outfile << "n12" << std::endl;
		//		outfile << n12->GetElementId() << std::endl;
		//		outfile << n12->GetLevel() << std::endl;
		//		outfile.close();
		//}
		//for (auto m1 : rez->GetReachableElements()) {
		//		outfile.open(filePath, std::ios_base::app);
		//		outfile << "m1" << std::endl;
		//		outfile << m1.GetElementId() << std::endl;
		//		outfile.close();
		//}
		//rez->GetControlElementsP();
		//ISessionMgr::

		//elemRef->ca

		//for (CacheElemRef elRef = iter.FirstCacheElm(dgnCache->GetControlElms()); NULL != elRef; elRef = iter.NextCacheElm())
		//{
		//	
		//}

		

		//currentElem.GetDisplayHandler()->
		
		//ISharedCellQuery::IsNormalCell();

		/*Elm_hdr hdr;
		currentElem.*/


		// error
		//WCharP nana;
		//NormalCellHeaderHandler* nl;
		//nl->ExtractDescription(nana, 100, currentElem);

		//	outfile.open(filePath, std::ios_base::app);
		//	outfile << "nananame" << std::endl;
		//	outfile << static_cast<Utf8String>(nana) << std::endl;
		//	outfile.close();
		
		//for (auto i = currentElem.BeginElementLinkages(); i != currentElem.EndElementLinkages(); ++i)
		//{
		//	
		//	outfile.open(filePath, std::ios_base::app);
		//	outfile << "cacat2" << std::endl;
		//	outfile << i->primaryID << std::endl;
		//	outfile.close();
		//}

		
		

		//mdl_Scan

		WString elDescr;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

		SmartFeatureContainer* smartFeatureContainer = nullptr;
		DictionaryProperties* propertiesDictionary = new DictionaryProperties(currentElem.GetElementId(), StringUtils::getString(elDescr.GetWCharCP()));

		if (SmartFeatureElement::IsSmartFeature(currentElem))
		{
			ElementHandle leafNode;
			SmartFeatureNodePtr sFeatNode;
			T_SmartFeatureVector sFeatVec;

			smartFeatureContainer = createSmartFeatureContainer(currentElem, sFeatNode, leafNode, sFeatVec);
			if (smartFeatureContainer != nullptr) {
				//smartFeatureContainerVector.push_back(smartFeatureContainer);
				propertiesDictionary->setSmartFeatureContainer(smartFeatureContainer);
			}
		}

		/*const bool simplify = false;
		ISolidPrimitivePtr solid = ISolidPrimitiveQuery::ElementToSolidPrimitive(currentElem, simplify);
		bool valid = solid.IsValid();
		ISolidKernelEntityPtr smartSolid;
		bool validSolid = (SUCCESS == SolidUtil::Convert::ElementToBody(smartSolid, currentElem) && smartSolid.IsValid());*/
					


		outfile.open(filePath, std::ios_base::app);
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "Element Description: " << static_cast<Utf8String>(elDescr.GetWCharCP()) << std::endl;
		outfile << "Element ID: " << currentElem.GetElementId() << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << std::endl;
		outfile.close();

		//SmartFeatureElement::ExtractTree(sFeatNode, currentElem);
		//DgnLinkTree::GetTreeSpecPtr();
		//ElementGraphicsTool::

		//NormalCellHeaderHandler::cell
		// doesnt work either
		//UInt* culoare1;
		//mdlLevel_getColor(culoare1, false, currentElem.GetDgnModelP(), 0);

		//UInt* culoare2;
		//mdlLevel_getColor(culoare2, false, currentElem.GetDgnModelP(), 1);

		//if (culoare1 != nullptr) {
		//	//FloatRgb* c = new FloatRgb()
		//	int red = (*culoare1 >> 16) & 0xFF;
		//	int green = (*culoare1 >> 8) & 0xFF;
		//	int blue = *culoare1 & 0xFF;
		//	outfile.open(filePath, std::ios_base::app);
		//	outfile << "=======================zaebisi============================" << std::endl;
		//	outfile << "Cell cacat: " << culoare1 << std::endl;
		//	outfile << "Cell cacat: " << *culoare1 << std::endl;
		//	outfile << "Cell red: " << red << std::endl;
		//	outfile << "Cell green: " << green << std::endl;
		//	outfile << "Cell blue: " << blue << std::endl;
		//	outfile << "Cell cacat: " << culoare2 << std::endl;
		//	outfile << "Cell cacat: " << *culoare2 << std::endl;
		//	outfile << "===================================================" << std::endl;
		//	outfile << std::endl;
		//	outfile.close();
		//}

		

		//NoteCellHeaderHandler c(2);

		//SolidHandler* s = new SolidHandler();
		
		//ISolidPrimitiveQuery::

		//lidHandler::ExposeChildren(currentElem, );

		currentElem.GetElementCP()->GetID();

		propertiesReaderProcessor->processElementReaderProperties(currentElem, *propertiesDictionary, *smartFeatureContainer);

		graphicsProcessorEnhancer->setDictionaryProperties(*propertiesDictionary);

		graphicsProcessorEnhancer->mCurrentElementHandle = currentElem; //store the element in graphic processor enhancer

		TestSubEntityTool* test = new TestSubEntityTool();
		


		// color objects are null or empty
		//graphicsProcessorEnhancer->getColor();

		// works if the element is basic(slab,cylinder) doesnt work for pipe
		//UInt32 colour;
		//mdlElement_getSymbology(&colour, 0, 0, currentElem.GetElementCP());

		//ElementHandle eh(currentElem);
		//DisplayHandlerP handler = currentElem.GetDisplayHandler();
		//if (nullptr != handler)
		//{
		//	NormalCellHeaderHandler* cellHandler = dynamic_cast<NormalCellHeaderHandler*>(handler);
		//	if (nullptr != cellHandler)
		//	{
		//		//DoSomethingWithCellHandler(handler, eh);
		//		if (nullptr != cellHandler) {
		//			WChar name[MAX_MODEL_NAME_LENGTH];
		//			cellHandler->ExtractName(name, MAX_MODEL_NAME_LENGTH, currentElem);
		//			outfile.open(filePath, std::ios_base::app);
		//			outfile << "=======================CELL============================" << std::endl;
		//			outfile << "Cell Description: " << static_cast<Utf8String>(name) << std::endl;
		//			outfile << "===================================================" << std::endl;
		//			outfile << std::endl;
		//			outfile.close();
		//		}


		//	}
		//}


		ElementGraphicsOutput::Process(currentElem, graphicsProcessor);

		//ScanCriteriaP	criteria = mdlScanCriteria_create();
		//mdlScanCriteria_setModel(criteria, this->mDgnModel);

		//mdlScanCriteria_setReturnType(criteria, MSSCANCRIT_ITERATE_ELMREF, FALSE, TRUE);
		//mdlScanCriteria_setElemRefCallback(criteria, ElementRefScanCallback, &this->mDgnModel);

		GraphicElementTool* ccc = new GraphicElementTool();
		ccc->_DoCollectElementGraphics(currentElem);
		ccc->_CollectComplexComponents();
		ccc->_CollectSolids();


		//ISolidPrimitivePtr s = ISolidPrimitiveQuery::ElementToSolidPrimitive(currentElem, true);

		//ExtendedElementHandler::
		//mdlSolid_bodyToElement

		

		//ccc->_OnProcessSolidPrimitive();
		//ccc->InstallTool();

		//elementcolordata::blue;

		//ElementColorData* ecd = new ElementColorData();
		//int reee = ecd->red;
		//int gee = ecd->green;
		//int blll = ecd->blue;
		//ecd->colorBook;

		//outfile.open(filePath, std::ios_base::app);
		//outfile << "=======================cecece============================" << std::endl;
		//outfile << reee << std::endl;
		//outfile << gee << std::endl;
		//outfile << blll << std::endl;
		//outfile << std::endl;
		//outfile.close();

		//ElementGraphicsTool::

		NamedViewCollectionCR nvCollect = ISessionMgr::GetActiveDgnFile()->GetNamedViews();
		//NamedViewCollectionCR NamedViewCollection = dgnFile->GetNamedViews();
		//for each (NamedViewPtr namedView in nvCollect)
		//{
		//	// do something with the namedView here.
		//}
		//int totalSavedViews = nvCollect.Size();

		for each(NamedViewPtr namedView in nvCollect)
		{

						outfile.open(filePath, std::ios_base::app);
						outfile << "=======================bl1============================" << std::endl;
						outfile << " Description: " << static_cast<Utf8String>(namedView->GetName()) << std::endl;
						outfile << namedView->GetElementId() << std::endl;
						outfile << std::endl;
						outfile.close();
			
			/*INamedViewElementHandler*   namedViewHandler = namedView->GetElementHandlerP();
			ISupportCallout*            supportDetailingSymbol = dynamic_cast <ISupportCallout*> (namedViewHandler);
			if (!supportDetailingSymbol)
				continue;
			DetailingSymbolType symbolType = supportDetailingSymbol->GetCalloutType(ElementHandle(namedView->GetElementRef(), NULL));
			switch (symbolType)
			{
			case DetailingSymbolType::SectionCallout:
			{
				sectionViewCount++;
				break;
			}
			case DetailingSymbolType::PlanCallout:
			{
				planViewCount++;
				break;
			}
			default:
				break;
			}*/
		}
		
		
		// doesnt work properly
		//UInt32* col1 = 0;
		//mdlElement_getFillColor(col1, currentElem.GetElementCP());

		//if (col1 != nullptr) {
		//	//FloatRgb* c = new FloatRgb()
		//	int red = (*col1 >> 16) & 0xFF;
		//	int green = (*col1 >> 8) & 0xFF;
		//	int blue = *col1 & 0xFF;

		//	outfile.open(filePath, std::ios_base::app);
		//	outfile << "=======================col 1============================" << std::endl;
		//	outfile << "Cell cacat: " << col1 << std::endl;
		//	outfile << "Cell cacat: " << *col1 << std::endl;
		//	outfile << "Cell cacat: " << (int)*col1 << std::endl;
		//	outfile << "Cell cacat: " << red << std::endl;
		//	outfile << "Cell cacat: " << green << std::endl;
		//	outfile << "Cell cacat: " << blue << std::endl;
		//	outfile << "===================================================" << std::endl;
		//	outfile << std::endl;
		//	outfile.close();
		//}
		

		//mdlcell
		//auto rez = currentElem.GetElementCP()->colorTable;
		//auto r = rez.color_info;
		//auto nana = r[0];


		//Add as BRep after finishing processing
		if (graphicsProcessorEnhancer->mBRepGraphicProperties != nullptr)
		{
			if (graphicsProcessorEnhancer->mBRepGraphicProperties->getSolidEntityVector().size() > 0)
				propertiesDictionary->addGraphicProperties(graphicsProcessorEnhancer->mBRepGraphicProperties);

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