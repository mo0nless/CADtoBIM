#include "../headers/RuledSweepGraphicProperties.h"

RuledSweepGraphicProperties::RuledSweepGraphicProperties(): SolidPrimitiveProperties(PrimitiveTypeEnum::RULED_SWEEP)
{
}

vector<ShapesGraphicProperties*> RuledSweepGraphicProperties::getSectionCurvesVector()
{
	return this->mSectionCurvesVector;
}

void RuledSweepGraphicProperties::addSectionCurve(ShapesGraphicProperties * newSectionCurve)
{
	this->mSectionCurvesVector.push_back(newSectionCurve);
}
