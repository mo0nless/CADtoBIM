#pragma once

#include "CurveGraphicProperties.h"

class LineGraphicProperties: public CurveGraphicProperties
{

private:
	DVec3d mDirectionTangent;

public:
	LineGraphicProperties();

	void setDirectionTanget(DVec3d newDirTanget);
	DVec3d getDirectionTangent();


};
