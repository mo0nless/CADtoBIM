#pragma once

class SlabGraphicProperties {

private:
	double length;
	double width;
	double height;

public:
	SlabGraphicProperties();

	double getLength();
	void setLength(double newLength);

	double getWidth();
	void setWidth(double newWidth);

	double getHeight();
	void setHeight(double newHeight);
};