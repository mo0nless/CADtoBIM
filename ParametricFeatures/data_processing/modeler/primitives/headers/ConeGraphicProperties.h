#pragma once

#include "SolidPrimitiveProperties.h"

class ConeGraphicProperties : public SolidPrimitiveProperties {

private:
	double _baseRadius;
	double _topRadius;
	double _height;
	DPoint3d _topOrigin;
	DPoint3d _baseOrigin;

public:
	ConeGraphicProperties(PrimitiveTypeEnum primitiveTypeEnum);

	double getBaseRadius();
	void setBaseRadius(double newBaseRadius);

	double getTopRadius();
	void setTopRadius(double newTopRadius);

	double getHeight();
	void setHeight(double newHeight);

	DPoint3d getTopOrigin();
	void setTopOrigin(DPoint3d newTopOrigin);

	DPoint3d getBaseOrigin();
	void setBaseOrigin(DPoint3d newBaseOrigin);

	string toString();
};