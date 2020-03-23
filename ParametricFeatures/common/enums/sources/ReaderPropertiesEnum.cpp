#include "../headers/ReaderPropertiesEnum.h"
namespace ReaderPropertiesEnum 
{
	ReaderPropertiesEnum getElementPropertiesEnumByStringValue(std::string stringValue)
	{
		std::map<ReaderPropertiesEnum, std::string> mappedValues = {
			{ ReaderPropertiesEnum::NODE_ID, "NodeId" },
			{ ReaderPropertiesEnum::BOOLEAN_FUNCTION,"BooleanFunction" },
			{ ReaderPropertiesEnum::ROTATION,"Rotation" },
			{ ReaderPropertiesEnum::NONE,"" },
		};

		for (auto const& element : mappedValues) {
			if (element.second == stringValue) {
				return element.first;
			}
		}
		// TODO add warning log value not found
		return ReaderPropertiesEnum::NONE;
	}
}