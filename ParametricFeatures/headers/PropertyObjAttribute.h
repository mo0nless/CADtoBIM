#pragma once

#include "../stdafx.h"
#include <tuple>

template<class pEnum>
class PropertyObjAttribute {
private:

	std::string className;
	Int64 elementID;
	pEnum propertyAttribute;
public:
	PropertyObjAttribute();
	PropertyObjAttribute(const Int64 &elmID, const std::string &clsName, const pEnum &propertyAttribute);

	const std::string& getClassName() const;	
	const Int64& getElementID() const;
	const pEnum& getPropertyAttribute() const;

	std::string getClassName();
	Int64 getElementID();
	pEnum getPropertyAttribute();
};


//The function needs to be placed here otherwise it will end up as an unresolved external symbol
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

/*Definition of the Operator with overloading*/
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