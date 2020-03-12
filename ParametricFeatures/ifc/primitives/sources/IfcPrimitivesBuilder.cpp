#include "../headers/IfcPrimitivesBuilder.h"



Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildIfcPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveType, GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file)
{

	Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(graphicProperties, file);

	Ifc4::IfcRepresentationItem* item = nullptr;
	if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE || primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX ||
		primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE || primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER)
	{
		item = buildBasicPrimitive(primitiveType, graphicProperties, place, file);
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS || primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::TRUNCATED_CONE)
	{
		item = buildComplexPrimitive(primitiveType,graphicProperties, place, file);
	}
	
	return item;
	
}

Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildBasicPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum, GraphicProperties& graphicProperties, Ifc4::IfcAxis2Placement3D * place, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE) {

		SphereGraphicProperties sphereGraphicProperties;
		if (graphicProperties.tryGetSphereGraphicProperties(sphereGraphicProperties)) {
			my = new Ifc4::IfcSphere(place, sphereGraphicProperties.getRadius() / 1000000);
		}
		else
		{
			// TODO log sphere properties not found
		}
	}
	else if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX) {
		/*my = new Ifc4::IfcBlock(place, a, b, c);*/
		SlabGraphicProperties slabGraphicProperties;
		if (graphicProperties.tryGetSlabProperties(slabGraphicProperties)) {
			my = new Ifc4::IfcBlock(place, slabGraphicProperties.getLength() / 1000000, slabGraphicProperties.getWidth() / 1000000, slabGraphicProperties.getHeight() / 1000000);
		}
		else {
			// TODO log slab properties not found
		}

	}
	//else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::PYRAMID) {
	//	my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
	//}
	else if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) {
		CylinderGraphicProperties cylinderGraphicProperties;
		if (graphicProperties.tryGetCylinderGraphicProperties(cylinderGraphicProperties)) {
			my = new Ifc4::IfcRightCircularCylinder(place, cylinderGraphicProperties.getHeight() / 1000000, cylinderGraphicProperties.getRadius() / 1000000);
		}
		else {
			// TODO log cylinder properties not found
		}
	}
	else if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE) {
		ConeGraphicProperties coneGraphicProperties;
		if (graphicProperties.tryGetConeGraphicProperties(coneGraphicProperties)) {
			/*my = new Ifc4::IfcRightCircularCone(place, dictionaryProperties.getGraphicProperties()->getHeight() / 100, dictionaryProperties.getGraphicProperties()->getRadius() / 100);*/
			my = new Ifc4::IfcRightCircularCone(place, coneGraphicProperties.getHeight() / 1000000, coneGraphicProperties.getBaseRadius() / 1000000);
		}
		else {
			// TODO log cone properties not found
		}

	}

	if (my != nullptr) {
		Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(my);
		file.addEntity(my);
		return solid;

	}
	return nullptr;
}

Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildComplexPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum, GraphicProperties& graphicProperties, Ifc4::IfcAxis2Placement3D * place, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;


	if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS) {

		TorusGraphicProperties torusGraphicProperties;
		if (graphicProperties.tryGetTorusGraphicProperties(torusGraphicProperties))
		{
			Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0, torusGraphicProperties.getMajorRadius() / 1000000),
				file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			Ifc4::IfcCircleProfileDef* profileDef = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement, torusGraphicProperties.getMinorRadius() / 1000000);
			Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			my = new Ifc4::IfcRevolvedAreaSolid(profileDef, place, localAxis1Placement, torusGraphicProperties.getSweepRadians());
		}
		else
		{
			// TODO log sphere properties not found
		}
	}
	else if (primitiveTypeEnum == PrimitiveTypeEnum::PrimitiveTypeEnum::TRUNCATED_CONE) {
		ConeGraphicProperties coneGraphicProperties;
		if (graphicProperties.tryGetConeGraphicProperties(coneGraphicProperties)) {


			double similarityRatio = coneGraphicProperties.getTopRadius() / coneGraphicProperties.getBaseRadius();
			double smallConeHeight = (similarityRatio*coneGraphicProperties.getHeight()) / (1 - similarityRatio);

			// !!! overrite the place for cone, as the cone is positioned in the space not based on the centroid, but the origin
			Ifc4::IfcAxis2Placement3D* bigConePlacement = new Ifc4::IfcAxis2Placement3D(
				file.addTriplet<Ifc4::IfcCartesianPoint>(coneGraphicProperties.getBaseOrigin().x / 1000000, coneGraphicProperties.getBaseOrigin().y / 1000000, coneGraphicProperties.getBaseOrigin().z / 1000000),
				file.addTriplet<Ifc4::IfcDirection>(graphicProperties.getVectorAxisZ().x, graphicProperties.getVectorAxisZ().y, graphicProperties.getVectorAxisZ().z),
				file.addTriplet<Ifc4::IfcDirection>(graphicProperties.getVectorAxisX().x, graphicProperties.getVectorAxisX().y, graphicProperties.getVectorAxisX().z)
			);

			Ifc4::IfcAxis2Placement3D* smallConePlacement = new Ifc4::IfcAxis2Placement3D(
				file.addTriplet<Ifc4::IfcCartesianPoint>(coneGraphicProperties.getTopOrigin().x / 1000000, coneGraphicProperties.getTopOrigin().y / 1000000, coneGraphicProperties.getTopOrigin().z / 1000000),
				file.addTriplet<Ifc4::IfcDirection>(graphicProperties.getVectorAxisZ().x, graphicProperties.getVectorAxisZ().y, graphicProperties.getVectorAxisZ().z),
				file.addTriplet<Ifc4::IfcDirection>(graphicProperties.getVectorAxisX().x, graphicProperties.getVectorAxisX().y, graphicProperties.getVectorAxisX().z)
			);

			Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* bigCompleteCone = new Ifc4::IfcRightCircularCone(bigConePlacement, (coneGraphicProperties.getHeight() + smallConeHeight) / 1000000, coneGraphicProperties.getBaseRadius() / 1000000);
			Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* smallCompleteCone = new Ifc4::IfcRightCircularCone(smallConePlacement, smallConeHeight / 1000000, coneGraphicProperties.getTopRadius() / 1000000);

			file.addEntity(bigCompleteCone);
			file.addEntity(smallCompleteCone);

			my = new Ifc4::IfcBooleanResult(Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE, bigCompleteCone, smallCompleteCone);
		}
		else {
			// TODO log cone properties not found
		}
	}

	if (my != nullptr) {
		file.addEntity(my);

	}

	return my;
}

Ifc4::IfcAxis2Placement3D * IfcPrimitivesBuilder::buildIfcAxis2Placement3D(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file)
{
	double centroid_x = graphicProperties.getCentroid().x / 1000000;
	double centroid_y = graphicProperties.getCentroid().y / 1000000;
	double centroid_z = graphicProperties.getCentroid().z / 1000000;

	double z_axis_x = graphicProperties.getVectorAxisZ().x;
	double z_axis_y = graphicProperties.getVectorAxisZ().y;
	double z_axis_z = graphicProperties.getVectorAxisZ().z;

	double x_axis_x = graphicProperties.getVectorAxisX().x;
	double x_axis_y = graphicProperties.getVectorAxisX().y;
	double x_axis_z = graphicProperties.getVectorAxisX().z;


	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
		file.addTriplet<Ifc4::IfcCartesianPoint>(centroid_x, centroid_y, centroid_z),
		file.addTriplet<Ifc4::IfcDirection>(z_axis_x, z_axis_y, z_axis_z),
		file.addTriplet<Ifc4::IfcDirection>(x_axis_x, x_axis_y, x_axis_z)
	);
	return place;
}
