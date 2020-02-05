#pragma once

#include "../stdafx.h"
#include "../utils/ElementPropertiesEnum.cpp"
#include "../utils/GraphicPropertiesEnum.cpp"
#include "PropertyTypeValue.h"
#include "PropertyObjAttribute.h"
#include "SmartFeatureProperties.h"

class PropertiesDictionary {
public:
	PropertiesDictionary();
	
	void addElementProperty(PropertyObjAttribute<ElementPropertiesEnum> elementPropertiesEnum, PropertyTypeValue propertyTypeValue);
	void addGraphicProperty(PropertyObjAttribute<GraphicPropertiesEnum> graphicPropertiesEnum, PropertyTypeValue propertyTypeValue);

	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> getElementPropertiesMap();
	std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> getGraphicPropertiesMap();

	PropertyObjAttribute<ElementPropertiesEnum> getElementPropertyObjAttribute(ElementPropertiesEnum ePenum);
	PropertyObjAttribute<GraphicPropertiesEnum> getGraphicPropertyObjAttribute(GraphicPropertiesEnum eGenum);

	std::string getElemDescrName();
	void setElemDescrName(std::string s);

	bool checkSmartFeature();
	void triggerSmartFeature(SmartFeatureNodePtr sFeatPtr);

	SmartFeatureProperties* getSmartFeatProperties();

private:
	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> elementPropertiesMap;
	std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> graphicPropertiesMap;
	
	SmartFeatureProperties* sFeatProps;

	std::string elemDescrName;
	bool isSmartFeature = false;

};