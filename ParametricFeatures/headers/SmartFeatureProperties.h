#pragma once
#include "../stdafx.h"

#include "../utils/ElementPropertiesEnum.cpp"
#include "../headers/PropertyTypeValue.h"
#include "../headers/PropertyObjAttribute.h"

using namespace ElementProperties;

class SmartFeatureProperties
{
private:
	UInt32 nodeId;
	UInt32 parentNodeId;
	std::string currentElement;
	std::string className;

	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> smartFeaturesMap;

public:
	SmartFeatureProperties(UInt32 nodeIdValue, UInt32 parentNodeIdValue, std::string currentElementValue,std::string classNameValue);

	void addSmartFeatureProperty(PropertyObjAttribute<ElementPropertiesEnum> key, PropertyTypeValue value);
	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> getSmartFeaturesMap();

	UInt32 getNodeId();
	UInt32 getParentNodeId();
	std::string getCurrentElement();
	std::string getClassName();

};