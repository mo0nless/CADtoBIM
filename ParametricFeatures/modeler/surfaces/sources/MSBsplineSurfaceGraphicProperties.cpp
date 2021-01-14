#include "../headers/MSBsplineSurfaceGraphicProperties.h"

using namespace Modeler::Surfaces;

MSBsplineSurfaceGraphicProperties::MSBsplineSurfaceGraphicProperties()
{
	this->mUDegree = 0;
	this->mUOrder = 0;
	this->mVDegree = 0;
	this->mVOrder = 0;
	this->mIsSelfIntersect = false;
	this->mUIsClosed = false;
	this->mVIsClosed = false;
	this->mUKnots = vector<double>();
	this->mUKnotsMultiplicity = vector<int>();
	this->mVKnots = vector<double>();
	this->mVKnotsMultiplicity = vector<int>();
	this->mControlPoints = vector<vector<DPoint3d>>();
	this->mNumUPoles = 0;
	this->mNumVPoles = 0;
	this->mNodeId = -1;
	this->mFaceId = -1;
	this->mSurfaceBoundary = nullptr;
}

void MSBsplineSurfaceGraphicProperties::setControlPoints(vector<vector<DPoint3d>> newControlPoints, int numU, int numV)
{
	this->mControlPoints = newControlPoints;
	this->mNumUPoles = numU;
	this->mNumVPoles = numV;
};

vector<vector<DPoint3d>> MSBsplineSurfaceGraphicProperties::getControlPoints()
{
	return this->mControlPoints;
}
int MSBsplineSurfaceGraphicProperties::getNumUPoles()
{
	return this->mNumUPoles;
}
int MSBsplineSurfaceGraphicProperties::getNumVPoles()
{
	return this->mNumVPoles;
}

void MSBsplineSurfaceGraphicProperties::setUVOrder(size_t newUOrder, size_t newVOrder)
{
	this->mUOrder = int(newUOrder);
	this->mUDegree = mUOrder - 1; // A spline function of order N is a piecewise polynomial function of degree N-1 

	this->mVOrder = int(newVOrder);
	this->mVDegree = mVOrder - 1; // A spline function of order N is a piecewise polynomial function of degree N-1 
}

int MSBsplineSurfaceGraphicProperties::getUOrder()
{
	return this->mUOrder;
}

int MSBsplineSurfaceGraphicProperties::getVOrder()
{
	return this->mVOrder;
}

int MSBsplineSurfaceGraphicProperties::getUDegree()
{
	return this->mUDegree;
}

int MSBsplineSurfaceGraphicProperties::getVDegree()
{
	return this->mVDegree;
}

void MSBsplineSurfaceGraphicProperties::setUVIsClosed(bool newUIsClosed, bool newVIsClosed)
{
	this->mUIsClosed = newUIsClosed;
	this->mVIsClosed = newVIsClosed;
}

bool MSBsplineSurfaceGraphicProperties::getUIsCLosed()
{
	return this->mUIsClosed;
}

bool MSBsplineSurfaceGraphicProperties::getVIsCLosed()
{
	return this->mVIsClosed;
}

void MSBsplineSurfaceGraphicProperties::setIsSelfIntersect(bool newIsSelfIntersect)
{
	this->mIsSelfIntersect = newIsSelfIntersect;
}

bool MSBsplineSurfaceGraphicProperties::getIsSelfIntersect()
{
	return this->mIsSelfIntersect;
}

void MSBsplineSurfaceGraphicProperties::setUVKnots(bvector<double> newUKnots, bvector<double> newVKnots)
{
	for each (double knotU in newUKnots)
	{
		this->mUKnots.push_back(knotU);
	}
	for each (double knotV in newVKnots)
	{
		this->mVKnots.push_back(knotV);
	}
}

vector<double> MSBsplineSurfaceGraphicProperties::getUKnots()
{
	return this->mUKnots;
}

vector<double> MSBsplineSurfaceGraphicProperties::getVKnots()
{
	return this->mVKnots;
}

void MSBsplineSurfaceGraphicProperties::setUVKnotsMultiplicity(bvector<size_t> newUMultiplicity, bvector<size_t> newVMultiplicity)
{
	for each (size_t mU in newUMultiplicity)
	{
		this->mUKnotsMultiplicity.push_back(int(mU));
	}
	for each (size_t mV in newVMultiplicity)
	{
		this->mVKnotsMultiplicity.push_back(int(mV));
	}
}

vector<int> MSBsplineSurfaceGraphicProperties::getUKnotsMultiplicity()
{
	return this->mUKnotsMultiplicity;
}

vector<int> MSBsplineSurfaceGraphicProperties::getVKnotsMultiplicity()
{
	return this->mVKnotsMultiplicity;
}

void MSBsplineSurfaceGraphicProperties::setWeights(vector<vector<double>> newWeights)
{
	this->mWeigths = newWeights;
	
}

vector<vector<double>> MSBsplineSurfaceGraphicProperties::getWeights()
{
	return this->mWeigths;
}

void MSBsplineSurfaceGraphicProperties::setFaceId(FaceId id)
{
	this->mBentleyFaceId = id;
}

FaceId MSBsplineSurfaceGraphicProperties::getBFaceId()
{
	return this->mBentleyFaceId;
}

void MSBsplineSurfaceGraphicProperties::setFaceId(int id)
{
	this->mFaceId = id;
}

int MSBsplineSurfaceGraphicProperties::getFaceId()
{
	return this->mFaceId;
}

void MSBsplineSurfaceGraphicProperties::setNodeId(int id)
{
	this->mNodeId = id;
}

int MSBsplineSurfaceGraphicProperties::getNodeId()
{
	return this->mNodeId;
}

void MSBsplineSurfaceGraphicProperties::setNumberOfBounds(int num)
{
	this->mNumberOfBounds = num;
}

int MSBsplineSurfaceGraphicProperties::getNumberOfBounds()
{
	return this->mNumberOfBounds;
}

void MSBsplineSurfaceGraphicProperties::setBoundsVectorPoints(vector<vector<DPoint3d>> bounds)
{
	this->mBoundsVectorPoints = bounds;
}

vector<vector<DPoint3d>> MSBsplineSurfaceGraphicProperties::getBoundsVectorPoints()
{
	return this->mBoundsVectorPoints;
}

void MSBsplineSurfaceGraphicProperties::addSurfaceBoundaryShape(ShapesGraphicProperties * bound)
{
	this->mSurfaceBoundary = bound;
}

ShapesGraphicProperties* MSBsplineSurfaceGraphicProperties::getSurfaceBoundaryShape()
{
	return this->mSurfaceBoundary;
}

