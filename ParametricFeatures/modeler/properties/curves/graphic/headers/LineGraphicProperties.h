#pragma once

#include "CurveGraphicProperties.h"

class LineGraphicProperties: public CurveGraphicProperties
{
public:
	LineGraphicProperties();

	void setDirectionTanget(DPoint3d newDirTanget);
	DPoint3d getDirectionTangent();

private:
	DPoint3d mDirectionTangent;
};
