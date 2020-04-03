#include "../headers/RevolveReaderProperties.h"

RevolveReaderProperties::RevolveReaderProperties()
{
	this->angle = -1;
	this->minimumRadius = -1;
	this->maximumRadius = -1;
	this->centroidalRadius = -1;
}

double RevolveReaderProperties::getAngle()
{
	return this->angle;
}

void RevolveReaderProperties::setAngle(double newAngle)
{
	this->angle = newAngle;
}

double RevolveReaderProperties::getMinimumRadius()
{
	return this->minimumRadius;
}

void RevolveReaderProperties::setMinimumRadius(double newMinimumRadius)
{
	this->minimumRadius = newMinimumRadius;
}

double RevolveReaderProperties::getMaximumRadius()
{
	return this->maximumRadius;
}

void RevolveReaderProperties::setMaximumRadius(double newMaximumRadius)
{
	this->maximumRadius = newMaximumRadius;
}

double RevolveReaderProperties::getCentroidalRadius()
{
	return this->centroidalRadius;
}

void RevolveReaderProperties::setCentroidalRadius(double newCentroidalRadius)
{
	this->centroidalRadius = newCentroidalRadius;
}
