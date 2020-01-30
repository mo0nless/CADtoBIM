#pragma once

#include "../stdafx.h"
#include <tuple>

template<class pEnum>
class PropertyObjAttribute {
private:

	std::string propertyObj;	
	pEnum propertyAttribute;
public:
	PropertyObjAttribute();
	PropertyObjAttribute(const std::string &propertyObj, const pEnum &propertyAttribute);

	const std::string& getPropertyObj() const;	
	const pEnum& getPropertyAttribute() const;

	std::string getPropertyObj();
	pEnum getPropertyAttribute();
};


//The function needs to be placed here otherwise it will end up as an unresolved external symbol
//More information at the address: https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates

template<class pEnum>
inline PropertyObjAttribute<pEnum>::PropertyObjAttribute()
{
}

template<class pEnum>
inline PropertyObjAttribute<pEnum>::PropertyObjAttribute(const std::string & propertyObj, const pEnum & propertyAttribute)
{
	this->propertyAttribute = propertyAttribute;
	this->propertyObj = propertyObj;
}

template<class pEnum>
inline std::string PropertyObjAttribute<pEnum>::getPropertyObj()
{
	return this->propertyObj;
}

template<class pEnum>
inline pEnum PropertyObjAttribute<pEnum>::getPropertyAttribute()
{
	return this->propertyAttribute;
}

template<class pEnum>
inline const std::string& PropertyObjAttribute<pEnum>::getPropertyObj() const
{
	return this->propertyObj;
}

template<class pEnum>
inline const pEnum& PropertyObjAttribute<pEnum>::getPropertyAttribute() const
{
	return this->propertyAttribute;
}

/*Definition of the Operator with overloading*/
template<class pEnum>
inline bool operator==(const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) {
	return lhs.getPropertyObj() == rhs.getPropertyObj() && lhs.getPropertyAttribute() == lhs.getPropertyAttribute();
}
template<class pEnum>
inline bool operator!=(const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) { return !operator==(lhs, rhs); }

template<class pEnum>
inline bool operator< (const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) {
	// std::tuple's lexicographic ordering does all the actual work for you
	// and using std::tie means no actual copies are made
	return std::tie(lhs.getPropertyObj(), lhs.getPropertyAttribute()) < std::tie(rhs.getPropertyObj(), rhs.getPropertyAttribute());
}

template<class pEnum>
inline bool operator> (const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) { return  operator< (rhs, lhs); }

template<class pEnum>
inline bool operator<=(const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) { return !operator> (lhs, rhs); }

template<class pEnum>
inline bool operator>=(const PropertyObjAttribute<pEnum>& lhs, const PropertyObjAttribute<pEnum>& rhs) { return !operator< (lhs, rhs); }