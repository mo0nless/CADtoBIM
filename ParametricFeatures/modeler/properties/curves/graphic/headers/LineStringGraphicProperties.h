#pragma once

#include "CurveGraphicsProperties.h"

class LineStringGraphicProperties : public CurveGraphicProperties
{
public:
	LineStringGraphicProperties();

	void setDirectionTanget(DPoint3d newDirTanget);
	DPoint3d getDirectionTangent();

private:
	DPoint3d mDirectionTangent;
	int mNumSegment;
};
