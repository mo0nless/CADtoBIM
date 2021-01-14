#pragma once

#include "SolidPrimitiveProperties.h"
#include "../../shapes/headers/ShapesGraphicProperties.h"

using namespace Modeler::Shapes; 
using namespace Modeler::Primitives;

namespace Modeler
{
	namespace Primitives
	{

		class RuledSweepGraphicProperties : public SolidPrimitiveProperties {

		private:
			vector<ShapesGraphicProperties*> mSectionCurvesVector;

		public:
			RuledSweepGraphicProperties();

			vector<ShapesGraphicProperties*> getSectionCurvesVector();
			void addSectionCurve(ShapesGraphicProperties* newSectionCurve);

			double getWidth();
			void setWidth(double newWidth);

			double getHeight();
			void setHeight(double newHeight);
		};
	}
}