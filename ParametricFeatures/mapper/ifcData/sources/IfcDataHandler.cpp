#include "../headers/IfcDataHandler.h"


IfcDataHandler::IfcDataHandler(std::vector<DictionaryProperties*> dictProps, SmartFeatureContainer* smartContainer) :
	dictionaryProperties(dictProps), smartFeatContainer(smartContainer)
{
	typedef Ifc4::IfcGloballyUniqueId guid;
	this->file = new IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));

	std::string name = "PrimitiveTest";
	//std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";
	std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";

	Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
	Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);
	
	IfcEntityList* entityList = new IfcEntityList();
	entityList->push(ifcUnitLength);
	entityList->push(ifcUnitAngle);
	boost::shared_ptr<IfcEntityList> unitEntity(entityList);
	
	Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);

	Ifc4::IfcProject* project = new Ifc4::IfcProject(
		guid::IfcGloballyUniqueId(name), file->getSingle<Ifc4::IfcOwnerHistory>(),
		std::string("Project"), 
		boost::none, 
		boost::none, 
		boost::none, 
		boost::none, 
		boost::none, 
		unitAssigment
	);

	file->addEntity(project);


	Ifc4::IfcBuildingElementProxy* elementProxy = new Ifc4::IfcBuildingElementProxy(
		guid::IfcGloballyUniqueId("Primitives"),
		0,
		std::string("Primitives"),
		boost::none,
		boost::none,
		0,
		0,
		boost::none,
		boost::none
	);

	file->addBuildingProduct(elementProxy);

	elementProxy->setOwnerHistory(file->getSingle<Ifc4::IfcOwnerHistory>());
	elementProxy->setObjectPlacement(file->addLocalPlacement());

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* representationItem = nullptr;

	if (smartFeatContainer->getRoot() != nullptr) 
	{
		representationItem = PrimitivesMapperSwitch(*smartFeatContainer->getRoot());

		Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(representationItem);
		items->push(solid);
	};

	if (!dictionaryProperties.empty()) 
	{
		for (int i = 0; i < dictionaryProperties.size(); i++)
		{
			representationItem = PrimitivesMapperSwitch(*dictionaryProperties.at(i));

			Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(representationItem);
			items->push(solid);
		}
	}

	Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
		file->getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body"), std::string("Model"), items);

	reps->push(rep);
	file->addEntity(rep);

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);
	file->addEntity(shape);
	elementProxy->setRepresentation(shape);
	
	std::ofstream f;
	f.open(filename);
	f << *file;
	f.close();
}

Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* IfcDataHandler::PrimitivesMapperSwitch(SmartFeatureTreeNode& treeNode)
{
	Ifc4::IfcBooleanOperator::Value ifcOperatorBool;
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	if (treeNode.getReaderProperties()->getBooleanFunction() != BooleanFunctions::BooleanFunctionsEnum::UNDEFINED)
	{
		BooleanFunctions::BooleanFunctionsEnum currentBooleanOperation = treeNode.getReaderProperties()->getBooleanFunction();

		if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::UNION) {
			ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION;
		}
		else if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::DIFFERENCE) {
			ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE;
		}
		else if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::INTERSECTION) {
			ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_INTERSECTION;
		}

		my = new Ifc4::IfcBooleanResult(ifcOperatorBool, PrimitivesMapperSwitch(*treeNode.getLeftNode()), PrimitivesMapperSwitch(*treeNode.getRightNode()));

	}
	else
	{
		GraphicProperties* graphicProperties = treeNode.getGraphicProperties();
		PrimitiveTypeEnum::PrimitiveTypeEnum primitiveType = treeNode.getGeneralProperties()->getPrimitiveTypeEnum();
		my = PrimitivesSolver(primitiveType, graphicProperties);
	}


	file->addEntity(my);

	return my;
}

Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem * IfcDataHandler::PrimitivesMapperSwitch(DictionaryProperties& dictionaryProp)
{
	GraphicProperties* graphicProperties = dictionaryProp.getGraphicProperties();
	PrimitiveTypeEnum::PrimitiveTypeEnum primitiveType = dictionaryProp.getGeneralProperties()->getPrimitiveTypeEnum();
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = PrimitivesSolver(primitiveType, graphicProperties);

	file->addEntity(my);

	return my;
}

inline Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* IfcDataHandler::PrimitivesSolver(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveType, GraphicProperties* graphicProperties)
{
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	double a = 50, b = 50, c = 50;
	DVec3d objectOrigin = graphicProperties->getCentroid() / 1000000;
	DVec3d vectorBaseX = graphicProperties->getVectorAxisX();

	DVec3d vectorBaseZ = graphicProperties->getVectorAxisZ();

	vectorBaseX.Normalize();
	vectorBaseZ.Normalize();

	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
		file->addTriplet<Ifc4::IfcCartesianPoint>(objectOrigin.x, objectOrigin.y, objectOrigin.z),
		file->addTriplet<Ifc4::IfcDirection>(vectorBaseZ.x, vectorBaseZ.y, vectorBaseZ.z),
		file->addTriplet<Ifc4::IfcDirection>(vectorBaseX.x, vectorBaseX.y, vectorBaseX.z)
	);

	if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE) {
		SphereGraphicProperties sphereGraphicProperties;
		if (graphicProperties->tryGetSphereGraphicProperties(sphereGraphicProperties)) {
			my = new Ifc4::IfcSphere(place, NumberUtils::convertMicrometersToMetters(sphereGraphicProperties.getRadius()));
		}
		else
		{
			// TODO log sphere properties not found
		}
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX) {
		SlabGraphicProperties slabGraphicProperties;
		if (graphicProperties->tryGetSlabProperties(slabGraphicProperties)) {
			my = new Ifc4::IfcBlock(place, NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getLength()), NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getWidth()),
				NumberUtils::convertMicrometersToMetters(slabGraphicProperties.getHeight()));
		}
		else {
			// TODO log slab properties not found
		}
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::PYRAMID) {
		my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) {
		CylinderGraphicProperties cylinderGraphicProperties;
		if (graphicProperties->tryGetCylinderGraphicProperties(cylinderGraphicProperties)) {
			my = new Ifc4::IfcRightCircularCylinder(place, NumberUtils::convertMicrometersToMetters(cylinderGraphicProperties.getHeight()), NumberUtils::convertMicrometersToMetters(cylinderGraphicProperties.getRadius()));
		}
		else {
			// TODO log cylinder properties not found
		}
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE) {
		ConeGraphicProperties coneGraphicProperties;
		if (graphicProperties->tryGetConeGraphicProperties(coneGraphicProperties)) {
			my = new Ifc4::IfcRightCircularCone(place, NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getHeight()), NumberUtils::convertMicrometersToMetters(coneGraphicProperties.getBaseRadius()));
		}
		else {
			// TODO log cone properties not found
		}
	}

	return my;
}
