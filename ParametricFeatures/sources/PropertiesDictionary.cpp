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

//PropertyObjAttribute<ElementPropertiesEnum> PropertiesDictionary::getElementPropertyObjAttribute(ElementPropertiesEnum ePenum)
//{
//	PropertyObjAttribute<ElementPropertiesEnum> pOA;
//	try 
//	{
//		for (auto const& element : elementPropertiesMap)
//		{
//			pOA = element.first;
//			if (pOA.getPropertyAttribute() == ePenum) { return pOA; }
//		}
//		
//	}
//	catch (const std::exception& e) 
//	{ 
//		std::cout << e.what(); 		 
//	}
//	return pOA; //Needs to be handle this, at the moment it's an empty object this one.
//}

//std::vector<PropertyTypeValue> PropertiesDictionary::getPropertyTypeValuesByByElementId(Int64 elementId)
//{
//	std::vector<PropertyTypeValue> propertyTypeValues;
//	try
//	{
//		for (auto const& element : elementPropertiesMap)
//		{
//			if (element.first.getElementID() == elementId)
//			{
//				propertyTypeValues.push_back(element.second);
//			}
//		}
//	}
//	catch (const std::exception& e)
//	{
//		//std::cout << e.what();
//	}
//	return propertyTypeValues;
//}
//
//std::vector<PropertyTypeValue> PropertiesDictionary::getPropertyTypeValuesByClassName(std::string className)
//{
//	std::vector<PropertyTypeValue> propertyTypeValues;
//	try
//	{
//		for (auto const& element : elementPropertiesMap)
//		{
 //			if (element.first.getClassName() == className)
//			{
//				propertyTypeValues.push_back(element.second);
//			}
//		}
//	}
//	catch (const std::exception& e)
//	{
//		//std::cout << e.what();
//	}
//	return propertyTypeValues;
//}
//
//std::vector<PropertyTypeValue> PropertiesDictionary::getPropertyTypeValuesByElementPropertiesEnum(ElementPropertiesEnum elementPropertiesEnum)
//{
//	std::vector<PropertyTypeValue> propertyTypeValues;
//	try
//	{
//		for (auto const& element : elementPropertiesMap)
//		{
//			if (element.first.getPropertyAttribute() == elementPropertiesEnum)
//			{
//				propertyTypeValues.push_back(element.second);
//			}
//		}
//	}
//	catch (const std::exception& e)
//	{
//		//std::cout << e.what();
//	}
//	return propertyTypeValues;
//}

std::vector<PropertyTypeValue> PropertiesDictionary::getElementPropertyTypeValues(Int64 elementId, std::string className,ElementPropertiesEnum elementPropertiesEnum)
{
	std::vector<PropertyTypeValue> propertyTypeValues;

	if (elementId == -1 && className.empty() && elementPropertiesEnum == ElementPropertiesEnum::DEFAULT) {
		for (auto const& element : elementPropertiesMap)
		{
			propertyTypeValues.push_back(element.second);
		}
		return propertyTypeValues;
	}
	try
	{
		for (auto const& element : elementPropertiesMap)
		{
			if (elementId >= 0 )
			{
				if (!className.empty())
				{
					if (elementPropertiesEnum != ElementPropertiesEnum::DEFAULT)
					{
						if (element.first.getElementID() == elementId && element.first.getClassName() == className && element.first.getPropertyAttribute() == elementPropertiesEnum)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
					else
					{
						if (element.first.getElementID() == elementId && element.first.getClassName() == className)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
				}
				else
				{
					if (elementPropertiesEnum != ElementPropertiesEnum::DEFAULT)
					{
						if (element.first.getElementID() == elementId && element.first.getPropertyAttribute() == elementPropertiesEnum)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
				}
			}
			else 
			{
				if (!className.empty())
				{
					if (elementPropertiesEnum != ElementPropertiesEnum::DEFAULT)
					{
						if ( element.first.getClassName() == className && element.first.getPropertyAttribute() == elementPropertiesEnum)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
					else
					{
						if (element.first.getClassName() == className)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
				}
				else
				{
					if (elementPropertiesEnum != ElementPropertiesEnum::DEFAULT)
					{
						if ( element.first.getPropertyAttribute() == elementPropertiesEnum)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
				}
			}
			
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	return propertyTypeValues;
}

std::vector<PropertyTypeValue> PropertiesDictionary::getElementPropertyTypeValues(ElementPropertiesEnum elementPropertiesEnum)
{
	return getElementPropertyTypeValues(-1,"", elementPropertiesEnum);
}

std::vector<PropertyTypeValue> PropertiesDictionary::getGraphicPropertyTypeValues(Int64 elementId, std::string className,GraphicPropertiesEnum graphicPropertiesEnum)
{
	std::vector<PropertyTypeValue> propertyTypeValues;

	if (elementId == -1 && className.empty() && graphicPropertiesEnum == GraphicPropertiesEnum::DEFAULT) {
		for (auto const& element : graphicPropertiesMap)
		{
			propertyTypeValues.push_back(element.second);
		}
		return propertyTypeValues;
	}
	try
	{
		for (auto const& element : graphicPropertiesMap)
		{
			if (elementId >= 0)
			{
				if (!className.empty())
				{
					if (graphicPropertiesEnum != GraphicPropertiesEnum::DEFAULT)
					{
						if (element.first.getElementID() == elementId && element.first.getClassName() == className && element.first.getPropertyAttribute() == graphicPropertiesEnum)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
					else
					{
						if (element.first.getElementID() == elementId && element.first.getClassName() == className)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
				}
				else
				{
					if (graphicPropertiesEnum != GraphicPropertiesEnum::DEFAULT)
					{
						if (element.first.getElementID() == elementId && element.first.getPropertyAttribute() == graphicPropertiesEnum)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
				}
			}
			else
			{
				if (!className.empty())
				{
					if (graphicPropertiesEnum != GraphicPropertiesEnum::DEFAULT)
					{
						if (element.first.getClassName() == className && element.first.getPropertyAttribute() == graphicPropertiesEnum)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
					else
					{
						if (element.first.getClassName() == className)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
				}
				else
				{
					if (graphicPropertiesEnum != GraphicPropertiesEnum::DEFAULT)
					{
						if (element.first.getPropertyAttribute() == graphicPropertiesEnum)
						{
							propertyTypeValues.push_back(element.second);
						}
					}
				}
			}


		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	return propertyTypeValues;
}

std::vector<PropertyTypeValue> PropertiesDictionary::getGraphicPropertyTypeValues(GraphicPropertiesEnum graphicPropertiesEnum)
{
	
	return getGraphicPropertyTypeValues(-1,"",graphicPropertiesEnum);
}

std::string PropertiesDictionary::getElemDescrName()
{
	return elemDescrName;
}

void PropertiesDictionary::setElemDescrName(std::string s)
{
	this->elemDescrName = s;
}
