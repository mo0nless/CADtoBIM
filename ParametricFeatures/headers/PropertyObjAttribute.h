#pragma once

#include "../stdafx.h"

/// @addtogroup DataContainer
/// @beginGroup

/*=================================================================================**//**
* Class used as a storage to keep track of the element key values.
* This class is used as a key of an element in the map created in the properties dictionary
* @see PropertiesDictionary
* @bsiclass
+===============+===============+===============+===============+===============+======*/
template<class pEnum>
class PropertyObjAttribute {

public:
	//! Deafult constructor without parameters
	PropertyObjAttribute();

	//! Constructor for the class instance.
	//! @param[in] the current element ID
	//! @param[in] the current element class name
	//! @param[in] the Enumeration property that needs to be stored (ElementPropertiesEnum or GraphicPropertiesEnum)
	//! @remark this is the constructor used for creating the instance that is stored in the PropertiesDictionary.
	PropertyObjAttribute(const Int64 &elmID, const std::string &clsName, const pEnum &propertyAttribute);

	//! Getter method for the class name of the element.
	//! @return the string with the name of the class
	std::string getClassName();

	//! Getter method for the ID of the element.
	//! @return the Int64 with the element ID
	Int64 getElementID();

	//! Getter method for the enumeration property.
	//! @return the enumeration property for the current element (ElementPropertiesEnum or GraphicPropertiesEnum)
	pEnum getPropertyAttribute();
	
	//! Getter method for the class name of the element.
	//! @return AS CONST REF the string with the name of the class
	const std::string& getClassName() const;

	//! Getter method for the ID of the element.
	//! @return AS CONST REF the Int64 with the element ID
	const Int64& getElementID() const;

	//! Getter method for the enumeration property.
	//! @return AS CONST REF the enumeration property for the current element (ElementPropertiesEnum or GraphicPropertiesEnum)
	const pEnum& getPropertyAttribute() const;

private:
	std::string className;
	Int64 elementID;
	pEnum propertyAttribute;
};


//The functions need to be placed here otherwise it will end up as an unresolved external symbol
//More information at the address: https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates

template<class pEnum>
inline PropertyObjAttribute<pEnum>::PropertyObjAttribute()
{
}

template<class pEnum>
inline PropertyObjAttribute<pEnum>::PropertyObjAttribute(const Int64 & elmID, const std::string & clsName, const pEnum & propertyAttribute)
{
	this->propertyAttribute = propertyAttribute;
	this->className = clsName;
	this->elementID = elmID;
}

template<class pEnum>
inline std::string PropertyObjAttribute<pEnum>::getClassName()
{
	return this->className;
}

template<class pEnum>
inline Int64 PropertyObjAttribute<pEnum>::getElementID()
{
	return this->elementID;
}

template<class pEnum>
inline pEnum PropertyObjAttribute<pEnum>::getPropertyAttribute()
{
	return this->propertyAttribute;
}

template<class pEnum>
inline const std::string& PropertyObjAttribute<pEnum>::getClassName() const
{
	return this->className;
}

template<class pEnum>
inline const Int64& PropertyObjAttribute<pEnum>::getElementID() const
{
	return this->elementID;
}

template<class pEnum>
inline const pEnum& PropertyObjAttribute<pEnum>::getPropertyAttribute() const
{
	return this->propertyAttribute;
}

/*=================================================================================**//**
 * Definition of the Operator with overloading
+===============+===============+===============+===============+===============+======*/

template<class pEnum>
inline bool operator==(const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) {
	return lhs.getClassName() == rhs.getClassName() && lhs.getPropertyAttribute() == lhs.getPropertyAttribute() && lhs.getElementID() == rhs.getElementID();
}
template<class pEnum>
inline bool operator!=(const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) { return !operator==(lhs, rhs); }

template<class pEnum>
inline bool operator< (const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) {
	// std::tuple's lexicographic ordering does all the actual work for you
	// and using std::tie means no actual copies are made
	return std::tie(lhs.getClassName(), lhs.getPropertyAttribute(), lhs.getElementID()) < std::tie(rhs.getClassName(), rhs.getPropertyAttribute(), rhs.getElementID());
}

template<class pEnum>
inline bool operator> (const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) { return  operator< (rhs, lhs); }

template<class pEnum>
inline bool operator<=(const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) { return !operator> (lhs, rhs); }

template<class pEnum>
inline bool operator>=(const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) { return !operator< (lhs, rhs); }

/// @endGroup