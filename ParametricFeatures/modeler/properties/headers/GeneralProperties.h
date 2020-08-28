#pragma once

#include <string>

using namespace std;

class GeneralProperties {

private:
	string mElementClassName;
	string mElementDescriptorName;

	long mElementId;
	long mCurrentElementId;

	bool mIsSmartFeature;

public:
	GeneralProperties();

	string getElementClassName();
	void setElementClassName(string newClassName);

	string getElementDescriptorName();
	void setElementDescriptorName(string newElementDescriptorName);
	
	long getElementId();
	void setElementId(long newElementId);

	bool getIsSmartFeature();
	void setIsSmartFeature(bool newIsSmartFeature);

	long getCurrentElementId();
	void setCurrentElementId(long newCurrentElementId);




};