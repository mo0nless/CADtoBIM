#pragma once

#include "../../../../common/enums/headers/SmartFeatureTypeEnum.h"

class SmartFeatureGeneralProperties {

private:
	long mLocalNodeId;
	long mLocalParentNodeId;

	SmartFeatureTypeEnum::SmartFeatureTypeEnum mSmartFeatureTypeEnum;


public:
	SmartFeatureGeneralProperties();

	long getLocalNodeId();
	void setLocalNodeId(long newLocalNodeId);

	long getLocalParentNodeId();
	void setLocalParentNodeId(long newLocalParentNodeId);

	SmartFeatureTypeEnum::SmartFeatureTypeEnum getSmartFeatureTypeEnum();
	void setSmartFeatureTypeEnum(SmartFeatureTypeEnum::SmartFeatureTypeEnum newSmartFeatureTypeEnum);
};