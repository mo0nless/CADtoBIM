#pragma once

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

/**
 *   Class contains needed graphic properties
 */
class GraphicProperties {

private:
	double area;
	double volume;
	double radius;

	DVec3d centroid;
	RotMatrix rotMatrix;
	DVec3d momentxyz;

	DVec3d vectorBaseX;
	DVec3d vectorBaseY;
	DVec3d vectorBaseZ;

	double slabLength;
	double slabWidth;
	double slabHeight;


public:
	GraphicProperties();

	double getArea();
	void setArea(double newArea);

	double getVolume();
	void setVolume(double newVolume);

	double getRadius();
	void setRadius(double newRadius);

	DVec3d getCentroid();
	void setCentroid(DVec3d newCentroid);

	DVec3d getVectorBaseX();
	void setVectorBaseX(DVec3d newVectorBaseX);
	
	DVec3d getVectorBaseY();
	void setVectorBaseY(DVec3d newVectorBaseY);

	DVec3d getVectorBaseZ();
	void setVectorBaseZ(DVec3d newVectorBaseZ);

	RotMatrix getRotMatrixAxis();
	void setRotMatrixAxis(RotMatrix rotationMatrix);

	double getSlabLength();
	void setSlabLength(double newSlabLength);


	double getSlabWidth();
	void setSlabWidth(double newSlabWidth);

	double getSlabHeight();
	void setSlabHeight(double newSlabHeight);

};