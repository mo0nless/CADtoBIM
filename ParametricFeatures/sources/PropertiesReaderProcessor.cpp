#include "../headers/PropertiesReaderProcessor.h"

PropertiesReaderProcessor::PropertiesReaderProcessor()
{
}

void PropertiesReaderProcessor::processElementReaderProperties(ElementHandleCR currentElem, DictionaryProperties& dictionaryProperties, SmartFeatureContainer& smartFeatureContainer)
{
	std::ofstream outfile;
	std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	//std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";

	WString elDescr;

	// Handles persistance of ECInstances
	DgnECManagerR ecMgr = DgnECManager::GetManager();

	// Flag for searching the attachments in the scope as well
	bool includeReferenceAttachments = true;

	// Create a scope which finds instances in the given element. 
	FindInstancesScopePtr scope = FindInstancesScope::CreateScope(currentElem, FindInstancesScopeOption(DgnECHostType::Element, includeReferenceAttachments));

	// Analogous to a SQL query and is used with DgnECManager::FindElementInstances to find ECInstances that satisfy the query's 'where' clause.
	// Specify ECQUERY_PROCESS_SearchAllClasses for the query to consider instances of all classes
	ECQueryPtr ecQuery = ECQuery::CreateQuery(ECQUERY_PROCESS_SearchAllClasses);
	
	//ECQUERY_PROCESS_SearchAllExtrinsic will only search ECXAttr
	ecQuery->SetSelectProperties(true);
	
	//dictionaryProperties.getGeneralProperties()->setIsSmartFeature(SmartFeatureElement::IsSmartFeature(currentElem));

	currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
	
	if (ecMgr.FindInstances(*scope, *ecQuery).empty())
	{
		/*outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "= Properties Not Found =" << std::endl;
		outfile.close();*/
		this->mElemClassName = "SmartFeatureSolid"; 

	}
	else
	{

		for (DgnECInstancePtr instance : ecMgr.FindInstances(*scope, *ecQuery))
		{
			DgnElementECInstanceP elemInst = instance->GetAsElementInstance();
			/////// CHECK THIS ONE FOR OBTAINING THE SCHEMA AS SUGGESTED FROM THE GUY IN BENTLEY FORUM 
			//https://communities.bentley.com/products/programming/microstation_programming/f/microstation-programming---forum/192201/connect-c-list-with-all-the-class-name-types-of-an-element
			ECSchemaCR ecSchemaR = instance->GetClass().GetSchema();

			this->mElemClassName = StringUtils::getString(elemInst->GetClass().GetName());
			
			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "------------ Instance Schema full name: " << StringUtils::getString( ecSchemaR.GetFullSchemaName());
			outfile.close();

			// get class name
			std::string className = StringUtils::getString(elemInst->GetClass().GetName());

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "--------- ClassName = " << mElemClassName <<", current element id = "<< currentElem.GetElementId() << ", id = " << elemInst->GetLocalId()<<" ---------" << std::endl;
			outfile.close();

			// set class name
			//dictionaryProperties.getGeneralProperties()->setElementClassName(mElemClassName);
			
			ReaderPropertyBundle* readerPropertyBundle = new ReaderPropertyBundle(mElemClassName, elemInst->GetLocalId());
			ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, readerPropertyBundle);
			dictionaryProperties.getReaderProperties()->addReaderPropertyBundle(readerPropertyBundle);

			/*for (size_t i = 0; i <elemInst->GetClass().GetBaseClasses().size(); i++)
			{
				outfile.open(filePath, std::ios_base::app);
				outfile << "elemInst Full class name: ----- :" << StringUtils::getString(elemInst->GetClass().GetBaseClasses().at(i)->GetFullName()) << std::endl;
				outfile.close();
			}*/
			
			//
			//if (SmartFeatureElement::IsSmartFeature(currentElem)) 
			//{

			//	SmartFeatureTypeEnum smartFeatureTypeEnum = SmartFeatureTypeEnumUtils::getSmartFeatureTypeEnumByClassName(className);
			//	
			//	outfile.open(filePath, std::ios_base::app);
			//	outfile << std::endl;
			//	outfile << "Is smart feature" << std::endl;
			//	outfile.close();

			//	SmartFeatureTreeNode* currentNode = smartFeatureContainer.searchByElementLocalNodeId(smartFeatureContainer.getRoot(), elemInst->GetLocalId());

			//	if (currentNode != nullptr) 
			//	{

			//		// set class name in the ReaderProperties
			//		currentNode->getReaderProperties()->getSmartFeatureGeneralProperties()->setSmartFeatureTypeEnum(smartFeatureTypeEnum);
			//		// if it's a smart feature and the node is found, pass to the mapper the ReaderProperties of the SmartFeatureTreeNode
			//		ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, *currentNode->getReaderProperties(), smartFeatureTypeEnum);
			//	}
			//	else 
			//	{
			//		outfile.open(filePath, std::ios_base::app);
			//		outfile << "is smart feature, but not found in the smartfeaturetree" << std::endl;
			//		outfile.close();

			//		// set class name in the ReaderProperties
			//		dictionaryProperties.getReaderProperties()->getSmartFeatureGeneralProperties()->setSmartFeatureTypeEnum(smartFeatureTypeEnum);
			//		// if node is not found, pass the ReaderProperties from the dictionary properties to map 
			//		ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, *dictionaryProperties.getReaderProperties(), smartFeatureTypeEnum);
			//	}
			//	
			//}
			//else 
			//{
			//	outfile.open(filePath, std::ios_base::app);
			//	outfile << "is NOT smart feature" << std::endl;
			//	outfile.close();

			//	// if it's not a smart feature, pass the ReaderProperties from the dictionary properties to map 
			//	ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, *dictionaryProperties.getReaderProperties(), SmartFeatureTypeEnum::UNDEFINED);

			//	
			//}			
		}
	}
}