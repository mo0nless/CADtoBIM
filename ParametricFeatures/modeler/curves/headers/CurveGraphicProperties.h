#pragma once

#include <sstream>

#include <DgnPlatform/ElementGeometry.h>
#include <vector>
#include "../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "../../../common/enums/headers/ShapesTypeEnum.h"

using namespace std; 
using namespace Common;
using namespace Common::Enums;
using namespace Common::Utilities;

class CurveGraphicProperties 
{

private:
	DPoint3d _startPoint;
	DPoint3d _endPoint;

	DPoint3d _UVstartPoint;
	DPoint3d _UVendPoint;

	int mNumCPoints;
	vector<DPoint3d> _controlPoints;
	vector<DPoint3d> _UVcontrolPoints;
	CurvesPrimitivesTypeEnum _curvesTypeEnum;

public:
	CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType);
	void setControlPoints(bvector<DPoint3d> newControlPoints);
	void setControlPoints(vector<DPoint3d> newControlPoints);
	vector<DPoint3d> getControlPoints();

	void setUVcontrolPoints(vector<DPoint3d> newControlPoints);
	vector<DPoint3d> getUVcontrolPoints();

	CurvesPrimitivesTypeEnum getCurvesTypeEnum();

	void setStartEndPoints(DPoint3d sPoint, DPoint3d ePoint);
	void setUVstartEndPoints(DPoint3d sPoint, DPoint3d ePoint);

	DPoint3d getUVstartPoint();
	DPoint3d getUVendPoint();

	DPoint3d getStartPoint();
	DPoint3d getEndPoint();

	virtual ~CurveGraphicProperties() {}; //Needed for dynamic cast at least one virtual function

	string toString();
};

