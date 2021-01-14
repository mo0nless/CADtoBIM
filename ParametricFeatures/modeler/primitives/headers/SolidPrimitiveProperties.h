#pragma once

#include "../../../common/enums/headers/PrimitiveTypeEnum.h"
#include "../../properties/headers/GraphicProperties.h"

using namespace Common::Enums;
using namespace Modeler::Properties;

namespace Modeler
{
	namespace Primitives
	{
		class SolidPrimitiveProperties : public GraphicProperties {

		private:
			PrimitiveTypeEnum primitiveTypeEnum;
		public:
			SolidPrimitiveProperties(PrimitiveTypeEnum newPrimitiveTypeEnum);
			virtual ~SolidPrimitiveProperties() {}

			PrimitiveTypeEnum getPrimitiveTypeEnum();
		};
	}
}