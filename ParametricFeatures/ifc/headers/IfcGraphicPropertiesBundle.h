#pragma once

//#include "../../stdafx.h"
#include <ifcparse\IfcSchema.h>
#include <ifcparse\Ifc2x3.h>
#include <ifcparse\Ifc4.h>
#include <ifcparse\Ifc4x1.h>
#include <ifcparse\utils.h>
#include <ifcparse\IfcHierarchyHelper.h>
#include "../../modeler/properties/headers/GraphicProperties.h"


class IfcGraphicPropertiesBundle {

private:
	GraphicProperties* graphicProperties;

	Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem;
	//Ifc4::IfcRepresentationItem* ifcRepresentationItem;

	// if the graphic element is included in another operation/object (ex BooleanResult), it should not be showed(show=false)
	bool show = true;

public:
	IfcGraphicPropertiesBundle(GraphicProperties* newGraphicProperties,Ifc4::IfcGeometricRepresentationItem* newIfcRepresentationItem);

	GraphicProperties* getGraphicProperties();

	void setIfcRepresentationItem(Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItemValue);
	//void setIfcRepresentationItem(Ifc4::IfcRepresentationItem* ifcRepresentationItemValue);
	//Ifc4::IfcRepresentationItem* getIfcRepresentationItem();
	Ifc4::IfcGeometricRepresentationItem* getIfcRepresentationItem();
	
	bool getShow();
	void setShow(bool newShow);
};