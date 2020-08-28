#pragma once

#include "SolidPrimitiveProperties.h"
#include "../../shapes/headers/ShapesGraphicProperties.h"

class ExtrusionGraphicProperties : public SolidPrimitiveProperties {

private:
	DVec3d mDirectionExtrusion;
	ShapesGraphicProperties* mShapesGraphicProperties;

	bool mIsSolid;

public:
	ExtrusionGraphicProperties();

	void setDirectionOfExtrusion(DVec3d newDirection);
	DVec3d getDirectionOfExtrusion();
	
	void setIsSolid(bool value);
	bool getIsSolid();	

	double getLegnthOfExtrusion();

	ShapesGraphicProperties* getShapesGraphicProperties();
	void setShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

};