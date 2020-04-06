#include "../headers/IfcPrimitivesBuilder.h"


std::vector<Ifc4::IfcRepresentation*> IfcPrimitivesBuilder::buildIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, IfcHierarchyHelper<Ifc4>& file)
{
	std::vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;

	// create simple primitives, which are not a smartfeature
	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			IfcTemplatedEntityList<Ifc4::IfcRepresentationItem>* ifcTemplatedEntityList = new IfcTemplatedEntityList<Ifc4::IfcRepresentationItem>();

			for (auto const& primitivePropertiesValue : dictionaryProperties.getGraphicProperties()->getPrimitiveGraphicPropertiesVector())
			{
				Ifc4::IfcRepresentationItem* ifcRepresentationItem = buildIfcPrimitive(*primitivePropertiesValue, dictionaryProperties.getReaderProperties()->getReaderPropertyBundleVector(), file);


				if (ifcRepresentationItem != nullptr) 
				{
					ifcTemplatedEntityList->push(ifcRepresentationItem);

					//ifcRepresentationItemVector.push_back(ifcRepresentationItem);
					/*file.addBuildingProduct(ifcBuildingElementProxy);*/
					//Ifc4::IfcRepresentationItem* ceva  = new Ifc4::IfcBooleanResult(Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION, ifcBuildingElementProxy, pipe);


				}
			}

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentationItem>> sharedIfcTemplatedEntityList(ifcTemplatedEntityList);
			Ifc4::IfcRepresentation* ifcRepresentation = new Ifc4::IfcRepresentation(file.getSingle<Ifc4::IfcRepresentationContext>(), std::string("ceva"), std::string("ceva"), sharedIfcTemplatedEntityList);
			ifcRepresentationVector.push_back(ifcRepresentation);
		}
	}

	return ifcRepresentationVector;
}

Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildIfcPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties, std::vector<ReaderPropertyBundle*> readerPropertiesVector,
	IfcHierarchyHelper<Ifc4>& file)
{
	//std::string name = "PrimitiveTest";
	//typedef Ifc4::IfcGloballyUniqueId guid;
	//Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(guid::IfcGloballyUniqueId(name),0,name,boost::none,boost::none,0,0,boost::none,boost::none);
	//primitive->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());
	//primitive->setObjectPlacement(file.addLocalPlacement());

	Ifc4::IfcRepresentationItem* ifcRepresentationItem = nullptr;
	//Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	//Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

	PrimitiveTypeEnum primitiveType = primitiveGraphicProperties.getPrimitiveTypeEnum();
	if (primitiveType == PrimitiveTypeEnum::SPHERE || primitiveType == PrimitiveTypeEnum::BOX ||
			primitiveType == PrimitiveTypeEnum::CONE || primitiveType == PrimitiveTypeEnum::CYLINDER)
	{
		ifcRepresentationItem = buildBasicPrimitive(primitiveGraphicProperties, readerPropertiesVector, file);
	}
	else if (primitiveType == PrimitiveTypeEnum::TORUS || primitiveType == PrimitiveTypeEnum::TRUNCATED_CONE)
	{
		ifcRepresentationItem = buildComplexPrimitive(primitiveGraphicProperties, file);
	}

	//if (ifcRepresentationItem != nullptr) 
	//{
	//	items->push(ifcRepresentationItem);
	//}

	//Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body"), std::string("Model"), items);

	//reps->push(rep);
	//file.addEntity(rep);

	//Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);

	//file.addEntity(shape);

	//primitive->setRepresentation(shape);

	return ifcRepresentationItem;
	
}

Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildBasicPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties, std::vector<ReaderPropertyBundle*> readerPropertiesVector,
	IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcRepresentationItem* ifcRepresentationItem = nullptr;

		PrimitiveTypeEnum primitiveTypeEnum = primitiveGraphicProperties.getPrimitiveTypeEnum();

		if (primitiveTypeEnum == PrimitiveTypeEnum::SPHERE) {

			SphereGraphicProperties sphereGraphicProperties;
			if (primitiveGraphicProperties.tryGetSphereGraphicProperties(sphereGraphicProperties)) {

				Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(primitiveGraphicProperties, file, primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getCentroid(),
					primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisZ(), primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisX());
				ifcRepresentationItem = new Ifc4::IfcSphere(place, NumberUtils::convertMicrometersToMetters(sphereGraphicProperties.getRadius()));
			}
			else
			{
				// TODO log sphere properties not found
			}
		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::BOX)
		{
			SlabGraphicProperties slabGraphicProperties;
			if (primitiveGraphicProperties.tryGetSlabProperties(slabGraphicProperties)) {
				Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(primitiveGraphicProperties, file, primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getCentroid(),
					primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisZ(), primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisX());
				ifcRepresentationItem = new Ifc4::IfcBlock(place, NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getLength()),
					NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getWidth()), NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getHeight()));
			}
			else {
				// TODO log slab properties not found
			}

		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::CYLINDER)
		{
			CylinderGraphicProperties cylinderGraphicProperties;
			if (primitiveGraphicProperties.tryGetCylinderGraphicProperties(cylinderGraphicProperties))
			{
				// the cylinder point of placement is the base origin, not the centroid
				DVec3d* cylinderPlacement = new DVec3d();
				cylinderPlacement->x = cylinderGraphicProperties.getBaseOrigin().x;
				cylinderPlacement->y = cylinderGraphicProperties.getBaseOrigin().y;
				cylinderPlacement->z = cylinderGraphicProperties.getBaseOrigin().z;

				Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(primitiveGraphicProperties, file, *cylinderPlacement,
					primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisZ(), primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisX());
				ifcRepresentationItem = new Ifc4::IfcRightCircularCylinder(place, NumberUtils::convertMicrometersToMetters(cylinderGraphicProperties.getHeight()),
					NumberUtils::convertMicrometersToMetters(cylinderGraphicProperties.getRadius()));
			}
			else {
				// TODO log cylinder properties not found
			}
		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::CONE)
		{
			ConeGraphicProperties coneGraphicProperties;
			if (primitiveGraphicProperties.tryGetConeGraphicProperties(coneGraphicProperties))
			{

				// the cone point of placement is the base origin, not the centroid
				DVec3d* conePlacement = new DVec3d();
				conePlacement->x = coneGraphicProperties.getBaseOrigin().x;
				conePlacement->y = coneGraphicProperties.getBaseOrigin().y;
				conePlacement->z = coneGraphicProperties.getBaseOrigin().z;

				Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(primitiveGraphicProperties, file, *conePlacement, primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisZ(),
					primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisX());
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

Ifc4::IfcRepresentationItem * IfcPrimitivesBuilder::buildComplexPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcRepresentationItem* ifcRepresentationItem = nullptr;

		PrimitiveTypeEnum primitiveTypeEnum = primitiveGraphicProperties.getPrimitiveTypeEnum();

		if (primitiveTypeEnum == PrimitiveTypeEnum::TORUS)
		{

			TorusGraphicProperties torusGraphicProperties;
			if (primitiveGraphicProperties.tryGetTorusGraphicProperties(torusGraphicProperties))
			{
				// the cone point of placement is the base origin, not the centroid
				DVec3d* torusPointPlacement = new DVec3d();
				torusPointPlacement->x = torusGraphicProperties.getCenterPointOfRotation().x;
				torusPointPlacement->y = torusGraphicProperties.getCenterPointOfRotation().y;
				torusPointPlacement->z = torusGraphicProperties.getCenterPointOfRotation().z;

				Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0,
					NumberUtils::convertMicrometersToMetters(torusGraphicProperties.getMajorRadius())), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

				Ifc4::IfcCircleProfileDef* profileDef = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement,
					NumberUtils::convertMicrometersToMetters(torusGraphicProperties.getMinorRadius()));
				Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

				// !!! torus placement axes should be provided in the order of Z,Y
				Ifc4::IfcAxis2Placement3D* torusPlacement = buildIfcAxis2Placement3D(primitiveGraphicProperties, file, *torusPointPlacement,
					primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisY(), primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisZ());
				ifcRepresentationItem = new Ifc4::IfcRevolvedAreaSolid(profileDef, torusPlacement, localAxis1Placement, torusGraphicProperties.getSweepRadians());
			}
			else
			{
				// TODO log sphere properties not found
			}
		}
		else if (primitiveTypeEnum == PrimitiveTypeEnum::TRUNCATED_CONE)
		{
			ConeGraphicProperties coneGraphicProperties;
			if (primitiveGraphicProperties.tryGetConeGraphicProperties(coneGraphicProperties))
			{


				double similarityRatio = coneGraphicProperties.getTopRadius() / coneGraphicProperties.getBaseRadius();
				double smallConeHeight = (similarityRatio*coneGraphicProperties.getHeight()) / (1 - similarityRatio);

				// !!! overrite the place for cone, as the cone is positioned in the space not based on the centroid, but the base origin
				DVec3d* bigConePlacementVector = new DVec3d();
				bigConePlacementVector->x = coneGraphicProperties.getBaseOrigin().x;
				bigConePlacementVector->y = coneGraphicProperties.getBaseOrigin().y;
				bigConePlacementVector->z = coneGraphicProperties.getBaseOrigin().z;

				Ifc4::IfcAxis2Placement3D* bigConePlacement = buildIfcAxis2Placement3D(primitiveGraphicProperties, file, *bigConePlacementVector, primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisZ(),
					primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisX());

				DVec3d* smallConePlacementVector = new DVec3d();
				smallConePlacementVector->x = coneGraphicProperties.getTopOrigin().x;
				smallConePlacementVector->y = coneGraphicProperties.getTopOrigin().y;
				smallConePlacementVector->z = coneGraphicProperties.getTopOrigin().z;
				Ifc4::IfcAxis2Placement3D* smallConePlacement = buildIfcAxis2Placement3D(primitiveGraphicProperties, file, *smallConePlacementVector, primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisZ(),
					primitiveGraphicProperties.getPrimitiveCommonGraphicProperties().getVectorAxisX());

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
	

	if (ifcRepresentationItem != nullptr) 
	{
		file.addEntity(ifcRepresentationItem);
	}

	return ifcRepresentationItem;
}

Ifc4::IfcAxis2Placement3D * IfcPrimitivesBuilder::buildIfcAxis2Placement3D(PrimitiveGraphicProperties& primitiveGraphicProperties,IfcHierarchyHelper<Ifc4>& file,
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
