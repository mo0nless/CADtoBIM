#pragma once

#include "SmartFeatureTreeNode.h"

class SmartFeatureContainer {

private:
	SmartFeatureTreeNode* root;

public:
	SmartFeatureContainer() {};
	void insertNodeInTree(long newCurrentElementId, long newLocalNodeId, long newParentLocalNodeId, long newElementId);
	SmartFeatureTreeNode* search(SmartFeatureTreeNode* searchNode, long searchLocalId);

	SmartFeatureTreeNode* getRoot();
};