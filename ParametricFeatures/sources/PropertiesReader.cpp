#include "../headers/PropertiesReader.h"

PropertiesReader::PropertiesReader()
{
}

std::string PropertiesReader::getElemClassName()
{
	return this->elemClassName;
}


PropertiesReader::PropertiesReader(ElementHandleCR currentElem, std::ofstream & outfile, std::string & filePath, PropertiesDictionary& propsDictionary)
{
	WString elDescr;
	enum StringLength
	{
		DesiredLength = 128,
	};

	Handler& elemHandler = currentElem.GetHandler();
	elemHandler.GetDescription(currentElem, elDescr, DesiredLength);
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

	if (ecMgr.FindInstances(*scope, *ecQuery).empty())
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "======================== pROPS nOT fOUND ===========================" << std::endl;
		outfile.close();
		elemClassName = "SmartFeatureSolid"; 
	}
	else{

		for (DgnECInstancePtr instance : ecMgr.FindInstances(*scope, *ecQuery))
		{
			DgnElementECInstanceP elemInst = instance->GetAsElementInstance();

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "--------- className = " << static_cast<Utf8String>(elemInst->GetClass().GetName()) << " ---------" << std::endl;
			outfile.close();

			for (ECPropertyP ecProp : elemInst->GetClass().GetProperties())
			{
				WString wStr;
				ECValue ecVal;

				// Gets the value stored in the specified ECProperty. 
				elemInst->GetValue(ecVal, ecProp->GetName().GetWCharCP());

				// Provides methods for converting to and from an ECProperty's internal type to a user-fristd::endly representation. 
				// Obtain a type adapter for the specified property. 
				IDgnECTypeAdapterR typeAdapter = IDgnECTypeAdapter::GetForProperty(*ecProp);
				// Create a context for a DgnECInstance
				IDgnECTypeAdapterContextPtr typeContext = IDgnECTypeAdapterContext::Create(*ecProp, *elemInst, ecProp->GetName().GetWCharCP());

				// Converts the ECValue to a display string. 
				typeAdapter.ConvertToString(wStr, ecVal, *typeContext);

				if (!(static_cast<Utf8String>(wStr) == ""))
				{
					elemClassName = StringUtils::getString(elemInst->GetClass().GetName());
					propsDictionary.addElementProperty(
						PropertyObjAttribute<ElementPropertiesEnum>(currentElem.GetElementId(),elemClassName, ElementPropertiesEnum::NODE_ID),
						PropertyTypeValue(StringUtils::getString(ecProp->GetTypeName()), wStr)
					);

					outfile.open(filePath, std::ios_base::app);
					outfile << static_cast<Utf8String>(ecProp->GetDisplayLabel()) << "["
						<< static_cast<Utf8String>(ecProp->GetTypeName()) << "] "
						<< "= " << static_cast<Utf8String>(wStr) << std::endl;
					outfile.close();
				}
			}
		}
	}
	outfile.open(filePath, std::ios_base::app);
	outfile << std::endl;
	outfile << "===================================================" << std::endl;
	outfile << "===================================================" << std::endl;
	outfile << "====" << static_cast<Utf8String>(elDescr.GetWCharCP()) << "====" << std::endl;
	outfile << "===================================================" << std::endl;
	outfile << "===================================================" << std::endl;
	outfile << std::endl;
	outfile.close();
}


