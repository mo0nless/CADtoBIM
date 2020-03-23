#pragma once

#include "../../../../common/enums/headers/SmartFeatureTypeEnum.h"

class SmartFeatureGeneralProperties {

private:
	long mLocalNodeId;
	long mLocalParentNodeId;

	SmartFeatureTypeEnum smartFeatureTypeEnum;


public:
	SmartFeatureGeneralProperties();

	long getLocalNodeId();
	void setLocalNodeId(long newLocalNodeId);

	long getLocalParentNodeId();
	void setLocalParentNodeId(long newLocalParentNodeId);

	SmartFeatureTypeEnum getSmartFeatureTypeEnum();
	void setSmartFeatureTypeEnum(SmartFeatureTypeEnum newSmartFeatureTypeEnum);
};