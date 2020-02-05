#pragma once
#include "../stdafx.h"

#include "../utils/SmartFeaturePropertiesEnum.cpp"
#include "../headers/PropertyTypeValue.h"
#include "../headers/PropertyObjAttribute.h"

using namespace SmartPropertiesEnum;

class SmartFeatureProperties
{
private:
	UInt32 nodeId;
	UInt32 parentNodeId;
	std::string currentElement;
	std::string className;

	std::map<PropertyObjAttribute<SmartFeaturePropertiesEnum>, PropertyTypeValue> smartFeaturesMap;

public:
	SmartFeatureProperties(UInt32 nodeIdValue, UInt32 parentNodeIdValue, std::string currentElementValue,std::string classNameValue);

	void addSmartFeatureProperty(PropertyObjAttribute<SmartFeaturePropertiesEnum> key, PropertyTypeValue value);
	std::map<PropertyObjAttribute<SmartFeaturePropertiesEnum>, PropertyTypeValue> getSmartFeaturesMap();

	UInt32 getNodeId();
	UInt32 getParentNodeId();
	std::string getCurrentElement();
	std::string getClassName();

};