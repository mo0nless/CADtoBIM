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

void TextGraphicProperties::setBackgroundColor(UInt32 fillColor)
{
	_bFillColor = fillColor;
}

UInt32 TextGraphicProperties::getBackgroundColor()
{
	return _bFillColor;
}

void TextGraphicProperties::setFontSize(double s)
{
	_fontSize = s;
}

double TextGraphicProperties::getFontSize()
{
	return _fontSize;
}

void TextGraphicProperties::setFontName(string s)
{
	_namefont = s;
}

string TextGraphicProperties::getFontName()
{
	return _namefont;
}

void TextGraphicProperties::setTextColor(UInt32 color)
{
	_textColor = color;
}

UInt32 TextGraphicProperties::getTextColor()
{
	return _textColor;
}
