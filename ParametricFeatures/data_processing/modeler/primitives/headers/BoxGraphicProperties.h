#pragma once

#include"SolidPrimitiveProperties.h"

class BoxGraphicProperties : public SolidPrimitiveProperties {

private:
	double _length;
	double _width;
	double _height;

public:
	BoxGraphicProperties();

	double getLength();
	void setLength(double newLength);

	double getWidth();
	void setWidth(double newWidth);

	double getHeight();
	void setHeight(double newHeight);

	string toString();
};