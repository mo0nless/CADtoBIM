#pragma once

#include "CurveGraphicProperties.h"

class BsplineGraphicProperties : public CurveGraphicProperties
{

private:
	vector<double> mKnots;
	vector<int> mKnotsMultiplicity;

	int mNumberKnots;
	int mDegree;
	int mOrder;

	bool mIsClosed;
	bool mIsSelfIntersect;
	bool mKnotsValid;

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
	vector<double> getKnots();
	int getNumberKnots();

	void setAreKnotsValid(bool value);
	bool getAreKnotsValid();

	void setKnotsMultiplicity(bvector<size_t> newMultiplicity);
	vector<int> getKnotsMultiplicity();


};
