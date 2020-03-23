#include "../headers/ThickenReaderProperties.h"

ThickenReaderProperties::ThickenReaderProperties()
{
	this->thikness = -1;
}

double ThickenReaderProperties::getThikness()
{
	return this->thikness;
}

void ThickenReaderProperties::setThikness(double newThikness)
{
	this->thikness = newThikness;
}
