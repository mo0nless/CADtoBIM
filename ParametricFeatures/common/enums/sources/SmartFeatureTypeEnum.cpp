#include "../headers//SmartFeatureTypeEnum.h"


namespace SmartFeatureTypeEnum 
{
	SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(std::string classNameValue)
	{
		std::map<SmartFeatureTypeEnum, std::vector<std::string>> mappedValues = {
			{ SmartFeatureTypeEnum::BOOLEAN_FEATURE,{ "BooleanFeature" } },
			{ SmartFeatureTypeEnum::CREATE_SOLIDS,{ "Revolve", "ThickenFeature" } },
			{ SmartFeatureTypeEnum::UNDEFINED,{ "" } },
		};

		for (auto const& element : mappedValues) {
			for (int i = 0; i < element.second.size(); ++i) {
				if (element.second[i] == classNameValue) {
					return element.first;
				}
			}

		}
		// TODO add warning log value not found
		return SmartFeatureTypeEnum::UNDEFINED;
	}
}