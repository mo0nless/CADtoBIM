#include "..\headers\SmartFeatureProperties.h"

SmartFeatureProperties::SmartFeatureProperties(UInt32 nodeIdValue, UInt32 parentNodeIdValue, std::string currentElementValue, std::string classNameValue)
{
	this->nodeId = nodeIdValue;
	this->parentNodeId = parentNodeIdValue;
	this->currentElement = currentElementValue;
	this->className = classNameValue;
}

void SmartFeatureProperties::addSmartFeatureProperty(PropertyObjAttribute<ElementPropertiesEnum> key, PropertyTypeValue value)
{
	this->smartFeaturesMap[key] = value;
}

std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> SmartFeatureProperties::getSmartFeaturesMap()
{
	return this->smartFeaturesMap;
}

UInt32 SmartFeatureProperties::getNodeId()
{
	return this->nodeId;;
}

UInt32 SmartFeatureProperties::getParentNodeId()
{
	return this->parentNodeId;
}

std::string SmartFeatureProperties::getCurrentElement()
{
	return this->currentElement;
}

std::string SmartFeatureProperties::getClassName()
{
	return this->className;
}
