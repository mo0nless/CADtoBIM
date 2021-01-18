#pragma once

/**
 * @file SolidPrimitiveProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../common/enums/headers/PrimitiveTypeEnum.h"
#include "../../properties/headers/GraphicProperties.h"

using namespace Common::Enums;
using namespace Modeler::Properties;

namespace Modeler
{
	namespace Primitives
	{
		/**
		 * @brief GraphicProperties Handle class for Base solid primitive
		 * 
		 * @remark This class inherits the GraphicProperties class
		 * @see GraphicProperties
		 */
		class SolidPrimitiveProperties : public GraphicProperties {

		private:
			PrimitiveTypeEnum primitiveTypeEnum;
		public:
			/**
			 * @brief Construct a new Solid Primitive Properties object
			 * 
			 * @param newPrimitiveTypeEnum the primitive type
			 */
			SolidPrimitiveProperties(PrimitiveTypeEnum newPrimitiveTypeEnum);
			virtual ~SolidPrimitiveProperties() {}

			/**
			 * @brief Get the Primitive Type Enum object
			 * 
			 * @return PrimitiveTypeEnum 
			 */
			PrimitiveTypeEnum getPrimitiveTypeEnum();
		};
	}
}