#pragma once

//#include <DgnPlatform/ElementGraphics.h>
#include <DgnPlatform/ElementGeometry.h>

class CurveGraphicProperties
{
public:
	CurveGraphicProperties();

	void setDegree(int newDegree);
	int getDegree();

	void setIsClosed(bool newIsClosed);
	bool getIsCLosed();

	void setIsSelfIntersect(bool newIsSelfIntersect);
	bool getIsSelfIntersect();

	void setControlPoints(bvector<DPoint3d> newControlPoints);
	bvector<DPoint3d> getControlPoints();

private:
	int degree;
	bool isClosed;
	bool isSelfIntersect;
	bvector<DPoint3d> controlPoints;
};
