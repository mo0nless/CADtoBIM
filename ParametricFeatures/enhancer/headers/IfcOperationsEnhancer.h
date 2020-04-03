#pragma once

#include <vector>
#include "../../common/utils/headers/NumberUtils.h"
#include "../../stdafx.h"

class IfcOperationsEnhancer
{
public:
	static Ifc4::IfcCartesianPoint* buildIfcCartesianFromCoordsPoint3D(DPoint3d newControlPoint);
	static Ifc4::IfcVector* buildIfcVectorFromDirectionPoint3D(DPoint3d newVector);
	static Ifc4::IfcDirection* buildIfcDirectionFromDirectionVec3D(DVec3d newDirection);
	
private:
	IfcOperationsEnhancer();

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