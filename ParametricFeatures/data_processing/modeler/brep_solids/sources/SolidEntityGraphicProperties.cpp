#include "../headers/SolidEntityGraphicProperties.h"

SolidEntityGraphicProperties::SolidEntityGraphicProperties()
{
}

void SolidEntityGraphicProperties::addSolidOrSurfaceFace(GraphicProperties*& newFace)
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

void SolidEntityGraphicProperties::addMeshTriangulated(MeshTriangles* mesh)
{
	this->mMeshTriangulatedVector.push_back(mesh);
}

vector<MeshTriangles*> SolidEntityGraphicProperties::getMeshTriangulated()
{
	return this->mMeshTriangulatedVector;
}
