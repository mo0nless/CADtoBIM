#pragma once

#include "SolidPrimitiveProperty.h"
#include "../../shapes/headers/ShapesGraphicProperties.h"

class RuledSweepGraphicProperties : public SolidPrimitiveProperty {

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