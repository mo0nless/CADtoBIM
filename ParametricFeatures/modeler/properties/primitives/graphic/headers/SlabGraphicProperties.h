#pragma once

class SlabGraphicProperties {

private:
	double mLength;
	double mWidth;
	double mHeight;

public:
	SlabGraphicProperties();

	double getLength();
	void setLength(double newLength);

	double getWidth();
	void setWidth(double newWidth);

	double getHeight();
	void setHeight(double newHeight);
};