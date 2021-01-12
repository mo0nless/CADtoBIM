#pragma once


#include "../../../stdafx.h"
#include "../../bundle/headers/IfcElementBundle.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../../modeler/shapes/headers/ShapesGraphicProperties.h"

using namespace Ifc::Bundle;

class IfcBRepRelationship
{
public:
	IfcBRepRelationship();

	void processBRepEntityEdge(ShapesGraphicProperties* shapeGraphicProperties, vector<Ifc4::IfcCurve*> curveRepresentationVec, int boundType);
	void connectContinuosEdges();

	vector<SolidEdge*> getSmartSolidEdgesCollection();

private:	
	Logs::Logger* _logger = Logs::Logger::getLogger();

	bool processContinuosEdges(ContinuosEdge*& head, ContinuosEdge*& currentEdge);
	vector<SolidEdge*> mSmartSolidEdgesCollection;
	vector<ContinuosEdge*> mContinuosEdgeList;
};


