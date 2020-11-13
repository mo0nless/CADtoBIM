#include "../headers/IfcPropertiesEnhancer.h"

void IfcPropertiesEnhancer::enhance(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcOwnerHistory* ownerHistory)
{
	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Starting enhancing the IFC properties -!");

	typedef Ifc4::IfcGloballyUniqueId guid;
	vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;
	this->_ownerHistory = ownerHistory;

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcElementBundle*& ifcElementBundle = ifcBundleVector.at(i);

			Ifc4::IfcObjectDefinition::list::ptr ifcObjectDefinitionList(new Ifc4::IfcObjectDefinition::list());
			ifcObjectDefinitionList->push(ifcElementBundle->getIfcElement());

			for (auto const& readerPropertyBundle : dictionaryProperties.getElementReaderPropertiesBundleVector()) {
				Ifc4::IfcPropertySet* ifcPropertySet = createIfcPropertySet(*readerPropertyBundle,file);

				Ifc4::IfcRelDefinesByProperties* ifcRelDefinesByProperties = new Ifc4::IfcRelDefinesByProperties(
					guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor() + readerPropertyBundle->getCassName()),
					//file.getSingle<Ifc4::IfcOwnerHistory>(), 
					this->_ownerHistory,
					ifcElementBundle->getModelerElementDescriptor() + readerPropertyBundle->getCassName(), 
					boost::none, 
					ifcObjectDefinitionList, 
					ifcPropertySet
				);
				file.addEntity(ifcRelDefinesByProperties);
			}

		}
	}
	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Ended enhancing the IFC properties -!");


}

Ifc4::IfcPropertySet* IfcPropertiesEnhancer::createIfcPropertySet(ReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcProperty::list::ptr ifcPropertyList(new Ifc4::IfcProperty::list());

	for (auto const& readerPropertyDefinition : readerPropertiesBundle.getProperties()) 
	{
		PropertyTypeEnum propertyTypeEnum = PropertyTypeEnumUtils::getEnumByStringValue(readerPropertyDefinition->getPropertyTypeName());

		// TODO [MP] to be reviews if possible to extract and add unit/context
		if (propertyTypeEnum == PropertyTypeEnum::BINARY || propertyTypeEnum == PropertyTypeEnum::BOOLEAN || propertyTypeEnum == PropertyTypeEnum::DATETIME ||
			propertyTypeEnum == PropertyTypeEnum::DOUBLE || propertyTypeEnum == PropertyTypeEnum::INTEGER || propertyTypeEnum == PropertyTypeEnum::LONG ||
			propertyTypeEnum == PropertyTypeEnum::STRING) {

			ifcPropertyList->push(createIfcBasicProperty(*readerPropertyDefinition));
		}
		else if (propertyTypeEnum == PropertyTypeEnum::POINT2D || propertyTypeEnum == PropertyTypeEnum::POINT3D) {

			ifcPropertyList->push(createIfcComplexProperty(*readerPropertyDefinition));
		}
		else {
			_logger->logWarning(__FILE__, __LINE__, __func__, "Unmapped property");
			// log unmapped property type
		}

/*		string normalized_value = StringUtils::getNormalizedString(readerPropertyDefinition->getPropertyValueAsString());
		ifcPropertyList->push(new Ifc4::IfcProperty(readerPropertyDefinition->getPropertyName(), normalized_value));*/		
	}

	Ifc4::IfcPropertySet* ifcPropertySet = new Ifc4::IfcPropertySet(
		guid::IfcGloballyUniqueId(readerPropertiesBundle.getCassName()), 
		//file.getSingle<Ifc4::IfcOwnerHistory>(),
		this->_ownerHistory,
		readerPropertiesBundle.getCassName(), 
		boost::none, 
		ifcPropertyList
	);

	file.addEntity(ifcPropertySet);

	return ifcPropertySet;
}

