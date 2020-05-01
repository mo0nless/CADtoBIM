#include "../headers/IfcCreateSolidsOperationBuilder.h"

//Ifc4::IfcRepresentationItem* IfcCreateSolidsOperationBuilder::buildIfcCreateSolidsOperation(SmartFeatureTreeNode& smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file)
//{
//	Ifc4::IfcRepresentationItem* item = nullptr;
//
//	//TODO[MP / SB] find another implementation
//	//CreateSolidsOperationProperties createSolidsOperationProperties;
//	//
//	//smartFeatureTreeNode.getReaderProperties()->tryGetCreateSolidsOperationProperties(createSolidsOperationProperties);
//	//
//	//switch (createSolidsOperationProperties.getCreateSolidTypeEnum())
//	//{
//	//	case CreateSolidFunctionsEnum::EXTRUDE:
//	//	{
//	//		ExtrusionReaderProperties* extrusionReaderProperties;
//	//		createSolidsOperationProperties.tryGetExtrusionReaderProperties(extrusionReaderProperties);
//	//
//	//		GraphicProperties* graphicProperties = nullptr;
//	//
//	//		CurvesPrimitivesContainer* curvesPrimitivesContainer;
//	//		TODO [MP/SB] find another implementation
//	//		/*if (smartFeatureTreeNode.getLeftNode()->getGraphicProperties()->tryGetCurvesPrimitivesContainer(curvesPrimitivesContainer))
//	//		{
//	//			graphicProperties = smartFeatureTreeNode.getLeftNode()->getGraphicProperties();
//	//		}
//	//		else if (smartFeatureTreeNode.getRightNode()->getGraphicProperties()->tryGetCurvesPrimitivesContainer(curvesPrimitivesContainer))
//	//		{
//	//			graphicProperties = smartFeatureTreeNode.getRightNode()->getGraphicProperties();
//	//		}
//	//		else
//	//		{
//	//			break;
//	//		}*/
//	//
//	//			if(curvesPrimitivesContainer->getBoundaryTypeCurvesContainer() == CurvesBoundaryTypeEnum::OUTER)
//	//			{
//	//				IfcShapesEnhancer* IfcShapesEnhancer = new IfcShapesEnhancer();
//	//				std::vector<Ifc4::IfcCurve*> ifcCurvesItemsVector = IfcShapesEnhancer->buildIfcCurvesPrimitives(
//	//					*graphicProperties,
//	//					file
//	//				);
//	//
//	//				Ifc4::IfcArbitraryClosedProfileDef* profileDef = new Ifc4::IfcArbitraryClosedProfileDef(
//	//					Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
//	//					boost::none,
//	//					ifcCurvesItemsVector[0]
//	//				);
//	//
//	//				Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
//	//					IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(curvesPrimitivesContainer->getCentroIDxy()),
//	//					IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(curvesPrimitivesContainer->getDirectionZ()), //Need to be Checked
//	//					IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(curvesPrimitivesContainer->getDirectionX()) //Need to be Checked
//	//				);
//	//
//	//				item  = new Ifc4::IfcExtrudedAreaSolid(
//	//					profileDef,
//	//					place,
//	//					IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(curvesPrimitivesContainer->getNormal()), //Need to be Checked
//	//					NumberUtils::convertMicrometersToMetters(extrusionReaderProperties->getDistance())
//	//				);
//	//			}
//	//		}
//	//	}
//	//	break;
//	//	default:
//	//		break;
//	//}
//	
//
//	return item;
//}

Ifc4::IfcRepresentationItem* IfcCreateSolidsOperationBuilder::buildIfcCreateSolidsOperation(Ifc4::IfcRepresentationItem * leftIfcRepresentationItem, Ifc4::IfcRepresentationItem * rigthIfcRepresentationItem, 
	IfcReaderPropertiesBundle& ifcReaderPropertiesBundle, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcRepresentationItem* representationItem = nullptr;
	if (leftIfcRepresentationItem != nullptr) {
		representationItem = leftIfcRepresentationItem;
	}
	else if (rigthIfcRepresentationItem != nullptr) {
		representationItem = rigthIfcRepresentationItem;
	}

	switch (CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getCassName()))
	{
	case CreateSolidFunctionsEnum::REVOLVE:
	{
		double sweepRadians = 0;
		for (auto const& modelerProperty : ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getProperties()) {
			if (modelerProperty->getPropertyName() == "Angle") {
				sweepRadians = modelerProperty->getPropertyValue().GetDouble();
			}
		}
		//Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));
		//Ifc4::IfcCircleProfileDef* profileDefinition = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement, 1);
		Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, std::string("Revolve"), (Ifc4::IfcBoundedCurve*)representationItem);
		Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));
		Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0), file.addTriplet<Ifc4::IfcDirection>(0, 0, 1));

		Ifc4::IfcRepresentationItem* result = new Ifc4::IfcRevolvedAreaSolid(profileDef, placement, localAxis1Placement, sweepRadians);
		return result;

	}

	case CreateSolidFunctionsEnum::EXTRUDE:
	{
		double length = 0;
		for (auto const& modelerProperty : ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getProperties()) {
			if (modelerProperty->getPropertyName() == "Distance") {
				length = NumberUtils::convertMicrometersToMetters(modelerProperty->getPropertyValue().GetDouble());
			}
		Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,std::string("Extrude"),(Ifc4::IfcBoundedCurve*)representationItem);
		Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0), file.addTriplet<Ifc4::IfcDirection>(0, 0, 1));
		
		Ifc4::IfcRepresentationItem* result =  new Ifc4::IfcExtrudedAreaSolid(profileDef, placement, file.addTriplet<Ifc4::IfcDirection>(1, 0, 0), length);
		return result;

	}

	default:
		return nullptr;
	}

	
}
