#pragma once

/**
 * @file AkimaGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "CurveGraphicProperties.h"

using namespace Modeler::Curves;

namespace Modeler
{
	namespace Curves
	{
		/**
		 * @brief GraphicProperties Handle class for Akima Curve
		 * 
		 * @remark This class inherits the CurveGraphicProperties class
		 * @see CurveGraphicProperties
		 */
		class AkimaGraphicProperties : public CurveGraphicProperties
		{
		public:
			AkimaGraphicProperties();

		private:

		};
	}
}
