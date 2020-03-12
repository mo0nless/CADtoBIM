#include "../headers/IfcBooleanOperatorHandler.h"

Ifc4::IfcRepresentationItem* IfcBooleanOperatorHandler::buildBooleanRepresentation(SmartFeatureTreeNode& smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file)
{
	
	Ifc4::IfcRepresentationItem* my = nullptr;

	if (smartFeatureTreeNode.getReaderProperties()->getBooleanFunction() != BooleanFunctions::BooleanFunctionsEnum::UNDEFINED)
	{
		my = solveBooleanOperaionts(smartFeatureTreeNode, file);
	}
	else
	{

		IfcPrimitivesBuilder* ifcPrimitivesBuilder = new IfcPrimitivesBuilder();
		my = ifcPrimitivesBuilder->buildIfcPrimitive(smartFeatureTreeNode.getGeneralProperties()->getPrimitiveTypeEnum(), *smartFeatureTreeNode.getGraphicProperties(), file);
		//my = PrimitivesSolver(primitiveType, graphicProperties);
	}


	file.addEntity(my);

	return my;
}

Ifc4::IfcRepresentationItem* IfcBooleanOperatorHandler::solveBooleanOperaionts(SmartFeatureTreeNode & smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcBooleanOperator::Value ifcOperatorBool;

	BooleanFunctions::BooleanFunctionsEnum currentBooleanOperation = smartFeatureTreeNode.getReaderProperties()->getBooleanFunction();

	if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::UNION) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION;
	}
	else if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::DIFFERENCE) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE;
	}
	else if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::INTERSECTION) {
		ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_INTERSECTION;
	}

	return new Ifc4::IfcBooleanResult(ifcOperatorBool, buildBooleanRepresentation(*smartFeatureTreeNode.getLeftNode(), file), buildBooleanRepresentation(*smartFeatureTreeNode.getRightNode(), file));
}
