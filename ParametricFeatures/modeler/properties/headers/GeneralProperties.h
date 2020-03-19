#pragma once

#include <string>


class GeneralProperties {

private:
	std::string className;

	long elementId;
	long currentElementId;

	bool isSmartFeature;

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




};