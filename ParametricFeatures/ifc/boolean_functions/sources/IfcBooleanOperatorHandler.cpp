#include "../headers/IfcBooleanOperatorHandler.h"

Ifc4::IfcRepresentationItem* IfcBooleanOperatorHandler::buildBooleanRepresentation(SmartFeatureTreeNode& smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file)
{
	
	Ifc4::IfcRepresentationItem* ifcRepresentationItem = nullptr;
	//if (smartFeatureTreeNode.getReaderProperties()->getSmartFeatureGeneralProperties()->getSmartFeatureTypeEnum() != SmartFeatureTypeEnum::SmartFeatureTypeEnum::BOOLEAN_FEATURE) {
	//	return nullptr;
	//}
	BooleanOperationProperties booleanOperationProperties;
	PrimitiveGraphicProperties* primitiveGraphicProperties;
	if (smartFeatureTreeNode.getReaderProperties()->tryGetBooleanOperationProperties(booleanOperationProperties)) {
		if (booleanOperationProperties.getBooleanFunction() != BooleanFunctions::BooleanFunctionsEnum::UNDEFINED)
		{
			ifcRepresentationItem = solveBooleanOperaionts(smartFeatureTreeNode, file, booleanOperationProperties);
		}

	}
	else if(smartFeatureTreeNode.getGraphicProperties()->tryGetPrimitiveGraphicProperties(primitiveGraphicProperties))
	{
		IfcPrimitivesBuilder* ifcPrimitivesBuilder = new IfcPrimitivesBuilder();
		ifcRepresentationItem = ifcPrimitivesBuilder->buildIfcPrimitive(*smartFeatureTreeNode.getGraphicProperties(), file);
	}

	// handle when ifcRepresentationItem is nullptr
	if (ifcRepresentationItem != nullptr) 
	{
		file.addEntity(ifcRepresentationItem);
	}

	

	return ifcRepresentationItem;
}

Ifc4::IfcRepresentationItem* IfcBooleanOperatorHandler::solveBooleanOperaionts(SmartFeatureTreeNode& smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file, 
	BooleanOperationProperties& booleanOperationProperties)
{
	Ifc4::IfcBooleanOperator::Value ifcOperatorBool;

	BooleanFunctions::BooleanFunctionsEnum currentBooleanOperation = booleanOperationProperties.getBooleanFunction();

	if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::UNION) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION;
	}
	else if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::DIFFERENCE) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE;
	}
	else if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::INTERSECTION) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_INTERSECTION;
	}
	else {
		// log boolean function not found or not mapped
		return nullptr;
	}

	if (smartFeatureTreeNode.getLeftNode() == nullptr || smartFeatureTreeNode.getRightNode() == nullptr) {
		return nullptr;
	}

	Ifc4::IfcRepresentationItem* leftRepresentationItem = buildBooleanRepresentation(*smartFeatureTreeNode.getLeftNode(), file);
	Ifc4::IfcRepresentationItem* rightRepresentationItem = buildBooleanRepresentation(*smartFeatureTreeNode.getRightNode(), file);
	if (leftRepresentationItem != nullptr && rightRepresentationItem != nullptr) {
		return new Ifc4::IfcBooleanResult(ifcOperatorBool, leftRepresentationItem, rightRepresentationItem);
	}
	
	return nullptr;
}
