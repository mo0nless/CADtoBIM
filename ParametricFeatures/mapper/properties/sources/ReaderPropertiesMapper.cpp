#include "../headers/ReaderPropertiesMapper.h"

#include <fstream> 
#include <filesystem>

void ReaderPropertiesMapper::mapECPropertiesToReaderProperties(DgnElementECInstanceP dgnElementECInstanceP, ReaderPropertiesBundle*& readerPropertiesBundle)
{
	std::ofstream outfile;
	//std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	outfile.open(filePath, std::ios_base::app);

	for (ECPropertyP ecProp : dgnElementECInstanceP->GetClass().GetProperties())
	{
		WString wStr;
		ECValue ecVal;

		// Gets the value stored in the specified ECProperty. 
		dgnElementECInstanceP->GetValue(ecVal, ecProp->GetName().GetWCharCP());

		// Provides methods for converting to and from an ECProperty's internal type to a user-fristd::endly representation. 
		// Obtain a type adapter for the specified property. 
		IDgnECTypeAdapterR typeAdapter = IDgnECTypeAdapter::GetForProperty(*ecProp);
		// Create a context for a DgnECInstance
		IDgnECTypeAdapterContextPtr typeContext = IDgnECTypeAdapterContext::Create(*ecProp, *dgnElementECInstanceP, ecProp->GetName().GetWCharCP());

		// Converts the ECValue to a display string.
		typeAdapter.ConvertToString(wStr, ecVal, *typeContext);

		std::string valueAsString = StringUtils::getString(wStr);
		std::string propertyName = StringUtils::getString(ecProp->GetDisplayLabel());

		if (!valueAsString.empty()) {
			//mapPropertyToReaderPropertiesMember(propertyName, ecVal, readerProperties,smartFeatureTypeEnum);
			readerPropertiesBundle->addProperty(new ReaderPropertyDefinition(propertyName, StringUtils::getString(ecProp->GetTypeName()), ecVal));
			//ReaderPropertyDefinition* readerPropertyDefinition =

			outfile << static_cast<Utf8String>(ecProp->GetDisplayLabel()) << "["
				<< static_cast<Utf8String>(ecProp->GetTypeName()) << "] "
				<< "= " << static_cast<Utf8String>(wStr) << std::endl;

			//outfile << "val " << propertyName << "["
			//	<< StringUtils::getString(ecProp->GetTypeName()) << "] "
			//	<< "= " << ecVal.GetUtf8CP() << std::endl;
		}

		
		


		//HARD CODED FOR CURVES//
		/*if (propertyName == "Degree")
			readerProperties.curveDegree = ecVal.GetInteger();*/
		//---------------------//
			
	}
	outfile.close();
	
}

