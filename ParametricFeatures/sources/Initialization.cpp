#include "../headers/ParametricFeatures.h"

#ifndef Private
#define Private
#endif


typedef std::string S;
boost::none_t const null = boost::none;
using boost::any_cast;

typedef IfcParse::IfcGlobalId guid;

template<class IfcSchema>
inline std::string IfcTextSolver()
{
	if (std::is_same<IfcSchema, Ifc2x3>::value) return "IFC2X3";
	if (std::is_same<IfcSchema, Ifc4>::value) return "IFC4";
	if (std::is_same<IfcSchema, Ifc4x1>::value) return "IFC4X1";
	if (std::is_same<IfcSchema, Ifc4x2>::value) return "IFC4X2";
}

//template<class IfcSchema>
//void CreateCurveRebar()
//{
//	/*const char filename[] = "C:/Users/LX5990/Documents/Internal Projects Development/DevOpenPlant/ParametricFeatures/IfcCurveRebar.ifc";*/
//	const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/IfcCurveRebar.ifc";
//	IfcHierarchyHelper<IfcSchema> file = IfcHierarchyHelper<IfcSchema>(IfcParse::schema_by_name(IfcTextSolver<IfcSchema>()));
//	file.header().file_name().name("IfcCurveBar.ifc");
//
//	typedef IfcSchema::IfcGloballyUniqueId guid;
//	int dia = 24;
//	int R = 3 * dia;
//	int length = 12 * dia;
//
//	double crossSectionarea = M_PI * (dia / 2) * 2;
//
//	//Create the IfcReinforcingBar element
//	IfcSchema::IfcReinforcingBar* rebar = new IfcSchema::IfcReinforcingBar(
//		guid::IfcGloballyUniqueId("IfcCsgPrimitive"), 0, S("test"), null,
//		null, 0, 0,
//		null, S("SR24"),		//SteelGrade
//		dia,						//diameter
//		crossSectionarea,		//crossSectionarea = math.pi*(12.0/2)**2
//		0,
//		//IfcSchema::IfcReinforcingBarRoleEnum::IfcReinforcingBarRoleEnum::IfcReinforcingBarRole_LIGATURE, ------> Ifc2x3
//		IfcSchema::IfcReinforcingBarTypeEnum::IfcReinforcingBarType_LIGATURE,
//		IfcSchema::IfcReinforcingBarSurfaceEnum::IfcReinforcingBarSurfaceEnum::IfcReinforcingBarSurface_PLAIN	//PLAIN or TEXTURED
//	);
//
//
//
//	file.addBuildingProduct(rebar);
//	rebar->setOwnerHistory(file.getSingle<IfcSchema::IfcOwnerHistory>());
//
//	IfcSchema::IfcCompositeCurveSegment::list::ptr segments(new IfcSchema::IfcCompositeCurveSegment::list());
//
//	IfcSchema::IfcCartesianPoint* p1 = file.addTriplet<IfcSchema::IfcCartesianPoint>(0, 0, 1000.);
//	IfcSchema::IfcCartesianPoint* p2 = file.addTriplet<IfcSchema::IfcCartesianPoint>(0, 0, 0);
//	IfcSchema::IfcCartesianPoint* p3 = file.addTriplet<IfcSchema::IfcCartesianPoint>(0, R, 0);
//	IfcSchema::IfcCartesianPoint* p4 = file.addTriplet<IfcSchema::IfcCartesianPoint>(0, R, -R);
//	IfcSchema::IfcCartesianPoint* p5 = file.addTriplet<IfcSchema::IfcCartesianPoint>(0, R + length, -R);
//
//	/*first segment - line */
//	IfcSchema::IfcCartesianPoint::list::ptr points1(new IfcSchema::IfcCartesianPoint::list());
//	points1->push(p1);
//	points1->push(p2);
//	file.addEntities(points1->generalize());
//	IfcSchema::IfcPolyline* poly1 = new IfcSchema::IfcPolyline(points1);
//	file.addEntity(poly1);
//
//	IfcSchema::IfcCompositeCurveSegment* segment1 = new IfcSchema::IfcCompositeCurveSegment(IfcSchema::IfcTransitionCode::IfcTransitionCode_CONTINUOUS, true, poly1);
//	file.addEntity(segment1);
//	segments->push(segment1);
//
//	/*second segment - arc */
//	IfcSchema::IfcAxis2Placement3D* axis1 = new IfcSchema::IfcAxis2Placement3D(p3, file.addTriplet<IfcSchema::IfcDirection>(1, 0, 0), file.addTriplet<IfcSchema::IfcDirection>(0, 1, 0));
//	file.addEntity(axis1);
//	IfcSchema::IfcCircle* circle = new IfcSchema::IfcCircle(axis1, R);
//	file.addEntity(circle);
//
//	IfcEntityList::ptr trim1(new IfcEntityList);
//	IfcEntityList::ptr trim2(new IfcEntityList);
//
//	trim1->push(new IfcSchema::IfcParameterValue(180));
//	trim1->push(p2);
//
//	trim2->push(new IfcSchema::IfcParameterValue(270));
//	trim2->push(p4);
//	IfcSchema::IfcTrimmedCurve* trimmed_curve = new IfcSchema::IfcTrimmedCurve(circle, trim1, trim2, false, IfcSchema::IfcTrimmingPreference::IfcTrimmingPreference_PARAMETER);
//	file.addEntity(trimmed_curve);
//
//	IfcSchema::IfcCompositeCurveSegment* segment2 = new IfcSchema::IfcCompositeCurveSegment(IfcSchema::IfcTransitionCode::IfcTransitionCode_CONTSAMEGRADIENT, false, trimmed_curve);
//	file.addEntity(segment2);
//	segments->push(segment2);
//
//	/*third segment - line */
//	IfcSchema::IfcCartesianPoint::list::ptr points2(new IfcSchema::IfcCartesianPoint::list());
//	points2->push(p4);
//	points2->push(p5);
//	file.addEntities(points2->generalize());
//	IfcSchema::IfcPolyline* poly2 = new IfcSchema::IfcPolyline(points2);
//	file.addEntity(poly2);
//
//	IfcSchema::IfcCompositeCurveSegment* segment3 = new IfcSchema::IfcCompositeCurveSegment(IfcSchema::IfcTransitionCode::IfcTransitionCode_CONTINUOUS, true, poly2);
//	file.addEntity(segment3);
//	segments->push(segment3);
//
//	IfcSchema::IfcCompositeCurve* curve = new IfcSchema::IfcCompositeCurve(segments, false);
//	file.addEntity(curve);
//
//	IfcSchema::IfcSweptDiskSolid* solid = new IfcSchema::IfcSweptDiskSolid(curve, dia / 2, null, 0, 1);
//
//	IfcSchema::IfcRepresentation::list::ptr reps(new IfcSchema::IfcRepresentation::list());
//	IfcSchema::IfcRepresentationItem::list::ptr items(new IfcSchema::IfcRepresentationItem::list());
//	items->push(solid);
//	IfcSchema::IfcShapeRepresentation* rep = new IfcSchema::IfcShapeRepresentation(
//		file.getSingle<IfcSchema::IfcRepresentationContext>(), S("Body"), S("AdvancedSweptSolid"), items);
//	reps->push(rep);
//
//	IfcSchema::IfcProductDefinitionShape* shape = new IfcSchema::IfcProductDefinitionShape(null, null, reps);
//	file.addEntity(shape);
//
//	rebar->setRepresentation(shape);
//
//	IfcSchema::IfcObjectPlacement* storey_placement = file.getSingle<IfcSchema::IfcBuildingStorey>()->ObjectPlacement();
//	rebar->setObjectPlacement(file.addLocalPlacement(storey_placement, 0, 0, 0));
//
//	std::ofstream f;
//	f.open(filename);
//	f << file;
//	f.close();
//}

