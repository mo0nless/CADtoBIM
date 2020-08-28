#include "../headers/IfcPrimitivesEnhancer.h"


void IfcPrimitivesEnhancer::enhanceIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	std::vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);
		
			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcElementBundle*& ifcElementBundle = ifcBundleVector.at(i);

			Ifc4::IfcRepresentationItem::list::ptr ifcTemplatedEntityList(new Ifc4::IfcRepresentationItem::list());

			for (auto element : dictionaryProperties.getElementBundle())
			{
				SolidPrimitiveProperties* solidPrimitiveProperties = dynamic_cast<SolidPrimitiveProperties*>(element->getGraphicProperties());
				if (solidPrimitiveProperties != nullptr) {
					Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildIfcPrimitive(*solidPrimitiveProperties, file,element);
					if (ifcRepresentationItem != nullptr)
					{
						auto bundle = new IfcGraphicPropertiesBundle(element->getGraphicProperties(),
							ifcRepresentationItem, element->getElementHandle(), element->getElemDisplayParamsCP());
						bundle->setColor(element->getColor());
						bundle->setTransparency(element->getTransparency());
						bundle->setMaterial(element->getMaterial());
						ifcElementBundle->addIfcGraphicPropertiesBundle(bundle);
						//ifcTemplatedEntityList->push(ifcRepresentationItem);
					}
				}
			}
		}
	}

}

Ifc4::IfcGeometricRepresentationItem * IfcPrimitivesEnhancer::buildIfcPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
	ElementBundle* elementBundle)
{
	Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = nullptr;

	PrimitiveTypeEnum primitiveType = primitiveGraphicProperties.getPrimitiveTypeEnum();
	if (primitiveType == PrimitiveTypeEnum::SPHERE || primitiveType == PrimitiveTypeEnum::BOX ||
			primitiveType == PrimitiveTypeEnum::CONE || primitiveType == PrimitiveTypeEnum::CYLINDER)
	{
		ifcRepresentationItem = buildBasicPrimitive(primitiveGraphicProperties, file);
	}
	else if (primitiveType == PrimitiveTypeEnum::TORUS || primitiveType == PrimitiveTypeEnum::TRUNCATED_CONE || 
		primitiveType == PrimitiveTypeEnum::ROTATIONAL_SWEEP || primitiveType == PrimitiveTypeEnum::EXTRUSION)
	{
		ifcRepresentationItem = buildComplexPrimitive(primitiveGraphicProperties, file, elementBundle);
	}

	return ifcRepresentationItem;
	
}

