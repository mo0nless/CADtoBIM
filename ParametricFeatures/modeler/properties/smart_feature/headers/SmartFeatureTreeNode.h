#pragma once
#include "SmartFeatureProperties.h"


/**
 *  The representation of the smartfeature tree structure, where every node has a parent and 2 children(binary tree without order)
 */
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