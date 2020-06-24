#include "../headers/IfcPrimitivesEnhancer.h"


void IfcPrimitivesEnhancer::enhanceIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	std::vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			double rotationX, rotationY, rotationZ;
			int orientation;

			for each (auto readerBundle in dictionaryProperties.getReaderPropertiesBundleVector())
			{
				for each(auto readerProperty in readerBundle->getProperties()) {
					if (readerProperty->getPropertyName() == "Rotation-X") {
						rotationX = readerProperty->getPropertyValue().GetDouble();
					}
					else if (readerProperty->getPropertyName() == "Rotation-Y") {
						rotationY = readerProperty->getPropertyValue().GetDouble();
					}
					else if (readerProperty->getPropertyName() == "Rotation-Z") {
						rotationZ = readerProperty->getPropertyValue().GetDouble();
					}
					else if (readerProperty->getPropertyName() == "Orientation") {
						orientation = readerProperty->getPropertyValue().GetInteger();
					}
				}
			}

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcElementBundle*& ifcElementBundle = ifcBundleVector.at(i);

			Ifc4::IfcRepresentationItem::list::ptr ifcTemplatedEntityList(new Ifc4::IfcRepresentationItem::list());

			for (GraphicProperties* graphicProperties : dictionaryProperties.getGraphicPropertiesVector())
			{
				SolidPrimitiveProperty* solidPrimitiveProperty = dynamic_cast<SolidPrimitiveProperty*>(graphicProperties);
				if (solidPrimitiveProperty != nullptr) {
					Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildIfcPrimitive(*solidPrimitiveProperty, file, rotationX, rotationY, rotationZ,orientation);
					if (ifcRepresentationItem != nullptr)
					{
						ifcElementBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(graphicProperties, ifcRepresentationItem));
						//ifcTemplatedEntityList->push(ifcRepresentationItem);
					}
				}
			}
		}
	}

}

Ifc4::IfcGeometricRepresentationItem * IfcPrimitivesEnhancer::buildIfcPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
	double rotationX, double rotationY, double rotationZ, int orientation)
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
		ifcRepresentationItem = buildComplexPrimitive(primitiveGraphicProperties, file,  rotationX,  rotationY,  rotationZ, orientation);
	}

	return ifcRepresentationItem;
	
}

