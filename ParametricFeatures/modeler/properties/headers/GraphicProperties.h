#pragma once

#include "../primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../curves/headers/CurvesPrimitivesContainer.h"

/**
 *   Class contains needed graphic properties
 */
class GraphicProperties {

private:
	double mArea;
	double mVolume;

	DVec3d mCentroid;

	DVec3d mVectorAxisX;
	DVec3d mVectorAxisY;
	DVec3d mVectorAxisZ;

	PrimitiveGraphicProperties* pPrimitiveGraphicProperties;
	CurvesPrimitivesContainer* pCurvesPrimitivesContainer;

public:
	GraphicProperties();

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

	bool tryGetCurvesPrimitivesContainer(CurvesPrimitivesContainer*& curvesPrimitivesContainersR);
	void setCurvesPrimitivesContainer(CurvesPrimitivesContainer* newCurvesPrimitivesContainer);

	bool tryGetPrimitiveGraphicProperties(PrimitiveGraphicProperties*& primitiveGraphicPropertiesR);
	void setPrimitiveGraphicProperties(PrimitiveGraphicProperties* newPrimitiveGraphicProperties);
};