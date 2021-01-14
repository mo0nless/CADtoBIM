#include "../headers/ShapesGraphicProperties.h"

using namespace Modeler::Shapes;

ShapesGraphicProperties::ShapesGraphicProperties()
{
	this->_curvesBoundaryType = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
	this->_isFilled = false;
	this->_isClosed = false;
	this->_curvesPrimitivesContainer = vector<CurveGraphicProperties*>();
	this->_shapesGraphicsContainer = vector<ShapesGraphicProperties*>();
	this->_hasShapesGraphicsContainer = false;
	this->_isSingleCurve = false;
	this->_normal = DVec3d();
	this->_faceBoundIdentifiers = vector<int>();
	this->_nodeId = -1;
}

void ShapesGraphicProperties::insertCurvesGraphicsProperties(CurveGraphicProperties * newCurveGraphicProperties)
{
	this->_curvesPrimitivesContainer.push_back(newCurveGraphicProperties);
}

vector<CurveGraphicProperties*> ShapesGraphicProperties::getCurvesPrimitivesContainerVector()
{
	return this->_curvesPrimitivesContainer;
}

void ShapesGraphicProperties::setBoundaryTypeCurvesContainer(int boundaryBentleyType)
{
	this->_curvesBoundaryType = ShapesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(boundaryBentleyType);
}

CurvesBoundaryTypeEnum ShapesGraphicProperties::getBoundaryTypeCurvesContainer()
{
	return this->_curvesBoundaryType;
}

void ShapesGraphicProperties::addFaceBoundID(int newFaceidentifier)
{
	this-> _faceBoundIdentifiers.push_back(newFaceidentifier);
}

vector<int> ShapesGraphicProperties::getFacesBoundIDs()
{
	return this->_faceBoundIdentifiers;
}

void ShapesGraphicProperties::setIsFilled(bool value)
{
	this->_isFilled = value;
}

bool ShapesGraphicProperties::getIsFilled()
{
	return this->_isFilled;
}

bool ShapesGraphicProperties::getIsClosed() const
{
	return _isClosed;
}

void ShapesGraphicProperties::setIsClosed(bool isClosed)
{
	this->_isClosed = isClosed;
}

bool ShapesGraphicProperties::hasShapesGraphicsContainer() const
{
	return this->_hasShapesGraphicsContainer;
}

vector<ShapesGraphicProperties*> ShapesGraphicProperties::getShapesGraphicsContainer()
{
	return this->_shapesGraphicsContainer;
}

DVec3d ShapesGraphicProperties::getNormal() const
{
	return this->_normal;
}

void ShapesGraphicProperties::setNormal(DVec3d normal)
{
	this->_normal = normal;
}

void ShapesGraphicProperties::setStartEndPoints(DPoint3d start, DPoint3d end)
{
	this->mStartPoint = start;
	this->mEndPoint = end;
}

DPoint3d ShapesGraphicProperties::getStartPoint()
{
	return this->mStartPoint;
}

DPoint3d ShapesGraphicProperties::getEndPoint()
{
	return this->mEndPoint;
}

void ShapesGraphicProperties::setUVstartEndPoints(DPoint3d sPoint, DPoint3d ePoint)
{
	this->mUVstartPoint = sPoint;
	this->mUVendPoint = ePoint;
}

DPoint3d ShapesGraphicProperties::getUVstartPoint()
{
	return this->mUVstartPoint;
}

DPoint3d ShapesGraphicProperties::getUVendPoint()
{
	return this->mUVendPoint;
}

void ShapesGraphicProperties::setNodeId(int id)
{
	this->_nodeId = id;
}

int ShapesGraphicProperties::getNodeId()
{
	return this->_nodeId;
}

bool ShapesGraphicProperties::getHasSingleCurve()
{
	return this->_isSingleCurve;
}

void ShapesGraphicProperties::setHasSingleCurve(bool value)
{
	this->_isSingleCurve = value;
}

void ShapesGraphicProperties::insertShapesGraphicProperties(ShapesGraphicProperties * newShapesGraphicProperties)
{
	this->_shapesGraphicsContainer.push_back(newShapesGraphicProperties);
	this->_hasShapesGraphicsContainer = true;
}

ShapesGraphicProperties::~ShapesGraphicProperties()
{
}

string ShapesGraphicProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(ShapesGraphicProperties).name();
	stringStream << ", _nodeId = " << _nodeId;
	stringStream << ", _isFilled = " << _isFilled;
	stringStream << ", _isClosed = " << _isClosed;
	stringStream << ", _hasShapesGraphicsContainer = " << _hasShapesGraphicsContainer;
	stringStream << ", _isSingleCurve = " << _isSingleCurve;
	stringStream << ", _normal x= " << _normal.x << ", y= " << _normal.y << ", z= " << _normal.z;

	if (!_faceBoundIdentifiers.empty()) {
		stringStream << ", _faceBoundIdentifiers = {" << endl;
		for each (int faceBound in _faceBoundIdentifiers)
		{
			stringStream << ", faceBound = " << faceBound;
		}
		stringStream << "}";
	}

	if (!_curvesPrimitivesContainer.empty()) {
		stringStream << ", _curvesPrimitivesContainer = {" << endl;
		for each (CurveGraphicProperties* cruveGraphicProperty in _curvesPrimitivesContainer)
		{
			if (cruveGraphicProperty != nullptr) {
				stringStream << ", cruveGraphicProperty = " << cruveGraphicProperty->toString();
			}
		}
		stringStream << "}" ;
	}
	if (!_shapesGraphicsContainer.empty()) {
		stringStream << ", _shapesGraphicsContainer = {" << endl;
		for each (ShapesGraphicProperties* shapesGraphicProperty in _shapesGraphicsContainer)
		{
			if (shapesGraphicProperty != nullptr) {
				stringStream << ", shapesGraphicProperty = " << shapesGraphicProperty->toString();
			}
		}
		stringStream << "}";
	}
	stringStream << endl;

	return stringStream.str();
}
