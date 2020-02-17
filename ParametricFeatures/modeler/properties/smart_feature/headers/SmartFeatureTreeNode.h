#pragma once
#include "SmartFeatureProperties.h"

class SmartFeatureTreeNode {

private:
	SmartFeatureProperties* smartFeatureProperties;

	SmartFeatureTreeNode* rightNode;
	SmartFeatureTreeNode* leftNode;

public:
	SmartFeatureTreeNode();

	void setSmartFeatureProperties(SmartFeatureProperties* newSmartFeatureProperties);
	SmartFeatureProperties* getSmartFeatureProperties();

	void setLeftNode(SmartFeatureTreeNode* newLeftNode);
	void setRightNode(SmartFeatureTreeNode* newRightNode);

	SmartFeatureTreeNode* getLeftNode();
	SmartFeatureTreeNode* getRightNode();
};