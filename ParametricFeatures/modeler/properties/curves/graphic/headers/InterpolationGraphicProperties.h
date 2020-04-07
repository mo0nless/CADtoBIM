#pragma once

#include "ICurvesGraphicsProperties.h"

class InterpolationGraphicProperties : public ICurveGraphicProperties
{
public:
	InterpolationGraphicProperties();

	void setOrder(size_t newOrder);
	int getOrder();

	int getDegree();

	void setIsPeriodic(bool newIsPeriodic);
	bool getIsPeriodic();

private:

	int mDegree;
	int mOrder;
	bool mIsPeriodic;
};
