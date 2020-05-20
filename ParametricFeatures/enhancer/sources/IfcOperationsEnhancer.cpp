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

Ifc4::IfcAxis2Placement3D * IfcOperationsEnhancer::buildIfcAxis2Placement3D(DVec3d pointOfPlacement, DVec3d dirVectorZ, DVec3d dirVectorX)
{
	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
		IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(pointOfPlacement),
		IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(dirVectorZ),
		IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(dirVectorX)
	);

	return place;
}

bool IfcOperationsEnhancer::isDoubleEqual(double x, double y)
{
	/* some small number such as 1e-5 */
	const double epsilon = 1e-5;
	return std::abs(x - y) <= epsilon * std::abs(x);
	// see Knuth section 4.2.2 pages 217-218
}

bool IfcOperationsEnhancer::isVectorDoubleEqual(std::vector<double> v1, std::vector<double> v2)
{
	if (v1.size() == v2.size())
	{
		for (size_t i = 0; i < v1.size(); i++)
		{
			if (isDoubleEqual(v1[i], v2[i]))
				continue;
			else
				return false;
		}
		return true;
	}

	return false;
}


