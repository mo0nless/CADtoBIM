#pragma once

class TorusGraphicProperties {

private:
	double minorRadius;
	double majorRadius;
	double sweepRadians;

public:
	TorusGraphicProperties();

	double getMinorRadius();
	void setMinorRadius(double newMinorRadius);

	double getMajorRadius();
	void setMajorRadius(double newMajorRadius);

	double getSweepRadians();
	void setSweepRadians(double newSweepRadians);
};