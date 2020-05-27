#include "../headers/BRepSolidsKernelEntity.h"

BRepSolidsKernelEntity::BRepSolidsKernelEntity()
{
}

void BRepSolidsKernelEntity::addBSplineSurfaceFace(MSBsplineSurfaceGraphicProperties*& newFace)
{
	this->mBrepFaces.push_back(newFace);
}

std::vector<MSBsplineSurfaceGraphicProperties*> BRepSolidsKernelEntity::getBSplineSurfaceFacesVector()
{
	return this->mBrepFaces;
}
