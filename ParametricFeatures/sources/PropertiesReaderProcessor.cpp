#include "../headers/PropertiesReaderProcessor.h"

PropertiesReaderProcessor::PropertiesReaderProcessor()
{
}

ReaderPropertiesBundle* PropertiesReaderProcessor::processElementReaderProperties(ElementHandleCR currentElem)
{
	std::ofstream outfile;
	std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	//std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";

	WString elDescr;

	// Handles persistance of ECInstances
	DgnECManagerR ecMgr = DgnECManager::GetManager();
	
	// Flag for searching the attachments in the scope as well
	bool includeReferenceAttachments = true;

	//auto some1 = ISessionMgr::GetActiveDgnModelRefP();

	// Create a scope which finds instances in the given element. 
	FindInstancesScopePtr scope = FindInstancesScope::CreateScope(currentElem, FindInstancesScopeOption(DgnECHostType::All, includeReferenceAttachments));
	/*FindInstancesScopePtr scope = FindInstancesScope::CreateScope(*currentElem.GetDgnModelP(), FindInstancesScopeOption(DgnECHostType::All, includeReferenceAttachments));*/
	//FindInstancesScopePtr scope = FindInstancesScope::CreateScope(some1,

	// Analogous to a SQL query and is used with DgnECManager::FindElementInstances to find ECInstances that satisfy the query's 'where' clause.
	// Specify ECQUERY_PROCESS_SearchAllClasses for the query to consider instances of all classes
	ECQueryPtr ecQuery = ECQuery::CreateQuery(ECQUERY_PROCESS_SearchAllClasses);
	//Queryptr
	
	//ECQUERY_PROCESS_SearchAllExtrinsic will only search ECXAttr
	ecQuery->SetSelectProperties(true);
	
	//dictionaryProperties.getGeneralProperties()->setIsSmartFeature(SmartFeatureElement::IsSmartFeature(currentElem));

	currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

	//ecMgr.
	
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
		//ElementECClassInfo  info;
		//ecMgr.FindECClassesOnElement(currentElem.GetElementRef(), info);

		//outfile.open(filePath, std::ios_base::app);
		//outfile << std::endl;
		//outfile << "extra" << std::endl;		
		//outfile << info.count << std::endl;
		//outfile << info.empty() << std::endl;
		////outfile << info.leaf_nodes.size() << std::endl;
		////outfile << info.nodes.size() << std::endl;
		//outfile.close();


		for (DgnECInstancePtr instance : ecMgr.FindInstances(*scope, *ecQuery))
		{

			//instance->GetAsElementInstance()->get

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
			//outfile.close();

			// set class name
			//dictionaryProperties.getGeneralProperties()->setElementClassName(mElemClassName);
			
			ReaderPropertiesBundle* readerPropertiesBundle = new ReaderPropertiesBundle(mElemClassName, elemInst->GetLocalId());
			ReaderPropertiesMapper::mapECPropertiesToReaderProperties(elemInst, readerPropertiesBundle);

			//for (auto const& readerPropertyDefinition : readerPropertiesBundle->getProperties()) {
			//	if (readerPropertyDefinition->getPropertyName().find("Color") != std::string::npos && 
			//		readerPropertyDefinition->getPropertyValueAsString().find("ByLevel")) {
			//		outfile << "found level" << std::endl;

			//		std::string result;
			//		std::string searched = readerPropertyDefinition->getPropertyValueAsString();
			//		try {
			//			std::regex re("Level by//(//d+//)");
			//			std::smatch match;
			//			if (std::regex_search(searched, match, re) && match.size() > 0) {
			//				result = match.str(0);
			//			}
			//			else {
			//				result = std::string("");
			//			}
			//		}
			//		catch (std::regex_error& e) {
			//			e.code();
			//		}

			//		outfile << " level = " << result << std::endl;

			//		int intValue;
			//		try {
			//			intValue = std::stoi(result);
			//			outfile << " level int = " << intValue << std::endl;

			//		}
			//		catch (std::exception& e) {
			//			e.what();
			//		}

			//		if (intValue > 0) {
			//			auto model = ISessionMgr::GetActiveDgnModelRefP();
			//			LevelId l(intValue);
			//			UInt colorOut;
			//			bool ov;
			//			mdlLevel_getColor(&colorOut, &ov, model, l);
			//			outfile << "level color"<< colorOut<<" , "<<& colorOut << std::endl;

			//		}
			//	}
			//}
	
			return readerPropertiesBundle;
		}
	}
	outfile.close();


	return new ReaderPropertiesBundle("", -1);
}