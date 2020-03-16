#include "../headers/IfcPrimitivesBuilder.h"



Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildIfcPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveType, GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file)
{


	Ifc4::IfcRepresentationItem* ifcRepresentationItem = nullptr;
	if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE || primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX ||
		primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE || primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER)
	{
		ifcRepresentationItem = buildBasicPrimitive(primitiveType, graphicProperties, file);
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS || primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::TRUNCATED_CONE)
	{
		ifcRepresentationItem = buildComplexPrimitive(primitiveType,graphicProperties, file);
	}
	// crashed here
	return ifcRepresentationItem;
	
}

Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildBasicPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum, GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcRepresentationItem* ifcRepresentationItem = nullptr;

	if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE) {

		SphereGraphicProperties sphereGraphicProperties;
		if (graphicProperties.tryGetSphereGraphicProperties(sphereGraphicProperties)) {

			Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(graphicProperties, file, graphicProperties.getCentroid(), graphicProperties.getVectorAxisZ(), graphicProperties.getVectorAxisX());
			ifcRepresentationItem = new Ifc4::IfcSphere(place, NumberUtils::convertMicrometersToMetters(sphereGraphicProperties.getRadius()));
		}
		else
		{
			// TODO log sphere properties not found
		}
	}
	else if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX) 
	{
		SlabGraphicProperties slabGraphicProperties;
		if (graphicProperties.tryGetSlabProperties(slabGraphicProperties)) {
			Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(graphicProperties, file, graphicProperties.getCentroid(), graphicProperties.getVectorAxisZ(),
				graphicProperties.getVectorAxisX());
			ifcRepresentationItem = new Ifc4::IfcBlock(place, NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getLength()), 
				NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getWidth()), NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getHeight()));
		}
		else {
			// TODO log slab properties not found
		}

	}
	else if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) 
	{
		CylinderGraphicProperties cylinderGraphicProperties;
		if (graphicProperties.tryGetCylinderGraphicProperties(cylinderGraphicProperties)) {
			Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(graphicProperties, file, graphicProperties.getCentroid(), 
				graphicProperties.getVectorAxisZ(), graphicProperties.getVectorAxisX());
			ifcRepresentationItem = new Ifc4::IfcRightCircularCylinder(place, NumberUtils::convertMicrometersToMetters(cylinderGraphicProperties.getHeight()),
				NumberUtils::convertMicrometersToMetters(cylinderGraphicProperties.getRadius()));
		}
		else {
			// TODO log cylinder properties not found
		}
	}
	else if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE) 
	{
		ConeGraphicProperties coneGraphicProperties;
		if (graphicProperties.tryGetConeGraphicProperties(coneGraphicProperties)) {

			// the cone point of placement is the base origin, not the centroid
			DVec3d* conePlacement = new DVec3d();
			conePlacement->x = coneGraphicProperties.getBaseOrigin().x;
			conePlacement->y = coneGraphicProperties.getBaseOrigin().y;
			conePlacement->z = coneGraphicProperties.getBaseOrigin().z;

			Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(graphicProperties, file, *conePlacement, graphicProperties.getVectorAxisZ(), 
				graphicProperties.getVectorAxisX());
			ifcRepresentationItem = new Ifc4::IfcRightCircularCone(place, NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getHeight()),
				NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getBaseRadius()));
		}
		else {
			// TODO log cone properties not found
		}

	}

	if (ifcRepresentationItem != nullptr) {
		Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(ifcRepresentationItem);
		file.addEntity(ifcRepresentationItem);
		return solid;

	}
	return nullptr;
}

Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildComplexPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum, GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcRepresentationItem* ifcRepresentationItem = nullptr;


	if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS) 
	{

		TorusGraphicProperties torusGraphicProperties;
		if (graphicProperties.tryGetTorusGraphicProperties(torusGraphicProperties))
		{
			Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0, 
				NumberUtils::convertMicrometersToMetters(torusGraphicProperties.getMajorRadius())), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			Ifc4::IfcCircleProfileDef* profileDef = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement, 
				NumberUtils::convertMicrometersToMetters(torusGraphicProperties.getMinorRadius()));
			Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			// !!! torus placement axes should be provided in the order of X,Z
			Ifc4::IfcAxis2Placement3D* torusPlacement = buildIfcAxis2Placement3D(graphicProperties, file, graphicProperties.getCentroid(),
				graphicProperties.getVectorAxisX(), graphicProperties.getVectorAxisZ());
			ifcRepresentationItem = new Ifc4::IfcRevolvedAreaSolid(profileDef, torusPlacement, localAxis1Placement, torusGraphicProperties.getSweepRadians());
		}
		else
		{
			// TODO log sphere properties not found
		}
	}
	else if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::TRUNCATED_CONE) 
	{
		ConeGraphicProperties coneGraphicProperties;
		if (graphicProperties.tryGetConeGraphicProperties(coneGraphicProperties)) 
		{


			double similarityRatio = coneGraphicProperties.getTopRadius() / coneGraphicProperties.getBaseRadius();
			double smallConeHeight = (similarityRatio*coneGraphicProperties.getHeight()) / (1 - similarityRatio);

			// !!! overrite the place for cone, as the cone is positioned in the space not based on the centroid, but the base origin
			DVec3d* bigConePlacementVector = new DVec3d();
			bigConePlacementVector->x = coneGraphicProperties.getBaseOrigin().x;
			bigConePlacementVector->y = coneGraphicProperties.getBaseOrigin().y;
			bigConePlacementVector->z = coneGraphicProperties.getBaseOrigin().z;

			Ifc4::IfcAxis2Placement3D* bigConePlacement = buildIfcAxis2Placement3D(graphicProperties, file, *bigConePlacementVector, graphicProperties.getVectorAxisZ(), 
				graphicProperties.getVectorAxisX());

			DVec3d* smallConePlacementVector = new DVec3d();
			smallConePlacementVector->x = coneGraphicProperties.getTopOrigin().x;
			smallConePlacementVector->y = coneGraphicProperties.getTopOrigin().y;
			smallConePlacementVector->z = coneGraphicProperties.getTopOrigin().z;
			Ifc4::IfcAxis2Placement3D* smallConePlacement = buildIfcAxis2Placement3D(graphicProperties, file, *smallConePlacementVector, graphicProperties.getVectorAxisZ(), 
				graphicProperties.getVectorAxisX());

			Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* bigCompleteCone = new Ifc4::IfcRightCircularCone(bigConePlacement, 
				NumberUtils::convertMicrometersToMetters((coneGraphicProperties.getHeight() + smallConeHeight)), 
				NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getBaseRadius()));

			Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* smallCompleteCone = new Ifc4::IfcRightCircularCone(smallConePlacement, 
				NumberUtils::convertMicrometersToMetters(smallConeHeight), NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getTopRadius()));

			file.addEntity(bigCompleteCone);
			file.addEntity(smallCompleteCone);

			ifcRepresentationItem = new Ifc4::IfcBooleanResult(Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE, bigCompleteCone, smallCompleteCone);
		}
		else {
			// TODO log cone properties not found
		}
	}

	if (ifcRepresentationItem != nullptr) {
		file.addEntity(ifcRepresentationItem);

	}

	return ifcRepresentationItem;
}

Ifc4::IfcAxis2Placement3D * IfcPrimitivesBuilder::buildIfcAxis2Placement3D(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file, 
	DVec3d pointOfPlacement, DVec3d axe1, DVec3d axe2)
{
	double centroid_x = NumberUtils::convertMicrometersToMetters(pointOfPlacement.x);
	double centroid_y = NumberUtils::convertMicrometersToMetters(pointOfPlacement.y);
	double centroid_z = NumberUtils::convertMicrometersToMetters(pointOfPlacement.z);

	double z_axis_x = axe1.x;
	double z_axis_y = axe1.y;
	double z_axis_z = axe1.z;

	double x_axis_x = axe2.x;
	double x_axis_y = axe2.y;
	double x_axis_z = axe2.z;


	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
		file.addTriplet<Ifc4::IfcCartesianPoint>(centroid_x, centroid_y, centroid_z),
		file.addTriplet<Ifc4::IfcDirection>(z_axis_x, z_axis_y, z_axis_z),
		file.addTriplet<Ifc4::IfcDirection>(x_axis_x, x_axis_y, x_axis_z)
	);
	return place;
}