//template<class IfcSchema>
//void WallTest(std::vector<PropertiesDictionary*>* propsDictVec)
//{
//	auto prop = propsDictVec->at(0)->getGraphicPropertiesMap();
//	//The program crash here, NULL values inside the map
//	//PropertyTypeValue pRange = prop.at(GraphicPropertiesEnum::RANGE);
//	//PropertyTypeValue pRange = prop.at(propsDictVec->at(0)->getGraphicPropertyObjAttribute(GraphicPropertiesEnum::RANGE));
//
//
//	//const char filename[] = "C:/Users/LX5990/Documents/Internal Projects Development/DevOpenPlant/ParametricFeatures/IfcWallTest.ifc";
//	const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/IfcWallTest.ifc";
//	typedef Ifc2x3::IfcGloballyUniqueId guid;
//	IfcHierarchyHelper<Ifc2x3> file = IfcHierarchyHelper<Ifc2x3>(IfcParse::schema_by_name("IFC2X3"));
//
//	//Ifc2x3::IfcWallStandardCase* south_wall = new Ifc2x3::IfcWallStandardCase(
//	//	guid::IfcGloballyUniqueId("Wall"),             // GlobalId
//	//	0,                     // OwnerHistory
//	//	S("South wall"),     // Name
//	//	null,                 // Description
//	//	null,                 // ObjectType
//	//	0,                     // ObjectPlacement
//	//	0,                     // Representation
//	//	null                // Tag
//	//);
//	
//	
//	Ifc2x3::IfcBuildingElementProxy* south_wall = new Ifc2x3::IfcBuildingElementProxy(
//		guid::IfcGloballyUniqueId("Wall"),
//		0,
//		std::string("Wall"),
//		null,
//		null,
//		0,
//		0,
//		null,
//		null
//	);
//
//	file.addBuildingProduct(south_wall);
//
//	// By adding a wall, a hierarchy has been automatically created that consists of the following
//	// structure: IfcProject > IfcSite > IfcBuilding > IfcBuildingStorey > IfcWall
//
//	// Lateron changing the name of the IfcProject can be done by obtaining a reference to the 
//	// project, which has been created automatically.
//	file.getSingle<Ifc2x3::IfcProject>()->setName("IfcOpenHouse");
//
//	//south_wall->setOwnerHistory(file.getSingle<Ifc2x3::IfcOwnerHistory>());
//	
//	file.addOwnerHistory();
//	// The wall will be shaped as a box, with the dimensions specified in millimeters. The resulting
//	// product definition will consist of both a body representation as well as an axis representation
//	// that runs over the centerline of the box in the X-axis.
//	Ifc2x3::IfcProductDefinitionShape* south_wall_shape = file.addAxisBox(10000, 360, 3000);
//
//	// Obtain a reference to the placement of the IfcBuildingStorey in order to create a hierarchy
//	// of placements for the products
//	Ifc2x3::IfcObjectPlacement* storey_placement = file.getSingle<Ifc2x3::IfcBuildingStorey>()->ObjectPlacement();
//	
//	// The shape has to be assigned to the representation of the wall and is placed at the origin
//	// of the coordinate system.
//	south_wall->setRepresentation(south_wall_shape);
//	south_wall->setObjectPlacement(file.addLocalPlacement(storey_placement));
//	
//	//file.addLocalPlacement(storey_placement);
//	//Ifc2x3::IfcPresentationStyleAssignment* wall_colour = file.setSurfaceColour(
//	//	south_wall_shape, 0.25, 0.23, 0.28);
//	
//	Ifc2x3::IfcRepresentation::list::ptr reps(new Ifc2x3::IfcRepresentation::list());
//	Ifc2x3::IfcRepresentationItem::list::ptr items(new Ifc2x3::IfcRepresentationItem::list());
//	
//	//Ifc2x3::IfcShapeRepresentation* body = file.addEmptyRepresentation();
//	
//	//Ifc2x3::IfcPresentationStyleAssignment* wall_colour = file.setSurfaceColour(body, 0.25, 0.23, 0.28);
//	// THIS IS THE GEOMETRY SPECIFICATION 
//	//file.addBox(body, 5000, 360, 6000);
//	//Width, Depth, Height
//	//double width = test.range.XLength() / 10;
//	//double depth = test.range.YLength() / 10;
//	//double height = test.range.ZLength() / 10;	
//	//file.addBox(body, width, depth, height);
//
//
//	Ifc2x3::IfcAxis2Placement3D* axisP = new Ifc2x3::IfcAxis2Placement3D(file.addTriplet<Ifc2x3::IfcCartesianPoint>(0, 0, 0),file.addTriplet<Ifc2x3::IfcDirection>(0, 0, 1), file.addTriplet<Ifc2x3::IfcDirection>(0, 1, 0));
//	file.addEntity(axisP);
//	//Ifc2x3::IfcRepresentationItem* my = new Ifc2x3::IfcSphere(axisP, 5000);
//	Ifc2x3::IfcCsgPrimitive3D::IfcCsgPrimitive3D(axisP);
//	Ifc2x3::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = new Ifc2x3::IfcRightCircularCylinder(axisP, 60000, 500);
//	file.addEntity(my);
//	items->push(my);
//	Ifc2x3::IfcShapeRepresentation* rep = new Ifc2x3::IfcShapeRepresentation(
//		file.getSingle<Ifc2x3::IfcRepresentationContext>(), S("Body"), S("AdvancedSweptSolid"), items);
//	reps->push(rep);	
//	Ifc2x3::IfcProductDefinitionShape* shape = new Ifc2x3::IfcProductDefinitionShape(null, null, reps);
//	file.addEntity(shape);
//	//Ifc2x3::IfcPresentationStyleAssignment* wall_colour = file.setSurfaceColour(my, 0.25, 0.23, 0.28);
//	//file.setSurfaceColour(shape,wall_colour);
//
//	/*file.setSurfaceColour(body, wall_colour);
//	reps->push(body);
//	
//	Ifc2x3::IfcProductDefinitionShape* shape = new Ifc2x3::IfcProductDefinitionShape(null, null, reps);
//	file.addEntity(shape);*/
//	
//	//south_wall->setRepresentation(shape);
//
//	std::ofstream f;
//	f.open(filename);
//	f << file;
//	f.close();
//}


