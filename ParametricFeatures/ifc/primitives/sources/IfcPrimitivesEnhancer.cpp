#include "../headers/IfcPrimitivesEnhancer.h"


void IfcPrimitivesEnhancer::enhanceIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	std::vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcBundle*& ifcBundle = ifcBundleVector.at(i);

			Ifc4::IfcRepresentationItem::list::ptr ifcTemplatedEntityList(new Ifc4::IfcRepresentationItem::list());

			for (GraphicProperties* graphicProperties : dictionaryProperties.getGraphicPropertiesVector())
			{
				SolidPrimitiveProperty* solidPrimitiveProperty = dynamic_cast<SolidPrimitiveProperty*>(graphicProperties);
				if (solidPrimitiveProperty != nullptr) {
					Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildIfcPrimitive(*solidPrimitiveProperty, file);
					if (ifcRepresentationItem != nullptr)
					{
						ifcBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(graphicProperties, ifcRepresentationItem));
						ifcTemplatedEntityList->push(ifcRepresentationItem);
					}
				}
			}
		}
	}

}

Ifc4::IfcGeometricRepresentationItem * IfcPrimitivesEnhancer::buildIfcPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = nullptr;

	PrimitiveTypeEnum primitiveType = primitiveGraphicProperties.getPrimitiveTypeEnum();
	if (primitiveType == PrimitiveTypeEnum::SPHERE || primitiveType == PrimitiveTypeEnum::BOX ||
			primitiveType == PrimitiveTypeEnum::CONE || primitiveType == PrimitiveTypeEnum::CYLINDER)
	{
		ifcRepresentationItem = buildBasicPrimitive(primitiveGraphicProperties, file);
	}
	else if (primitiveType == PrimitiveTypeEnum::TORUS || primitiveType == PrimitiveTypeEnum::TRUNCATED_CONE)
	{
		ifcRepresentationItem = buildComplexPrimitive(primitiveGraphicProperties, file);
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

Ifc4::IfcGeometricRepresentationItem * IfcPrimitivesEnhancer::buildComplexPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file)
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
		} else if (primitiveTypeEnum == PrimitiveTypeEnum::TRUNCATED_CONE) {

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


	return ifcRepresentationItem;
}

