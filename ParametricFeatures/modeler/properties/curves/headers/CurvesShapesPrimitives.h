#pragma once

#include "../graphic/headers/BsplineGraphicProperties.h"
#include "../graphic/headers/ArcGraphicProperties.h"
#include "../graphic/headers/InterpolationGraphicProperties.h"
#include "../graphic/headers/LineGraphicProperties.h"
#include "../graphic/headers/AkimaGraphicProperties.h"
#include "../../headers/GraphicProperty.h"
#include <vector>

class CurvesShapesPrimitives: public GraphicProperty
{
public:
	CurvesShapesPrimitives(CurvesShapeTypeEnum newShapeType);

	void insertCurvesGraphicsProperties(ICurveGraphicProperties* newCurveGraphicProperties);
	std::vector<ICurveGraphicProperties*> getCurvesPrimitivesContainerVector();

	void setBoundaryTypeCurvesContainer(int boundaryBentleyType);
	CurvesBoundaryTypeEnum getBoundaryTypeCurvesContainer();

	CurvesShapeTypeEnum getCurvesShapeTypeEnum();

	void setIsFilled(bool value);
	bool getIsFilled();

	bool getIsClosed() const;
	void setIsClosed(bool isClosed);

	DVec3d getNormal() const;
	void setNormal(DVec3d normal);

private:
	bool mIsFilled;
	bool mIsClosed;

	DVec3d mNormal;
	
	CurvesShapeTypeEnum mCurvesShapeTypeEnum;
	CurvesBoundaryTypeEnum mCurvesBoundaryType;
	std::vector<ICurveGraphicProperties*> mCurvesPrimitivesContainer;

};