void WallTest() {
	// The IfcHierarchyHelper is a subclass of the regular IfcFile that provides several
	// convenience functions for working with geometry in IFC files.
	IfcHierarchyHelper<Ifc2x3> file = IfcHierarchyHelper<Ifc2x3>(IfcParse::schema_by_name("IFC2X3"));
	file.header().file_name().name("IfcOpenHouse.ifc");

	// Start by adding a wall to the file, initially leaving most attributes blank.
	Ifc2x3::IfcWallStandardCase* south_wall = new Ifc2x3::IfcWallStandardCase(
		guid(), 			// GlobalId
		0, 					// OwnerHistory
		S("South wall"), 	// Name
		null, 				// Description
		null, 				// ObjectType
		0, 					// ObjectPlacement
		0, 					// Representation
		null				// Tag
		
	);
	file.addBuildingProduct(south_wall);

	// By adding a wall, a hierarchy has been automatically created that consists of the following
	// structure: IfcProject > IfcSite > IfcBuilding > IfcBuildingStorey > IfcWall

	// Lateron changing the name of the IfcProject can be done by obtaining a reference to the 
	// project, which has been created automatically.
	file.getSingle<Ifc2x3::IfcProject>()->setName("IfcOpenHouse");

	// An IfcOwnerHistory has been initialized as well, which should be assigned to the wall.
	south_wall->setOwnerHistory(file.getSingle<Ifc2x3::IfcOwnerHistory>());

	// The wall will be shaped as a box, with the dimensions specified in millimeters. The resulting
	// product definition will consist of both a body representation as well as an axis representation
	// that runs over the centerline of the box in the X-axis.
	Ifc2x3::IfcProductDefinitionShape* south_wall_shape = file.addAxisBox(10000, 360, 3000);

	// Obtain a reference to the placement of the IfcBuildingStorey in order to create a hierarchy
	// of placements for the products
	Ifc2x3::IfcObjectPlacement* storey_placement = file.getSingle<Ifc2x3::IfcBuildingStorey>()->ObjectPlacement();

	// The shape has to be assigned to the representation of the wall and is placed at the origin
	// of the coordinate system.
	south_wall->setRepresentation(south_wall_shape);
	south_wall->setObjectPlacement(file.addLocalPlacement(storey_placement));

	const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/IfcWallTest.ifc";
		std::ofstream f;
		f.open(filename);
		f << file;
		f.close();

	// A pale white colour is assigned to the wall.
	//Ifc2x3::IfcPresentationStyleAssignment* wall_colour = file.setSurfaceColour(
	//	south_wall_shape, 0.75, 0.73, 0.68);

	//le.setSurfaceColour(body, wall_colour);

	//Ifc2x3::IfcFooting* footing = new Ifc2x3::IfcFooting(guid(), file.getSingle<Ifc2x3::IfcOwnerHistory>(),
	//	S("Footing"), null, null, 0, 0, null, Ifc2x3::IfcFootingTypeEnum::IfcFootingType_STRIP_FOOTING);

	//file.addBuildingProduct(footing);

	//// The footing will span the entire floor plan of our building. The IfcRepresentationContext is
	//// something that has been created automatically as well, but representations could have been 
	//// assigned to a specific context, for example to add a two dimensional plan representation as well.
	//footing->setRepresentation(file.addBox(10100, 5460, 2000));
	//footing->setObjectPlacement(file.addLocalPlacement(storey_placement, 0, 2500, -2000));
	//// The footing will have a dark gray colour
	//Ifc2x3::IfcPresentationStyleAssignment* footing_colour = file.setSurfaceColour(footing->Representation(), 0.26, 0.22, 0.18);

	//south_wall->setRepresentation(shape);
}

