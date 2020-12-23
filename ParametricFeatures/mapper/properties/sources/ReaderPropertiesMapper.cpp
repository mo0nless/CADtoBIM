#include "../headers/ReaderPropertiesMapper.h"

#include <fstream> 
#include <filesystem>

void ReaderPropertiesMapper::mapECPropertiesToReaderProperties(DgnElementECInstanceP dgnElementECInstanceP, ReaderPropertiesBundle*& readerPropertiesBundle)
{
	ofstream outfile;
	string filePath = SessionManager::getInstance()->getDataOutputFilePath();
	outfile.open(filePath, ios_base::app);

	outfile << "Class Name: " << readerPropertiesBundle->getClassName() << endl;

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

		if (!valueAsString.empty()) {
			//mapPropertyToReaderPropertiesMember(propertyName, ecVal, readerProperties,smartFeatureTypeEnum);
			readerPropertiesBundle->addProperty(new ReaderPropertyDefinition(propertyName, StringUtils::getString(ecProp->GetTypeName()), ecVal, valueAsString));
			//ReaderPropertyDefinition* readerPropertyDefinition =

			outfile << static_cast<Utf8String>(ecProp->GetDisplayLabel()) << "["
				<< static_cast<Utf8String>(ecProp->GetTypeName()) << "] "
				<< "= " << static_cast<Utf8String>(wStr) << endl;

			//outfile << "val " << propertyName << "["
			//	<< StringUtils::getString(ecProp->GetTypeName()) << "] "
			//	<< "= " << ecVal.GetUtf8CP() << endl;
		}

		
		


		//HARD CODED FOR CURVES//
		/*if (propertyName == "Degree")
			readerProperties.curveDegree = ecVal.GetInteger();*/
		//---------------------//
			
	}
	outfile.close();
	
}

