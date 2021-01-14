#pragma once

#include "CurveGraphicProperties.h"

using namespace Modeler::Curves;

namespace Modeler
{
	namespace Curves
	{
		class InterpolationGraphicProperties : public CurveGraphicProperties
		{

		private:
			int mDegree;
			int mOrder;
			bool mIsPeriodic;

		public:
			InterpolationGraphicProperties();

			void setOrder(size_t newOrder);
			int getOrder();

			int getDegree();

			void setIsPeriodic(bool newIsPeriodic);
			bool getIsPeriodic();
		};
	}
}