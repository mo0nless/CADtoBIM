#include "../headers/IfcBooleanOperatorHandler.h"


Ifc4::IfcGeometricRepresentationItem* IfcBooleanOperatorHandler::solveBooleanOperation(Ifc4::IfcGeometricRepresentationItem* leftIfcRepresentationItem, Ifc4::IfcGeometricRepresentationItem* rigthIfcRepresentationItem, IfcReaderPropertiesBundle& ifcReaderPropertiesBundle)
{

	BooleanFunctions::BooleanFunctionsEnum booleanFunctionsEnum;
	for (auto const& modelerProperty : ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getProperties()) {
		if (modelerProperty->getPropertyName() == "BooleanFunction") {
			booleanFunctionsEnum = BooleanFunctions::getBooleanFunctionsEnumByIntValue(std::stoi(modelerProperty->getPropertyValueAsString()));
		}
	}

	Ifc4::IfcBooleanOperator::Value ifcOperatorBool;

	if (booleanFunctionsEnum == BooleanFunctions::BooleanFunctionsEnum::UNION) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION;
	}
	else if (booleanFunctionsEnum == BooleanFunctions::BooleanFunctionsEnum::DIFFERENCE) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE;
	}
	else if (booleanFunctionsEnum == BooleanFunctions::BooleanFunctionsEnum::INTERSECTION) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_INTERSECTION;
	}
	else {
		// log boolean function not found or not mapped
		return nullptr;
	}

	if (leftIfcRepresentationItem != nullptr && rigthIfcRepresentationItem != nullptr){
		return new Ifc4::IfcBooleanResult(ifcOperatorBool, leftIfcRepresentationItem, rigthIfcRepresentationItem);
	}
	
	return nullptr;
}

