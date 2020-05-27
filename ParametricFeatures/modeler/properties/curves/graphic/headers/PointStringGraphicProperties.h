#pragma once
#include "CurveGraphicsProperties.h"

class PointStringGraphicProperties: public CurveGraphicProperties
{
public:
	PointStringGraphicProperties();
	
	bool getIsPort();
	void setIsPort(bool value);
private:

	bool mIsPort = true;
};

