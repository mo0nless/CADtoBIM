#include "../headers/ReaderPropertiesMapper.h"

#include <fstream> 
#include <filesystem>

void ReaderPropertiesMapper::mapECPropertiesToReaderProperties(DgnElementECInstanceP dgnElementECInstanceP, ReaderProperties & readerProperties)
{
	std::ofstream outfile;
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	//std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
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

		readerProperties.setBooleanFunction(-1);

		if (!valueAsString.empty()) {
			mapPropertyToReaderPropertiesMember(propertyName, ecVal, readerProperties);
		}
		
		outfile << static_cast<Utf8String>(ecProp->GetDisplayLabel()) << "["
			<< static_cast<Utf8String>(ecProp->GetTypeName()) << "] "
			<< "= " << static_cast<Utf8String>(wStr) << std::endl;
			
	}
	outfile.close();
	
}

void ReaderPropertiesMapper::mapPropertyToReaderPropertiesMember(std::string labelValue, ECValue eCValue, ReaderProperties &readerProperties)
{
	ReaderPropertiesEnum::ReaderPropertiesEnum value = ReaderPropertiesEnumUtils::getElementPropertiesEnumByStringValue(labelValue);

	switch (value)
	{
	case ReaderPropertiesEnum::ReaderPropertiesEnum::NODE_ID:
		readerProperties.setNodeId(eCValue.GetInteger());
		break;
	case ReaderPropertiesEnum::ReaderPropertiesEnum::BOOLEAN_FUNCTION:
		readerProperties.setBooleanFunction(eCValue.GetInteger());
		break;
	case ReaderPropertiesEnum::ReaderPropertiesEnum::NONE:
		break;
	default:
		// TODO add info log
		break;
	}

}
