#include "../headers/ParametricFeatures.h"

#ifndef Private
#define Private
#endif


typedef std::string S;
boost::none_t const null = boost::none;
using boost::any_cast;


Ifc4::IfcAxis2Placement3D* buildIfcAxis2Placement3D(DictionaryProperties& dictionaryProperties, IfcHierarchyHelper<Ifc4>& file) {

	double centroid_x = dictionaryProperties.getGraphicProperties()->getCentroid().x / 1000000;
	double centroid_y = dictionaryProperties.getGraphicProperties()->getCentroid().y / 1000000;
	double centroid_z = dictionaryProperties.getGraphicProperties()->getCentroid().z / 1000000;

	double z_axis_x = dictionaryProperties.getGraphicProperties()->getVectorAxisZ().x;
	double z_axis_y = dictionaryProperties.getGraphicProperties()->getVectorAxisZ().y;
	double z_axis_z = dictionaryProperties.getGraphicProperties()->getVectorAxisZ().z;

	double x_axis_x = dictionaryProperties.getGraphicProperties()->getVectorAxisX().x;
	double x_axis_y = dictionaryProperties.getGraphicProperties()->getVectorAxisX().y;
	double x_axis_z = dictionaryProperties.getGraphicProperties()->getVectorAxisX().z;


	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
		file.addTriplet<Ifc4::IfcCartesianPoint>(centroid_x, centroid_y, centroid_z),
		file.addTriplet<Ifc4::IfcDirection>(z_axis_x, z_axis_y, z_axis_z),
		file.addTriplet<Ifc4::IfcDirection>(x_axis_x, x_axis_y, x_axis_z)
	);
	return place;
}


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
Ifc4::IfcRepresentationItem* buildComplexPrimitive(DictionaryProperties& dictionaryProperties, Ifc4::IfcAxis2Placement3D* place, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	
	if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS) {

		TorusGraphicProperties torusGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetTorusGraphicProperties(torusGraphicProperties)) 
		{
			Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0, torusGraphicProperties.getMajorRadius()/1000000), 
				file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			Ifc4::IfcCircleProfileDef* profileDef = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement, torusGraphicProperties.getMinorRadius()/1000000);
			Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			my = new Ifc4::IfcRevolvedAreaSolid(profileDef, place, localAxis1Placement, torusGraphicProperties.getSweepRadians());
		}
		else
		{
			// TODO log torus properties not found
		}
	}


	if (my != nullptr) {
		file.addEntity(my);

	}

	return my;

}

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
Ifc4::IfcRepresentationItem* buildPrimitive(DictionaryProperties& dictionaryProperties, Ifc4::IfcAxis2Placement3D* place, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE) {

		SphereGraphicProperties sphereGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetSphereGraphicProperties(sphereGraphicProperties)) {
			my = new Ifc4::IfcSphere(place, sphereGraphicProperties.getRadius() / 1000000);
			Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(my);
		}
		else
		{
			// TODO log sphere properties not found
		}
	}
	else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX) {
		/*my = new Ifc4::IfcBlock(place, a, b, c);*/
		SlabGraphicProperties slabGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetSlabProperties(slabGraphicProperties)) {
			my = new Ifc4::IfcBlock(place, slabGraphicProperties.getLength() / 1000000, slabGraphicProperties.getWidth() / 1000000, slabGraphicProperties.getHeight() / 1000000);
		}
		else {
			// TODO log slab properties not found
		}

	}
	//else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::PYRAMID) {
	//	my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
	//}
	else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) {
		CylinderGraphicProperties cylinderGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetCylinderGraphicProperties(cylinderGraphicProperties)) {
			my = new Ifc4::IfcRightCircularCylinder(place, cylinderGraphicProperties.getHeight() / 1000000, cylinderGraphicProperties.getRadius() / 1000000);
		}
		else {
			// TODO log cylinder properties not found
		}
	}
	else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE) {
		ConeGraphicProperties coneGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetConeGraphicProperties(coneGraphicProperties)) {
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
	//items->push(solid);

}

Ifc4::IfcRepresentationItem* create_solids_from_profile(IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcProfileDef* profile) {
	Ifc4::IfcExtrudedAreaSolid* extrusion = new Ifc4::IfcExtrudedAreaSolid(profile, file.addPlacement3d(), file.addTriplet<Ifc4::IfcDirection>(0, 0, 1), 100.);
	file.addEntity(extrusion);

	/*Ifc4::IfcAxis1Placement* ax1 = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 100, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));
	Ifc4::IfcRevolvedAreaSolid* revolution1 = new Ifc4::IfcRevolvedAreaSolid(profile, file.addPlacement3d(), ax1, 360.);
	Ifc4::IfcRevolvedAreaSolid* revolution2 = new Ifc4::IfcRevolvedAreaSolid(profile, file.addPlacement3d(), ax1, 90.);
	file.addEntity(ax1);
	file.addEntity(revolution1);
	file.addEntity(revolution2);*/

	//create_product_from_item(file, extrusion, "SweptSolid");
	//create_product_from_item(file, revolution1, "SweptSolid");
	//create_product_from_item(file, revolution2, "SweptSolid");
	return extrusion;
}