Ifc4::IfcProperty* IfcPropertiesEnhancer::createIfcBasicProperty(ReaderPropertyDefinition& readerPropertyDefinition)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	// TODO [MP] look for a binary value and check it should be translated in Ifc(binary->int or simply pur the value as text???)
	Ifc4::IfcValue* ifcValue;
	PropertyTypeEnum propertyTypeEnum = PropertyTypeEnumUtils::getEnumByStringValue(readerPropertyDefinition.getPropertyTypeName());
	if (propertyTypeEnum == PropertyTypeEnum::INTEGER) {
		ifcValue = new Ifc4::IfcInteger(readerPropertyDefinition.getPropertyValue().GetInteger());
	} else if (propertyTypeEnum == PropertyTypeEnum::DOUBLE) {
		ifcValue = new Ifc4::IfcReal(readerPropertyDefinition.getPropertyValue().GetDouble());
	} else if (propertyTypeEnum == PropertyTypeEnum::LONG) {
		ifcValue = new Ifc4::IfcReal(readerPropertyDefinition.getPropertyValue().GetLong());
	} else if (propertyTypeEnum == PropertyTypeEnum::BOOLEAN) {
		ifcValue = new Ifc4::IfcBoolean(readerPropertyDefinition.getPropertyValue().GetBoolean());
	} else if (propertyTypeEnum == PropertyTypeEnum::STRING) {
		ifcValue = new Ifc4::IfcText(StringUtils::getNormalizedString(readerPropertyDefinition.getPropertyValue().GetString()));
	}
	else {
		ifcValue = new Ifc4::IfcText(StringUtils::getNormalizedString(readerPropertyDefinition.getPropertyValue().GetString()));
	}

	return new Ifc4::IfcPropertySingleValue(readerPropertyDefinition.getPropertyName(), readerPropertyDefinition.getPropertyName(),
		ifcValue, 0);
}

Ifc4::IfcProperty * IfcPropertiesEnhancer::createIfcComplexProperty(ReaderPropertyDefinition & readerPropertyDefinition)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	Ifc4::IfcProperty::list::ptr ifcPropertyList(new Ifc4::IfcProperty::list());

	Ifc4::IfcValue* ifcValue;
	Ifc4::IfcPropertySingleValue* ifcPropertySingleValue;
	PropertyTypeEnum propertyTypeEnum = PropertyTypeEnumUtils::getEnumByStringValue(readerPropertyDefinition.getPropertyTypeName());
	if (propertyTypeEnum == PropertyTypeEnum::POINT2D) {
		DPoint2d point = readerPropertyDefinition.getPropertyValue().GetPoint2D();

		ifcValue = new Ifc4::IfcReal(point.x);
		ifcPropertySingleValue = new Ifc4::IfcPropertySingleValue(readerPropertyDefinition.getPropertyName(), readerPropertyDefinition.getPropertyName(),
			ifcValue, 0);

		ifcPropertyList->push(ifcPropertySingleValue);

		ifcValue = new Ifc4::IfcReal(point.y);
		ifcPropertySingleValue = new Ifc4::IfcPropertySingleValue(readerPropertyDefinition.getPropertyName(), readerPropertyDefinition.getPropertyName(),
			ifcValue, 0);

		ifcPropertyList->push(ifcPropertySingleValue);
	} else 	if (propertyTypeEnum == PropertyTypeEnum::POINT3D) {
		DPoint3d point = readerPropertyDefinition.getPropertyValue().GetPoint3D();

		ifcValue = new Ifc4::IfcReal(point.x);
		ifcPropertySingleValue = new Ifc4::IfcPropertySingleValue(readerPropertyDefinition.getPropertyName(), readerPropertyDefinition.getPropertyName(),
			ifcValue, 0);

		ifcPropertyList->push(ifcPropertySingleValue);

		ifcValue = new Ifc4::IfcReal(point.y);
		ifcPropertySingleValue = new Ifc4::IfcPropertySingleValue(readerPropertyDefinition.getPropertyName(), readerPropertyDefinition.getPropertyName(),
			ifcValue, 0);

		ifcPropertyList->push(ifcPropertySingleValue);

		ifcValue = new Ifc4::IfcReal(point.z);
		ifcPropertySingleValue = new Ifc4::IfcPropertySingleValue(readerPropertyDefinition.getPropertyName(), readerPropertyDefinition.getPropertyName(),
			ifcValue, 0);

		ifcPropertyList->push(ifcPropertySingleValue);
	}
	else {
		_logger->logWarning(__FILE__, __LINE__, __func__, "Unhandled propertyTypeEnum");
	}


	return new Ifc4::IfcComplexProperty(readerPropertyDefinition.getPropertyName(), readerPropertyDefinition.getPropertyName(),
		readerPropertyDefinition.getPropertyTypeName(), ifcPropertyList);

}
