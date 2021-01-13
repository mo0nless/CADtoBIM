#pragma once

#include "../../curves/headers/CurveGraphicProperties.h"
#include "../../curves/headers/BsplineGraphicProperties.h"
#include "../../curves/headers/ArcGraphicProperties.h"
#include "../../curves/headers/InterpolationGraphicProperties.h"
#include "../../curves/headers/LineGraphicProperties.h"
#include "../../curves/headers/LineStringGraphicProperties.h"
#include "../../curves/headers/AkimaGraphicProperties.h"
#include "../../curves/headers/PointStringGraphicProperties.h"
#include "../../properties/headers/GraphicProperties.h"
#include <vector>

using namespace std;
using namespace Common;
using namespace Common::Enums;
using namespace Common::Utilities;

class ShapesGraphicProperties: public GraphicProperties
{
public:
	ShapesGraphicProperties();

	void addFaceBoundID(int newFaceidentifier);
	vector<int> getFacesBoundIDs();

	void setBoundaryTypeCurvesContainer(int boundaryBentleyType);
	CurvesBoundaryTypeEnum getBoundaryTypeCurvesContainer();

	void insertCurvesGraphicsProperties(CurveGraphicProperties* newCurveGraphicProperties);
	vector<CurveGraphicProperties*> getCurvesPrimitivesContainerVector();

	void setIsFilled(bool value);
	bool getIsFilled();

	bool getIsClosed() const;
	void setIsClosed(bool isClosed);

	bool hasShapesGraphicsContainer() const;

	vector<ShapesGraphicProperties*> getShapesGraphicsContainer();

	DVec3d getNormal() const;
	void setNormal(DVec3d normal);

	void setStartEndPoints(DPoint3d start, DPoint3d end);
	DPoint3d getStartPoint();
	DPoint3d getEndPoint();

	void setUVstartEndPoints(DPoint3d sPoint, DPoint3d ePoint);

	DPoint3d getUVstartPoint();
	DPoint3d getUVendPoint();

	void setNodeId(int id);
	int getNodeId();
	
	bool getHasSingleCurve();
	void setHasSingleCurve(bool value);

	void insertShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

	virtual ~ShapesGraphicProperties();

	//TEMP
	string type = "";
	bool isPartOfLoop = false;

	string toString();

private:
	vector<int> _faceBoundIdentifiers;

	int _nodeId;

	DVec3d _normal;

	DPoint3d mStartPoint;
	DPoint3d mEndPoint;
	DPoint3d mCentroid;
	
	DPoint3d mUVstartPoint;
	DPoint3d mUVendPoint;

	bool _isFilled;
	bool _isClosed;
	bool _hasShapesGraphicsContainer;
	bool _isSingleCurve;

	ShapesTypeEnum _curvesShapeTypeEnum;
	CurvesBoundaryTypeEnum _curvesBoundaryType;
	vector<CurveGraphicProperties*> _curvesPrimitivesContainer;
	vector<ShapesGraphicProperties*> _shapesGraphicsContainer;
};