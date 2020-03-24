#pragma once
#include "../../../properties/headers/GeneralProperties.h"
#include "../../../properties/headers/ReaderProperties.h"
#include "../../../properties/headers/GraphicProperties.h"

/**
 *  The representation of the smartfeature tree structure, where every node has a parent and 2 children(binary tree without order)
 */
class SmartFeatureTreeNode {

private:
	GeneralProperties* mGeneralProperties;
	ReaderProperties* mReaderProperties;
	GraphicProperties* mGraphicProperties;

	SmartFeatureTreeNode* mRightNode;
	SmartFeatureTreeNode* mLeftNode;

public:
	SmartFeatureTreeNode();

	GeneralProperties* getGeneralProperties();
	ReaderProperties* getReaderProperties();

	GraphicProperties* getGraphicProperties();
	void setGraphicProperties(GraphicProperties* newGraphicProperties);

	void setLeftNode(SmartFeatureTreeNode* newLeftNode);
	void setRightNode(SmartFeatureTreeNode* newRightNode);

	SmartFeatureTreeNode* getLeftNode();
	SmartFeatureTreeNode* getRightNode();
};