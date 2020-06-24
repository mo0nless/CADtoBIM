#pragma once

#include "CurveGraphicProperties.h"

class LineGraphicProperties: public CurveGraphicProperties
{
public:
	LineGraphicProperties();

	void setDirectionTanget(DVec3d newDirTanget);
	DVec3d getDirectionTangent();

private:
	DVec3d mDirectionTangent;
};
