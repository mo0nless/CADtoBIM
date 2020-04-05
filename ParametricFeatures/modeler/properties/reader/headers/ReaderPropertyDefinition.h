#pragma once

#include <Bentley/WString.h>

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

#include <string>

class ReaderPropertyDefinition {

private:
	std::string propertyName;
	std::string propertyTypeName;
	ECValue propertyValue;

public:
	ReaderPropertyDefinition(std::string newPropertyName,std::string newPropertyTypeName,ECValue newPropertyValue);

	std::string getPropertyName();
	std::string getPropertyTypeName();
	ECValue getPropertyValue();

};