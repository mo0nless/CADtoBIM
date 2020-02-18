#pragma once

#include <string>

class GeneralProperties {

private:
	std::string className;
	long elementId;
	long currentElementId;

	long localNodeId;
	long localParentNodeId;

public:
	GeneralProperties();

	std::string getClassName();
	void setClassName(std::string newClassName);

	long getElementId();
	void setElementId(long newElementId);

	long getCurrentElementId();
	void setCurrentElementId(long newCurrentElementId);

	long getLocalNodeId();
	void setLocalNodeId(long newLocalNodeId);

	long getLocalParentNodeId();
	void setLocalParentNodeId(long newLocalParentNodeId);
};