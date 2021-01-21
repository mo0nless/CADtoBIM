#pragma once

/**
 * @file IfcTextEnhancer.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../../stdafx.h"
#include "../../../bundle/headers/IfcElementBundle.h"
#include "../../../../modeler/text/headers/TextGraphicProperties.h"
#include <vector>

using namespace Ifc::Bundle;
using namespace Modeler::TextString;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		/**
		 * @brief Ifc Text Class Enhancer. Process the TextGraphicProperties to build Text IFC representation
		 * 
		 * @remark the function is called by the class IfcBuilder
		 * @see IfcBuilder
		 */
		class IfcTextEnhancer
		{
		public:
			IfcTextEnhancer();

			/**
			 * @brief Enhancer that handle the processing process
			 * 
			 * @param file the Ifc file helper
			 * @param TextGraphicProperties the BSpline Text graphic properties
			 * @param ifcElementBundle the Element in which the Text belongs
			 * @param ifcGraphicPropertiesBundle  the ifcGraphicPropertiesBundle 
			 */
			void enhance(IfcHierarchyHelper<Ifc4>& file, TextGraphicProperties* textGraphicProperties, IfcElementBundle*& ifcElementBundle,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);

		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();
			/**
			 * @brief Build the correspondent IfcTextLiteralWithExtent
			 * 
			 * @param textGraphicProperties 
			 * @param file 
			 * @param ifcGraphicPropertiesBundle 
			 * @return Ifc4::IfcTextLiteralWithExtent* 
			 */
			Ifc4::IfcTextLiteralWithExtent* buildTextString(TextGraphicProperties* textGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle * ifcGraphicPropertiesBundle);
			
			/**
			 * @brief Build the IfcColourRgb
			 * 
			 * @param color 
			 * @return Ifc4::IfcColourRgb* 
			 */
			Ifc4::IfcColourRgb * buildIfcColor(UInt32 color);
			
			/**
			 * @brief Build the Style Text Model
			 * 
			 * @return Ifc4::IfcTextStyleTextModel* 
			 */
			Ifc4::IfcTextStyleTextModel* buildIfcTextStyleTextModel();

			/**
			 * @brief Build Family Font 
			 * 
			 * @return vector<string> 
			 */
			vector<string> buildFamilyFont();

			/**
			 * @brief Build Font Style
			 * 
			 * @return vector<string> 
			 */
			vector<string> buildFontStyle();
		};
	}
}