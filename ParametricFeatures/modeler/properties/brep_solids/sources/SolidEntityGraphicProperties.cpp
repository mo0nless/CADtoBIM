#include "../headers/SolidEntityGraphicProperties.h"

SolidEntityGraphicProperties::SolidEntityGraphicProperties()
{
}

void SolidEntityGraphicProperties::addBSplineSurfaceFace(MSBsplineSurfaceGraphicProperties*& newFace)
{
	this->mBrepFaces.push_back(newFace);
}

std::vector<MSBsplineSurfaceGraphicProperties*> SolidEntityGraphicProperties::getBSplineSurfaceFacesVector()
{
	return this->mBrepFaces;
}

void SolidEntityGraphicProperties::addFaceBoundaryShape(ShapesGraphicProperties * bound)
{
	this->mFaceBoundaries.push_back(bound);
}

std::vector<ShapesGraphicProperties*> SolidEntityGraphicProperties::getSurfaceBoundaryShapes()
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

void SolidEntityGraphicProperties::addFacetTriangulated(std::vector<DPoint3d> face)
{
	this->mFacetTriangulatedVector.push_back(face);
}

std::vector<std::vector<DPoint3d>> SolidEntityGraphicProperties::getFacetTriangulated()
{
	return this->mFacetTriangulatedVector;
}
