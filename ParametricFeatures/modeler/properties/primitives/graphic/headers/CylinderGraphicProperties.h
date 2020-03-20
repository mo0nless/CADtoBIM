#pragma once


class CylinderGraphicProperties {

private:
	double mRadius;
	double mHeight;

public:
	CylinderGraphicProperties();

	double getRadius();
	void setRadius(double newRadius);

	double getHeight();
	void setHeight(double newHeight);
};