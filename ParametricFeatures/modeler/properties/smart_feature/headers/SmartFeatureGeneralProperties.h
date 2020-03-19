#pragma once

#include "../../../../common/utils/headers/SmartFeatureTypeEnumUtils.h"

class SmartFeatureGeneralProperties {

private:
	long localNodeId;
	long localParentNodeId;

	SmartFeatureTypeEnum::SmartFeatureTypeEnum smartFeatureTypeEnum;


public:
	SmartFeatureGeneralProperties();

	long getLocalNodeId();
	void setLocalNodeId(long newLocalNodeId);

	long getLocalParentNodeId();
	void setLocalParentNodeId(long newLocalParentNodeId);

	SmartFeatureTypeEnum::SmartFeatureTypeEnum getSmartFeatureTypeEnum();
	void setSmartFeatureTypeEnum(SmartFeatureTypeEnum::SmartFeatureTypeEnum newSmartFeatureTypeEnum);
};