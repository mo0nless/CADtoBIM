#include "../headers/PropertiesReaderProcessor.h"

once_flag PropertiesReaderProcessor::initInstanceFlag;
PropertiesReaderProcessor* PropertiesReaderProcessor::_PropertiesReaderProcessor = 0;

PropertiesReaderProcessor::PropertiesReaderProcessor()
{	
}

vector<ReaderPropertiesBundle*> PropertiesReaderProcessor::processElementReaderProperties(ElementHandleCR currentElem, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle)
{
	vector<ReaderPropertiesBundle*>	readerPropertiesBundleVector;

	_logger->logDebug(__FILE__, __LINE__, __func__);
		
	ofstream outfile;
	string filePath = SessionManager::getInstance()->getDataOutputFilePath();

	WString elDescr;

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
		_logger->logInfo(__FILE__, __LINE__, __func__, "No properties found!! The current element is possibly a SmartFeatureSolid " + to_string(currentElem.GetElementId()));

	}
	else 
	{
		for (DgnECInstancePtr instance : ecMgr.FindInstances(*scope, *ecQuery))
		{
			//instance->WriteToXmlFile(outXML, true, true);
			DgnElementECInstanceP elemInst = instance->GetAsElementInstance();
			//CHECK THIS ONE FOR OBTAINING THE SCHEMA AS SUGGESTED FROM THE GUY IN BENTLEY FORUM 
			//https://communities.bentley.com/products/programming/microstation_programming/f/microstation-programming---forum/192201/connect-c-list-with-all-the-class-name-types-of-an-element


			ECSchemaCR ecSchemaR = instance->GetClass().GetSchema();

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "------------ Instance Schema full name: " << StringUtils::getString(ecSchemaR.GetFullSchemaName());
			outfile << std::endl;
			outfile << "--------- className = " << static_cast<Utf8String>(elemInst->GetClass().GetName()) << ", current element id = " << currentElem.GetElementId() << ", id = " << elemInst->GetLocalId() << " ---------" << std::endl;
			outfile.close();

			mElemClassName = StringUtils::getNormalizedString(elemInst->GetClass().GetName());
			ReaderPropertiesBundle* readerPropertiesBundle = new ReaderPropertiesBundle(mElemClassName, elemInst->GetLocalId());
			mapECPropertiesToReaderProperties(elemInst, readerPropertiesBundle);

			for (auto const& readerPropertyDefinition : readerPropertiesBundle->getProperties()) {
				if (readerPropertyDefinition->getPropertyName().find("Material") != string::npos) {
					PropertyTypeEnum propertyTypeEnum = PropertyTypeEnumUtils::getEnumByStringValue(readerPropertyDefinition->getPropertyTypeName());
					if (PropertyTypeEnum::STRING == propertyTypeEnum && ifcGraphicPropertiesBundle != nullptr) {
						string val = StringUtils::getNormalizedString(readerPropertyDefinition->getPropertyValue().GetString());
						if (!val.empty()) {
							ifcGraphicPropertiesBundle->setMaterial(readerPropertyDefinition->getPropertyValueAsString());
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
			
			readerPropertiesBundleVector.push_back(readerPropertiesBundle);
		}
	}

	return readerPropertiesBundleVector;
}

void PropertiesReaderProcessor::mapECPropertiesToReaderProperties(DgnElementECInstanceP dgnElementECInstanceP, ReaderPropertiesBundle*& readerPropertiesBundle)
{
	ofstream outfile;
	string filePath = SessionManager::getInstance()->getDataOutputFilePath();
	outfile.open(filePath, ios_base::app);
	
	for (ECPropertyP ecProp : dgnElementECInstanceP->GetClass().GetProperties())
	{
		WString wStr;
		ECValue ecVal;

		// Gets the value stored in the specified ECProperty. 
		dgnElementECInstanceP->GetValue(ecVal, ecProp->GetName().GetWCharCP());

		// Provides methods for converting to and from an ECProperty's internal type to a user-friendly representation. 
		// Obtain a type adapter for the specified property. 
		IDgnECTypeAdapterR typeAdapter = IDgnECTypeAdapter::GetForProperty(*ecProp);
		// Create a context for a DgnECInstance
		IDgnECTypeAdapterContextPtr typeContext = IDgnECTypeAdapterContext::Create(*ecProp, *dgnElementECInstanceP, ecProp->GetName().GetWCharCP());

		// Converts the ECValue to a display string.
		typeAdapter.ConvertToString(wStr, ecVal, *typeContext);
		

		string valueAsString = StringUtils::getString(wStr);
		string propertyName = StringUtils::getString(ecProp->GetDisplayLabel());

		if (!valueAsString.empty()) 
		{
			readerPropertiesBundle->addProperty(new ReaderPropertyDefinition(propertyName, StringUtils::getString(ecProp->GetTypeName()), ecVal, valueAsString));

			outfile << static_cast<Utf8String>(ecProp->GetDisplayLabel()) << "["
				<< static_cast<Utf8String>(ecProp->GetTypeName()) << "] "
				<< "= " << static_cast<Utf8String>(wStr) << endl;
		}
	}
	outfile.close();

}

string PropertiesReaderProcessor::getElementClassName()
{
	return this->mElemClassName;
}