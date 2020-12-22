#include "../headers/PropertiesReaderProcessor.h"

once_flag PropertiesReaderProcessor::initInstanceFlag;
PropertiesReaderProcessor* PropertiesReaderProcessor::_PropertiesReaderProcessor = 0;

PropertiesReaderProcessor::PropertiesReaderProcessor()
{	
}

vector<ReaderPropertiesBundle*> PropertiesReaderProcessor::processElementReaderProperties(ElementHandleCR currentElem, IfcGraphicPropertiesBundle* elementBundle)
{
	vector<ReaderPropertiesBundle*>	readerPropertiesBundleVector;

	_logger->logDebug(__FILE__, __LINE__, __func__);
		
	//ofstream outfile;
	string filePath = SessionManager::getInstance()->getDataOutputFilePath();

	WString elDescr;

	// Handles persistance of ECInstances
	//DgnECManagerR ecMgr = DgnECManager::GetManager();
	
	// Flag for searching the attachments in the scope as well
	bool includeReferenceAttachments = true;

	// Create a scope which finds instances in the given element. 
	FindInstancesScopePtr scope = FindInstancesScope::CreateScope(currentElem, FindInstancesScopeOption(DgnECHostType::Element, includeReferenceAttachments));

	// Analogous to a SQL query and is used with DgnECManager::FindElementInstances to find ECInstances that satisfy the query's 'where' clause.
	// Specify ECQUERY_PROCESS_SearchAllClasses for the query to consider instances of all classes
	ECQueryPtr ecQuery = ECQuery::CreateQuery(ECQUERY_PROCESS_SearchAllClasses);

	//ECQUERY_PROCESS_SearchAllExtrinsic will only search ECXAttr
	ecQuery->SetSelectProperties(true);

	if (ecMgr.FindInstances(*scope, *ecQuery).empty())
	{
		mElemClassName = "SmartFeatureSolid"; 

	}
	else {
		for (DgnECInstancePtr instance : ecMgr.FindInstances(*scope, *ecQuery))
		{
			//instance->WriteToXmlFile(outXML, true, true);
			DgnElementECInstanceP elemInst = instance->GetAsElementInstance();
			/////// CHECK THIS ONE FOR OBTAINING THE SCHEMA AS SUGGESTED FROM THE GUY IN BENTLEY FORUM 
			//https://communities.bentley.com/products/programming/microstation_programming/f/microstation-programming---forum/192201/connect-c-list-with-all-the-class-name-types-of-an-element
			//ECSchemaCR ecSchemaR = instance->GetClass().GetSchema();
			/////////////////////////

			/*outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "------------ Instance Schema full name: " << StringUtils::getString(ecSchemaR.GetFullSchemaName());
			outfile.close();

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "--------- className = " << static_cast<Utf8String>(elemInst->GetClass().GetName()) << ", current element id = " << currentElem.GetElementId() << ", id = " << elemInst->GetLocalId() << " ---------" << std::endl;
			outfile << "--------- caca = " << StringUtils::getString(elemInst->GetClass().GetName()) << std::endl;

			outfile.close();*/

			mElemClassName = StringUtils::getNormalizedString(elemInst->GetClass().GetName());
			ReaderPropertiesBundle* readerPropertiesBundle = new ReaderPropertiesBundle(mElemClassName, elemInst->GetLocalId());
			ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, readerPropertiesBundle);

			for (auto const& readerPropertyDefinition : readerPropertiesBundle->getProperties()) {
				if (readerPropertyDefinition->getPropertyName().find("Material") != string::npos) {
					PropertyTypeEnum propertyTypeEnum = PropertyTypeEnumUtils::getEnumByStringValue(readerPropertyDefinition->getPropertyTypeName());
					if (PropertyTypeEnum::STRING == propertyTypeEnum && elementBundle != nullptr) {
						string val = StringUtils::getNormalizedString(readerPropertyDefinition->getPropertyValue().GetString());
						if (!val.empty()) {
							elementBundle->setMaterial(readerPropertyDefinition->getPropertyValueAsString());
							break;
						}

					}

				}
				if (readerPropertyDefinition->getPropertyName() == "Name") {
					PropertyTypeEnum propertyTypeEnum = PropertyTypeEnumUtils::getEnumByStringValue(readerPropertyDefinition->getPropertyTypeName());
					if (PropertyTypeEnum::STRING == propertyTypeEnum) {
						string val = StringUtils::getNormalizedString(readerPropertyDefinition->getPropertyValue().GetString());
						if (!val.empty()) {
							readerPropertiesBundle->setName(readerPropertyDefinition->getPropertyValueAsString());
							break;
						}

					}
				}
			}
			//elementBundle->getReaderPropertiesBundle()->addProperty(readerPropertiesBundle);
			//return readerPropertiesBundle; 
			readerPropertiesBundleVector.push_back(readerPropertiesBundle);

			for (size_t i = 0; i <elemInst->GetClass().GetBaseClasses().size(); i++)
			{
				/*outfile.open(filePath, std::ios_base::app);
				outfile << std::endl;
				outfile << "elemInst Full class name: ----- :" << StringUtils::getString(elemInst->GetClass().GetBaseClasses().at(i)->GetFullName()) << std::endl;
				outfile.close();*/
			}


			/*outfile.open(filePath, std::ios_base::app);
			outfile << "is NOT smart feature" << std::endl;

			outfile.close();*/

		}
	}


	/*_logger->logWarning(__FILE__, __LINE__, __FUNCTION__,"Returning an empty ReaderPropertiesBundle");*/

	//return new ReaderPropertiesBundle("", -1);

	return readerPropertiesBundleVector;
}

string PropertiesReaderProcessor::getElementClassName()
{
	return this->mElemClassName;
}