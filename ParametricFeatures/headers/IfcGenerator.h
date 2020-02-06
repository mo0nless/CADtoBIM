#pragma once

#include "../stdafx.h"
#include "PropertiesDictionary.h"
#include <ifcparse\IfcSchema.h>
#include <ifcparse\Ifc2x3.h>
#include <ifcparse\Ifc4.h>
#include <ifcparse\Ifc4x1.h>
#include <ifcparse\utils.h>
#include <ifcparse\IfcHierarchyHelper.h>


class IfcGenerator
{
private:
	typedef enum { OP_ADD, OP_SUBTRACT, OP_INTERSECT, OP_TERMINAL } Operation;
	typedef enum { PRIM_BOX, PRIM_CONE, PRIM_CYLINDER, PRIM_PYRAMID, PRIM_SPHERE, PRIM_TORUS, NONE} Primitives;

	boost::none_t const null = boost::none;
	/*
	double x, y, z, zx, zy, zz, xx, xy, xz, a, b, c = 0.;
	const IfcGenerator *left, *right;*/

	Operation op;
	Primitives prim;
	std::vector<PropertiesDictionary*>* vecPropertiesDictionary;
	std::string ifcProjectName;

	template<class IfcSchema>
	std::string IfcTextSolver();
	/*
	IfcGenerator& operate(Operation opr, const IfcGenerator& p);
	IfcGenerator(Primitives p, double la, double lb = 0., double lc = 0.);*/
	Primitives DescriptionNameToEnumSolver(std::string& elementDescriptionName);
	void CreateIfcFile(Primitives primitives);
public:
	IfcGenerator(std::vector<PropertiesDictionary*>* propsDictVec, std::string ifcPrjName);
	void Sphere(double r);
	void Box(double dx, double dy, double dz);
	void Pyramid(double dx, double dy, double dz);
	void Cylinder(double r, double h);
	void Cone(double r, double h);

	/*
	static IfcGenerator Sphere(double r);
	static IfcGenerator Box(double dx, double dy, double dz);
	static IfcGenerator Pyramid(double dx, double dy, double dz);
	static IfcGenerator Cylinder(double r, double h);
	static IfcGenerator Cone(double r, double h);
	
	IfcGenerator& move(
		double px = 0., double py = 0., double pz = 0.,
		double zX = 0., double zY = 0., double zZ = 1.,
		double xX = 1., double xY = 0., double xZ = 0.);

	IfcGenerator& add(const IfcGenerator& p);
	IfcGenerator& subtract(const IfcGenerator& p);
	IfcGenerator& intersect(const IfcGenerator& p);
	
	template<class IfcSchema>
	typename IfcSchema::IfcRepresentationItem* serialize(IfcHierarchyHelper<IfcSchema>& file) const;*/
};

template<class IfcSchema>
inline std::string IfcGenerator::IfcTextSolver()
{
	if (std::is_same<IfcSchema, Ifc2x3>::value) return "IFC2X3";
	if (std::is_same<IfcSchema, Ifc4>::value) return "IFC4";
	if (std::is_same<IfcSchema, Ifc4x1>::value) return "IFC4X1";
	if (std::is_same<IfcSchema, Ifc4x2>::value) return "IFC4X2";
}
//The function needs to be placed here otherwise it will end up as an unresolved external symbol
//More information at the address: https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates
/*
template<class IfcSchema>
inline typename IfcSchema::IfcRepresentationItem* IfcGenerator::serialize(IfcHierarchyHelper<IfcSchema>& file) const {
	IfcSchema::IfcRepresentationItem* my = nullptr;
	if (op == OP_TERMINAL) {
		IfcSchema::IfcCartesianPoint* point = file.addTriplet<IfcSchema::IfcCartesianPoint>(x, y, z);
		IfcSchema::IfcAxis2Placement3D* place = new IfcSchema::IfcAxis2Placement3D(point, file.addTriplet<IfcSchema::IfcDirection>(zx, zy, zz), file.addTriplet<IfcSchema::IfcDirection>(xx, xy, xz));
		//file.addEntity(my);
		//file.addPlacement3d(x, y, z, zx, zy, zz, xx, xy, xz); //(Ifc4::IfcCartesianPoint *v1_Location, Ifc4::IfcDirection *v2_Axis, Ifc4::IfcDirection *v3_RefDirection)
		if (prim == PRIM_SPHERE) {
			my = new IfcSchema::IfcSphere(place, a);
		}
		else if (prim == PRIM_BOX) {
			my = new IfcSchema::IfcBlock(place, a, b, c);
		}
		else if (prim == PRIM_PYRAMID) {
			my = new IfcSchema::IfcRectangularPyramid(place, a, b, c);
		}
		else if (prim == PRIM_CYLINDER) {
			my = new IfcSchema::IfcRightCircularCylinder(place, b, a);
		}
		else if (prim == PRIM_CONE) {
			my = new IfcSchema::IfcRightCircularCone(place, b, a);
		}
	}
	else {
		IfcSchema::IfcBooleanOperator::Value o;
		if (op == OP_ADD) {
			o = IfcSchema::IfcBooleanOperator::IfcBooleanOperator_UNION;
		}
		else if (op == OP_SUBTRACT) {
			o = IfcSchema::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE;
		}
		else if (op == OP_INTERSECT) {
			o = IfcSchema::IfcBooleanOperator::IfcBooleanOperator_INTERSECTION;
		}
		my = new IfcSchema::IfcBooleanResult(o, left->serialize(file), right->serialize(file));
	}

	file.addEntity(my);
	return my;
}
*/