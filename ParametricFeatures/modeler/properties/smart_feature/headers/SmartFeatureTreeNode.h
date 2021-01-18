#pragma once

/**
 * @file SmartFeatureTreeNode.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

namespace Modeler
{
	namespace Properties
	{
		/**
		 *  @brief The representation of the smartfeature tree structure, where every node has a parent and 2 children(binary tree without order)
		 */
		class SmartFeatureTreeNode {

		private:

			long globalNodeId;
			long localNodeId;
			long localParentNodeId;

			SmartFeatureTreeNode* rightNode;
			SmartFeatureTreeNode* leftNode;

		public:

			/**
			 * @brief Construct a new Smart Feature Tree Node object
			 * 
			 * @param newGlobalNodeId The current Global Node ID
			 * @param newLocalNodeId The current Local Node ID
			 * @param newLocalParentNodeId the Parent ID
			 */
			SmartFeatureTreeNode(long newGlobalNodeId, long newLocalNodeId, long newLocalParentNodeId);

			/**
			 * @brief Set the Left Node object
			 * 
			 * @param newLeftNode 
			 */
			void setLeftNode(SmartFeatureTreeNode* newLeftNode);

			/**
			 * @brief Set the Right Node object
			 * 
			 * @param newRightNode 
			 */
			void setRightNode(SmartFeatureTreeNode* newRightNode);

			/**
			 * @brief Get the Left Node object
			 * 
			 * @return SmartFeatureTreeNode* 
			 */
			SmartFeatureTreeNode* getLeftNode();

			/**
			 * @brief Get the Right Node object
			 * 
			 * @return SmartFeatureTreeNode* 
			 */
			SmartFeatureTreeNode* getRightNode();

			/**
			 * @brief Get the Global Node Id object
			 * 
			 * @return long 
			 */
			long getGlobalNodeId();

			/**
			 * @brief Get the Local Node Id object
			 * 
			 * @return long 
			 */
			long getLocalNodeId();

			/**
			 * @brief Get the Local Parent Node Id object
			 * 
			 * @return long 
			 */
			long getLocalParentNodeId();
		};
	}
}