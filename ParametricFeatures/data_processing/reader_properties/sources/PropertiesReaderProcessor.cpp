#include "../headers/PropertiesReaderProcessor.h"

once_flag PropertiesReaderProcessor::initInstanceFlag;
PropertiesReaderProcessor* PropertiesReaderProcessor::_PropertiesReaderProcessor = 0;

PropertiesReaderProcessor::PropertiesReaderProcessor()
{	
}

ReaderPropertiesBundle* PropertiesReaderProcessor::processElementReaderProperties(ElementHandleCR currentElem, ElementBundle* elementBundle)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);
		
	//ofstream outfile;
	string filePath = SessionManager::getInstance()->getDataOutputFilePath();

	WString elDescr;

	// Handles persistance of ECInstances
	//DgnECManagerR ecMgr = DgnECManager::GetManager();
	
	// Flag for searching the attachments in the scope as well
	bool includeReferenceAttachments = true;

	// Create a scope which finds instances in the given element. 
	FindInstancesScopePtr scope = FindInstancesScope::CreateScope(currentElem, FindInstancesScopeOption(DgnECHostType::All, includeReferenceAttachments));

	// Analogous to a SQL query and is used with DgnECManager::FindElementInstances to find ECInstances that satisfy the query's 'where' clause.
	// Specify ECQUERY_PROCESS_SearchAllClasses for the query to consider instances of all classes
	ECQueryPtr ecQuery = ECQuery::CreateQuery(ECQUERY_PROCESS_SearchAllClasses);

	//ECQUERY_PROCESS_SearchAllExtrinsic will only search ECXAttr
	ecQuery->SetSelectProperties(true);
	
	//dictionaryProperties.getGeneralProperties()->setIsSmartFeature(SmartFeatureElement::IsSmartFeature(currentElem));

	currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

	if (ecMgr.FindInstances(*scope, *ecQuery).empty())	
	{
		this->mElemClassName = "SmartFeatureSolid"; 

	}
	else
	{
		//ElementECClassInfo  info;
		//ecMgr.FindECClassesOnElement(currentElem.GetElementRef(), info);

		//outfile.open(filePath, ios_base::app);
		//outfile << endl;
		//outfile << "extra" << endl;		
		//outfile << info.count << endl;
		//outfile << info.empty() << endl;
		////outfile << info.leaf_nodes.size() << endl;
		////outfile << info.nodes.size() << endl;
		//outfile.close();


		for (DgnECInstancePtr instance : ecMgr.FindInstances(*scope, *ecQuery))
		{

			//instance->GetAsElementInstance()->get

			DgnElementECInstanceP elemInst = instance->GetAsElementInstance();
			/////// CHECK THIS ONE FOR OBTAINING THE SCHEMA AS SUGGESTED FROM THE GUY IN BENTLEY FORUM 
			//https://communities.bentley.com/products/programming/microstation_programming/f/microstation-programming---forum/192201/connect-c-list-with-all-the-class-name-types-of-an-element
			//ECSchemaCR ecSchemaR = instance->GetClass().GetSchema();

			this->mElemClassName = StringUtils::getString(elemInst->GetClass().GetName());
			
			//outfile.open(filePath, ios_base::app);
			//outfile << endl;
			//outfile << "------------ Instance Schema full name: " << StringUtils::getString( ecSchemaR.GetFullSchemaName());
			//outfile.close();

			// get class name
			string className = StringUtils::getString(elemInst->GetClass().GetName());

			//outfile.open(filePath, ios_base::app);
			//outfile << endl;
			//outfile << "--------- ClassName = " << mElemClassName <<", current element id = "<< currentElem.GetElementId() << ", id = " << elemInst->GetLocalId()<<" ---------" << endl;
			//outfile.close();

			ReaderPropertiesBundle* readerPropertiesBundle = new ReaderPropertiesBundle(mElemClassName, elemInst->GetLocalId());
			ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, readerPropertiesBundle);

			for (auto const& readerPropertyDefinition : readerPropertiesBundle->getProperties()) {
				if (readerPropertyDefinition->getPropertyName().find("Material") != string::npos) {
					PropertyTypeEnum propertyTypeEnum = PropertyTypeEnumUtils::getEnumByStringValue(readerPropertyDefinition->getPropertyTypeName());
					if (PropertyTypeEnum::STRING == propertyTypeEnum && elementBundle!=nullptr) {
						string val = StringUtils::getNormalizedString(readerPropertyDefinition->getPropertyValue().GetString());
						if (!val.empty()) {
							elementBundle->setMaterial(readerPropertyDefinition->getPropertyValueAsString());
							break;
						}
						
					}
					
				}
			}
	
			return readerPropertiesBundle;
		}
	}

	_logger->logWarning(__FILE__, __LINE__, __func__,"Returning an empty ReaderPropertiesBundle");

	return new ReaderPropertiesBundle("", -1);
}