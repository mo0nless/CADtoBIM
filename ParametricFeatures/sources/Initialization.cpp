#include "../headers/ParametricFeatures.h"

#ifndef Private
#define Private
#endif


typedef std::string S;
boost::none_t const null = boost::none;
using boost::any_cast;

typedef enum {
	PRIM_BOX, PRIM_CONE, PRIM_CYLINDER, PRIM_PYRAMID, PRIM_SPHERE
} Primitives;

template<class IfcSchema>
inline std::string IfcTextSolver()
{
	if (std::is_same<IfcSchema, Ifc2x3>::value) return "IFC2X3";
	if (std::is_same<IfcSchema, Ifc4>::value) return "IFC4";
	if (std::is_same<IfcSchema, Ifc4x1>::value) return "IFC4X1";
	if (std::is_same<IfcSchema, Ifc4x2>::value) return "IFC4X2";
}

void CSG(Primitives prim, std::string name, double a = 0., double b = 0., double c = 0.)
{
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	/*std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";*/
	std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
	typedef Ifc4::IfcGloballyUniqueId guid2;
	
	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0), file.addTriplet<Ifc4::IfcDirection>(0, 1, 0));
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	if (prim == PRIM_SPHERE) {
		my = new Ifc4::IfcSphere(place, a);
	}
	else if (prim == PRIM_BOX) {
		my = new Ifc4::IfcBlock(place, a, b, c);
	}
	else if (prim == PRIM_PYRAMID) {
		my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
	}
	else if (prim == PRIM_CYLINDER) {
		my = new Ifc4::IfcRightCircularCylinder(place, b, a);
	}
	else if (prim == PRIM_CONE) {
		my = new Ifc4::IfcRightCircularCone(place, b, a);
	}

	Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(
		guid2::IfcGloballyUniqueId(name),
		0,
		name,
		null,
		null,
		0,
		0,
		null,
		null
	);

	file.addBuildingProduct(primitive);

	primitive->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());
	primitive->setObjectPlacement(file.addLocalPlacement());

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());
	
	Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(my);

	file.addEntity(my);
	items->push(solid);

	Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
		file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), S("Body"), S("Model"), items);

	reps->push(rep);

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(null, null, reps);

	file.addEntity(rep);
	file.addEntity(shape);

	primitive->setRepresentation(shape);

	file.getSingle<Ifc4::IfcProject>()->setName("proxy with CSG");

	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();
}

void CSGPrimitiveTest()
{
	const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/IfcSphereTest.ifc";
	//const char filename[] = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/IfcSphereTest.ifc";
	typedef Ifc4::IfcGloballyUniqueId guid2;
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));


	Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(
		guid2::IfcGloballyUniqueId("Sphere"),
		0,
		std::string("Sphere"),
		null,
		null,
		0,
		0,
		null,
		null
	);

	file.addBuildingProduct(primitive);

	// By adding a wall, a hierarchy has been automatically created that consists of the following
	// structure: IfcProject > IfcSite > IfcBuilding > IfcBuildingStorey > IfcWall

	primitive->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());

	//file.addOwnerHistory();
	// The wall will be shaped as a box, with the dimensions specified in millimeters. The resulting
	// product definition will consist of both a body representation as well as an axis representation
	// that runs over the centerline of the box in the X-axis.
	//Ifc4::IfcProductDefinitionShape* primitive_shape = file.addAxisBox(10000, 360, 3000);

	// Obtain a reference to the placement of the IfcBuildingStorey in order to create a hierarchy
	// of placements for the products
	//Ifc4::IfcObjectPlacement* storey_placement = file.getSingle<Ifc4::IfcBuildingStorey>()->ObjectPlacement();


	// The shape has to be assigned to the representation of the wall and is placed at the origin
	// of the coordinate system.
	//primitive->setRepresentation(primitive_shape);
	//primitive->setObjectPlacement(file.addLocalPlacement(storey_placement));
	primitive->setObjectPlacement(file.addLocalPlacement());

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

	Ifc4::IfcAxis2Placement3D* axisP = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0), file.addTriplet<Ifc4::IfcDirection>(0, 1, 0));
	//Ifc4::IfcRepresentationItem* my = new Ifc4::IfcSphere(axisP, 5000);

	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = new Ifc4::IfcSphere(axisP, 5000);
	Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(my);
	//Ifc4::IfcCsgPrimitive3D::IfcRepresentationItem* my = new Ifc4::IfcSphere(axisP, 5000);
	//Ifc4::IfcCsgPrimitive3D::IfcCsgPrimitive3D(axisP);
	//Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = new Ifc4::IfcRightCircularCylinder(axisP, 60000, 500);
	file.addEntity(my);

	items->push(solid);

	Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
		file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), S("Body"), S("Model"), items);
	reps->push(rep);

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(null, null, reps);
	file.addEntity(rep);
	file.addEntity(shape);
	//Ifc4::IfcPresentationStyleAssignment* wall_colour = file.setSurfaceColour(my, 0.25, 0.23, 0.28);
	//file.setSurfaceColour(shape,wall_colour);

	/*file.setSurfaceColour(body, wall_colour);
	reps->push(body);

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(null, null, reps);
	file.addEntity(shape);*/

	primitive->setRepresentation(shape);
	// Lateron changing the name of the IfcProject can be done by obtaining a reference to the 
	// project, which has been created automatically.
	file.getSingle<Ifc4::IfcProject>()->setName("proxy with CSG");

	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();
}

