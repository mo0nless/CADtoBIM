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

class ShapesGraphicProperties: public GraphicProperties
{
public:
	ShapesGraphicProperties(ShapesTypeEnum newShapeType);

	ShapesTypeEnum getCurvesShapeTypeEnum();

	void setFaceBoundID(int newFaceidentifier);
	std::vector<int> getFacesBoundIDs();

	void setBoundaryTypeCurvesContainer(int boundaryBentleyType);
	CurvesBoundaryTypeEnum getBoundaryTypeCurvesContainer();

	void insertCurvesGraphicsProperties(CurveGraphicProperties* newCurveGraphicProperties);
	std::vector<CurveGraphicProperties*> getCurvesPrimitivesContainerVector();

	void setIsFilled(bool value);
	bool getIsFilled();

	bool getIsClosed() const;
	void setIsClosed(bool isClosed);

	bool hasShapesGraphicsContainer() const;

	std::vector<ShapesGraphicProperties*> getShapesGraphicsContainer();

	DVec3d getNormal() const;
	void setNormal(DVec3d normal);

	void setStartEndPoints(DPoint3d start, DPoint3d end);
	DPoint3d getStartPoint();
	DPoint3d getEndPoint();

	void setNodeId(int id);
	int getNodeId();
	
	bool getHasSingleCurve();
	void setHasSingleCurve(bool value);

	void insertShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

	virtual ~ShapesGraphicProperties();

private:
	std::vector<int> mFaceBoundIdentifier;

	int mNodeId;

	DVec3d mNormal;

	DPoint3d mStartPoint;
	DPoint3d mEndPoint;
	DPoint3d mCentroid;

	bool mIsFilled;
	bool mIsClosed;
	bool mHasShapesGraphicsContainer;
	bool mIsSingleCurve;

	ShapesTypeEnum mCurvesShapeTypeEnum;
	CurvesBoundaryTypeEnum mCurvesBoundaryType;
	std::vector<CurveGraphicProperties*> mCurvesPrimitivesContainer;
	std::vector<ShapesGraphicProperties*> mShapesGraphicsContainer;
};