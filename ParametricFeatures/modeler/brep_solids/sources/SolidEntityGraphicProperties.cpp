#include "../headers/SolidEntityGraphicProperties.h"

SolidEntityGraphicProperties::SolidEntityGraphicProperties()
{
}

void SolidEntityGraphicProperties::addSurfaceFace(GraphicProperties*& newFace)
{
	this->mBrepFaces.push_back(newFace);
}

vector<GraphicProperties*> SolidEntityGraphicProperties::getSurfaceFacesVector()
{
	return this->mBrepFaces;
}

void SolidEntityGraphicProperties::addFaceBoundaryShape(ShapesGraphicProperties * bound)
{
	this->mFaceBoundaries.push_back(bound);
}

vector<ShapesGraphicProperties*> SolidEntityGraphicProperties::getSurfaceBoundaryShapes()
{
	return this->mFaceBoundaries;
}

void SolidEntityGraphicProperties::setBRepTypeEnum(int solidBentleyType)
{
	this->mBRepType = BRepTypeEnumUtils::getBRepTypeEnumByInt(solidBentleyType);
}

BRepTypeEnum SolidEntityGraphicProperties::getBRepTypeEnum()
{
	return this->mBRepType;
}

void SolidEntityGraphicProperties::addFacetTriangulated(vector<DPoint3d> face)
{
	this->mFacetTriangulatedVector.push_back(face);
}

vector<vector<DPoint3d>> SolidEntityGraphicProperties::getFacetTriangulated()
{
	return this->mFacetTriangulatedVector;
}
