#pragma once

#include "../../headers/GraphicProperties.h"
#include <vector>
#include "MSBsplineSurfaceGraphicProperties.h"

class BRepSolidsKernelEntity: public GraphicProperties
{
public:
	BRepSolidsKernelEntity();

	void addBSplineSurfaceFace(MSBsplineSurfaceGraphicProperties*& newFace);
	std::vector<MSBsplineSurfaceGraphicProperties*> getBSplineSurfaceFacesVector();

private:
	std::vector<MSBsplineSurfaceGraphicProperties*> mBrepFaces;
};
