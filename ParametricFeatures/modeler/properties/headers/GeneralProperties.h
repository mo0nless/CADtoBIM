#pragma once

#include <string>
#include "../../../common/enums/headers/PrimitiveTypeEnum.h"

class GeneralProperties {

private:
	std::string className;
	long elementId;
	long currentElementId;

	long localNodeId;
	long localParentNodeId;

	bool isSmartFeature;

	PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum;

public:
	GeneralProperties();

	std::string getClassName();
	void setClassName(std::string newClassName);

	long getElementId();
	void setElementId(long newElementId);

	bool getIsSmartFeature();
	void setIsSmartFeature(bool newIsSmartFeature);

	long getCurrentElementId();
	void setCurrentElementId(long newCurrentElementId);

	long getLocalNodeId();
	void setLocalNodeId(long newLocalNodeId);

	long getLocalParentNodeId();
	void setLocalParentNodeId(long newLocalParentNodeId);

	PrimitiveTypeEnum::PrimitiveTypeEnum getPrimitiveTypeEnum();
	void setPrimitiveTypeEnum(PrimitiveTypeEnum::PrimitiveTypeEnum newPrimitiveTypeEnum);
};