#include "../headers/ReaderPropertiesEnumUtils.h"



std::map<ReaderPropertiesEnum, std::string> ReaderPropertiesEnumUtils::mappedValues =
{
	{ ReaderPropertiesEnum::NODE_ID, "NodeId" },
	{ ReaderPropertiesEnum::BOOLEAN_FUNCTION,"BooleanFunction" },
	{ ReaderPropertiesEnum::ROTATION,"Rotation" },
	{ ReaderPropertiesEnum::NONE,"" },
};

ReaderPropertiesEnum ReaderPropertiesEnumUtils::getElementPropertiesEnumByStringValue(std::string stringValue)
{
	for (auto const& element : mappedValues) 
	{
		if (element.second == stringValue) 
		{
			return element.first;
		}
	}
	// TODO add warning log value not found
	return ReaderPropertiesEnum::NONE;
}
