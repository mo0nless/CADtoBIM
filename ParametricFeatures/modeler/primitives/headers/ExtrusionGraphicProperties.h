#pragma once

#include "SolidPrimitiveProperties.h"
#include "../../shapes/headers/ShapesGraphicProperties.h"

class ExtrusionGraphicProperties : public SolidPrimitiveProperties {

private:
	DVec3d _directionExtrusion;
	ShapesGraphicProperties* _shapesGraphicProperties;

	bool _isSolid;

public:
	ExtrusionGraphicProperties();

	void setDirectionOfExtrusion(DVec3d newDirection);
	DVec3d getDirectionOfExtrusion();
	
	void setIsSolid(bool value);
	bool getIsSolid();	

	double getLegnthOfExtrusion();

	ShapesGraphicProperties* getShapesGraphicProperties();
	void setShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

	string toString();

};