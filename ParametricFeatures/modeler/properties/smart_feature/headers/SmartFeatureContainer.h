#pragma once

/**
 * @file SmartFeatureContainer.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "SmartFeatureTreeNode.h"

using namespace Modeler::Properties;

namespace Modeler
{
	namespace Properties
	{
		/**
		 *   @brief Class contains the tree structure(root) of the smartfeature and methods to interact with it(insert, search...)
		 */
		class SmartFeatureContainer {

		private:
			long elementId;
			SmartFeatureTreeNode* root;

		public:
			SmartFeatureContainer(long newElementId);
			/**
			 *  @brief Method used to insert a new node int the tree based on it's parent id
			 *  @param newCurrentElementId[in] the id of the current smartfeature element
			 *  @param newLocalNodeId[in] the local node id of the tree
			 *  @param newParentLocalNodeId[in] the parent node id, based on which it will be inserted
			 *  @param newLeafElementId[in] the leaf id/the if of the referenced element
			 */
			void insertNodeInTree(long newLocalNodeId, long newParentLocalNodeId, long newLeafElementId);

			/**
			 * @brief Get the Tree Max Depth of the SmartFeatureTreeNode object
			 * 
			 * @param tree SmartFeatureTreeNode
			 * @return int 
			 */
			int getTreeMaxDepth(SmartFeatureTreeNode* tree);

			/**
			 * @brief Search the SmartFeatureTreeNode by Element Local NodeId
			 * 
			 * @param searchNode the node SmartFeatureTreeNode
			 * @param searchedLocalId the Element Local ID
			 * @return SmartFeatureTreeNode* 
			 */
			SmartFeatureTreeNode* searchByElementLocalNodeId(SmartFeatureTreeNode* searchNode, long searchedLocalId);

			/**
			 * @brief Search the SmartFeatureTreeNode by Element Global NodeId
			 * 
			 * @param searchNode the node SmartFeatureTreeNode
			 * @param searchedLocalId the Element Global ID
			 * @return SmartFeatureTreeNode* 
			 */
			SmartFeatureTreeNode* searchByElementGlobalId(SmartFeatureTreeNode* searchNode, long searchedByElementId);

			/**
			 * @brief Get the Root of thee Tree object
			 * 
			 * @return SmartFeatureTreeNode* 
			 */
			SmartFeatureTreeNode* getRoot();

			/**
			 * @brief Get the Element Id of the SmartFeatureContainer object
			 * 
			 * @return long 
			 */
			long getElementId();

		};
	}
}