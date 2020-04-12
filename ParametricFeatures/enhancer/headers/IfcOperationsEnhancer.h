#pragma once

#include <vector>
#include "../../common/utils/headers/NumberUtils.h"
#include "../../stdafx.h"

class IfcOperationsEnhancer
{
public:
	IfcOperationsEnhancer();

	static Ifc4::IfcCartesianPoint* buildIfcCartesianFromCoordsPoint3D(DPoint3d newControlPoint);
	static Ifc4::IfcVector* buildIfcVectorFromDirectionPoint3D(DPoint3d newVector);
	static Ifc4::IfcDirection* buildIfcDirectionFromDirectionVec3D(DVec3d newDirection);
	static Ifc4::IfcAxis2Placement3D * buildIfcAxis2Placement3D(DVec3d pointOfPlacement, DVec3d dirVectorZ, DVec3d dirVectorX);
private:
	template<class Triplet>
	static std::vector<double> buildDoubleVectorFromTriplet(Triplet newTriplet);
};

template<class Triplet>
inline std::vector<double> IfcOperationsEnhancer::buildDoubleVectorFromTriplet(Triplet newTriplet)
{
	std::vector<double> points;
	points.push_back(NumberUtils::convertMicrometersToMetters(newTriplet.x));
	points.push_back(NumberUtils::convertMicrometersToMetters(newTriplet.y));
	points.push_back(NumberUtils::convertMicrometersToMetters(newTriplet.z));

	return points;
}