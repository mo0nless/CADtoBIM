#pragma once
#include "CurveGraphicProperties.h"

class PointStringGraphicProperties: public CurveGraphicProperties
{

private:
	bool mIsPort = true;

public:
	PointStringGraphicProperties();
	
	bool getIsPort();
	void setIsPort(bool value);

};

