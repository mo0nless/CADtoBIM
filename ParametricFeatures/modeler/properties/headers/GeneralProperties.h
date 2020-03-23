#pragma once

#include <string>


class GeneralProperties {

private:
	std::string mElementClassName;
	std::string mElementDescriptorName;

	long mElementId;
	long mCurrentElementId;

	bool mIsSmartFeature;

public:
	GeneralProperties();

	std::string getElementClassName();
	void setElementClassName(std::string newClassName);

	std::string getElementDescriptorName();
	void setElementDescriptorName(std::string newElementDescriptorName);
	
	long getElementId();
	void setElementId(long newElementId);

	bool getIsSmartFeature();
	void setIsSmartFeature(bool newIsSmartFeature);

	long getCurrentElementId();
	void setCurrentElementId(long newCurrentElementId);




};