#pragma once

class GraphicProperties {

private:
	double area;
	double volume;
	double radius;

public:
	GraphicProperties();

	double getArea();
	void setArea(double newArea);

	double getVolume();
	void setVolume(double newVolume);

	double getRadius();
	void setRadius(double newRadius);
};