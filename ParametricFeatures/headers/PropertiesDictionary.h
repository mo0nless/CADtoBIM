#pragma once

#include "SmartFeatureProperties.h"

using namespace GraphicProperties;
using namespace ElementProperties;

class PropertiesDictionary {
public:
	PropertiesDictionary();
	
	void addElementProperty(PropertyObjAttribute<ElementPropertiesEnum> elementPropertiesEnum, PropertyTypeValue propertyTypeValue);
	void addGraphicProperty(PropertyObjAttribute<GraphicPropertiesEnum> graphicPropertiesEnum, PropertyTypeValue propertyTypeValue);

	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> getElementPropertiesMap();
	std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> getGraphicPropertiesMap();


	std::vector<PropertyTypeValue> PropertiesDictionary::getElementPropertyTypeValues(Int64 elementId = -1, std::string className = "", ElementPropertiesEnum elementPropertiesEnum = ElementPropertiesEnum::DEFAULT);
	std::vector<PropertyTypeValue> PropertiesDictionary::getElementPropertyTypeValues(ElementPropertiesEnum elementPropertiesEnum);
	
	std::vector<PropertyTypeValue> PropertiesDictionary::getGraphicPropertyTypeValues(Int64 elementId = -1, std::string className = "", GraphicPropertiesEnum graphicPropertiesEnum = GraphicPropertiesEnum::DEFAULT);
	std::vector<PropertyTypeValue> PropertiesDictionary::getGraphicPropertyTypeValues(GraphicPropertiesEnum graphicPropertiesEnum);

	std::string getElemDescrName();
	void setElemDescrName(std::string s);

private:
	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> elementPropertiesMap;
	std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> graphicPropertiesMap;
	
	std::string elemDescrName;

};