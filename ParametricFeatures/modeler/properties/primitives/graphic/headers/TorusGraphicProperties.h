#pragma once

class TorusGraphicProperties {

private:
	double mMinorRadius;
	double mMajorRadius;
	double mSweepRadians;

public:
	TorusGraphicProperties();

	double getMinorRadius();
	void setMinorRadius(double newMinorRadius);

	double getMajorRadius();
	void setMajorRadius(double newMajorRadius);

	double getSweepRadians();
	void setSweepRadians(double newSweepRadians);
};