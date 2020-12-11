#include "../headers/TextGraphicProperties.h"


TextGraphicProperties::TextGraphicProperties()
{
}

double TextGraphicProperties::getHeight()
{
	return _height;
}

double TextGraphicProperties::getWidth()
{
	return _width;
}

void TextGraphicProperties::setHeightWidth(double h, double w)
{
	_height = h;
	_width = w;
}

string TextGraphicProperties::getTextString()
{
	return _text;
}

void TextGraphicProperties::setTextString(string s)
{
	_text = s;
}
