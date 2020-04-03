#include "../headers/IfcOperationsEnhancer.h"

IfcOperationsEnhancer::IfcOperationsEnhancer()
{
}

Ifc4::IfcCartesianPoint * IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(DPoint3d newControlPoints)
{
	Ifc4::IfcCartesianPoint* cP = new Ifc4::IfcCartesianPoint(
		IfcOperationsEnhancer::buildDoubleVectorFromTriplet<DPoint3d>(newControlPoints)
	);

	return cP;
}

Ifc4::IfcVector * IfcOperationsEnhancer::buildIfcVectorFromDirectionPoint3D(DPoint3d newVector)
{
	Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(
		IfcOperationsEnhancer::buildDoubleVectorFromTriplet<DPoint3d>(newVector)
	);

	Ifc4::IfcVector* vC = new Ifc4::IfcVector(dir, newVector.Magnitude());

	return vC;
}

Ifc4::IfcDirection * IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(DVec3d newDirection)
{
	Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(
		IfcOperationsEnhancer::buildDoubleVectorFromTriplet<DPoint3d>(newDirection)
	);

	return dir;
}