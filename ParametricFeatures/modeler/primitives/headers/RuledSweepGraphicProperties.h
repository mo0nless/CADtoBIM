#pragma once

#include "SolidPrimitiveProperties.h"
#include "../../shapes/headers/ShapesGraphicProperties.h"

class RuledSweepGraphicProperties : public SolidPrimitiveProperties {

private:
	std::vector<ShapesGraphicProperties*> mSectionCurvesVector;

public:
	RuledSweepGraphicProperties();

	std::vector<ShapesGraphicProperties*> getSectionCurvesVector();
	void addSectionCurve(ShapesGraphicProperties* newSectionCurve);

	double getWidth();
	void setWidth(double newWidth);

	double getHeight();
	void setHeight(double newHeight);
};