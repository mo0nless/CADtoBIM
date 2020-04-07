#pragma once

#include "ICurvesGraphicsProperties.h"

class LineGraphicProperties: public ICurveGraphicProperties
{
public:
	LineGraphicProperties();

	void setDirectionTanget(DPoint3d newDirTanget);
	DPoint3d getDirectionTangent();

private:
	DPoint3d mDirectionTangent;
};
