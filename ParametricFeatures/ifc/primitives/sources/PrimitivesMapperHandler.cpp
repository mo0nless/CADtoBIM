#include "../headers/PrimitivesMapperHandler.h"

void PrimitivesMapperHandler::buildPrimitive(DictionaryProperties& dictionaryProperties)
{
	double a = 50, b = 50, c = 50;
	std::string name = "PrimitiveTest";
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	/*std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";*/
	std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
	typedef Ifc4::IfcGloballyUniqueId guid2;

	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0), file.addTriplet<Ifc4::IfcDirection>(0, 1, 0));
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE) {
		my = new Ifc4::IfcSphere(place, a);
	}
	else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX) {
		my = new Ifc4::IfcBlock(place, a, b, c);
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

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

	Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(my);

	file.addEntity(my);
	items->push(solid);

	Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
		file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body"), std::string("Model"), items);

	reps->push(rep);

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);

	file.addEntity(rep);
	file.addEntity(shape);

	primitive->setRepresentation(shape);

	file.getSingle<Ifc4::IfcProject>()->setName("proxy with CSG");

	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();

}
