#include "../headers/IfcOperationsEnhancer.h"

IfcOperationsEnhancer::IfcOperationsEnhancer()
{
}

//3 Dimension
Ifc4::IfcCartesianPoint * IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(DPoint3d newControlPoints)
{
	Ifc4::IfcCartesianPoint* cP = new Ifc4::IfcCartesianPoint(
		IfcOperationsEnhancer::buildDoubleVectorFromTriplet<DPoint3d>(newControlPoints)
	);

	return cP;
}

//2 Dimension
Ifc4::IfcCartesianPoint * IfcOperationsEnhancer::buildIfcCartesian2DfromCoordsPoint3D(DPoint3d newControlPoint)
{
	Ifc4::IfcCartesianPoint* cP = new Ifc4::IfcCartesianPoint(
		IfcOperationsEnhancer::buildDoubleVectorFromTuple<DPoint3d>(newControlPoint)
	);

	return cP;
}

//3 Dimension
Ifc4::IfcDirection * IfcOperationsEnhancer::buildIfcDirection3DfromDirectionVec3D(DVec3d newDirection)
{
	std::vector<double> points;
	points.push_back(NumberUtils::convertMicrometersToMetters(newDirection.x));
	points.push_back(NumberUtils::convertMicrometersToMetters(newDirection.y));
	points.push_back(NumberUtils::convertMicrometersToMetters(newDirection.z));

	Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(points);

	return dir;
}

//2 Dimension
Ifc4::IfcDirection * IfcOperationsEnhancer::buildIfcDirection2DfromDirectionVec3D(DVec3d newDirection)
{
	std::vector<double> points;
	points.push_back(NumberUtils::convertMicrometersToMetters(newDirection.x));
	points.push_back(NumberUtils::convertMicrometersToMetters(newDirection.y));

	Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(points);

	return dir;
}

//3 Dimension
Ifc4::IfcAxis2Placement3D * IfcOperationsEnhancer::buildIfcAxis2Placement3D(DVec3d pointOfPlacement, DVec3d dirVectorZ, DVec3d dirVectorX)
{
	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
		IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(pointOfPlacement),
		IfcOperationsEnhancer::buildIfcDirection3DfromDirectionVec3D(dirVectorZ),
		IfcOperationsEnhancer::buildIfcDirection3DfromDirectionVec3D(dirVectorX)
	);

	return place;
}

//2 Dimension
Ifc4::IfcAxis2Placement2D * IfcOperationsEnhancer::buildIfcAxis2Placement2D(DVec3d pointOfPlacement, DVec3d dirVectorX)
{
	Ifc4::IfcAxis2Placement2D* place = new Ifc4::IfcAxis2Placement2D(
		IfcOperationsEnhancer::buildIfcCartesian2DfromCoordsPoint3D(pointOfPlacement),
		IfcOperationsEnhancer::buildIfcDirection2DfromDirectionVec3D(dirVectorX)
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


