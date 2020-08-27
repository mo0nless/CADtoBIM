#pragma once

#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/enums/headers/IfcDimensionEnum.h"
#include "../../../common/utils/headers/Comparator.h"

#include "../../../stdafx.h"

#include "../../../modeler/shapes/headers/ShapesGraphicProperties.h"

class IfcOperationsHelper
{
public:
	IfcOperationsHelper();

	
	static Ifc4::IfcCartesianPoint* buildIfcCartesian3DfromCoordsPoint3D(DPoint3d newControlPoint);
	static Ifc4::IfcCartesianPoint* buildIfcCartesian2DfromCoordsPoint3D(DPoint3d newControlPoint);
	
	static Ifc4::IfcDirection* buildIfcDirection3DfromDirectionVec3D(DVec3d newDirection);
	static Ifc4::IfcDirection* buildIfcDirection2DfromDirectionVec3D(DVec3d newDirection);
	
	static Ifc4::IfcAxis2Placement3D * buildIfcAxis2Placement3D(DVec3d pointOfPlacement, DVec3d dirVectorZ, DVec3d dirVectorX);
	static Ifc4::IfcAxis2Placement2D * buildIfcAxis2Placement2D(DVec3d pointOfPlacement, DVec3d dirVectorX);

	template<class Triplet3D>
	static bool areTripletsDoubleEqual(Triplet3D firstTriplet, Triplet3D secondTriplet);

	template<class Triplet3D>
	static Ifc4::IfcVector* buildIfcVectorFromDirectionPoint3D(Triplet3D newVector);

	static void adjustShapeGlobalPlacement(ShapesGraphicProperties* shape, DVec3d position, bool rotatePoint);
	
private:
	static DPoint3d rotateAlongAxis(std::string axis, DPoint3d oldPoint);
	template<class Triplet3D>
	static std::vector<double> buildDoubleVectorFromTriplet(Triplet3D newTriplet);
	template<class Tuple2D>
	static std::vector<double> buildDoubleVectorFromTuple(Tuple2D newTuple);
};

//Dpoint3d, Dvec3d
template<class Triplet3D>
Ifc4::IfcVector * IfcOperationsHelper::buildIfcVectorFromDirectionPoint3D(Triplet3D newVector)
{
	Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(
		IfcOperationsHelper::buildDoubleVectorFromTriplet<Triplet3D>(newVector)
	);

	Ifc4::IfcVector* vC = new Ifc4::IfcVector(dir, newVector.Magnitude());

	return vC;
}

//Dpoint3d, Dvec3d
template<class Triplet3D>
inline bool IfcOperationsHelper::areTripletsDoubleEqual(Triplet3D firstTriplet, Triplet3D secondTriplet)
{
	for (int i = 0; i < 3; i++)
	{
		if (Comparator::isEqual (firstTriplet.GetComponent(i), secondTriplet.GetComponent(i)))
		{
			continue;
		}
		else return false;
	}

	return true;
}

template<class Triplet3D>
inline std::vector<double> IfcOperationsHelper::buildDoubleVectorFromTriplet(Triplet3D newTriplet)
{
	std::vector<double> points;
	points.push_back(NumberUtils::convertCurrentUnitToMeters(newTriplet.x));
	points.push_back(NumberUtils::convertCurrentUnitToMeters(newTriplet.y));
	points.push_back(NumberUtils::convertCurrentUnitToMeters(newTriplet.z));

	return points;
}

template<class Tuple2D>
inline std::vector<double> IfcOperationsHelper::buildDoubleVectorFromTuple(Tuple2D newTuple)
{
	std::vector<double> points;
	points.push_back(NumberUtils::convertCurrentUnitToMeters(newTuple.x));
	points.push_back(NumberUtils::convertCurrentUnitToMeters(newTuple.y));

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


