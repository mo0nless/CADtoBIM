#include "ReaderPropertiesEnumUtils.h"



std::map<ReaderPropertiesEnum::ReaderPropertiesEnum, std::string> ReaderPropertiesEnumUtils::mappedValues = {
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::NODE_ID, "NodeId" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::BOOLEAN_FUNCTION,"BooleanFunction" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::WIDTH, "Width" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::LENGTH,"Length" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::HEIGHT, "Height" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::ROTATION_X,"Rotation-X" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::ROTATION_Y,"Rotation-Y" },
		{ ReaderPropertiesEnum::ReaderPropertiesEnum::ROTATION_Z,"Rotation-Z" },
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
