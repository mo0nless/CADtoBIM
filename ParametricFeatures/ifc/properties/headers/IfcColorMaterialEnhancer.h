#pragma once

/**
 * @file IfcColorMaterialEnhancer.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../stdafx.h"

#include "../../bundle/headers/IfcElementBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

using namespace Ifc::Bundle;
using namespace Common::Utilities;

namespace Ifc
{
	namespace Properties
	{
		/**
		 * @brief Ifc Color and Material Class Enhancer. Process the Color and Material to build to add to all the IfcElement
		 * 
		 * @remark the function is called by the class IfcBuilder
		 * @see IfcBuilder
		 */
		class IfcColorMaterialEnhancer {

		public:
			/**
			 * @brief Enhancer that handle the processing process
			 * 
			 * @param ifcBundleVector 
			 * @param file 
			 * @param ownerHistory 
			 */
			void enhance(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcOwnerHistory* ownerHistory);

		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();
			Ifc4::IfcOwnerHistory* _ownerHistory;

			/**
			 * @brief 
			 * 
			 * @param ifcGraphicPropertiesBundle 
			 * @param file 
			 */
			void processColour(IfcGraphicPropertiesBundle& ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Create 
			 * 
			 * @param color 
			 * @return Ifc4::IfcColourRgb* 
			 */
			Ifc4::IfcColourRgb* buildIfcColor(UInt32 color);

			/**
			 * @brief 
			 * 
			 * @param color 
			 * @return Ifc4::IfcColourRgb* 
			 */
			Ifc4::IfcColourRgb * buildIfcColor(RgbFactor color);

		};
	}
}