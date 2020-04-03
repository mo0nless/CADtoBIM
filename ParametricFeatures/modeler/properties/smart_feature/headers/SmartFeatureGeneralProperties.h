#pragma once

#include "../../../../common/utils/headers/SmartFeatureTypeEnumUtils.h"
#include "../../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"

class SmartFeatureGeneralProperties {

private:
	long mLocalNodeId;
	long mLocalParentNodeId;

	SmartFeatureTypeEnum mSmartFeatureTypeEnum;
	CreateSolidFunctionsEnum mCreateSolidFunctionsEnum;

public:
	SmartFeatureGeneralProperties();

	long getLocalNodeId();
	void setLocalNodeId(long newLocalNodeId);

	long getLocalParentNodeId();
	void setLocalParentNodeId(long newLocalParentNodeId);

	SmartFeatureTypeEnum getSmartFeatureTypeEnum();
	void setSmartFeatureTypeEnum(std::string newClassName);
	void setSmartFeatureTypeEnum(SmartFeatureTypeEnum newSmartFeatureTypeEnum);

	CreateSolidFunctionsEnum getCreateSolidTypeEnum();

};