#pragma once


class CylinderGraphicProperties {

private:
	double radius;
	double height;

public:
	CylinderGraphicProperties();

	double getRadius();
	void setRadius(double newRadius);

	double getHeight();
	void setHeight(double newHeight);
};