void WallTest() {
	// The IfcHierarchyHelper is a subclass of the regular IfcFile that provides several
	// convenience functions for working with geometry in IFC files.
	IfcHierarchyHelper<Ifc2x3> file = IfcHierarchyHelper<Ifc2x3>(IfcParse::schema_by_name("IFC2X3"));
	file.header().file_name().name("IfcOpenHouse.ifc");
	
	typedef IfcParse::IfcGlobalId guid;

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

	const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/IfcWallTest.ifc";
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


//class CSGBool {
//private:
//	typedef enum {
//		OP_ADD, OP_SUBTRACT, OP_INTERSECT, OP_TERMINAL
//	} Op;
//	typedef enum {
//		PRIM_BOX, PRIM_CONE, PRIM_CYLINDER, PRIM_PYRAMID, PRIM_SPHERE
//	} Prim;
//
//	double x, y, z, zx, zy, zz, xx, xy, xz, a, b, c;
//	const CSGBool *left, *right;
//
//	Op op;
//	Prim prim;
//
//	CSGBool& operate(Op oP, const CSGBool& p) {
//		left = new CSGBool(*this);
//		right = new CSGBool(p);
//		this->op = oP;
//		return *this;
//	}
//
//	CSGBool(Prim p, double la, double lb = 0., double lc = 0.)
//		: prim(p), op(OP_TERMINAL),
//		x(0.), y(0.), z(0.),
//		zx(0.), zy(0.), zz(1.),
//		xx(1.), xy(0.), xz(0.),
//		a(la), b(lb), c(lc) {}
//public:
//	static CSGBool Sphere(double r) {
//		return CSGBool(PRIM_SPHERE, r);
//	}
//	static CSGBool Box(double dx, double dy, double dz) {
//		return CSGBool(PRIM_BOX, dx, dy, dz);
//	}
//	static CSGBool Pyramid(double dx, double dy, double dz) {
//		return CSGBool(PRIM_PYRAMID, dx, dy, dz);
//	}
//	static CSGBool Cylinder(double r, double h) {
//		return CSGBool(PRIM_CYLINDER, r, h);
//	}
//	static CSGBool Cone(double r, double h) {
//		return CSGBool(PRIM_CONE, r, h);
//	}
//
//	CSGBool& move(
//		double px = 0., double py = 0., double pz = 0.,
//		double zX = 0., double zY = 0., double zZ = 1.,
//		double xX = 1., double xY = 0., double xZ = 0.)
//	{
//		this->x = px; this->y = py;	this->z = pz;
//		this->zx = zX; this->zy = zY; this->zz = zZ;
//		this->xx = xX; this->xy = xY; this->xz = xZ;
//		return *this;
//	}
//
//	CSGBool& add(const CSGBool& p) {
//		return operate(OP_ADD, p);
//	}
//	CSGBool& subtract(const CSGBool& p) {
//		return operate(OP_SUBTRACT, p);
//	}
//	CSGBool& intersect(const CSGBool& p) {
//		return operate(OP_INTERSECT, p);
//	}
//
//	Ifc4::IfcRepresentationItem* serialize(IfcHierarchyHelper<Ifc4>& file) const {
//		Ifc4::IfcRepresentationItem* my = nullptr;
//		if (op == OP_TERMINAL) {
//			Ifc4::IfcAxis2Placement3D* place = file.addPlacement3d(x, y, z, zx, zy, zz, xx, xy, xz);
//			if (prim == PRIM_SPHERE) {
//				my = new Ifc4::IfcSphere(place, a);
//			}
//			else if (prim == PRIM_BOX) {
//				my = new Ifc4::IfcBlock(place, a, b, c);
//			}
//			else if (prim == PRIM_PYRAMID) {
//				my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
//			}
//			else if (prim == PRIM_CYLINDER) {
//				my = new Ifc4::IfcRightCircularCylinder(place, b, a);
//			}
//			else if (prim == PRIM_CONE) {
//				my = new Ifc4::IfcRightCircularCone(place, b, a);
//			}
//		}
//		else {
//			Ifc4::IfcBooleanOperator::Value o;
//			if (op == OP_ADD) {
//				o = Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION;
//			}
//			else if (op == OP_SUBTRACT) {
//				o = Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE;
//			}
//			else if (op == OP_INTERSECT) {
//				o = Ifc4::IfcBooleanOperator::IfcBooleanOperator_INTERSECTION;
//			}
//			my = new Ifc4::IfcBooleanResult(o, left->serialize(file), right->serialize(file));
//		}
//		file.addEntity(my);
//		return my;
//	}
//};

//void test()
//{
//	typedef IfcParse::IfcGlobalId guid;
//	//const char filename[] = "C:/Users/LX5990/Documents/Internal Projects Development/DevOpenPlant/ParametricFeatures/IfcCsgPrimitive.ifc";
//	const char filename[] ="examples/ifc/IfcCsgPrimitive.ifc";
//	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
//	file.header().file_name().name(filename);
//
//	/*Ifc4::IfcRepresentationItem* csg1 = CSGBool::Box(8000.,6000.,3000.).subtract(
//		CSGBool::Box(7600.,5600.,2800.).move(200.,200.,200.)
//	).add(
//		CSGBool::Pyramid(8000.,6000.,3000.).move(0,0,3000.).add(
//			CSGBool::Cylinder(1000.,4000.).move(4000.,1000.,4000., 0.,1.,0.)
//		).subtract(
//			CSGBool::Pyramid(7600.,5600.,2800.).move(200.,200.,3000.)
//		).subtract(
//			CSGBool::Cylinder(900.,4000.).move(4000.,1000.,4000., 0.,1.,0.).intersect(
//				CSGBool::Box(2000.,4000.,1000.).move(3000.,1000.,4000.)
//			)
//		)
//	).serialize(file);*/
//
//	//const double x = 1000.; const double y = -4000.;
//
//	Ifc4::IfcRepresentationItem* csg2 = CSGBool::Sphere(5000.).move(0.,0.,4500.).intersect(
//		CSGBool::Box(6000., 6000., 6000.).move(3000., 3000., 0.)
//	).add(
//		CSGBool::Cone(500., 3000.).move(0,0).add(
//			CSGBool::Cone(1500., 1000.).move(0,0, 900.).add(
//				CSGBool::Cone(1100., 1000.).move(0,0, 1800.).add(
//					CSGBool::Cone(750., 600.).move(0,0, 2700.)
//				)))).serialize(file);
//
//	/*Ifc4::IfcRepresentationItem* csg2 = CSGBool::Cone(5000., 6000.).move(x, y, -4500.).intersect(
//		CSGBool::Box(6000., 6000., 6000.).move(x - 3000., y - 3000., 0.)
//	).add(
//		CSGBool::Cone(500., 3000.).move(x, y).add(
//			CSGBool::Cone(1500., 1000.).move(x, y, 900.).add(
//				CSGBool::Pyramid(1100., 1000., 6000.).move(x, y, 1800.).add(
//					CSGBool::Cone(7500., 600.).move(x, y, 2700.)
//				)))).serialize(file);*/
//
//	Ifc4::IfcBuildingElementProxy* product = new Ifc4::IfcBuildingElementProxy(
//		guid(), 0, S("IfcCsgPrimitive"), null, null, 0, 0, null, null);
//
//	file.addBuildingProduct(product);
//
//	product->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());
//
//	product->setObjectPlacement(file.addLocalPlacement());
//
//	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
//	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());
//
//	//items->push(csg1);
//	items->push(csg2);
//	Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
//		file.getSingle<Ifc4::IfcRepresentationContext>(), S("Body"), S("CSG"), items);
//	reps->push(rep);
//
//	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(null, null, reps);
//	file.addEntity(rep);
//	file.addEntity(shape);
//
//	product->setRepresentation(shape);
//
//	file.getSingle<Ifc4::IfcProject>()->setName("IfcCompositeProfileDef");
//
//	std::ofstream f(filename);
//	f << file;
//}


void booleanOperation(DictionaryProperties& dictionaryProperties, SmartFeatureContainer& smartFeatureContainer){



}


void buildPrimitive(std::vector<DictionaryProperties*>& dictionaryPropertiesVector)
{
	double a = 50, b = 50, c = 50;
	std::string name = "PrimitiveTest";
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	/*std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";*/
	std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
	typedef Ifc4::IfcGloballyUniqueId guid2;

	

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

	Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(
		guid2::IfcGloballyUniqueId(name),
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

	for (int i = 0; i < dictionaryPropertiesVector.size(); ++i) {
		DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

		if (dictionaryProperties.getIsSmartFeature()) {
			continue;
		}
		Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

		double centroid_x = dictionaryProperties.getGraphicProperties()->getCentroid().x / 100;
		double centroid_y = dictionaryProperties.getGraphicProperties()->getCentroid().y / 100;
		double centroid_z = dictionaryProperties.getGraphicProperties()->getCentroid().z / 100;

		double z_axis_x = dictionaryProperties.getGraphicProperties()->getVectorBaseZ().x;
		double z_axis_y = dictionaryProperties.getGraphicProperties()->getVectorBaseZ().y;
		double z_axis_z = dictionaryProperties.getGraphicProperties()->getVectorBaseZ().z;

		double x_axis_x = dictionaryProperties.getGraphicProperties()->getVectorBaseX().x;
		double x_axis_y = dictionaryProperties.getGraphicProperties()->getVectorBaseX().y;
		double x_axis_z = dictionaryProperties.getGraphicProperties()->getVectorBaseX().z;


		Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(centroid_x, centroid_y, centroid_z),
			file.addTriplet<Ifc4::IfcDirection>(z_axis_x, z_axis_y, z_axis_z), file.addTriplet<Ifc4::IfcDirection>(x_axis_x, x_axis_y, x_axis_z));

	
		if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE) {
			my = new Ifc4::IfcSphere(place, a);
		}
		else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX) {
			/*my = new Ifc4::IfcBlock(place, a, b, c);*/
			my = new Ifc4::IfcBlock(place, dictionaryProperties.getGraphicProperties()->getSlabLength() / 100, dictionaryProperties.getGraphicProperties()->getSlabWidth() / 100,
				dictionaryProperties.getGraphicProperties()->getSlabHeight() / 100);
		}
		else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::PYRAMID) {
			my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
		}
		else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) {
			my = new Ifc4::IfcRightCircularCylinder(place, b, a);
		}
		else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE) {
			my = new Ifc4::IfcRightCircularCone(place, b, a);
		}

		Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(my);
		
		file.addEntity(my);
		items->push(solid);

		Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
			file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body")+std::to_string(i), std::string("Model") + std::to_string(i), items);

		reps->push(rep);

		file.addEntity(rep);

	}

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);
	
	file.addEntity(shape);

	primitive->setRepresentation(shape);

	file.getSingle<Ifc4::IfcProject>()->setName("proxy with CSG");

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
	DgnModelP dgnModel = ISessionMgr::GetActiveDgnModelP();
	std::ofstream outfile;
	//std::string filePath = "C:/Users/LX5990/Documents/Internal Projects Development/DevOpenPlant/ParametricFeatures/TEST.txt";
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";

	WString myString, sFeatTree;
	WString dgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName().AppendUtf8(".txt");

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
		
		/*bool isSmartElement = mdlSolid_isSmartElement(MSElementDescrP(currentElem.GetElementDescrCP()), ISessionMgr::GetActiveDgnModelRefP());
		bool isSmartSolidElement = mdlSolid_isSmartSolidElement (MSElementDescrP(currentElem.GetElementDescrCP()), ISessionMgr::GetActiveDgnModelRefP());

		if(isSmartElement)
		{
			outfile.open(filePath);
			outfile << "========================isSmartElement===========================" << std::endl;
			outfile.close();
		}

		if (isSmartSolidElement)
		{
			outfile.open(filePath);
			outfile << "=========================isSmartSolidElement==========================" << std::endl;
			outfile.close();
		}*/

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
		outfile << "===================================================" << std::endl;
		outfile << "Element Description: " << static_cast<Utf8String>(elDescr.GetWCharCP())<< std::endl;
		outfile << "Element ID: " << currentElem.GetElementId() << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << std::endl;
		outfile.close();

		DictionaryProperties* propertiesDictionary = new DictionaryProperties();
		propertiesDictionary->getGeneralProperties()->setClassName(StringUtils::getString(elDescr.GetWCharCP()));
		propertiesDictionary->getGeneralProperties()->setElementId(currentElem.GetElementId());
		propertiesDictionary->getGeneralProperties()->setCurrentElementId(currentElem.GetElementId());
		//propertiesDictionary->set(StringUtils::getString(elDescr.GetWCharCP()));
		
		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor(currentElem, outfile, filePath, *propertiesDictionary,*smartFeatureContainer);

		graphicsProcessor.setPropertiesDictionary(propertiesDictionary);
		graphicsProcessor.updateClassAndID(propertiesReaderProcessor->getElemClassName(), currentElem.GetElementId());
		ElementGraphicsOutput::Process(currentElem, graphicsProcessor);

		propsDictVec.push_back(propertiesDictionary);

		ISolidKernelEntityPtr solidKernPtr;
		//SolidUtil::Convert::ElementToBody(solidKernPtr, currentElem, true, true, true);

	}

	for (int i = 0; i < propsDictVec.size(); ++i) {
		DictionaryProperties* propertiesDictionary = propsDictVec.at(i);
		if (!propertiesDictionary->getAreReaderPropertiesFound()) {
			SmartFeatureTreeNode* treeNode = smartFeatureContainer->searchByElementId(smartFeatureContainer->getRoot(), propertiesDictionary->getGeneralProperties()->getElementId());
			if (treeNode != nullptr) {
				treeNode->setGraphicProperties(propertiesDictionary->getGraphicProperties());
			}
		}	
	
	}

	buildPrimitive(propsDictVec);

	outfile.close();
	//IfcSchemaTester<Ifc2x3>();
	//WallTest();
	//CSG(PRIM_BOX, "Box", 50, 60, 50);
	//CSG(PRIM_CONE, "Cone", 50, 60, 50);
	//CSG(PRIM_CYLINDER, "Cylinder", 50, 60, 50);
	//CSG(PRIM_PYRAMID, "Pyramid", 50, 60, 50);
	//CSG(PRIM_SPHERE, "Sphere", 50, 60, 50);
	//CSGPrimitiveTest();

//	PrimitivesMapperHandler::buildPrimitive(*propsDictVec.at(0));

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
