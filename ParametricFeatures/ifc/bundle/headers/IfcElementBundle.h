#pragma once

/**
 * @file IfcElementBundle.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>
#include <string>
#include "IfcGraphicPropertiesBundle.h"
#include "IfcReaderPropertiesBundle.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../../modeler/brep_solids/headers/TopologyStructures.h"
#include "../../../ifc/operations_helper/headers/IfcOperationsHelper.h"
#include "../../../common/models/headers/SessionManager.h"

using namespace Ifc::Helper;
using namespace Ifc::Bundle;
using namespace Common::Models;
using namespace Modeler::Properties;
using namespace Modeler::Topology;

namespace Ifc
{
	namespace Bundle
	{
		/**
		 * @brief Ifc Element bundle class that contains all the information of an element:
		 * IfcElement, Reader Properties, Graphic Properties, Name, Class, etc..
		 * 
		 */
		class IfcElementBundle {

		private:
			long modelerElementId;
			string modelerElementDescriptor;

			vector<IfcReaderPropertiesBundle*> ifcElementReaderPropertiesBundleVector;
			vector<IfcGraphicPropertiesBundle*> ifcGraphicPropertiesBundleVector;

			vector<Ifc4::IfcCartesianPoint*> ifcPointsPortsVector;
			vector<Ifc4::IfcDistributionPort*> ifcDistributionPortVector;

			vector<SolidEdge*> smartSolidEdgesCollection;

			Ifc4::IfcElement* ifcElement;

			bool hasConnections;

			bool badIfcElemetBuild = false;

			SmartFeatureContainer* smartFeatureContainer;
			string representationType;
			string mElemClassName;
		public:
			
			/**
			 * @brief Construct a new Ifc Element Bundle object
			 * 
			 * @param newModelerElementId the ID
			 * @param newModelerElementName the description Name
			 */
			IfcElementBundle(long newModelerElementId, string newModelerElementName);

			/**
			 * @brief Get the Element Class Name object
			 * 
			 * @return string 
			 */
			string getElementClassName();

			/**
			 * @brief Set the Element Class Name object
			 * 
			 * @param name 
			 */
			void setElementClassName(string name);

			/**
			 * @brief Set if the Ifc geometric Class object is Bad Constructed
			 * 
			 * @param value 
			 */
			void setBadIfcClassBuild(bool value);

			/**
			 * @brief Get if the Ifc geometric Class object is Bad Constructed
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getBadIfcClassBuild();

			/**
			 * @brief Add a new Ifc Distribution Ports object
			 * 
			 * @param newDistPort 
			 */
			void addIfcDistributionPorts(Ifc4::IfcDistributionPort* newDistPort);

			/**
			 * @brief Add the Ifc Distribution Ports shape as IfcCartesianPoint
			 * 
			 * @remark I used to keep track of the ports parsed at point from IfcShapeEnhancer
			 * @param newIfcPoint 
			 */
			void addIfcPortsPoints(Ifc4::IfcCartesianPoint* newIfcPoint);

			/**
			 * @brief Set the Ifc Element Reader Properties Bundle Vector object
			 * 
			 * @param newReaderPropertiesBundleVector the new set of reader properties
			 */
			void setIfcElementReaderPropertiesBundleVector(vector<IfcReaderPropertiesBundle*> newReaderPropertiesBundleVector);

			/**
			 * @brief Add a new IfcGraphicPropertiesBundle geometry to the element
			 * 
			 * @param newIfcGraphicPropertiesBundle the new geometry
			 */
			void addIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle* newIfcGraphicPropertiesBundle);

			/**
			 * @brief Set the Smart Feature Container object
			 * 
			 * @param newSmartFeatureContainer smart feature container
			 */
			void setSmartFeatureContainer(SmartFeatureContainer*& newSmartFeatureContainer);

			/**
			 * @brief Get the Smart Feature Container object
			 * 
			 * @return SmartFeatureContainer* 
			 */
			SmartFeatureContainer* getSmartFeatureContainer();

			/**
			 * @brief Add the Solid edges collection
			 * 
			 * @param solidEdges 
			 */
			void addSolidEdgesCollection(vector<SolidEdge*> solidEdges);

			/**
			 * @brief Get the Solid Edges Collection object
			 * 
			 * @return vector<SolidEdge*> 
			 */
			vector<SolidEdge*> getSolidEdgesCollection();

			/**
			 * @brief Get the Ifc Element Reader Properties Bundle Vector object
			 * 
			 * @return vector<IfcReaderPropertiesBundle*> 
			 */
			vector<IfcReaderPropertiesBundle*> getIfcElementReaderPropertiesBundleVector();

			/**
			 * @brief Get the Ifc Graphic Properties Bundle Vector object
			 * 
			 * @return vector<IfcGraphicPropertiesBundle*> 
			 */
			vector<IfcGraphicPropertiesBundle*> getIfcGraphicPropertiesBundleVector();

			/**
			 * @brief Get the Ifc Ports IfcCartesianPoint Vector object
			 * 
			 * @return vector<Ifc4::IfcCartesianPoint*> 
			 */
			vector<Ifc4::IfcCartesianPoint*> getIfcPortsPointsVector();

			/**
			 * @brief Get the Ifc Distribution Ports Vector object
			 * 
			 * @return vector<Ifc4::IfcDistributionPort*> 
			 */
			vector<Ifc4::IfcDistributionPort*> getIfcDistributionPortsVector();

			/**
			 * @brief Get the Ifc Element object
			 * 
			 * @return Ifc4::IfcElement* 
			 */
			Ifc4::IfcElement* getIfcElement();

			/**
			 * @brief Set the Ifc Element object
			 * 
			 * @param newIfcElement 
			 */
			void setIfcElement(Ifc4::IfcElement* newIfcElement);

			/**
			 * @brief Get if the Element has Connection ports 
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getHasElementConnection();

			/**
			 * @brief Get the Element Id object
			 * 
			 * @return long 
			 */
			long getElementId();

			/**
			 * @brief Get the Element Descriptor object
			 * 
			 * @return string 
			 */
			string getElementDescriptor();
			
			/**
			 * @brief Get the Is Smart Feature object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsSmartFeature();


		};
	}
}