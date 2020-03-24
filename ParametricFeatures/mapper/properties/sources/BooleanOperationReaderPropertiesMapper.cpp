#include "../headers/BooleanOperationReaderPropertiesMapper.h"

void BooleanOperationReaderPropertiesMapper::mapBooleanOperationReaderPropertiesToReaderProperties(std::string labelValue, ECValue eCValue, ReaderProperties & readerProperties)
{
	if (ReaderPropertiesEnum::getElementPropertiesEnumByStringValue(labelValue) == ReaderPropertiesEnum::ReaderPropertiesEnum::BOOLEAN_FUNCTION)
	{
		BooleanOperationProperties* booleanOperationProperties = new BooleanOperationProperties();
		booleanOperationProperties->setBooleanFunction(eCValue.GetInteger());
		readerProperties.setBooleanOperationProperties(booleanOperationProperties);
	}
}
