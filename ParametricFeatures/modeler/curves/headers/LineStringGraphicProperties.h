#pragma once

#include "CurveGraphicProperties.h"

class LineStringGraphicProperties : public CurveGraphicProperties
{

private:
	DPoint3d mDirectionTangent;
	int mNumSegment;

public:
	LineStringGraphicProperties();

	void setDirectionTanget(DPoint3d newDirTanget);
	DPoint3d getDirectionTangent();


};
