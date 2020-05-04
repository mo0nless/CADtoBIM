#pragma once

#include "CurvesGraphicsProperties.h"

class BsplineGraphicProperties : public CurveGraphicProperties
{
public:
	BsplineGraphicProperties();

	void setOrder(size_t newOrder);
	int getOrder();

	int getDegree();

	void setIsClosed(bool newIsClosed);
	bool getIsCLosed();

	void setIsSelfIntersect(bool newIsSelfIntersect);
	bool getIsSelfIntersect();
	
	void setKnots(bvector<double> newKnots);
	std::vector<double> getKnots();
	int getNumberKnots();

	void setAreKnotsValid(bool value);
	bool getAreKnotsValid();

	void setKnotsMultiplicity(bvector<size_t> newMultiplicity);
	std::vector<int> getKnotsMultiplicity();
private:
	std::vector<double> mKnots;
	std::vector<int> mKnotsMultiplicity;
	int mNumberKnots;
	int mDegree;
	int mOrder;
	bool mIsClosed;
	bool mIsSelfIntersect;
	bool mKnotsValid;
};
