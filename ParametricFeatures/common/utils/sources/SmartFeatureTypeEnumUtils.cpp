#include "../headers/SmartFeatureTypeEnumUtils.h"



map<SmartFeatureTypeEnum, vector<string>> SmartFeatureTypeEnumUtils::mappedValues = {
	{ SmartFeatureTypeEnum::BOOLEAN_FEATURE,{ "BooleanFeature" } },
	{ SmartFeatureTypeEnum::CREATE_SOLIDS,{ "Revolve", "ThickenFeature", "Extrude", "ExtrudeAlong"} },
	{ SmartFeatureTypeEnum::UNDEFINED,{ "" } },
};

SmartFeatureTypeEnum SmartFeatureTypeEnumUtils::getSmartFeatureTypeEnumByClassName(string classNameValue)
{
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
