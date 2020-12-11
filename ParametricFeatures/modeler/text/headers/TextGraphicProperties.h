#pragma once

#include "../../properties/headers/GraphicProperties.h"

class TextGraphicProperties : public GraphicProperties
{
public:
	TextGraphicProperties();
	double getHeight();
	double getWidth();
	void setHeightWidth(double h, double w);

	string getTextString();
	void setTextString(string s);

private:
	double _height, _width;
	string _text;
};
