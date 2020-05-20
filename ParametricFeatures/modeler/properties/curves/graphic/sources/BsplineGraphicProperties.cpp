#include "../headers/BsplineGraphicProperties.h"

BsplineGraphicProperties::BsplineGraphicProperties():ICurveGraphicProperties(CurvesPrimitivesTypeEnum::BSPLINE)
{
	this->mDegree = 0;
	this->mOrder = 0;
	this->mIsSelfIntersect = false;
	this->mIsClosed = false;
	this->mKnots = std::vector<double>();
	this->mNumberKnots = 0;
	this->mKnotsValid = false;
	this->mKnotsMultiplicity = std::vector<int>();
}

void BsplineGraphicProperties::setOrder(size_t newOrder)
{
	this->mOrder = int(newOrder);
	this->mDegree = mOrder - 1; // A spline function of order N is a piecewise polynomial function of degree N-1 
}

int BsplineGraphicProperties::getOrder()
{
	return this->mOrder;
}

int BsplineGraphicProperties::getDegree()
{
	return this->mDegree;
}

void BsplineGraphicProperties::setIsClosed(bool newIsClosed)
{
	this->mIsClosed = newIsClosed;
}

bool BsplineGraphicProperties::getIsCLosed()
{
	return this->mIsClosed;
}

void BsplineGraphicProperties::setIsSelfIntersect(bool newIsSelfIntersect)
{
	this->mIsSelfIntersect = newIsSelfIntersect;
}

bool BsplineGraphicProperties::getIsSelfIntersect()
{
	return this->mIsSelfIntersect;
}

void BsplineGraphicProperties::setKnots(bvector<double> newKnots)
{
	for each (double knot in newKnots)
	{
		this->mKnots.push_back(knot);
	}
	this->mNumberKnots = int(mKnots.size());
}

std::vector<double> BsplineGraphicProperties::getKnots()
{
	return this->mKnots;
}

int BsplineGraphicProperties::getNumberKnots()
{
	return this->mNumberKnots;
}

void BsplineGraphicProperties::setAreKnotsValid(bool value)
{
	this->mKnotsValid = value;
}

bool BsplineGraphicProperties::getAreKnotsValid()
{
	return this->mKnotsValid;
}

void BsplineGraphicProperties::setKnotsMultiplicity(bvector<size_t> newMultiplicity)
{
	for each (size_t m in newMultiplicity)
	{
		this->mKnotsMultiplicity.push_back(int(m));

	}
}

std::vector<int> BsplineGraphicProperties::getKnotsMultiplicity()
{
	return this->mKnotsMultiplicity;
}


