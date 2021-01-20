#pragma once

/**
 * @file IfcGraphicPropertiesBundle.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/GraphicProperties.h"
#include <fstream>
#include "../../../common/models/headers/SessionManager.h"

using namespace Common::Models; 
using namespace Modeler::Properties;

namespace Ifc
{
	namespace Bundle
	{

		/**
		 * @brief Ifc Graphic Properties bundle class that contains all the graphic information of a single geometry:
		 * IfcGeometricRepresentationItem, Graphic Properties, Color, Level, Type, etc..
		 * 
		 */
		class IfcGraphicPropertiesBundle {

		private:
			Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem;
			GraphicProperties* graphicProperties;

			ElementHandle elementHandle;
			ElemDisplayParamsCP elemDisplayParamsCP;

			// if the graphic element is included in another operation/object (ex BooleanResult), it should not be showed(show=false)
			bool show = true;

			UInt32 color;
			double transparency;
			string _material;
			LevelHandle _levelHandle;
			IntColorDef lineColorDef;
			RgbFactor fillColorDef;

			string representationType = "";
			string representationIdentifier = "";

		public:
			/**
			 * @brief Construct a new Ifc Graphic Properties Bundle object
			 * 
			 * @param newElementHandle element Handle
			 * @param level Level definition of the element
			 */
			IfcGraphicPropertiesBundle(ElementHandle newElementHandle, LevelHandle level);

			/**
			 * @brief Construct a new Ifc Graphic Properties Bundle object
			 * 
			 * @remark remark used for Solids Operation mainly e.g. Boolean Operation
			 * @param newGraphicProperties geometry
			 * @param newIfcRepresentationItem the IfcGeometricRepresentationItem
			 */
			IfcGraphicPropertiesBundle(GraphicProperties* newGraphicProperties, Ifc4::IfcGeometricRepresentationItem* newIfcRepresentationItem);

			/**
			 * @brief Set the Graphic Properties object
			 * 
			 * @param newGraphicProperties 
			 */
			void setGraphicProperties(GraphicProperties& newGraphicProperties);

			/**
			 * @brief Get the Graphic Properties object
			 * 
			 * @return GraphicProperties* 
			 */
			GraphicProperties* getGraphicProperties();

			/**
			 * @brief Set the Ifc Representation Item object
			 * 
			 * @param ifcRepresentationItemValue 
			 */
			void setIfcRepresentationItem(Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItemValue);

			/**
			 * @brief Get the Ifc Representation Item object
			 * 
			 * @return Ifc4::IfcGeometricRepresentationItem* 
			 */
			Ifc4::IfcGeometricRepresentationItem* getIfcRepresentationItem();

			/**
			 * @brief Get the Element Handle object
			 * 
			 * @return ElementHandle 
			 */
			ElementHandle getElementHandle();

			/**
			 * @brief Set the Element Handle object
			 * 
			 * @param newElementHandle 
			 */
			void setElementHandle(ElementHandle newElementHandle);

			/**
			 * @brief Get if the geometry needs to be Shown 
			 * 
			 * @remark if the graphic element is included in another operation/object (ex BooleanResult), it should not be showed(show=false)
			 * @return true 
			 * @return false 
			 */
			bool getShow();

			/**
			 * @brief Set if the geometry needs to be Shown 
			 * 
			 * @remark if the graphic element is included in another operation/object (ex BooleanResult), it should not be showed(show=false)
			 * @param newShow Yes or No (True or False)
			 */
			void setShow(bool newShow);

			/**
			 * @brief Set the Ifc Representation Type and Identifier object
			 * 
			 * @param rType the Representation type
			 * @param rIdentifier the Representation identifier
			 */
			void setIfcRepresentationTypeIdentifier(string rType, string rIdentifier);

			/**
			 * @brief Get the Ifc Representation Type object
			 * 
			 * @return string 
			 */
			string getIfcRepresentationType();

			/**
			 * @brief Get the Ifc Representation Identifier object
			 * 
			 * @return string 
			 */
			string getIfcRepresentationIdentifier();

			/**
			 * @brief Get the Elem Display Params CP object
			 * 
			 * @remark contains Bentley Info on the geometry e.g. LineColor, FillColor, Clipping
			 * @return ElemDisplayParamsCP 
			 */
			ElemDisplayParamsCP getElemDisplayParamsCP();

			/**
			 * @brief Get the Color object
			 * 
			 * @return UInt32 
			 */
			UInt32 getColor();

			/**
			 * @brief Set the Color object
			 * 
			 * @param newColor 
			 */
			void setColor(UInt32 newColor);

			/**
			 * @brief Get the Fill Color object
			 * 
			 * @return RgbFactor 
			 */
			RgbFactor getFillColor();

			/**
			 * @brief Set the Fill Color object
			 * 
			 * @param newColor 
			 */
			void setFillColor(RgbFactor newColor);

			/**
			 * @brief Get the Line Color object
			 * 
			 * @return IntColorDef 
			 */
			IntColorDef getLineColor();

			/**
			 * @brief Set the Line Color object
			 * 
			 * @param newColor 
			 */
			void setLineColor(IntColorDef newColor);

			/**
			 * @brief Get the Level Handle object
			 * 
			 * @return LevelHandle 
			 */
			LevelHandle getLevelHandle();

			/**
			 * @brief Set the Level Handle object
			 * 
			 * @param newlevelID 
			 */
			void setLevelHandle(LevelHandle newlevelID);

			/**
			 * @brief Get the Transparency object
			 * 
			 * @return double 
			 */
			double getTransparency();

			/**
			 * @brief Set the Transparency object
			 * 
			 * @param newTransparency 
			 */
			void setTransparency(double newTransparency);

			/**
			 * @brief Get the Material object
			 * 
			 * @return string 
			 */
			string getMaterial();

			/**
			 * @brief Set the Material object
			 * 
			 * @param material 
			 */
			void setMaterial(string material);

			/**
			 * @brief Check weather or not the Ifc Representation of the object is valid
			 * 
			 * @return true 
			 * @return false 
			 */
			bool isValid();
		};
	}
}