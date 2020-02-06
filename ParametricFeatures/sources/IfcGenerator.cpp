#include "../headers/IfcGenerator.h"

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


