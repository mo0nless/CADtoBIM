#include "../headers/InitializationUtilities.h"


InitializationUtilities::InitializationUtilities()
{	
	this->dgnModel = ISessionMgr::GetActiveDgnModelP();
	this->dgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName();//.AppendUtf8(".txt");

	this->pGraElement = dgnModel->GetGraphicElementsP();

	this->filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	//std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
}

SmartFeatureContainer * InitializationUtilities::createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec)
{
	std::ofstream outfile;

	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer();
	long newCurrentElementId = -1, newLocalNodeId = -1, newParentLocalNodeId = -1, newLeafElementId = -1;
	newCurrentElementId = currentElem.GetElementId();

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

			newLeafElementId = leafNode.GetElementId();
			
			outfile.open(filePath, std::ios_base::app);
			outfile << "Leaf ID:  " << leafNode.GetElementId() << std::endl;
			outfile.close();
		}

		outfile.open(filePath, std::ios_base::app);
		outfile << "finish==================" << std::endl;
		outfile.close();

		smartFeatureContainer->insertNodeInTree(newCurrentElementId, newLocalNodeId, newParentLocalNodeId, newLeafElementId);
	}

	outfile.open(filePath, std::ios_base::app);
	outfile << "Smart Feat Element Node ID: " << sFeatNode->GetNodeId() << std::endl;
	outfile << "Number of Child: " << sFeatNode->GetChildCount() << std::endl;
	outfile.close();


	return smartFeatureContainer;
}

std::vector<DictionaryProperties*> InitializationUtilities::orderDictionaryPropertyAndSmartFeature(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	std::vector<DictionaryProperties*> newPropsDictVec;

	if (smartFeatureContainerVector.empty()) {
		return propsDictVec;
	}
	else
	{
		for (int i = 0; i < propsDictVec.size(); ++i) {
			DictionaryProperties* propertiesDictionary = propsDictVec.at(i);

			for (int j = 0; j < smartFeatureContainerVector.size(); ++j) {
				SmartFeatureContainer* smartFeatureContainer = smartFeatureContainerVector.at(j);

				if (propertiesDictionary->getAreReaderPropertiesFound()) {
					SmartFeatureTreeNode* treeNode = smartFeatureContainer->searchByElementGlobalId(smartFeatureContainer->getRoot(), propertiesDictionary->getGeneralProperties()->getElementId());
					if (treeNode != nullptr) {
						treeNode->setGraphicProperties(propertiesDictionary->getGraphicProperties());
					}
				}
				else if (smartFeatureContainer->searchByElementGlobalId(smartFeatureContainer->getRoot(), propertiesDictionary->getGeneralProperties()->getElementId()) != nullptr)
				{
					continue;
				}
				else if (propertiesDictionary->getGeneralProperties()->getIsSmartFeature())
				{
					continue;
				}
				else
				{
					newPropsDictVec.push_back(propertiesDictionary);
				}
			}

		}
		return newPropsDictVec;
	}
}

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
void InitializationUtilities::processDgnGraphicsElements(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
	std::ofstream outfile;

	outfile.open(filePath);
	outfile << "" << std::endl;
	outfile.close();
			
	GraphicsProcessor graphicsProcessor = GraphicsProcessor();
	GraphicsProcessorUtilities graphicsProcessorUtils = graphicsProcessor.getGraphicsProcessorUtilities();

	for (PersistentElementRefP elemRef : *pGraElement)
	{		
		ElementHandle currentElem(elemRef);
		WString elDescr;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

		SmartFeatureContainer* smartFeatureContainer = nullptr;
		DictionaryProperties* propertiesDictionary = new DictionaryProperties();

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
		
		//This is the one that we use for the ENUMS
		propertiesDictionary->getGeneralProperties()->setElementDescriptorName(StringUtils::getString(elDescr.GetWCharCP())); 
		//The class name is visible only from the reader properties executing the query and we set it later

		propertiesDictionary->getGeneralProperties()->setElementId(currentElem.GetElementId());
		propertiesDictionary->getGeneralProperties()->setCurrentElementId(currentElem.GetElementId());
		
		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor();
		propertiesReaderProcessor->processElementReaderProperties(currentElem, *propertiesDictionary, *smartFeatureContainer);

		graphicsProcessorUtils.setDictionaryProperties(*propertiesDictionary);
		
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