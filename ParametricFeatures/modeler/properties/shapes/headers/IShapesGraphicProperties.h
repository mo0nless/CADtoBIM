#pragma once


#include "../../curves/graphic/headers/BsplineGraphicProperties.h"
#include "../../curves/graphic/headers/ArcGraphicProperties.h"
#include "../../curves/graphic/headers/InterpolationGraphicProperties.h"
#include "../../curves/graphic/headers/LineGraphicProperties.h"
#include "../../curves/graphic/headers/LineStringGraphicProperties.h"
#include "../../curves/graphic/headers/AkimaGraphicProperties.h"
#include "../../curves/graphic/headers/PointStringGraphicProperties.h"
#include "../../headers/GraphicProperties.h"
#include <vector>

class IShapesGraphicProperties: public GraphicProperties
{
public:
	IShapesGraphicProperties(CurvesShapeTypeEnum newShapeType);

	CurvesShapeTypeEnum getCurvesShapeTypeEnum();

	void setBoundaryTypeCurvesContainer(int boundaryBentleyType);
	CurvesBoundaryTypeEnum getBoundaryTypeCurvesContainer();

	void insertCurvesGraphicsProperties(ICurveGraphicProperties* newCurveGraphicProperties);
	std::vector<ICurveGraphicProperties*> getCurvesPrimitivesContainerVector();

	void setIsFilled(bool value);
	bool getIsFilled();

	bool getIsClosed() const;
	void setIsClosed(bool isClosed);

	DVec3d getNormal() const;
	void setNormal(DVec3d normal);

private:
	DVec3d mNormal;

	bool mIsFilled;
	bool mIsClosed;

	CurvesShapeTypeEnum mCurvesShapeTypeEnum;
	CurvesBoundaryTypeEnum mCurvesBoundaryType;
	std::vector<ICurveGraphicProperties*> mCurvesPrimitivesContainer;
};