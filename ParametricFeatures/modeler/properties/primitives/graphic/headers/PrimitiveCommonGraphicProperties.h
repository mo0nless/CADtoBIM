#pragma once

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

class PrimitiveCommonGraphicProperties {

private:
	double area;
	double volume;

	DVec3d centroid;

	DVec3d vectorAxisX;
	DVec3d vectorAxisY;
	DVec3d vectorAxisZ;

public:
	PrimitiveCommonGraphicProperties();

	double getArea();
	void setArea(double newArea);

	double getVolume();
	void setVolume(double newVolume);

	DVec3d getCentroid();
	void setCentroid(DVec3d newCentroid);

	DVec3d getVectorAxisX();
	void setVectorAxisX(DVec3d newVectorBaseX);

	DVec3d getVectorAxisY();
	void setVectorAxisY(DVec3d newVectorBaseY);

	DVec3d getVectorAxisZ();
	void setVectorAxisZ(DVec3d newVectorBaseZ);
};