void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector) {
	std::string name = "PrimitiveTest";
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";
	//std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
	Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);
	
	IfcEntityList* entityList = new IfcEntityList();
	entityList->push(ifcUnitLength);
	entityList->push(ifcUnitAngle);
	boost::shared_ptr<IfcEntityList> unitEntity(entityList);

	Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);
	Ifc4::IfcProject* project = new Ifc4::IfcProject(guid::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(), boost::none, boost::none, boost::none, boost::none, boost::none, boost::none, unitAssigment);

	file.addEntity(project);

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

	Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(
		guid::IfcGloballyUniqueId(name),
		0,
		name,
		boost::none,
		boost::none,
		0,
		0,
		boost::none,
		boost::none
	);

	file.addBuildingProduct(primitive);

	primitive->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());
	primitive->setObjectPlacement(file.addLocalPlacement());

	int micrometer = 1000000;

	for (int i = 0; i < dictionaryPropertiesVector.size(); ++i) {
		DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

		if (dictionaryProperties.getGeneralProperties()->getIsSmartFeature()) {
			continue;
		}
		
		/*Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(dictionaryProperties, file);

		Ifc4::IfcRepresentationItem* item = nullptr;
		if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE || dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX||
			dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE || dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) 
		{
			item = buildPrimitive(dictionaryProperties, place, file);
		}
		else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS) 
		{
			item = buildComplexPrimitive(dictionaryProperties, place, file);
		}

		if (item == nullptr) {
			continue;
		}*/

		CurveGraphicProperties curveProperties;
		dictionaryProperties.getGraphicProperties()->tryGetCurveGraphicsProperties(curveProperties);
		
		IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* temp = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();

		for (size_t k = 0; k < curveProperties.getControlPoints().size(); k++)
		{
			std::vector<double> p;
			p.push_back(curveProperties.getControlPoints().at(k).x / micrometer);
			p.push_back(curveProperties.getControlPoints().at(k).y / micrometer);
			p.push_back(curveProperties.getControlPoints().at(k).z / micrometer);

			Ifc4::IfcCartesianPoint* cP = new Ifc4::IfcCartesianPoint(p);
			temp->push(cP);
		}

		file.addEntities(temp->generalize());

		boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlP(temp);

		Ifc4::IfcRepresentationItem* item = new Ifc4::IfcBSplineCurve(
			dictionaryProperties.getReaderProperties()->curveDegree,
			controlP,
			Ifc4::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
			curveProperties.getIsCLosed(),
			curveProperties.getIsSelfIntersect()
		);
		
		
		file.addEntity(item);
		items->push(item);

		Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
			file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body") + std::to_string(i), std::string("Model") + std::to_string(i), items);

		reps->push(rep);

		file.addEntity(rep);
	}
	

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);

	file.addEntity(shape);

	primitive->setRepresentation(shape);

	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();
}


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
StatusInt GetSmartFeatureTree(WCharCP unparsedP)
{
	InitializationUtilities* initUtilities = new InitializationUtilities();
	
	std::vector<DictionaryProperties*> propsDictVec;
	std::vector<SmartFeatureContainer*> smartFeatureContainerVector;

	std::ofstream outfile;
	std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	//std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";

	outfile.open(filePath);
	outfile << "" << std::endl;
	outfile.close();
	
	initUtilities->analyzeDgnGraphicsElements(propsDictVec, smartFeatureContainerVector);
	
	propsDictVec = initUtilities->orderDictionaryPropertyAndSmartFeature(propsDictVec, smartFeatureContainerVector);

	//IfcBuilder* ifcBuilder = new IfcBuilder();
	//ifcBuilder->buildIfc(newPropsDictVec, smartFeatureContainerVector);

	//IfcDataHandler ifcDataHandler = IfcDataHandler(newPropsDictVec, smartFeatureContainer);
	
	//buildIfc(newPropsDictVec);

	//outfile.close();

	return SUCCESS;
}
#pragma warning( pop ) 


/*=================================================================================**//**
* @description  Unload this application
* @param[in] unparsed Additional input supplied after command string.
+===============+===============+===============+===============+===============+======*/
void UnloadParametricFeatures(WCharCP unparsedP)
{
	auto taskID = mdlSystem_getCurrTaskID();
	mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, taskID, INPUTQ_HEAD); //INPUTQ_EOQ
	return;
}
