#pragma once
#include "CurveGraphicProperties.h"

using namespace Modeler::Curves;

namespace Modeler
{
	namespace Curves
	{
		class PointStringGraphicProperties : public CurveGraphicProperties
		{

		private:
			bool mIsPort = true;

		public:
			PointStringGraphicProperties();

			bool getIsPort();
			void setIsPort(bool value);
		};
	}
}
