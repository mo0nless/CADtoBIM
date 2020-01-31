#include "../headers/PropertiesDictionary.h"

PropertiesDictionary::PropertiesDictionary()
{
}

void PropertiesDictionary::addElementProperty(PropertyObjAttribute<ElementPropertiesEnum> elementPropertiesEnum, PropertyTypeValue propertyTypeValue)
{
	this->elementPropertiesMap[elementPropertiesEnum] = propertyTypeValue;
}

void PropertiesDictionary::addGraphicProperty(PropertyObjAttribute<GraphicPropertiesEnum> graphicPropertiesEnum, PropertyTypeValue propertyTypeValue)
{
	this->graphicPropertiesMap[graphicPropertiesEnum] = propertyTypeValue;
}

std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> PropertiesDictionary::getElementPropertiesMap()
{
	return this->elementPropertiesMap;
}

std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> PropertiesDictionary::getGraphicPropertiesMap()
{
	return this->graphicPropertiesMap;
}

PropertyObjAttribute<ElementPropertiesEnum> PropertiesDictionary::getElementPropertyObjAttribute(ElementPropertiesEnum ePenum)
{
	PropertyObjAttribute<ElementPropertiesEnum> pOA;
	try 
	{
		for (auto const& element : elementPropertiesMap)
		{
			pOA = element.first;
			if (pOA.getPropertyAttribute() == ePenum) { return pOA; }
		}
		
	}
	catch (const std::exception& e) 
	{ 
		std::cout << e.what(); 		 
	}
	return pOA; //Needs to be handle this, at the moment it's an empty object this one.
}

PropertyObjAttribute<GraphicPropertiesEnum> PropertiesDictionary::getGraphicPropertyObjAttribute(GraphicPropertiesEnum eGenum)
{
	PropertyObjAttribute<GraphicPropertiesEnum> pOA;
	try 
	{
		for (auto const& element : graphicPropertiesMap)
		{
			pOA = element.first;
			if (pOA.getPropertyAttribute() == eGenum) { return pOA; }
		}
	}
	catch (const std::exception& e) 
	{ 
		std::cout << e.what(); 		
	}
	return pOA; //Needs to be handle this, at the moment it's an empty object this one.
}

std::string PropertiesDictionary::getElemDescrName()
{
	return elemDescrName;
}

void PropertiesDictionary::setElemDescrName(std::string s)
{
	this->elemDescrName = s;
}
