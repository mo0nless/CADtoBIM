#pragma once
#include "../../../properties/headers/GeneralProperties.h"
#include "../../../properties/headers/ReaderProperties.h"
#include "../../../properties/headers/GraphicProperties.h"

/**
 *  The representation of the smartfeature tree structure, where every node has a parent and 2 children(binary tree without order)
 */
class SmartFeatureTreeNode {

private:
	GeneralProperties* generalProperties;
	ReaderProperties* readerProperties;
	GraphicProperties* graphicProperties;

	SmartFeatureTreeNode* rightNode;
	SmartFeatureTreeNode* leftNode;

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