Ifc4::IfcCsgSolid * IfcPrimitivesEnhancer::buildBasicPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = nullptr;

		PrimitiveTypeEnum primitiveTypeEnum = primitiveGraphicProperties.getPrimitiveTypeEnum();
		Ifc4::IfcAxis2Placement3D* placement = IfcOperationsHelper::buildIfcAxis2Placement3D(
			primitiveGraphicProperties.getCentroid(), 
			primitiveGraphicProperties.getVectorAxisZ(), 
			primitiveGraphicProperties.getVectorAxisX()
		);

		if (primitiveTypeEnum == PrimitiveTypeEnum::SPHERE) {

			SphereGraphicProperties& sphereGraphicProperties = dynamic_cast<SphereGraphicProperties&>(primitiveGraphicProperties);
			ifcRepresentationItem = new Ifc4::IfcSphere(placement, NumberUtils::convertCurrentUnitToMeters(sphereGraphicProperties.getRadius()));

		} else if (primitiveTypeEnum == PrimitiveTypeEnum::BOX) {

			BoxGraphicProperties& boxGraphicProperties = dynamic_cast<BoxGraphicProperties&>(primitiveGraphicProperties);

			ifcRepresentationItem = new Ifc4::IfcBlock(placement, NumberUtils::convertCurrentUnitToMeters(boxGraphicProperties.getLength()),
			NumberUtils::convertCurrentUnitToMeters(boxGraphicProperties.getWidth()), NumberUtils::convertCurrentUnitToMeters(boxGraphicProperties.getHeight()));

		} else if (primitiveTypeEnum == PrimitiveTypeEnum::CYLINDER) {
			CylinderGraphicProperties& cylinderGraphicProperties = dynamic_cast<CylinderGraphicProperties&>(primitiveGraphicProperties);

			// the cylinder point of placement is the base origin, not the centroid
			DVec3d cylinderPlacement;
			cylinderPlacement.Init(cylinderGraphicProperties.getBaseOrigin());
			// overwrite the placement value
			placement = IfcOperationsHelper::buildIfcAxis2Placement3D(
				cylinderPlacement,
				cylinderGraphicProperties.getVectorAxisZ(),
				cylinderGraphicProperties.getVectorAxisX()
			);

			ifcRepresentationItem = new Ifc4::IfcRightCircularCylinder(placement, NumberUtils::convertCurrentUnitToMeters(cylinderGraphicProperties.getHeight()),
			NumberUtils::convertCurrentUnitToMeters(cylinderGraphicProperties.getRadius()));

		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::CONE)
		{
			ConeGraphicProperties& coneGraphicProperties = dynamic_cast<ConeGraphicProperties&>(primitiveGraphicProperties);

			// the cone point of placement is the base origin, not the centroid
			DVec3d conePlacement;
			conePlacement.Init(coneGraphicProperties.getBaseOrigin());
			// overwrite the placement value
			placement = IfcOperationsHelper::buildIfcAxis2Placement3D(
				conePlacement,
				coneGraphicProperties.getVectorAxisZ(),
				coneGraphicProperties.getVectorAxisX()
			);

			ifcRepresentationItem = new Ifc4::IfcRightCircularCone(placement, NumberUtils::convertCurrentUnitToMeters(coneGraphicProperties.getHeight()),
			NumberUtils::convertCurrentUnitToMeters(coneGraphicProperties.getBaseRadius()));
		}
	
	if (ifcRepresentationItem != nullptr) {
		Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(ifcRepresentationItem);
		return solid;

	}
	return nullptr;
}


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
Ifc4::IfcGeometricRepresentationItem * IfcPrimitivesEnhancer::buildComplexPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, 
	IfcHierarchyHelper<Ifc4>& file, ElementBundle* elementBundle)
{


	SessionManager* sm = sm->getInstance();
	sm->getDataOutputFilePath();
	sm->getIfcOutputFilePath();

	Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = nullptr;
	std::ofstream outfile;
	//std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::string filePath = SessionManager::getInstance()->getDataOutputFilePath();

		PrimitiveTypeEnum primitiveTypeEnum = primitiveGraphicProperties.getPrimitiveTypeEnum();

		if (primitiveTypeEnum == PrimitiveTypeEnum::TORUS)
		{
			TorusGraphicProperties& torusGraphicProperties = dynamic_cast<TorusGraphicProperties&>(primitiveGraphicProperties);
			
			// torus placement is NOT the centroid, but the center of rotation
			DVec3d torusPointPlacement;
			torusPointPlacement.Init(torusGraphicProperties.getCenterPointOfRotation());

			Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0,
				NumberUtils::convertCurrentUnitToMeters(torusGraphicProperties.getMajorRadius())), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			Ifc4::IfcCircleProfileDef* profileDefinition = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement,
				NumberUtils::convertCurrentUnitToMeters(torusGraphicProperties.getMinorRadius()));
			Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			// !!! torus placement axes should be provided in the order of Y, Z
			Ifc4::IfcAxis2Placement3D* torusPlacement = IfcOperationsHelper::buildIfcAxis2Placement3D(
				torusPointPlacement,
				torusGraphicProperties.getVectorAxisY(),
				torusGraphicProperties.getVectorAxisZ()
			);

			ifcRepresentationItem = new Ifc4::IfcRevolvedAreaSolid(profileDefinition, torusPlacement, localAxis1Placement, torusGraphicProperties.getSweepRadians());
		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::TRUNCATED_CONE) {

			ConeGraphicProperties& coneGraphicProperties = dynamic_cast<ConeGraphicProperties&>(primitiveGraphicProperties);

			double similarityRatio = coneGraphicProperties.getTopRadius() / coneGraphicProperties.getBaseRadius();
			double smallConeHeight = (similarityRatio*coneGraphicProperties.getHeight()) / (1 - similarityRatio);

			// !!! overrite the place for cone, as the cone is positioned in the space not based on the centroid, but the base origin
			DVec3d bigConePlacementVector;
			bigConePlacementVector.Init(coneGraphicProperties.getBaseOrigin());

			Ifc4::IfcAxis2Placement3D* bigConePlacement = IfcOperationsHelper::buildIfcAxis2Placement3D(
				bigConePlacementVector,
				coneGraphicProperties.getVectorAxisZ(),
				coneGraphicProperties.getVectorAxisX()
			);

			DVec3d smallConePlacementVector;
			smallConePlacementVector.Init(coneGraphicProperties.getTopOrigin());

			Ifc4::IfcAxis2Placement3D* smallConePlacement = IfcOperationsHelper::buildIfcAxis2Placement3D(
				smallConePlacementVector,
				coneGraphicProperties.getVectorAxisZ(),
				coneGraphicProperties.getVectorAxisX()
			);

			Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* bigCompleteCone = new Ifc4::IfcRightCircularCone(bigConePlacement,
				NumberUtils::convertCurrentUnitToMeters((coneGraphicProperties.getHeight() + smallConeHeight)),
				NumberUtils::convertCurrentUnitToMeters(coneGraphicProperties.getBaseRadius()));

			Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* smallCompleteCone = new Ifc4::IfcRightCircularCone(smallConePlacement,
				NumberUtils::convertCurrentUnitToMeters(smallConeHeight), NumberUtils::convertCurrentUnitToMeters(coneGraphicProperties.getTopRadius()));

			ifcRepresentationItem = new Ifc4::IfcBooleanResult(Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE, bigCompleteCone, smallCompleteCone);

		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::ROTATIONAL_SWEEP) 
		{
			RotationalSweepGraphicProperties& rotationalSweepGraphicProperties = dynamic_cast<RotationalSweepGraphicProperties&>(primitiveGraphicProperties);

			IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
			IfcElementBundle* ifcElementBundle = new IfcElementBundle(-1, "");

			DVec3d sweepCenterOfRotation;
			sweepCenterOfRotation.Init(rotationalSweepGraphicProperties.getCenterRotation());

			Ifc4::IfcGeometricRepresentationItem* result = nullptr;
			bool addToIfcElementBundle = false;
			//ifcShapesEnhancer->dimension = 2;
			ShapesGraphicProperties* shape = rotationalSweepGraphicProperties.getShapesGraphicProperties();
			
			//Single Bound
			if (shape->getShapesGraphicsContainer().empty())
			{				
				IfcOperationsHelper::adjustShapeGlobalPlacement(shape, sweepCenterOfRotation, true);
			}
			//Parity Region, set of bounds 
			else
			{
				for (auto bound: shape->getShapesGraphicsContainer())
					IfcOperationsHelper::adjustShapeGlobalPlacement(bound, sweepCenterOfRotation, true);
			}

			ifcShapesEnhancer->buildGeometricRepresentationShapes(shape, file, ifcElementBundle,elementBundle, addToIfcElementBundle);

			if (ifcShapesEnhancer->hasSingleShapeItem())
				result = ifcShapesEnhancer->getSingleShapeRepresentation();

			Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryClosedProfileDef(
				Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, 
				std::string("RotationalSweep"),
				(Ifc4::IfcCurve*) result
			);
			
			Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(
					file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0),
					IfcOperationsHelper::buildIfcDirection3DfromDirectionVec3D(rotationalSweepGraphicProperties.getVectorAxisZ())
				);

			Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(
				IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(rotationalSweepGraphicProperties.getCenterRotation()),
				new Ifc4::IfcDirection(std::vector<double>()), 
				new Ifc4::IfcDirection(std::vector<double>())
			);
			
			ifcRepresentationItem = new Ifc4::IfcRevolvedAreaSolid(
				profileDef, 
				placement,
				localAxis1Placement, 
				rotationalSweepGraphicProperties.getSweepRadians()
			);

			DVec3d rDX, rDY, rDZ, cDX, cDY, cDZ;
			rDX = rotationalSweepGraphicProperties.getVectorAxisX();
			rDY = rotationalSweepGraphicProperties.getVectorAxisY();
			rDZ = rotationalSweepGraphicProperties.getVectorAxisZ();

			cDX = shape->getVectorAxisX();
			cDY = shape->getVectorAxisY();
			cDZ = shape->getVectorAxisZ();
			
			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "IFC Revolve --------" << std::endl;
			outfile << "Revolved solid: " << std::endl;
			outfile << "Direction [X] = " << rDX.x << ", " << rDX.y << ", " << rDX.z << std::endl;
			outfile << "Direction [Y] = " << rDY.x << ", " << rDY.y << ", " << rDY.z << std::endl;
			outfile << "Direction [Z] = " << rDZ.x << ", " << rDZ.y << ", " << rDZ.z << std::endl;
			outfile << std::endl;
			outfile << "Curve Profile: " << std::endl;
			outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << std::endl;
			outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << std::endl;
			outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << std::endl;
			outfile.close();
		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::EXTRUSION)
		{
			ExtrusionGraphicProperties& extrusionGraphicProperties = dynamic_cast<ExtrusionGraphicProperties&>(primitiveGraphicProperties);
			IfcElementBundle* ifcElementBundle = new IfcElementBundle(-1, "");

			Ifc4::IfcCurve* ifcCurve = nullptr;
			ShapesGraphicProperties* shape = extrusionGraphicProperties.getShapesGraphicProperties();
			CurvesBoundaryTypeEnum curveBoundary = shape->getBoundaryTypeCurvesContainer();
			
			bool addToIfcElementBundle = false;
			Ifc4::IfcProfileDef* profileDef = nullptr;

			Ifc4::IfcProfileTypeEnum::Value pEnum;
			if (extrusionGraphicProperties.getIsSolid())
				pEnum = Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA;
			else
				pEnum = Ifc4::IfcProfileTypeEnum::IfcProfileType_CURVE;

			IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
			//Change dimension
			//ifcShapesEnhancer->dimension = 2;

			//Single Bound
			if (shape->getShapesGraphicsContainer().empty())
			{
				IfcOperationsHelper::adjustShapeGlobalPlacement(shape, extrusionGraphicProperties.getCentroid(), false);
			}
			//Parity Region, set of bounds 
			else
			{
				for (auto bound : shape->getShapesGraphicsContainer())
					IfcOperationsHelper::adjustShapeGlobalPlacement(bound, extrusionGraphicProperties.getCentroid(), false);
			}

			ifcShapesEnhancer->buildGeometricRepresentationShapes(shape, file, ifcElementBundle,elementBundle, addToIfcElementBundle);
			
			if (curveBoundary != CurvesBoundaryTypeEnum::PARITY_REGION && curveBoundary != CurvesBoundaryTypeEnum::UNION_REGION)
			{
				BoundTypeIfcCurve* curveBound = ifcShapesEnhancer->getCurvesShapeRepresentationVector().front();

				ifcCurve = curveBound->ifcCurve;
				
				if (curveBound->isClosed)
				{
					Ifc4::IfcCurve* curveToExtrude = ifcCurve;
					profileDef = new Ifc4::IfcArbitraryClosedProfileDef(
						pEnum,
						std::string("Closed Profile"),
						curveToExtrude
					);
				}
				else 
				{
					Ifc4::IfcBoundedCurve* curveToExtrude = (Ifc4::IfcBoundedCurve*)ifcCurve;
					profileDef = new Ifc4::IfcArbitraryOpenProfileDef(
						pEnum,
						std::string("Open Profile"),
						curveToExtrude
					);
				}
			}
			else
			{
				IfcTemplatedEntityList<Ifc4::IfcCurve>* profiles = new IfcTemplatedEntityList<Ifc4::IfcCurve>();
				Ifc4::IfcCurve* outer = nullptr;
				for (auto boundTypeCurve : ifcShapesEnhancer->getCurvesShapeRepresentationVector())
				{
					Ifc4::IfcCurve* curve = boundTypeCurve->ifcCurve;
					CurvesBoundaryTypeEnum bound = boundTypeCurve->boundary;

					if (CurvesBoundaryTypeEnum::INNER == bound)				
						profiles->push(curve);
					else if (CurvesBoundaryTypeEnum::OUTER == bound)
						outer = curve;
				}

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCurve>> tempProfiles(profiles);

				profileDef = new Ifc4::IfcArbitraryProfileDefWithVoids(
					pEnum,
					std::string("Outer and Inner"),
					outer,
					tempProfiles
				);

			}
			
			Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(
				IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(extrusionGraphicProperties.getCentroid()),
				new Ifc4::IfcDirection(std::vector<double>()),
				new Ifc4::IfcDirection(std::vector<double>())
			);


			if (extrusionGraphicProperties.getIsSolid())
			{
				Ifc4::IfcExtrudedAreaSolid* extrusionitem = new Ifc4::IfcExtrudedAreaSolid(
					profileDef,
					placement,
					IfcOperationsHelper::buildIfcDirection3DfromDirectionVec3D(extrusionGraphicProperties.getDirectionOfExtrusion()),
					NumberUtils::convertCurrentUnitToMeters(extrusionGraphicProperties.getLegnthOfExtrusion())
				);

				ifcRepresentationItem = extrusionitem;
			}
			else
			{
				Ifc4::IfcSurfaceOfLinearExtrusion* surfaceExtrusion = new Ifc4::IfcSurfaceOfLinearExtrusion(
					profileDef,
					placement,
					IfcOperationsHelper::buildIfcDirection3DfromDirectionVec3D(extrusionGraphicProperties.getDirectionOfExtrusion()),
					NumberUtils::convertCurrentUnitToMeters(extrusionGraphicProperties.getLegnthOfExtrusion())
				);

				ifcRepresentationItem = surfaceExtrusion;
			}

			DVec3d rDX, rDY, rDZ, cDX, cDY, cDZ, dirExt;
			rDX = extrusionGraphicProperties.getVectorAxisX();
			rDY = extrusionGraphicProperties.getVectorAxisY();
			rDZ = extrusionGraphicProperties.getVectorAxisZ();

			cDX = shape->getVectorAxisX();
			cDY = shape->getVectorAxisY();
			cDZ = shape->getVectorAxisZ();

			dirExt = extrusionGraphicProperties.getDirectionOfExtrusion();

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << std::fixed;
			outfile << "IFC Extrusion --------" << std::endl;
			outfile << "Extrusion solid: " << std::endl;
			outfile << "Direction [X] = " << rDX.x << ", " << rDX.y << ", " << rDX.z << std::endl;
			outfile << "Direction [Y] = " << rDY.x << ", " << rDY.y << ", " << rDY.z << std::endl;
			outfile << "Direction [Z] = " << rDZ.x << ", " << rDZ.y << ", " << rDZ.z << std::endl;
			outfile << std::endl;
			outfile << "Curve Profile: " << std::endl;
			outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << std::endl;
			outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << std::endl;
			outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << std::endl;
			outfile << std::endl;
			outfile << "Direction of Extrusion: " << std::endl;
			outfile << "Direction [X] = " << dirExt.x << ", " << dirExt.y << ", " << dirExt.z << std::endl;
			outfile.close();
		}


	return ifcRepresentationItem;
}
#pragma warning( pop )

