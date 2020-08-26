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

	void processBRepEntityEdge(ShapesGraphicProperties* shapeGraphicProperties, std::vector<Ifc4::IfcCurve*> curveRepresentationVec, int boundType);
	void connectContinuosEdges();

	std::vector<SolidEdge*> getSmartSolidEdgesCollection();

private:	
	bool processContinuosEdges(ContinuosEdge*& head, ContinuosEdge*& currentEdge);
	std::vector<SolidEdge*> mSmartSolidEdgesCollection;
	std::vector<ContinuosEdge*> mContinuosEdgeList;
};


