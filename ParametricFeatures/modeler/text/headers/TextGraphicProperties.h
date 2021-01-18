#pragma once

/**
 * @file TextGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../properties/headers/GraphicProperties.h"

using namespace Modeler::Properties;

namespace Modeler
{
	namespace TextString
	{
		/**
		 * @brief GraphicProperties Handle class for Base solid primitive
		 * 
		 * @remark This class inherits the GraphicProperties class
		 * @see GraphicProperties
		 */
		class TextGraphicProperties : public GraphicProperties
		{
		public:
			TextGraphicProperties();

			/**
			 * @brief Get the Height object
			 * 
			 * @return double 
			 */
			double getHeight();

			/**
			 * @brief Get the Width object
			 * 
			 * @return double 
			 */
			double getWidth();

			/**
			 * @brief Set the Height Width object
			 * 
			 * @param h height
			 * @param w width
			 */
			void setHeightWidth(double h, double w);

			/**
			 * @brief Get the Text String object
			 * 
			 * @return string 
			 */
			string getTextString();

			/**
			 * @brief Set the Text String object
			 * 
			 * @param s 
			 */
			void setTextString(string s);

			/**
			 * @brief Set the Background Color object
			 * 
			 * @param fillColor 
			 */
			void setBackgroundColor(UInt32 fillColor);//, UInt32 borderColor, UInt32 borderWeight, Int32 borderLineStyle, DPoint2d borderPadding);

			/**
			 * @brief Get the Background Color object
			 * 
			 * @return UInt32 
			 */
			UInt32 getBackgroundColor();

			/**
			 * @brief Get the Border Color object
			 * 
			 * @return UInt32 
			 */
			UInt32 getBorderColor();

			/**
			 * @brief Get the Border Weight object
			 * 
			 * @return UInt32 
			 */
			UInt32 getBorderWeight();

			/**
			 * @brief Get the Border Line Style object
			 * 
			 * @return Int32 
			 */
			Int32 getBorderLineStyle();

			/**
			 * @brief Get the Border Padding object
			 * 
			 * @return DPoint2d 
			 */
			DPoint2d getBorderPadding();

			/**
			 * @brief Set the Font Size object
			 * 
			 * @param s 
			 */
			void setFontSize(double s);

			/**
			 * @brief Get the Font Size object
			 * 
			 * @return double 
			 */
			double getFontSize();

			/**
			 * @brief Set the Font Name object
			 * 
			 * @param s 
			 */
			void setFontName(string s);

			/**
			 * @brief Get the Font Name object
			 * 
			 * @return string 
			 */
			string getFontName();
			
			/**
			 * @brief Set the Text Color object
			 * 
			 * @param color 
			 */
			void setTextColor(UInt32 color);

			/**
			 * @brief Get the Text Color object
			 * 
			 * @return UInt32 
			 */
			UInt32 getTextColor();
		private:
			double _height, _width, _fontSize;
			string _text, _namefont;

			UInt32 _bFillColor, _borderColor, _borderWeight, _textColor;
			Int32 _borderLineStyle;
			DPoint2d _borderPadding;
		};
	}
}
