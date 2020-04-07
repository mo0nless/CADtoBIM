
#pragma once


#include <DgnPlatform/ElementGeometry.h>

class GraphicProperty {

private:

	double volume;
	double area;

	DVec3d centroid; 

	DVec3d vectorAxisX;
	DVec3d vectorAxisY;
	DVec3d vectorAxisZ;

public:
	GraphicProperty() {};
	virtual ~GraphicProperty() {}

	double getArea();
	void setArea(double newArea);

	double getVolume();
	void setVolume(double newVolume);
	
	DVec3d getCentroid();
	void setCentroid(DVec3d newCentroid);
	
	void setVectorAxis(DVec3d newVectorAxisX, DVec3d newVectorAxisY, DVec3d newVectorAxisZ);
	DVec3d getVectorAxisX();
	DVec3d getVectorAxisY();
	DVec3d getVectorAxisZ();
};