#if false 
template<class IfcSchema>
void IfcSchemaTester()
{
	typedef IfcSchema::IfcGloballyUniqueId guid;
	/*const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/IfcCsgPrimitive.ifc";*/
	const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/IfcCsgPrimitive.ifc";

	IfcHierarchyHelper<IfcSchema> file = IfcHierarchyHelper<IfcSchema>(IfcParse::schema_by_name(IfcTextSolver<IfcSchema>()));
	file.header().file_name().name("IfcCsgPrimitive.ifc");

	/*
	IfcSchema::IfcRepresentationItem* csg1 = IfcGenerator::Box(8000., 6000., 3000.).subtract(
		IfcGenerator::Box(7600., 5600., 2800.).move(200., 200., 200.)
	).add(
		IfcGenerator::Pyramid(8000., 6000., 3000.).move(0, 0, 3000.).add(
			IfcGenerator::Cylinder(1000., 4000.).move(4000., 1000., 4000., 0., 1., 0.)
		).subtract(
			IfcGenerator::Pyramid(7600., 5600., 2800.).move(200., 200., 3000.)
		).subtract(
			IfcGenerator::Cylinder(900., 4000.).move(4000., 1000., 4000., 0., 1., 0.).intersect(
				IfcGenerator::Box(2000., 4000., 1000.).move(3000., 1000., 4000.)
			)
		)
	).serialize<IfcSchema>(file);

	const double x = 1000.; const double y = -4000.;

	IfcSchema::IfcRepresentationItem* csg2 = IfcGenerator::Sphere(5000.).move(x, y, -4500.).intersect(
		IfcGenerator::Box(6000., 6000., 6000.).move(x - 3000., y - 3000., 0.)
	).add(
		IfcGenerator::Cone(500., 3000.).move(x, y).add(
			IfcGenerator::Cone(1500., 1000.).move(x, y, 900.).add(
				IfcGenerator::Cone(1100., 1000.).move(x, y, 1800.).add(
					IfcGenerator::Cone(750., 600.).move(x, y, 2700.)
				)
			)
		)
	).serialize<IfcSchema>(file);
	*/
	
	int R = 3 * 20;
	IfcSchema::IfcCartesianPoint* point = file.addTriplet<IfcSchema::IfcCartesianPoint>(0, R, 0);
	IfcSchema::IfcAxis2Placement3D* place = new IfcSchema::IfcAxis2Placement3D(point, file.addTriplet<IfcSchema::IfcDirection>(1, 0, 0), file.addTriplet<IfcSchema::IfcDirection>(0, 1, 0));

	IfcSchema::IfcRepresentationItem* myItem = new IfcSchema::IfcSphere(place, 10);

	//Main proxy that holds all the shapes and representations
	/*IfcSchema::IfcBuildingElementProxy* product = new IfcSchema::IfcBuildingElementProxy(
		guid::IfcGloballyUniqueId("IfcCsgPrimitive"), 
		0, 
		std::string("IfcCsgPrimitive"), 
		null, 
		null, 
		0, 
		0, 
		null, 
		null
	);*/

	IfcSchema::IfcBuildingElement* product = new Ifc2x3::IfcBuildingElement(
		guid::IfcGloballyUniqueId("IfcCsgPrimitive"),
		0,
		std::string("IfcCsgPrimitive"),
		null,
		null,
		0,
		0,
		null//,
		//null
	);

	//Add the proxy to the IfcHierarchyHelper
	file.addBuildingProduct(product);

	//Add to the IfcBuildingElementProxy an Owner and a Local placement (NEEDS TO BE CLARIFIED) 
	product->setOwnerHistory(file.getSingle<IfcSchema::IfcOwnerHistory>());

	IfcSchema::IfcObjectPlacement* storey_placement = file.getSingle<IfcSchema::IfcBuildingStorey>()->ObjectPlacement();	
	product->setObjectPlacement(file.addLocalPlacement(storey_placement));
	//product->setObjectPlacement(file.addLocalPlacement());

	//Create new lists as containers for the IfcRepresentation and for the IfcRepresentationItem
	IfcSchema::IfcRepresentation::list::ptr reps(new IfcSchema::IfcRepresentation::list());
	IfcSchema::IfcRepresentationItem::list::ptr items(new IfcSchema::IfcRepresentationItem::list());

	//Push the IfcRepresentation generated before inside the IfcRepresentationItem List 
	//items->push(csg1);
	//items->push(csg2);

	items->push(myItem);

	//Create a new IfcShapeRepresentation and add the list of IfcRepresentationItem to it
	IfcSchema::IfcShapeRepresentation* rep = new IfcSchema::IfcShapeRepresentation(
		file.getSingle<IfcSchema::IfcRepresentationContext>(), std::string("Body"), std::string("CSG"), items);
	//Push the IfcShapeRepresentation inside the IfcRepresentation List that it was created previously
	reps->push(rep);

	IfcSchema::IfcProductDefinitionShape* shape = new IfcSchema::IfcProductDefinitionShape(null, null, reps);
	//file.addEntity(rep);
	file.addEntity(shape);

	//Push the shape inside the IfcBuildingElementProxy
	product->setRepresentation(shape);

	file.getSingle<IfcSchema::IfcProject>()->setName("IfcCompositeProfileDef");

	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();
}
#endif


