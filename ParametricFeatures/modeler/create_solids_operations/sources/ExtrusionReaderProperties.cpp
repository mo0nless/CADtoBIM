#include "../headers/ExtrusionReaderProperties.h"

ExtrusionReaderProperties::ExtrusionReaderProperties()
{
	this->mThickness = -1;
}

double ExtrusionReaderProperties::getDistance()
{
	return this->mDistance;
}

void ExtrusionReaderProperties::setDistance(double newDistance)
{
	this->mDistance = newDistance;
}

double ExtrusionReaderProperties::getThickness()
{
	return this->mThickness;
}

void ExtrusionReaderProperties::setThickness(double newThikness)
{
	this->mThickness = newThikness;
}
