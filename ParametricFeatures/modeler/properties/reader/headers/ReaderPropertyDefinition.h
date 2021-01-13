#pragma once

#include <Bentley/WString.h>

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

#include <string>

using namespace std;

class ReaderPropertyDefinition {

private:
	string propertyName;
	string propertyTypeName;
	ECValue propertyValue;
	string propertyValueAsString;

public:
	ReaderPropertyDefinition(string newPropertyName,string newPropertyTypeName,ECValue newPropertyValue, string newPropertyValueAsString);

	string getPropertyName();
	string getPropertyTypeName();
	ECValue getPropertyValue();
	string getPropertyValueAsString();

};