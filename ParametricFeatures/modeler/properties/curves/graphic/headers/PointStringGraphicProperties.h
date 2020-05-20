#pragma once
#include "ICurvesGraphicsProperties.h"

class PointStringGraphicProperties: public ICurveGraphicProperties
{
public:
	PointStringGraphicProperties();
	
	bool getIsPort();
	void setIsPort(bool value);
private:

	bool mIsPort = true;
};

