#pragma once
class ExtrusionReaderProperties {

private:
	double mThickness;
	double mDistance;

public:
	ExtrusionReaderProperties();

	double getDistance();
	void setDistance(double newDistance);

	double getThickness();
	void setThickness(double newThikness);

};