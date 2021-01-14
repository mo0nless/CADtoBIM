#include "../headers/CurveGraphicProperties.h"

using namespace Modeler::Curves;

CurveGraphicProperties::CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType)
{
	this->_curvesTypeEnum = newCurveType;
	this->_controlPoints = vector<DPoint3d>();
	this->_UVcontrolPoints = vector<DPoint3d>();
	this->_startPoint = DPoint3d();
	this->_endPoint = DPoint3d();
	this->_UVstartPoint = DPoint3d();
	this->_UVendPoint = DPoint3d();
}

void CurveGraphicProperties::setControlPoints(bvector<DPoint3d> newControlPoints)
{
	if(!this->_controlPoints.empty())
		this->_controlPoints.clear();
	for (auto p: newControlPoints)
		this->_controlPoints.push_back(p);
}
void CurveGraphicProperties::setControlPoints(vector<DPoint3d> newControlPoints)
{
	this->_controlPoints = newControlPoints;
}


vector<DPoint3d> CurveGraphicProperties::getControlPoints() 
{ 
	return this->_controlPoints;
}
void CurveGraphicProperties::setUVcontrolPoints(vector<DPoint3d> newControlPoints)
{
	this->_UVcontrolPoints = newControlPoints;
}

vector<DPoint3d> CurveGraphicProperties::getUVcontrolPoints()
{
	return this->_UVcontrolPoints;
}


CurvesPrimitivesTypeEnum CurveGraphicProperties::getCurvesTypeEnum() 
{ 
	return _curvesTypeEnum; 
}

void CurveGraphicProperties::setStartEndPoints(DPoint3d sPoint, DPoint3d ePoint)
{
	this->_startPoint = sPoint;
	this->_endPoint = ePoint;
}

void CurveGraphicProperties::setUVstartEndPoints(DPoint3d sPoint, DPoint3d ePoint)
{
	this->_UVstartPoint = sPoint;
	this->_UVendPoint = ePoint;
}

DPoint3d CurveGraphicProperties::getUVstartPoint()
{
	return this->_UVstartPoint;
}

DPoint3d CurveGraphicProperties::getUVendPoint()
{
	return this->_UVendPoint;
}

DPoint3d CurveGraphicProperties::getStartPoint()
{
	return this->_startPoint;
}

DPoint3d CurveGraphicProperties::getEndPoint()
{
	return this->_endPoint;
}

string CurveGraphicProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(CurveGraphicProperties).name();
	stringStream << ", _startPoint x= " << _startPoint.x << ", y= " << _startPoint.y << ", z= " << _startPoint.z;
	stringStream << ", _endPoint x= " << _endPoint.x << ", y= " << _endPoint.y << ", z= " << _endPoint.z;
	stringStream << ", _UVstartPoint x= " << _UVstartPoint.x << ", y= " << _UVstartPoint.y << ", z= " << _UVstartPoint.z;
	stringStream << ", _UVendPoint x= " << _UVendPoint.x << ", y= " << _UVendPoint.y << ", z= " << _UVendPoint.z;

	if (!_controlPoints.empty()) {
		stringStream << ", _controlPoints = {" << endl;
		for each (DPoint3d controlPoint in _controlPoints)
		{
			stringStream << ", controlPoint x= " << controlPoint.x << ", y= " << controlPoint.y << ", z= " << controlPoint.z;
		}
		stringStream << "}";
	}

	if (!_UVcontrolPoints.empty()) {
		stringStream << ", _UVcontrolPoints = {" << endl;
		for each (DPoint3d UVControlPoint in _UVcontrolPoints)
		{
			stringStream << ", UVControlPoint x= " << UVControlPoint.x << ", y= " << UVControlPoint.y << ", z= " << UVControlPoint.z;
		}
		stringStream << "}";
	}

	
	stringStream << endl;

	return stringStream.str();
}
