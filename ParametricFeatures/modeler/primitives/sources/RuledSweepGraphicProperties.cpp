#include "../headers/RuledSweepGraphicProperties.h"

RuledSweepGraphicProperties::RuledSweepGraphicProperties(): SolidPrimitiveProperties(PrimitiveTypeEnum::RULED_SWEEP)
{
}

std::vector<ShapesGraphicProperties*> RuledSweepGraphicProperties::getSectionCurvesVector()
{
	return this->mSectionCurvesVector;
}

void RuledSweepGraphicProperties::addSectionCurve(ShapesGraphicProperties * newSectionCurve)
{
	this->mSectionCurvesVector.push_back(newSectionCurve);
}
