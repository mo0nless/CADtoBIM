#pragma once


#include "../../../stdafx.h"
#include "../../main/headers/IfcElementBundle.h"
//#include "../../../enhancer/headers/IfcOperationsHelper.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../../modeler/shapes/headers/ShapesGraphicProperties.h"
//#include <vector>

class IfcBRepRelationship
{
public:
	IfcBRepRelationship();

	void processBRepEntityEdge(ShapesGraphicProperties* shapeGraphicProperties, vector<Ifc4::IfcCurve*> curveRepresentationVec, int boundType);
	void connectContinuosEdges();

	vector<SolidEdge*> getSmartSolidEdgesCollection();

private:	
	bool processContinuosEdges(ContinuosEdge*& head, ContinuosEdge*& currentEdge);
	vector<SolidEdge*> mSmartSolidEdgesCollection;
	vector<ContinuosEdge*> mContinuosEdgeList;
};