#pragma warning( push )
#pragma warning( disable : 4700)
StatusInt GetSmartFeatureTree(WCharCP unparsedP)
{
	DgnModelP dgnModel = ISessionMgr::GetActiveDgnModelP();
	std::ofstream outfile;
	//std::string filePath = "C:/Users/LX5990/Documents/Internal Projects Development/DevOpenPlant/ParametricFeatures/TEST.txt";
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/TEST.txt";

	WString myString, sFeatTree;
	WString dgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName().AppendUtf8(".txt");

	/*std::vector<Dicion*> propsDictVec;*/
	// Complete the full file path with the name of the model  
	/*for (char c : static_cast<Utf8String>(dgnFileName))
		filePath += c;*/

	std::cout << filePath << std::endl;

	// Create the instance for the Graphics Processor
	GraphicsProcessor graphicsProcessor = GraphicsProcessor(outfile, filePath);

	PersistentElementRefList *pGraElement = dgnModel->GetGraphicElementsP();
	outfile.open(filePath);
	outfile << "===================================================" << std::endl;
	outfile.close(); 

	std::vector<DictionaryProperties*>propsDictVec;
	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer();


	for (PersistentElementRefP elemRef : *pGraElement)
	{
		ElementHandle leafNode;
		ElementHandle currentElem(elemRef);
		SmartFeatureNodePtr sFeatNode;
		T_SmartFeatureVector sFeatVec;
		WString elDescr;
			
		
		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
		
		long newCurrentElementId = -1, newLocalNodeId = -1, newParentLocalNodeId = -1, newElementId=-1;

		newCurrentElementId = currentElem.GetElementId();
		if (SmartFeatureElement::IsSmartFeature(currentElem))
		{
			SmartFeatureElement::ExtractTree(sFeatNode, currentElem);

			outfile.open(filePath, std::ios_base::app);
			sFeatNode->GetAllChildrenRecursively(sFeatVec);
			
			for (size_t i = 0; i < sFeatVec.size(); i++)
			{
				outfile << "start==================" << std::endl;
				if (sFeatVec.at(i)->GetParent() != nullptr)
				{						
					outfile << "Parent Ref Count: " << sFeatVec.at(i)->GetParent()->GetRefCount() << std::endl;
					outfile << "Parent ID: " << sFeatVec.at(i)->GetParent()->GetNodeId() << std::endl;
					newParentLocalNodeId = sFeatVec.at(i)->GetParent()->GetNodeId();
				}

				outfile << "Node ID: " << sFeatVec.at(i)->GetNodeId() << std::endl;
				newLocalNodeId = sFeatVec.at(i)->GetNodeId();
				sFeatVec.at(i)->GetLeaf(leafNode);

				if (leafNode.IsValid()) {

					newElementId = leafNode.GetElementId();
					
					DependentElmP depElm = currentElem.GetElementRef()->GetFirstDependent();
					

					outfile << "leaf id:  " <<leafNode.GetElementId() << std::endl;
					outfile << "Display Handler " << leafNode.GetDisplayHandler() << std::endl;
					outfile << "Dependent Elem " << leafNode.GetElementRef()->GetFirstDependent() << std::endl;
					outfile << "Dependent Current Elem " << depElm << std::endl;
					outfile << "Element Level " << leafNode.GetElementRef()->GetLevel() << std::endl;					
					outfile << "Element Ref " << leafNode.GetIDependencyHandler() << std::endl;
				}
				outfile << "finish==================" << std::endl;
				smartFeatureContainer->insertNodeInTree(newCurrentElementId, newLocalNodeId, newParentLocalNodeId, newElementId);
			}

			outfile << "Smart Feat Element Node ID: " << sFeatNode->GetNodeId() << std::endl;
			outfile << "Number of Child: " << sFeatNode->GetChildCount() << std::endl;
			outfile.close();
		}

		outfile.open(filePath, std::ios_base::app);
		outfile << "===================================================" << std::endl;
		outfile << "====" << static_cast<Utf8String>(elDescr.GetWCharCP()) << "====" << std::endl;
		outfile << "==== Is Smart Feauture = " << SmartFeatureElement::IsSmartFeature(currentElem) << "====" << std::endl;
		outfile << currentElem.GetElementId() << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << std::endl;
		outfile.close();

		DictionaryProperties* propertiesDictionary = new DictionaryProperties();

		//propertiesDictionary->set(StringUtils::getString(elDescr.GetWCharCP()));
		
		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor(currentElem, outfile, filePath, *propertiesDictionary,*smartFeatureContainer);

		graphicsProcessor.setPropertiesDictionary(propertiesDictionary);
		graphicsProcessor.updateClassAndID(propertiesReaderProcessor->getElemClassName(), currentElem.GetElementId());
		ElementGraphicsOutput::Process(currentElem, graphicsProcessor);

		propsDictVec.push_back(propertiesDictionary);

	}

	for (int i = 0; i < propsDictVec.size(); ++i) {
		DictionaryProperties* propertiesDictionary = propsDictVec.at(i);
		if (!propertiesDictionary->getAreReaderPropertiesFound()) {
			SmartFeatureTreeNode* treeNode = smartFeatureContainer->search(smartFeatureContainer->getRoot(), propertiesDictionary->getReaderProperties()->getNodeId());
			if (treeNode != nullptr) {
				treeNode->getSmartFeatureProperties()->setGraphicProperties(propertiesDictionary->getGraphicProperties());
			}
		}
	
	}

	outfile.close();
	//IfcSchemaTester<Ifc2x3>();
	WallTest();

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
