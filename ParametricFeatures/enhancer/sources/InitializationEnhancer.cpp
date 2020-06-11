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

	for (PersistentElementRefP elemRef : *pGraElement)
	{	
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

			
		propertiesReaderProcessor->processElementReaderProperties(currentElem, *propertiesDictionary, *smartFeatureContainer);

		graphicsProcessorEnhancer->setDictionaryProperties(*propertiesDictionary);

		graphicsProcessorEnhancer->mCurrentElementHandle = currentElem; //store the element in graphic processor enhancer
		
		ElementGraphicsOutput::Process(currentElem, graphicsProcessor);

		//Add as BRep after finishing processing
		if (graphicsProcessorEnhancer->mBRepGraphicProperties != nullptr)
		{
			propertiesDictionary->addGraphicProperties(graphicsProcessorEnhancer->mBRepGraphicProperties);
			graphicsProcessorEnhancer->mBRepGraphicProperties = nullptr;
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