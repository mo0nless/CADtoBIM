#include "../headers/ReaderPropertiesEnumUtils.h"



std::map<ReaderPropertiesEnum::ReaderPropertiesEnum, std::string> ReaderPropertiesEnumUtils::mappedValues = {
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::NODE_ID, "NodeId" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::BOOLEAN_FUNCTION,"BooleanFunction" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::ROTATION,"Rotation" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::NONE,"" },
	};

ReaderPropertiesEnum::ReaderPropertiesEnum ReaderPropertiesEnumUtils::getElementPropertiesEnumByStringValue(std::string stringValue)
{
	for (auto const& element : mappedValues) {
		if (element.second == stringValue) {
			return element.first;
		}
	}
	// TODO add warning log value not found
	return ReaderPropertiesEnum::ReaderPropertiesEnum::NONE;
}
