#pragma once

#include <DgnPlatform/ElementGeometry.h>
#include <vector>

class MSBsplineSurfaceGraphicProperties 
{
public:
	MSBsplineSurfaceGraphicProperties();

	void setControlPoints(std::vector<std::vector<DPoint3d>> newControlPoints, int numU, int numV);
	std::vector<std::vector<DPoint3d>> getControlPoints();

	int getNumUPoles();
	int getNumVPoles();

	void setUVOrder(size_t newUOrder, size_t newVOrder);
	int getUOrder();
	int getVOrder();

	int getUDegree();
	int getVDegree();

	void setUVIsClosed(bool newUIsClosed, bool newVIsClosed);
	bool getUIsCLosed();
	bool getVIsCLosed();

	void setIsSelfIntersect(bool newIsSelfIntersect);
	bool getIsSelfIntersect();

	void setUVKnots(bvector<double> newUKnots, bvector<double> newVKnots);
	std::vector<double> getUKnots();
	std::vector<double> getVKnots();

	void setUVKnotsMultiplicity(bvector<size_t> newUMultiplicity, bvector<size_t> newVMultiplicity);
	std::vector<int> getUKnotsMultiplicity();
	std::vector<int> getVKnotsMultiplicity();

	void setWeights(std::vector<std::vector<double>> newWeights);
	std::vector<std::vector<double>> getWeights();

	void setFaceId(int id);
	int getFaceId();

	void setNodeId(int id);
	int getNodeId();

	void setNumberOfBounds(int num);
	int getNumberOfBounds();

private:
	std::vector<std::vector<DPoint3d>> mControlPoints;

	int mNumberOfBounds;
	int mFaceId;
	int mNodeId;

	std::vector<std::vector<double>> mWeigths;
	std::vector<double> mUKnots;
	std::vector<double> mVKnots;

	std::vector<int> mUKnotsMultiplicity;
	std::vector<int> mVKnotsMultiplicity;	

	int mNumUPoles;
	int mNumVPoles;

	int mUDegree;
	int mVDegree;

	int mUOrder;
	int mVOrder;

	bool mUIsClosed;
	bool mVIsClosed;

	bool mIsSelfIntersect;
};

