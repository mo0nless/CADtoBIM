#pragma once

#include "SolidPrimitiveProperties.h"

using namespace Modeler::Primitives;

namespace Modeler
{
	namespace Primitives
	{

		class SphereGraphicProperties : public SolidPrimitiveProperties {

		private:
			double _radius;

		public:
			SphereGraphicProperties();

			double getRadius();
			void setRadius(double newadius);

			string toString();
		};
	}
}