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
	static bool isDoubleEqual(double x, double y);
	static bool isVectorDoubleEqual(std::vector<double> v1, std::vector<double>  v2);

	template<class Triplet3D>
	static bool areTripletsDoubleEqual(Triplet3D firstTriplet, Triplet3D secondTriplet);

private:
	template<class Triplet3D>
	static std::vector<double> buildDoubleVectorFromTriplet(Triplet3D newTriplet);
};

//Dpoint3d, Dvec3d
template<class Triplet3D>
inline bool IfcOperationsEnhancer::areTripletsDoubleEqual(Triplet3D firstTriplet, Triplet3D secondTriplet)
{
	for (int i = 0; i < 3; i++)
	{
		if (isDoubleEqual(firstTriplet.GetComponent(i), secondTriplet.GetComponent(i)))
		{
			continue;
		}
		else return false;
	}

	return true;
}

template<class Triplet3D>
inline std::vector<double> IfcOperationsEnhancer::buildDoubleVectorFromTriplet(Triplet3D newTriplet)
{
	std::vector<double> points;
	points.push_back(NumberUtils::convertMicrometersToMetters(newTriplet.x));
	points.push_back(NumberUtils::convertMicrometersToMetters(newTriplet.y));
	points.push_back(NumberUtils::convertMicrometersToMetters(newTriplet.z));

	return points;
}

struct SolidEdge {
	Ifc4::IfcCurve* ifcCurve;
	std::vector<int> faceID;
	Ifc4::IfcOrientedEdge* edge = nullptr;


	int nodeID;
	bool isClosed;	
};

struct ContinuosEdge : public SolidEdge
{
	DPoint3d startDPoint3d;
	DPoint3d endDPoint3d;

	Ifc4::IfcVertex* startVertex = nullptr;
	Ifc4::IfcVertex* endVertex = nullptr;

	Ifc4::IfcEdgeLoop* edgeLoop = NULL;

	ContinuosEdge* next = NULL;
};


