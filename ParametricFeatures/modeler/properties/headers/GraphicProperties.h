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
	RotMatrix axes;
	DVec3d momentxyz;

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

	RotMatrix getAxes();
	void setAxes(RotMatrix newAxes);

	DVec3d getMomentxyz();
	void setMomentxyz(DVec3d newMomentxyz);
};