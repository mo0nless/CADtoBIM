#pragma once

#include "CurveGraphicProperties.h"

using namespace Modeler::Curves;

namespace Modeler
{
	namespace Curves
	{
		class LineStringGraphicProperties : public CurveGraphicProperties
		{

		private:
			DPoint3d mDirectionTangent;
			int mNumSegment;

		public:
			LineStringGraphicProperties();

			void setDirectionTanget(DPoint3d newDirTanget);
			DPoint3d getDirectionTangent();

		};
	}
}