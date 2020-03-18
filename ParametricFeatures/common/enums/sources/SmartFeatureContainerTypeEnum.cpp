#include "../headers/SmartFeatureContainerTypeEnum.h"


namespace SmartFeatureContainerTypeEnum {

	std::map<SmartFeatureContainerTypeEnum, std::vector<std::string>> mappedValues = {
		{ SmartFeatureContainerTypeEnum::BOOLEAN_FEATURE, {"BooleanFeature"} },
		{ SmartFeatureContainerTypeEnum::CREATE_SOLIDS,{ "Revolve", "ThickenFeature" } },
		{ SmartFeatureContainerTypeEnum::UNDEFINED, {"" }},
	};

	SmartFeatureContainerTypeEnum getSmartFeatureContainerTypeEnumByClassName(std::string stringValue)
	{
		for (auto const& element : mappedValues) {
			for (int i = 0; i < element.second.size(); ++i) {
				if (element.second[i] == stringValue) {
					return element.first;
				}
			}

		}
		// TODO add warning log value not found
		return SmartFeatureContainerTypeEnum::UNDEFINED;
	}
}