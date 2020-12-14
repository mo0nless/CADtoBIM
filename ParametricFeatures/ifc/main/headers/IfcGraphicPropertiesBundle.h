#pragma once

//#include "../../stdafx.h"
#include <ifcparse\IfcSchema.h>
#include <ifcparse\Ifc2x3.h>
#include <ifcparse\Ifc4.h>
#include <ifcparse\Ifc4x1.h>
#include <ifcparse\utils.h>
#include <ifcparse\IfcHierarchyHelper.h>
#include "../../../modeler/properties/headers/GraphicGeomBundle.h"
#include "../../../common/models/headers/SessionManager.h"


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

	string representationType = "";
	string representationIdentifier = "";

public:
	IfcGraphicPropertiesBundle(GraphicProperties* newGraphicProperties,Ifc4::IfcGeometricRepresentationItem* newIfcRepresentationItem,
		ElementHandle newElementHandle);
	IfcGraphicPropertiesBundle(GraphicProperties* newGraphicProperties, Ifc4::IfcGeometricRepresentationItem* newIfcRepresentationItem);

	GraphicProperties* getGraphicProperties();

	void setIfcRepresentationItem(Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItemValue);
	Ifc4::IfcGeometricRepresentationItem* getIfcRepresentationItem();

	ElementHandle getElementHandle();
	
	bool getShow();
	void setShow(bool newShow);

	void setRepresentationTypeIdentifier(string rType,	string rIdentifier);
	string getRepresentationType();
	string getRepresentationIdentifier();

	ElemDisplayParamsCP getElemDisplayParamsCP();

	UInt32 getColor();
	void setColor(UInt32 newColor);

	LevelHandle getLevelHandle();
	void setLevelHandle(LevelHandle newlevelID);

	double getTransparency();
	void setTransparency(double newTransparency);

	string getMaterial();
	void setMaterial(string material);


};