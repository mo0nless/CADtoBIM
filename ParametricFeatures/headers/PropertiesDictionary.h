#pragma once

#include "../stdafx.h"
#include "../utils/ElementPropertiesEnum.cpp"
#include "../utils/GraphicPropertiesEnum.cpp"
#include "../headers/PropertyTypeValue.h"
#include "../headers/PropertyObjAttribute.h"

class PropertiesDictionary {
private:
	/*std::map<ElementPropertiesEnum, PropertyTypeValue> elementPropertiesMap;
	std::map<GraphicPropertiesEnum, PropertyTypeValue> graphicPropertiesMap;*/

	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> elementPropertiesMap;
	std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> graphicPropertiesMap;

public:
	PropertiesDictionary();

	/*void addElementProperty(ElementPropertiesEnum elementPropertiesEnum, PropertyTypeValue propertyTypeValue);
	void addGraphicProperty(GraphicPropertiesEnum graphicPropertiesEnum, PropertyTypeValue propertyTypeValue);*/

	void addElementProperty(PropertyObjAttribute<ElementPropertiesEnum> elementPropertiesEnum, PropertyTypeValue propertyTypeValue);
	void addGraphicProperty(PropertyObjAttribute<GraphicPropertiesEnum> graphicPropertiesEnum, PropertyTypeValue propertyTypeValue);

	/*std::map<ElementPropertiesEnum, PropertyTypeValue> getElementPropertiesMap();
	std::map<GraphicPropertiesEnum, PropertyTypeValue> getGraphicPropertiesMap();*/

	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> getElementPropertiesMap();
	std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> getGraphicPropertiesMap();

	PropertyObjAttribute<ElementPropertiesEnum> getElementPropertyObjAttribute(ElementPropertiesEnum ePenum);
	PropertyObjAttribute<GraphicPropertiesEnum> getGraphicPropertyObjAttribute(GraphicPropertiesEnum eGenum);
};