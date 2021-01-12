#include "../headers/IfcOperationsHelper.h"

IfcOperationsHelper::IfcOperationsHelper()
{
}

//3 Dimension
Ifc4::IfcCartesianPoint * IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(DPoint3d newControlPoints)
{
	Logging::Logger::getLogger()->logDebug(__FILE__, __LINE__, __func__);

	Ifc4::IfcCartesianPoint* cP = new Ifc4::IfcCartesianPoint(
		IfcOperationsHelper::buildDoubleVectorFromTriplet<DPoint3d>(newControlPoints)
	);

	return cP;
}

//2 Dimension
Ifc4::IfcCartesianPoint * IfcOperationsHelper::buildIfcCartesian2DfromCoordsPoint3D(DPoint3d newControlPoint)
{
	Logging::Logger::getLogger()->logDebug(__FILE__, __LINE__, __func__);

	Ifc4::IfcCartesianPoint* cP = new Ifc4::IfcCartesianPoint(
		IfcOperationsHelper::buildDoubleVectorFromTuple<DPoint3d>(newControlPoint)
	);

	return cP;
}

//3 Dimension
Ifc4::IfcDirection * IfcOperationsHelper::buildIfcDirection3DfromDirectionVec3D(DVec3d newDirection)
{
	Logging::Logger::getLogger()->logDebug(__FILE__, __LINE__, __func__);

	vector<double> points;
	points.push_back(newDirection.x);
	points.push_back(newDirection.y);
	points.push_back(newDirection.z);

	Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(points);

	return dir;
}

//2 Dimension
Ifc4::IfcDirection * IfcOperationsHelper::buildIfcDirection2DfromDirectionVec3D(DVec3d newDirection)
{
	Logging::Logger::getLogger()->logDebug(__FILE__, __LINE__, __func__);

	vector<double> points;
	points.push_back(newDirection.x);
	points.push_back(newDirection.y);

	Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(points);

	return dir;
}

//3 Dimension
Ifc4::IfcAxis2Placement3D * IfcOperationsHelper::buildIfcAxis2Placement3D(DVec3d pointOfPlacement, DVec3d dirVectorZ, DVec3d dirVectorX)
{
	Logging::Logger::getLogger()->logDebug(__FILE__, __LINE__, __func__);

	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
		IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(pointOfPlacement),
		IfcOperationsHelper::buildIfcDirection3DfromDirectionVec3D(dirVectorZ),
		IfcOperationsHelper::buildIfcDirection3DfromDirectionVec3D(dirVectorX)
	);

	return place;
}

//2 Dimension
Ifc4::IfcAxis2Placement2D * IfcOperationsHelper::buildIfcAxis2Placement2D(DVec3d pointOfPlacement, DVec3d dirVectorX)
{
	Logging::Logger::getLogger()->logDebug(__FILE__, __LINE__, __func__);

	Ifc4::IfcAxis2Placement2D* place = new Ifc4::IfcAxis2Placement2D(
		IfcOperationsHelper::buildIfcCartesian2DfromCoordsPoint3D(pointOfPlacement),
		IfcOperationsHelper::buildIfcDirection2DfromDirectionVec3D(dirVectorX)
	);

	return place;
}

void IfcOperationsHelper::adjustShapeGlobalPlacement(ShapesGraphicProperties * shape, DVec3d position, bool rotatePoint)
{
	Logging::Logger::getLogger()->logDebug(__FILE__, __LINE__, __func__);

	bool invertedAxis = false;
	string axis = "";
	double epsilon = 0.11;// 1e-2;
	double valueNumber = 1.0;

	if (rotatePoint)
	{
		if (abs(abs(shape->getVectorAxisX().z) - valueNumber) <= epsilon )//* abs(shape->getVectorAxisX().z))//(abs(shape->getVectorAxisX().z) == 1) //CASE X is [0,0,1] it's not in the XY plane vector X should be [1,0,0]
		{
			invertedAxis = true;
			axis = "X";
		}
		else if (abs(abs(shape->getVectorAxisY().z) - valueNumber) <= epsilon)// * abs(shape->getVectorAxisY().z))//(abs(shape->getVectorAxisY().z) == 1) //CASE Y is [0,0,1] it's not in the XY plane vector Y should be [0,1,0]
		{
			invertedAxis = true;
			axis = "Y";
		}
	}

	// adjust global points of the shape/curve related to the global placement of the revolve			
	for (auto curve : shape->getCurvesPrimitivesContainerVector())
	{
		vector<DPoint3d> temp;
		for (auto point : curve->getControlPoints())
		{
			DPoint3d oldPoint;
			DPoint3d newPoint;

			if (invertedAxis)
			{
				oldPoint.Subtract(point, position);
				newPoint = rotateAlongAxis(axis, oldPoint);
			}
			else
			{
				oldPoint = point;
				newPoint.Subtract(oldPoint, position);
			}

			temp.push_back(newPoint);
		}
		curve->setControlPoints(temp);
	}
}

DPoint3d IfcOperationsHelper::rotateAlongAxis(string axis, DPoint3d oldPoint)
{
	Logging::Logger::getLogger()->logDebug(__FILE__, __LINE__, __func__);

	DPoint3d newPoint;

	if (axis == "X")
	{
		newPoint.x = oldPoint.x;
		newPoint.y = oldPoint.y*cos(-90) - oldPoint.z*sin(-90);
		newPoint.z = oldPoint.y*sin(-90) + oldPoint.z*cos(-90);
	}
	else if (axis == "Y")
	{
		newPoint.x = oldPoint.z*sin(-90) + oldPoint.x*cos(-90);
		newPoint.y = oldPoint.y;
		newPoint.z = oldPoint.y*cos(-90) - oldPoint.x*sin(-90);
	}

	return newPoint;
}


