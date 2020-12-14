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

	void setBackgroundColor(UInt32 fillColor);//, UInt32 borderColor, UInt32 borderWeight, Int32 borderLineStyle, DPoint2d borderPadding);
	UInt32 getBackgroundColor();

	UInt32 getBorderColor();
	UInt32 getBorderWeight();
	Int32 getBorderLineStyle();
	DPoint2d getBorderPadding();

	void setFontSize(double s);
	double getFontSize();

	void setFontName(string s);
	string getFontName();

	void setTextColor(UInt32 color);
	UInt32 getTextColor();
private:
	double _height, _width, _fontSize;
	string _text, _namefont;

	UInt32 _bFillColor, _borderColor, _borderWeight, _textColor;
	Int32 _borderLineStyle;
	DPoint2d _borderPadding;
};
