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

std::vector<DictionaryProperties*> InitializationEnhancer::orderDictionaryPropertyAndSmartFeature(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	return propsDictVec;
	//std::vector<DictionaryProperties*> newPropsDictVec;

	//if (smartFeatureContainerVector.empty()) {
	//	return propsDictVec;
	//}
	//else
	//{
	//	for (int i = 0; i < propsDictVec.size(); ++i) {
	//		DictionaryProperties* propertiesDictionary = propsDictVec.at(i);

	//		for (int j = 0; j < smartFeatureContainerVector.size(); ++j) {
	//			SmartFeatureContainer* smartFeatureContainer = smartFeatureContainerVector.at(j);

	//			if (!propertiesDictionary->getAreReaderPropertiesFound()) {
	//				SmartFeatureTreeNode* treeNode = smartFeatureContainer->searchByElementGlobalId(smartFeatureContainer->getRoot(), propertiesDictionary->getGeneralProperties()->getElementId());
	//				if (treeNode != nullptr) {
	//					//treeNode->setGraphicProperties(propertiesDictionary->getGraphicProperties());
	//				}
	//			}
	//			else if (smartFeatureContainer->searchByElementGlobalId(smartFeatureContainer->getRoot(), propertiesDictionary->getGeneralProperties()->getElementId()) != nullptr)
	//			{
	//				continue;
	//			}
	//			else if (propertiesDictionary->getGeneralProperties()->getIsSmartFeature())
	//			{
	//				continue;
	//			}
	//			else
	//			{
	//				newPropsDictVec.push_back(propertiesDictionary);
	//			}
	//		}

	//	}
	//	return newPropsDictVec;
	//}
}

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

	for (PersistentElementRefP elemRef : *pGraElement)
	{		
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
			if (smartFeatureContainer != nullptr)
			{
				smartFeatureContainerVector.push_back(smartFeatureContainer);
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
	
		
		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();
		propertiesReaderProcessor->processElementReaderProperties(currentElem, *propertiesDictionary, *smartFeatureContainer);

		graphicsProcessorEnhancer->setDictionaryProperties(*propertiesDictionary);
		
		ElementGraphicsOutput::Process(currentElem, graphicsProcessor);

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