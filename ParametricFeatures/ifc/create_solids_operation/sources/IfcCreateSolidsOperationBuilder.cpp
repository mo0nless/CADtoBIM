#include "../headers/IfcCreateSolidsOperationBuilder.h"

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
Ifc4::IfcRepresentationItem* IfcCreateSolidsOperationBuilder::buildIfcCreateSolidsOperation(SmartFeatureTreeNode& smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcRepresentationItem* item = nullptr;

	CreateSolidsOperationProperties createSolidsOperationProperties;
	smartFeatureTreeNode.getReaderProperties()->tryGetCreateSolidsOperationProperties(createSolidsOperationProperties);

	switch (createSolidsOperationProperties.getCreateSolidTypeEnum())
	{
		case CreateSolidFunctionsEnum::EXTRUDE:
		{
			ExtrusionReaderProperties* extrusionReaderProperties;
			createSolidsOperationProperties.tryGetExtrusionReaderProperties(extrusionReaderProperties);
			
			GraphicProperties* graphicProperties = nullptr;

			CurvesPrimitivesContainer* curvesPrimitivesContainer;
			if (smartFeatureTreeNode.getLeftNode()->getGraphicProperties()->tryGetCurvesPrimitivesContainer(curvesPrimitivesContainer))
			{
				graphicProperties = smartFeatureTreeNode.getLeftNode()->getGraphicProperties();
			}
			else if (smartFeatureTreeNode.getRightNode()->getGraphicProperties()->tryGetCurvesPrimitivesContainer(curvesPrimitivesContainer))
			{
				graphicProperties = smartFeatureTreeNode.getRightNode()->getGraphicProperties();
			}
			else break;

			if(curvesPrimitivesContainer->getBoundaryTypeCurvesContainer() == CurvesBoundaryTypeEnum::OUTER)
			{
				IfcCurvesPrimitivesBuilder* ifcCurvesPrimitivesBuilder = new IfcCurvesPrimitivesBuilder();
				std::vector<Ifc4::IfcCurve*> ifcCurvesItemsVector = ifcCurvesPrimitivesBuilder->buildIfcCurvesPrimitives(
					*graphicProperties,
					file
				);

				Ifc4::IfcArbitraryClosedProfileDef* profileDef = new Ifc4::IfcArbitraryClosedProfileDef(
					Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
					boost::none,
					ifcCurvesItemsVector[0]
				);

				Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
					IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(curvesPrimitivesContainer->getCentroIDxy()),
					IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(curvesPrimitivesContainer->getDirectionZ()), //Need to be Checked
					IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(curvesPrimitivesContainer->getDirectionX()) //Need to be Checked
				);

				item  = new Ifc4::IfcExtrudedAreaSolid(
					profileDef,
					place,
					IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(curvesPrimitivesContainer->getNormal()), //Need to be Checked
					NumberUtils::convertMicrometersToMetters(extrusionReaderProperties->getDistance())
				);
			}
		}
		break;
		default:
			break;
	}
	

	return item;
}
#pragma warning (pop)
