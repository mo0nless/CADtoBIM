#pragma once


/**
 *  The representation of the smartfeature tree structure, where every node has a parent and 2 children(binary tree without order)
 */
class SmartFeatureTreeNode {

private:

	long globalNodeId;
	long localNodeId;
	long localParentNodeId;

	SmartFeatureTreeNode* rightNode;
	SmartFeatureTreeNode* leftNode;

public:
	SmartFeatureTreeNode(long newGlobalNodeId,long newLocalNodeId,long newLocalParentNodeId);

	void setLeftNode(SmartFeatureTreeNode* newLeftNode);
	void setRightNode(SmartFeatureTreeNode* newRightNode);

	SmartFeatureTreeNode* getLeftNode();
	SmartFeatureTreeNode* getRightNode();

	long getGlobalNodeId();
	long getLocalNodeId();
	long getLocalParentNodeId();
};