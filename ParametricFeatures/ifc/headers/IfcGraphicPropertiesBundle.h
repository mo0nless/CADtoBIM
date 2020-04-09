#pragma once

#include "../../stdafx.h"
#include "../../modeler/properties/headers/GraphicProperties.h"


class IfcGraphicPropertiesBundle {

private:
	GraphicProperties* graphicProperties;
	Ifc4::IfcRepresentationItem* ifcRepresentationItem;

	// if the graphic element is included in another operation/object (ex BooleanResult), it should not be showed(show=false)
	bool show = true;

public:
	IfcGraphicPropertiesBundle(GraphicProperties* newGraphicProperties,Ifc4::IfcRepresentationItem* newIfcRepresentationItem);

	GraphicProperties* getGraphicProperties();
	Ifc4::IfcRepresentationItem* getIfcRepresentationItem();
	
	bool getShow();
	void setShow(bool newShow);
};