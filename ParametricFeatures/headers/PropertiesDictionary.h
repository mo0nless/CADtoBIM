#pragma once

#include "SmartFeatureProperties.h"

/// @addtogroup DataContainer
/// @beginGroup

using namespace GraphicProperties;
using namespace ElementProperties;

/*=================================================================================**//**
* Class for collectingand store all the graphical and non-graphical properties of 
* an element.
* This class define maps that are used to store the information in pair (key, value).
* @see PropertyObjAttribute and PropertyTypeValue 
* @bsiclass
+===============+===============+===============+===============+===============+======*/
class PropertiesDictionary {
public:
	PropertiesDictionary();
	
	//! Add a non-graphical information of the current element to the map.
	//! @param[in] PropertyObjAttribute<ElementPropertiesEnum>
	//! @param[in] PropertyTypeValue
	//! @see PropertyObjAttribute and PropertyTypeValue 
	//! @remark the Enumeration template passed must belong to ElementPropertiesEnum.
	void addElementProperty(PropertyObjAttribute<ElementPropertiesEnum> elementPropertiesEnum, PropertyTypeValue propertyTypeValue);

	//! Add a graphical information of the current element to the map.
	//! @param[in] PropertyObjAttribute<GraphicPropertiesEnum>
	//! @param[in] PropertyTypeValue
	//! @see PropertyObjAttribute and PropertyTypeValue 
	//! @remark the Enumeration template passed must belong to GraphicPropertiesEnum.
	void addGraphicProperty(PropertyObjAttribute<GraphicPropertiesEnum> graphicPropertiesEnum, PropertyTypeValue propertyTypeValue);

	//! Getter method for the ElementPropertiesMap of the current element.
	//! @return the ElementPropertiesMap if the operation is successful.
	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> getElementPropertiesMap();

	//! Getter method for the GraphicPropertiesMap of the current element.
	//! @return the GraphicPropertiesMap if the operation is successful.
	std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> getGraphicPropertiesMap();
	
	//! Getter method for the Property Values of the current element non-graphical.
	//! @param[in] the element ID
	//! @param[in] the class Name
	//! @param[in] the non-graphical enumeration for the property ElementPropertiesEnum
	//! @return the vector<PropertyTypeValue> if the operation is successful.
	std::vector<PropertyTypeValue> PropertiesDictionary::getElementPropertyTypeValues(Int64 elementId = -1, std::string className = "", ElementPropertiesEnum elementPropertiesEnum = ElementPropertiesEnum::DEFAULT);
	
	//! Getter method for the Property Values of the current element non-graphical.
	//! @param[in] the non-graphical enumeration for the property ElementPropertiesEnum
	//! @return the vector<PropertyTypeValue> if the operation is successful.
	std::vector<PropertyTypeValue> PropertiesDictionary::getElementPropertyTypeValues(ElementPropertiesEnum elementPropertiesEnum);
	
	//! Getter method for the Property Values of the current element graphical.
	//! @param[in] the element ID
	//! @param[in] the class Name
	//! @param[in] the graphical enumeration for the property GraphicPropertiesEnum
	//! @return the vector<PropertyTypeValue> if the operation is successful.
	std::vector<PropertyTypeValue> PropertiesDictionary::getGraphicPropertyTypeValues(Int64 elementId = -1, std::string className = "", GraphicPropertiesEnum graphicPropertiesEnum = GraphicPropertiesEnum::DEFAULT);
	
	//! Getter method for the Property Values of the current element graphical.
	//! @param[in] the graphical enumeration for the property GraphicPropertiesEnum
	//! @return the vector<PropertyTypeValue> if the operation is successful.
	std::vector<PropertyTypeValue> PropertiesDictionary::getGraphicPropertyTypeValues(GraphicPropertiesEnum graphicPropertiesEnum);

	//! Getter method for the Description of the current element.
	//! @return a string with the description if the operation is successful.
	std::string getElemDescrName();

	//! Setter method for the Description of the current element.
	//! @param[in] a string that contains the element description.
	void setElemDescrName(std::string s);

private:
	std::map<PropertyObjAttribute<ElementPropertiesEnum>, PropertyTypeValue> elementPropertiesMap;
	std::map<PropertyObjAttribute<GraphicPropertiesEnum>, PropertyTypeValue> graphicPropertiesMap;
	
	std::string elemDescrName;

};

/// @endGroup