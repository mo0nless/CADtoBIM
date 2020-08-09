#pragma once

//#include "../../stdafx.h"
#include <ifcparse\IfcSchema.h>
#include <ifcparse\Ifc2x3.h>
#include <ifcparse\Ifc4.h>
#include <ifcparse\Ifc4x1.h>
#include <ifcparse\utils.h>
#include <ifcparse\IfcHierarchyHelper.h>
#include "../../modeler/properties/headers/ElementBundle.h"


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

public:
	IfcGraphicPropertiesBundle(GraphicProperties* newGraphicProperties,Ifc4::IfcGeometricRepresentationItem* newIfcRepresentationItem,
		ElementHandle newElementHandle, ElemDisplayParamsCP newElemDisplayParamsCP);

	GraphicProperties* getGraphicProperties();

	void setIfcRepresentationItem(Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItemValue);
	Ifc4::IfcGeometricRepresentationItem* getIfcRepresentationItem();

	ElementHandle getElementHandle();
	
	bool getShow();
	void setShow(bool newShow);

	ElemDisplayParamsCP getElemDisplayParamsCP();

	UInt32 getColor();
	void setColor(UInt32 newColor);

	double getTransparency();
	void setTransparency(double newTransparency);

};