#pragma once

class ConeGraphicProperties {

private:
	double baseRadius;
	double topRadius;
	double height;

public:
	ConeGraphicProperties();

	double getBaseRadius();
	void setBaseRadius(double newBaseRadius);

	double getTopRadius();
	void setTopRadius(double newTopRadius);

	double getHeight();
	void setHeight(double newHeight);

};