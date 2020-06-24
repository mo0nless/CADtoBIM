#pragma once

#include <vector>
#include "../../common/utils/headers/NumberUtils.h"
#include "../../stdafx.h"

class IfcOperationsEnhancer
{
public:
	IfcOperationsEnhancer();

	
	static Ifc4::IfcCartesianPoint* buildIfcCartesian3DfromCoordsPoint3D(DPoint3d newControlPoint);
	static Ifc4::IfcCartesianPoint* buildIfcCartesian2DfromCoordsPoint3D(DPoint3d newControlPoint);
	
	static Ifc4::IfcDirection* buildIfcDirection3DfromDirectionVec3D(DVec3d newDirection);
	static Ifc4::IfcDirection* buildIfcDirection2DfromDirectionVec3D(DVec3d newDirection);
	
	static Ifc4::IfcAxis2Placement3D * buildIfcAxis2Placement3D(DVec3d pointOfPlacement, DVec3d dirVectorZ, DVec3d dirVectorX);
	static Ifc4::IfcAxis2Placement2D * buildIfcAxis2Placement2D(DVec3d pointOfPlacement, DVec3d dirVectorX);

	static bool isDoubleEqual(double x, double y);
	static bool isVectorDoubleEqual(std::vector<double> v1, std::vector<double>  v2);

	template<class Triplet3D>
	static bool areTripletsDoubleEqual(Triplet3D firstTriplet, Triplet3D secondTriplet);

	template<class Triplet3D>
	static Ifc4::IfcVector* buildIfcVectorFromDirectionPoint3D(Triplet3D newVector);
	
private:
	template<class Triplet3D>
	static std::vector<double> buildDoubleVectorFromTriplet(Triplet3D newTriplet);
	template<class Tuple2D>
	static std::vector<double> buildDoubleVectorFromTuple(Tuple2D newTuple);
};

//Dpoint3d, Dvec3d
template<class Triplet3D>
Ifc4::IfcVector * IfcOperationsEnhancer::buildIfcVectorFromDirectionPoint3D(Triplet3D newVector)
{
	Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(
		IfcOperationsEnhancer::buildDoubleVectorFromTriplet<Triplet3D>(newVector)
	);

	Ifc4::IfcVector* vC = new Ifc4::IfcVector(dir, newVector.Magnitude());

	return vC;
}

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

template<class Tuple2D>
inline std::vector<double> IfcOperationsEnhancer::buildDoubleVectorFromTuple(Tuple2D newTuple)
{
	std::vector<double> points;
	points.push_back(NumberUtils::convertMicrometersToMetters(newTuple.x));
	points.push_back(NumberUtils::convertMicrometersToMetters(newTuple.y));

	return points;
}




struct SolidEdge {
	Ifc4::IfcCurve* ifcCurve;
	std::vector<int> faceID;
	Ifc4::IfcOrientedEdge* edge = nullptr;
	
	int type;
	int nodeID;
	bool isClosed = false;	
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


