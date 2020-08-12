
#pragma once


#include <DgnPlatform/ElementGeometry.h>

class GraphicProperties {

private:

	double volume;
	double area;

	DPoint3d origin;
	DVec3d centroid; 

	DVec3d vectorAxisX;
	DVec3d vectorAxisY;
	DVec3d vectorAxisZ;



public:
	GraphicProperties();
	virtual ~GraphicProperties() {}

	double getArea();
	void setArea(double newArea);

	double getVolume();
	void setVolume(double newVolume);
	
	DVec3d getCentroid();
	void setCentroid(DVec3d newCentroid);

	DPoint3d getOrigin();
	void setOrigin(DPoint3d newOrigin);
	
	void setVectorAxis(DVec3d newVectorAxisX, DVec3d newVectorAxisY, DVec3d newVectorAxisZ);
	DVec3d getVectorAxisX();
	DVec3d getVectorAxisY();
	DVec3d getVectorAxisZ();
};