#include "../headers/IfcGenerator.h"


IfcGenerator::IfcGenerator( std::string ifcPrjName)
	:ifcProjectName(ifcPrjName)
{

}

#pragma warning( push )
#pragma warning( disable : 4715)
IfcGenerator::Primitives IfcGenerator::DescriptionNameToEnumSolver(std::string elementDescriptionName)
{
	if (elementDescriptionName == "Cylinder") { return IfcGenerator::PRIM_CYLINDER; }
	else if (elementDescriptionName == "Sphere") { return IfcGenerator::PRIM_SPHERE; }
	else if (elementDescriptionName == "Torus") { return IfcGenerator::PRIM_TORUS; }
	else if (elementDescriptionName == "Cone") { return IfcGenerator::PRIM_CONE; }
	else if (elementDescriptionName == "Slab") { return IfcGenerator::PRIM_BOX; }
	else IfcGenerator::NONE;
}

//void IfcGenerator::CreateIfcFile(Primitives primitives)
//{
//
//	IfcHierarchyHelper<Ifc2x3> file = IfcHierarchyHelper<Ifc2x3>(IfcParse::schema_by_name("IFC2X3"));
//	const char filename[] = "C:/Users/LX5990/Documents/Internal Projects Development/DevOpenPlant/ParametricFeatures/IfcTest.ifc";
//	/*const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/IfcWallTest.ifc";*/
//
//	for (size_t i = 0; i < vecPropertiesDictionary->size(); i++)
//	{
//		IfcGenerator::DescriptionNameToEnumSolver(vecPropertiesDictionary->at(i)->getElemDescrName());
//		Ifc2x3::IfcGloballyUniqueId guid = Ifc2x3::IfcGloballyUniqueId(vecPropertiesDictionary->at(i)->getElemDescrName());
//
//		Ifc2x3::IfcBuildingElementProxy* elementProxy = new Ifc2x3::IfcBuildingElementProxy(
//			guid,
//			0,
//			std::string(vecPropertiesDictionary->at(i)->getElemDescrName()),
//			null,
//			null,
//			0,
//			0,
//			null,
//			null
//		);
//
//		file.addBuildingProduct(elementProxy);
//
//		// Lateron changing the name of the IfcProject can be done by obtaining a reference to the 
//		// project, which has been created automatically.
//		file.getSingle<Ifc2x3::IfcProject>()->setName(ifcProjectName);
//
//		elementProxy->setOwnerHistory(file.getSingle<Ifc2x3::IfcOwnerHistory>());
//		// Obtain a reference to the placement of the IfcBuildingStorey in order to create a hierarchy
//		// of placements for the products
//		Ifc2x3::IfcObjectPlacement* storey_placement = file.getSingle<Ifc2x3::IfcBuildingStorey>()->ObjectPlacement();
//
//		// The shape has to be assigned to the representation of the wall and is placed at the origin
//		// of the coordinate system.
//		elementProxy->setObjectPlacement(file.addLocalPlacement(storey_placement));
//
//		Ifc2x3::IfcRepresentation::list::ptr reps(new Ifc2x3::IfcRepresentation::list());
//		Ifc2x3::IfcRepresentationItem::list::ptr items(new Ifc2x3::IfcRepresentationItem::list());
//
//		Ifc2x3::IfcShapeRepresentation* body = file.addEmptyRepresentation();
//		Ifc2x3::IfcPresentationStyleAssignment* colour = file.setSurfaceColour(body, 0.25, 0.23, 0.28);
//
//		switch (primitives)
//		{
//		case Primitives::PRIM_BOX:
//			Box(1, 1, 1);
//			break;
//		case Primitives::PRIM_CONE:
//			break;
//		case Primitives::PRIM_CYLINDER:
//			break;
//		case Primitives::PRIM_SPHERE:
//			break;
//		case Primitives::PRIM_TORUS:
//			break;
//		default:
//			break;
//		}
//
//		file.addBox(body, 5000, 360, 6000);
//		//Width, Depth, Height
//		file.setSurfaceColour(body, colour);
//		reps->push(body);
//
//		Ifc2x3::IfcProductDefinitionShape* shape = new Ifc2x3::IfcProductDefinitionShape(null, null, reps);
//		file.addEntity(shape);
//
//		elementProxy->setRepresentation(shape);
//
//		std::ofstream f;
//		f.open(filename);
//		f << file;
//		f.close();
//
//	}
//}


void IfcGenerator::Sphere(double r)
{
}

void IfcGenerator::Box(double dx, double dy, double dz)
{
}

void IfcGenerator::Pyramid(double dx, double dy, double dz)
{
}

void IfcGenerator::Cylinder(double r, double h)
{
}

void IfcGenerator::Cone(double r, double h)
{
}

void IfcGenerator::SamrtFeature()
{
}

/*
IfcGenerator& IfcGenerator::operate(Operation opr, const IfcGenerator& p)
{
	left = new IfcGenerator(*this);
	right = new IfcGenerator(p);
	this->op = opr;
	return *this;
}

IfcGenerator::IfcGenerator(Primitives p, double la, double lb, double lc)
	: prim(p), op(OP_TERMINAL),
	x(0.), y(0.), z(0.),
	zx(0.), zy(0.), zz(1.),
	xx(1.), xy(0.), xz(0.),
	a(la), b(lb), c(lc) {}

IfcGenerator IfcGenerator::Sphere(double r) {
	return IfcGenerator(PRIM_SPHERE, r);
}
IfcGenerator IfcGenerator::Box(double dx, double dy, double dz) {
	return IfcGenerator(PRIM_BOX, dx, dy, dz);
}
IfcGenerator IfcGenerator::Pyramid(double dx, double dy, double dz) {
	return IfcGenerator(PRIM_PYRAMID, dx, dy, dz);
}
IfcGenerator IfcGenerator::Cylinder(double r, double h) {
	return IfcGenerator(PRIM_CYLINDER, r, h);
}
IfcGenerator IfcGenerator::Cone(double r, double h) {
	return IfcGenerator(PRIM_CONE, r, h);
}

IfcGenerator& IfcGenerator::move(
	double px, double py, double pz,
	double zX, double zY, double zZ,
	double xX, double xY, double xZ)
{
	this->x = px; this->y = py;	this->z = pz;
	this->zx = zX; this->zy = zY; this->zz = zZ;
	this->xx = xX; this->xy = xY; this->xz = xZ;
	return *this;
}

IfcGenerator& IfcGenerator::add(const IfcGenerator& p) {
	return operate(OP_ADD, p);
}
IfcGenerator& IfcGenerator::subtract(const IfcGenerator& p) {
	return operate(OP_SUBTRACT, p);
}
IfcGenerator& IfcGenerator::intersect(const IfcGenerator& p) {
	return operate(OP_INTERSECT, p);
}
*/

