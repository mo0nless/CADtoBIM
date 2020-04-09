#pragma once

#include "ICurvesGraphicsProperties.h"

class LineStringGraphicProperties : public ICurveGraphicProperties
{
public:
	LineStringGraphicProperties();

	void setDirectionTanget(DPoint3d newDirTanget);
	DPoint3d getDirectionTangent();

private:
	DPoint3d mDirectionTangent;
	int mNumSegment;
};
