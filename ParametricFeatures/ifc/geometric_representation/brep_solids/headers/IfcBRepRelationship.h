#pragma once


#include "../../../../stdafx.h"
#include "../../../bundle/headers/IfcElementBundle.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../../../modeler/shapes/headers/ShapesGraphicProperties.h"

using namespace Ifc::Bundle;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		class IfcBRepRelationship
		{
		public:
			IfcBRepRelationship();

			void processBRepEntityEdge(ShapesGraphicProperties* shapeGraphicProperties, vector<Ifc4::IfcCurve*> curveRepresentationVec, int boundType);
			void connectContinuosEdges();

			vector<SolidEdge*> getSmartSolidEdgesCollection();

		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			bool processContinuosEdges(ContinuosEdge*& head, ContinuosEdge*& currentEdge);
			vector<SolidEdge*> mSmartSolidEdgesCollection;
			vector<ContinuosEdge*> mContinuosEdgeList;
		};
	}
}

