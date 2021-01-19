#pragma once

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
			IfcGraphicPropertiesBundle(ElementHandle newElementHandle, LevelHandle level);
			IfcGraphicPropertiesBundle(GraphicProperties* newGraphicProperties, Ifc4::IfcGeometricRepresentationItem* newIfcRepresentationItem);

			void setGraphicProperties(GraphicProperties& newGraphicProperties);
			GraphicProperties* getGraphicProperties();

			void setIfcRepresentationItem(Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItemValue);
			Ifc4::IfcGeometricRepresentationItem* getIfcRepresentationItem();

			ElementHandle getElementHandle();
			void setElementHandle(ElementHandle newElementHandle);

			bool getShow();
			void setShow(bool newShow);

			void setRepresentationTypeIdentifier(string rType, string rIdentifier);
			string getRepresentationType();
			string getRepresentationIdentifier();

			ElemDisplayParamsCP getElemDisplayParamsCP();

			UInt32 getColor();
			void setColor(UInt32 newColor);

			RgbFactor getFillColor();
			void setFillColor(RgbFactor newColor);

			IntColorDef getLineColor();
			void setLineColor(IntColorDef newColor);

			LevelHandle getLevelHandle();
			void setLevelHandle(LevelHandle newlevelID);

			double getTransparency();
			void setTransparency(double newTransparency);

			string getMaterial();
			void setMaterial(string material);

			bool isValid();
		};
	}
}