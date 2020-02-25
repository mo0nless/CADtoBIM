#include "../headers/PropertiesReaderProcessor.h"

PropertiesReaderProcessor::PropertiesReaderProcessor()
{
}

std::string PropertiesReaderProcessor::getElemClassName()
{
	return this->elemClassName;
}


PropertiesReaderProcessor::PropertiesReaderProcessor(ElementHandleCR currentElem, std::ofstream & outfile, std::string & filePath, DictionaryProperties& dictionaryProperties,
	SmartFeatureContainer& smartFeatureContainer)
{
	WString elDescr;
	//WCharCP outXML = L"C:/Users/LX5990/Documents/Internal Projects Development/DevOpenPlant/ParametricFeatures/TEST.xml";

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

	currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

	if (ecMgr.FindInstances(*scope, *ecQuery).empty())
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "======================== pROPS nOT fOUND ===========================" << std::endl;
		outfile.close();
		elemClassName = "SmartFeatureSolid"; 

		// set value if reader properties are missing for this element
		dictionaryProperties.setAreReaderPropertiesFound(false);
	}
	else{
		// set value if reader properties exist for this element
		dictionaryProperties.setAreReaderPropertiesFound(true);
		for (DgnECInstancePtr instance : ecMgr.FindInstances(*scope, *ecQuery))
		{
			//instance->WriteToXmlFile(outXML, true, true);
			DgnElementECInstanceP elemInst = instance->GetAsElementInstance();
			/////// CHECK THIS ONE FOR OBTAINING THE SCHEMA AS SUGGESTED FROM THE GUY IN BENTLEY FORUM 
			//https://communities.bentley.com/products/programming/microstation_programming/f/microstation-programming---forum/192201/connect-c-list-with-all-the-class-name-types-of-an-element
			ECSchemaCR ecSchemaR = instance->GetClass().GetSchema();
			/////////////////////////

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "------------ Instance Schema full name: " << StringUtils::getString( ecSchemaR.GetFullSchemaName());
			outfile.close();

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "--------- className = " << static_cast<Utf8String>(elemInst->GetClass().GetName())<<", current element id = "<< currentElem.GetElementId() << ", id = " << elemInst->GetLocalId()<<" ---------" << std::endl;
			outfile.close();

			for (size_t i = 0; i <elemInst->GetClass().GetBaseClasses().size(); i++)
			{
				outfile.open(filePath, std::ios_base::app);
				outfile << "elemInst Full class name: ----- :" << StringUtils::getString(elemInst->GetClass().GetBaseClasses().at(i)->GetFullName()) << std::endl;
				outfile.close();
			}

			dictionaryProperties.setIsSmartFeature(SmartFeatureElement::IsSmartFeature(currentElem));

			
			if (SmartFeatureElement::IsSmartFeature(currentElem)) {
				outfile.open(filePath, std::ios_base::app);

				outfile << std::endl;
				outfile << "is smart feature" << std::endl;
				//ReaderPropertiesMapper::mapECPropertiesToElementProperties(elemInst, *dictionaryProperties.getReaderProperties());
				SmartFeatureTreeNode* currentNode = smartFeatureContainer.searchByLocalId(smartFeatureContainer.getRoot(), elemInst->GetLocalId());
				if (currentNode != nullptr) {
					// if it's a smart feature and the node is found, pass to the mapper the ReaderProperties of the SmartFeatureTreeNode
					ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, *currentNode->getReaderProperties());
				}
				else {
					outfile << "is smart feature, but not found in the smartfeaturetree" << std::endl;
					// if node is not found, pass the ReaderProperties from the dictionary properties to map 
					ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, *dictionaryProperties.getReaderProperties());

				}
				outfile.close();
			}
			else {
				outfile.open(filePath, std::ios_base::app);
				outfile << "is NOT smart feature" << std::endl;
				// if it's not a smart feature, pass the ReaderProperties from the dictionary properties to map 
				ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, *dictionaryProperties.getReaderProperties());

				outfile.close();
			}

				
				//for (ECPropertyP ecProp : elemInst->GetClass().GetProperties(true))
				//{
				//	WString wStr;
				//	ECValue ecVal;
				//	//////////////////// WE CAN Check and store the type immediately WIth those functions
				//	ecVal.IsBoolean();
				//	/////////////////////
				//	// Gets the value stored in the specified ECProperty. 
				//	elemInst->GetValue(ecVal, ecProp->GetName().GetWCharCP());
				//
				//	// Provides methods for converting to and from an ECProperty's internal type to a user-fristd::endly representation. 
				//	// Obtain a type adapter for the specified property. 
				//	IDgnECTypeAdapterR typeAdapter = IDgnECTypeAdapter::GetForProperty(*ecProp);
				//	// Create a context for a DgnECInstance
				//	IDgnECTypeAdapterContextPtr typeContext = IDgnECTypeAdapterContext::Create(*ecProp, *elemInst, ecProp->GetName().GetWCharCP());
				//
				//	// Converts the ECValue to a display string. 
				//	typeAdapter.ConvertToString(wStr, ecVal, *typeContext);
				//
				//	if (!(static_cast<Utf8String>(wStr) == ""))
				//	{
				//		//elemClassName = StringUtils::getString(elemInst->GetClass().GetName());
				//		//propsDictionary.addElementProperty(
				//		//	PropertyObjAttribute<ElementPropertiesEnum>(currentElem.GetElementId(),elemClassName, ElementPropertiesEnum::NODE_ID),
				//		//	PropertyTypeValue(StringUtils::getString(ecProp->GetTypeName()), wStr)
				//		//);
				//
				//		outfile.open(filePath, std::ios_base::app);
				//		outfile << static_cast<Utf8String>(ecProp->GetDisplayLabel()) << "["
				//			<< static_cast<Utf8String>(ecProp->GetTypeName()) << "] "
				//			<< "= " << static_cast<Utf8String>(wStr) << std::endl;
				//		outfile.close();
				//	}
				//}
			
		}
	}

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


