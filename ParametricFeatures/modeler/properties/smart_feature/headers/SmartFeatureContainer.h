#pragma once

#include "SmartFeatureTreeNode.h"


/**
 *   Class contains the tree structure(root) of the smartfeature and methods to interact with it(insert, search...)
 */
class SmartFeatureContainer {

private:
	long elementId;
	SmartFeatureTreeNode* root;

public:
	SmartFeatureContainer(long newElementId);
	/**
	 *  Method used to insert a new node int the tree based on it's parent id
	 *  @param newCurrentElementId[in] the id of the current smartfeature element
	 *  @param newLocalNodeId[in] the local node id of the tree
	 *  @param newParentLocalNodeId[in] the parent node id, based on which it will be inserted
	 *  @param newLeafElementId[in] the leaf id/the if of the referenced element
	 */
	void insertNodeInTree(long newLocalNodeId, long newParentLocalNodeId, long newLeafElementId);
	int getTreeMaxDepth(SmartFeatureTreeNode* tree);

	SmartFeatureTreeNode* searchByElementLocalNodeId(SmartFeatureTreeNode* searchNode, long searchedLocalId);
	SmartFeatureTreeNode* searchByElementGlobalId(SmartFeatureTreeNode* searchNode, long searchedByElementId);

	SmartFeatureTreeNode* getRoot();
	long getElementId();

};