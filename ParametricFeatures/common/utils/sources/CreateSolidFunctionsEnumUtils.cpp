#include "../headers/CreateSolidFunctionsEnumUtils.h"


map<CreateSolidFunctionsEnum, string> CreateSolidFunctionsEnumUtils::mappedValues = {
	{ CreateSolidFunctionsEnum::REVOLVE, "Revolve" },
	{ CreateSolidFunctionsEnum::EXTRUDE, "Extrude" },
	{ CreateSolidFunctionsEnum::THICKEN, "ThickenFeature" },
	{ CreateSolidFunctionsEnum::EXTRUDE_ALONG, "ExtrudeAlong" },
	{ CreateSolidFunctionsEnum::UNDEFINED, "" },
};

map<CreateSolidPropertiesEnum, string> CreateSolidFunctionsEnumUtils::mappedValuesProps = {

	{ CreateSolidPropertiesEnum::THICKNESS,"Thickness" },
	{ CreateSolidPropertiesEnum::DISTANCE,"Distance" },
	{ CreateSolidPropertiesEnum::NONE,"" },
};


CreateSolidFunctionsEnum CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(string className)
{
	for (auto const& element : mappedValues) {
		if (element.second == className) {
			return element.first;
		}
	}
	// TODO add warning log value not found
	return CreateSolidFunctionsEnum::UNDEFINED;
}

CreateSolidPropertiesEnum CreateSolidFunctionsEnumUtils::getSolidPropertiesEnumByClassName(string className)
{
	for (auto const& element : mappedValuesProps) {
		if (element.second == className) {
			return element.first;
		}
	}
	// TODO add warning log value not found
	return CreateSolidPropertiesEnum::NONE;
}