Ifc4::IfcCsgSolid * IfcPrimitivesEnhancer::buildBasicPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = nullptr;

		PrimitiveTypeEnum primitiveTypeEnum = primitiveGraphicProperties.getPrimitiveTypeEnum();
		Ifc4::IfcAxis2Placement3D* placement = IfcOperationsEnhancer::buildIfcAxis2Placement3D(
			primitiveGraphicProperties.getCentroid(), 
			primitiveGraphicProperties.getVectorAxisZ(), 
			primitiveGraphicProperties.getVectorAxisX()
		);

		if (primitiveTypeEnum == PrimitiveTypeEnum::SPHERE) {

			SphereGraphicProperties& sphereGraphicProperties = dynamic_cast<SphereGraphicProperties&>(primitiveGraphicProperties);
			ifcRepresentationItem = new Ifc4::IfcSphere(placement, NumberUtils::convertMicrometersToMetters(sphereGraphicProperties.getRadius()));

		} else if (primitiveTypeEnum == PrimitiveTypeEnum::BOX) {

			BoxGraphicProperties& boxGraphicProperties = dynamic_cast<BoxGraphicProperties&>(primitiveGraphicProperties);

			ifcRepresentationItem = new Ifc4::IfcBlock(placement, NumberUtils::convertMicrometersToMetters(boxGraphicProperties.getLength()),
			NumberUtils::convertMicrometersToMetters(boxGraphicProperties.getWidth()), NumberUtils::convertMicrometersToMetters(boxGraphicProperties.getHeight()));

		} else if (primitiveTypeEnum == PrimitiveTypeEnum::CYLINDER) {
			CylinderGraphicProperties& cylinderGraphicProperties = dynamic_cast<CylinderGraphicProperties&>(primitiveGraphicProperties);

			// the cylinder point of placement is the base origin, not the centroid
			DVec3d cylinderPlacement;
			cylinderPlacement.Init(cylinderGraphicProperties.getBaseOrigin());
			// overwrite the placement value
			placement = IfcOperationsEnhancer::buildIfcAxis2Placement3D(
				cylinderPlacement,
				cylinderGraphicProperties.getVectorAxisZ(),
				cylinderGraphicProperties.getVectorAxisX()
			);

			ifcRepresentationItem = new Ifc4::IfcRightCircularCylinder(placement, NumberUtils::convertMicrometersToMetters(cylinderGraphicProperties.getHeight()),
			NumberUtils::convertMicrometersToMetters(cylinderGraphicProperties.getRadius()));

		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::CONE)
		{
			ConeGraphicProperties& coneGraphicProperties = dynamic_cast<ConeGraphicProperties&>(primitiveGraphicProperties);

			// the cone point of placement is the base origin, not the centroid
			DVec3d conePlacement;
			conePlacement.Init(coneGraphicProperties.getBaseOrigin());
			// overwrite the placement value
			placement = IfcOperationsEnhancer::buildIfcAxis2Placement3D(
				conePlacement,
				coneGraphicProperties.getVectorAxisZ(),
				coneGraphicProperties.getVectorAxisX()
			);

			ifcRepresentationItem = new Ifc4::IfcRightCircularCone(placement, NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getHeight()),
			NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getBaseRadius()));
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
Ifc4::IfcGeometricRepresentationItem * IfcPrimitivesEnhancer::buildComplexPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
	double rotationX, double rotationY, double rotationZ, int orientation)
{
	Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = nullptr;

		PrimitiveTypeEnum primitiveTypeEnum = primitiveGraphicProperties.getPrimitiveTypeEnum();

		if (primitiveTypeEnum == PrimitiveTypeEnum::TORUS)
		{
			TorusGraphicProperties& torusGraphicProperties = dynamic_cast<TorusGraphicProperties&>(primitiveGraphicProperties);
			
			// torus placement is NOT the centroid, but the center of rotation
			DVec3d torusPointPlacement;
			torusPointPlacement.Init(torusGraphicProperties.getCenterPointOfRotation());

			Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0,
				NumberUtils::convertMicrometersToMetters(torusGraphicProperties.getMajorRadius())), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			Ifc4::IfcCircleProfileDef* profileDefinition = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement,
				NumberUtils::convertMicrometersToMetters(torusGraphicProperties.getMinorRadius()));
			Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			// !!! torus placement axes should be provided in the order of Y, Z
			Ifc4::IfcAxis2Placement3D* torusPlacement = IfcOperationsEnhancer::buildIfcAxis2Placement3D(
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

			Ifc4::IfcAxis2Placement3D* bigConePlacement = IfcOperationsEnhancer::buildIfcAxis2Placement3D(
				bigConePlacementVector,
				coneGraphicProperties.getVectorAxisZ(),
				coneGraphicProperties.getVectorAxisX()
			);

			DVec3d smallConePlacementVector;
			smallConePlacementVector.Init(coneGraphicProperties.getTopOrigin());

			Ifc4::IfcAxis2Placement3D* smallConePlacement = IfcOperationsEnhancer::buildIfcAxis2Placement3D(
				smallConePlacementVector,
				coneGraphicProperties.getVectorAxisZ(),
				coneGraphicProperties.getVectorAxisX()
			);

			Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* bigCompleteCone = new Ifc4::IfcRightCircularCone(bigConePlacement,
				NumberUtils::convertMicrometersToMetters((coneGraphicProperties.getHeight() + smallConeHeight)),
				NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getBaseRadius()));

			Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* smallCompleteCone = new Ifc4::IfcRightCircularCone(smallConePlacement,
				NumberUtils::convertMicrometersToMetters(smallConeHeight), NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getTopRadius()));

			ifcRepresentationItem = new Ifc4::IfcBooleanResult(Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE, bigCompleteCone, smallCompleteCone);

		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::ROTATIONAL_SWEEP) {
			RotationalSweepGraphicProperties& rotationalSweepGraphicProperties = dynamic_cast<RotationalSweepGraphicProperties&>(primitiveGraphicProperties);

			IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
			IfcElementBundle* ifcElementBundle = new IfcElementBundle(-1, "");

			// torus placement is NOT the centroid, but the center of rotation
			DVec3d rotationalSweepPlacement;
			rotationalSweepPlacement.x = 0;
			rotationalSweepPlacement.y = 0;
			rotationalSweepPlacement.z = 0;

			DVec3d sweepCenterOfRotation;
			sweepCenterOfRotation.Init(rotationalSweepGraphicProperties.getCenterRotation());

			// adjust global points of the shape/curve related to the global placement of the revolve
			std::vector<DPoint3d> temp;
			std::vector<DPoint3d> points = rotationalSweepGraphicProperties.getShapesGraphicProperties()->getCurvesPrimitivesContainerVector().at(0)->getControlPoints();
			for (auto const c : points) {
				DPoint3d newPoint;

				newPoint.Subtract(c, sweepCenterOfRotation);
				temp.push_back(newPoint);
			}

			rotationalSweepGraphicProperties.getShapesGraphicProperties()->getCurvesPrimitivesContainerVector().at(0)->setControlPoints(temp);
			Ifc4::IfcGeometricRepresentationItem* result = nullptr;
			bool addToIfcElementBundle = false;
			ifcShapesEnhancer->buildGeometricRepresentationShapes(rotationalSweepGraphicProperties.getShapesGraphicProperties(), file, ifcElementBundle, addToIfcElementBundle);
			if (ifcShapesEnhancer->hasSingleShapeItem())
				result = ifcShapesEnhancer->getSingleShapeRepresentation();

			Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryClosedProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, std::string("RotationalSweep"),
				(Ifc4::IfcCurve*) result);

			Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0),
				file.addTriplet<Ifc4::IfcDirection>(rotationalSweepGraphicProperties.getVectorAxisZ().x, rotationalSweepGraphicProperties.getVectorAxisZ().y,
					rotationalSweepGraphicProperties.getVectorAxisZ().z));

			// leave the directions empty
			Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(
				file.addTriplet<Ifc4::IfcCartesianPoint>(NumberUtils::convertMicrometersToMetters(sweepCenterOfRotation.x),
					NumberUtils::convertMicrometersToMetters(sweepCenterOfRotation.y),
					NumberUtils::convertMicrometersToMetters(sweepCenterOfRotation.z )),
				new Ifc4::IfcDirection(std::vector<double>()), new Ifc4::IfcDirection(std::vector<double>()));

			ifcRepresentationItem = new Ifc4::IfcRevolvedAreaSolid(profileDef, placement, localAxis1Placement, rotationalSweepGraphicProperties.getSweepRadians());

		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::EXTRUSION)
		{
			ExtrusionGraphicProperties& extrusionGraphicProperties = dynamic_cast<ExtrusionGraphicProperties&>(primitiveGraphicProperties);
			IfcElementBundle* ifcElementBundle = new IfcElementBundle(-1, "");

			Ifc4::IfcGeometricRepresentationItem* item = nullptr;
			ShapesGraphicProperties* curveShape = extrusionGraphicProperties.getShapesGraphicProperties();
			CurvesBoundaryTypeEnum curveBoundary = curveShape->getBoundaryTypeCurvesContainer();
			
			bool addToIfcElementBundle = false;
			Ifc4::IfcProfileDef* profileDef = nullptr;

			Ifc4::IfcProfileTypeEnum::Value pEnum;
			if (extrusionGraphicProperties.isSolid)
				pEnum = Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA;
			else
				pEnum = Ifc4::IfcProfileTypeEnum::IfcProfileType_CURVE;

			IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
			//Change dimension
			ifcShapesEnhancer->dimension = 2;
			ifcShapesEnhancer->buildGeometricRepresentationShapes(curveShape, file, ifcElementBundle, addToIfcElementBundle);
			
			if (curveBoundary != CurvesBoundaryTypeEnum::PARITY_REGION && curveBoundary != CurvesBoundaryTypeEnum::UNION_REGION)
			{
				item = ifcShapesEnhancer->getSingleShapeRepresentation();
				
				if (curveShape->getIsClosed())
				{
					Ifc4::IfcCurve* curveToExtrude = (Ifc4::IfcCurve*)item;
					profileDef = new Ifc4::IfcArbitraryClosedProfileDef(
						pEnum,
						std::string("Closed Profile"),
						curveToExtrude
					);
				}
				else 
				{
					Ifc4::IfcBoundedCurve* curveToExtrude = (Ifc4::IfcBoundedCurve*)item;
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
			
			Ifc4::IfcAxis2Placement3D* place = IfcOperationsEnhancer::buildIfcAxis2Placement3D(
				extrusionGraphicProperties.getCentroid(),
				extrusionGraphicProperties.getVectorAxisZ(),
				extrusionGraphicProperties.getVectorAxisX()
			);


			if (extrusionGraphicProperties.isSolid)
			{
				Ifc4::IfcExtrudedAreaSolid* extrusionitem = new Ifc4::IfcExtrudedAreaSolid(
					profileDef,
					file.addPlacement3d(),
					//place,
					IfcOperationsEnhancer::buildIfcDirection3DfromDirectionVec3D(extrusionGraphicProperties.directionExtrusion),
					NumberUtils::convertMicrometersToMetters(extrusionGraphicProperties.directionExtrusion.Magnitude())
				);

				ifcRepresentationItem = extrusionitem;
			}
			else
			{
				Ifc4::IfcSurfaceOfLinearExtrusion* surfaceExtrusion = new Ifc4::IfcSurfaceOfLinearExtrusion(
					profileDef,
					file.addPlacement3d(),
					//place,
					IfcOperationsEnhancer::buildIfcDirection3DfromDirectionVec3D(extrusionGraphicProperties.directionExtrusion),
					NumberUtils::convertMicrometersToMetters(extrusionGraphicProperties.directionExtrusion.Magnitude())
				);

				ifcRepresentationItem = surfaceExtrusion;
			}
		}


	return ifcRepresentationItem;
}
#pragma warning( pop )

