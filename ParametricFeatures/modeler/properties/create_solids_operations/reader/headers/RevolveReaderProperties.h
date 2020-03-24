#pragma once

class RevolveReaderProperties {

private:
	double angle;
	double minimumRadius;
	double maximumRadius;
	double centroidalRadius;

public:
	RevolveReaderProperties();

	double getAngle();
	void setAngle(double newAngle);

	double getMinimumRadius();
	void setMinimumRadius(double newMinimumRadius);

	double getMaximumRadius();
	void setMaximumRadius(double newMaximumRadius);

	double getCentroidalRadius();
	void setCentroidalRadius(double newCentroidalRadius);
};