#pragma once

#include"SolidPrimitiveProperty.h"

class BoxGraphicProperties : public SolidPrimitiveProperty {

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