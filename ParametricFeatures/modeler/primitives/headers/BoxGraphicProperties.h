#pragma once

#include"SolidPrimitiveProperties.h"

class BoxGraphicProperties : public SolidPrimitiveProperties {

private:
	double mLength;
	double mWidth;
	double mHeight;

public:
	BoxGraphicProperties();

	double getLength();
	void setLength(double newLength);

	double getWidth();
	void setWidth(double newWidth);

	double getHeight();
	void setHeight(double newHeight);
};