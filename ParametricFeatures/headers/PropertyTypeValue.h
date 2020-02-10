#pragma once

#include "../stdafx.h"

/// @addtogroup DataContainer
/// @beginGroup

/*=================================================================================**//**
* Class used as a storage to keep track of the element properties values and types.
* This class is used as a values of an element in the map created in the properties dictionary 
* @see PropertiesDictionary
* @bsiclass
+===============+===============+===============+===============+===============+======*/
class PropertyTypeValue {
private:
	
	std::string propertyType;
	boost::any propertyValue;
public:
	//! Deafult constructor without parameters
	PropertyTypeValue();

	//! Constructor for the class instance.
	//! @param[in] the current type of the value that needs to be stored
	//! @param[in] the current value of the single property of the element
	//! @remark this is the constructor used for creating the instance that is stored in the PropertiesDictionary.
	PropertyTypeValue(const std::string &propertyType, const boost::any &propertyValue);

	//! Getter method for the property type
	//! @return the string that express the type of the value
	std::string getPropertyType();

	//! Getter method for the current value property of an element
	//! @return the boost::any value of the current property (need to be casted properly based on the type)
	boost::any getPropertyValue();
};

/// @endGroup