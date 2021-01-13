#include "../headers/ReaderPropertiesEnumUtils.h"

using namespace Common::Utilities;

map<ReaderPropertiesEnum, string> ReaderPropertiesEnumUtils::mappedValues =
{
	{ ReaderPropertiesEnum::NODE_ID, "NodeId" },
	{ ReaderPropertiesEnum::BOOLEAN_FUNCTION,"BooleanFunction" },
	{ ReaderPropertiesEnum::ROTATION,"Rotation" },
	{ ReaderPropertiesEnum::NONE,"" },
};

ReaderPropertiesEnum ReaderPropertiesEnumUtils::getElementPropertiesEnumByStringValue(string stringValue)
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

ReaderPropertiesEnum ReaderPropertiesEnumUtils::getElementPropertiesEnumByInt(int primitiveBentleyInt)
{
	return ReaderPropertiesEnum(primitiveBentleyInt);
}
