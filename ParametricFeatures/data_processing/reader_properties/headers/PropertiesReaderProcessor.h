#pragma once

/**
 * @file PropertiesReaderProcessor.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../stdafx.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/SmartFeatureTypeEnumUtils.h"

#include "../../../ifc/bundle/headers/IfcGraphicPropertiesBundle.h"
#include "../../../ifc/bundle/headers/IfcReaderPropertiesBundle.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"

#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"
#include "../../../common/models/headers/SessionManager.h"


#include <regex>

/** @ingroup data_processing Data Processing
*  @{
*/

using namespace Ifc::Bundle;
using namespace Common::Utilities;
using namespace Common::Models;
using namespace Modeler::Properties;

namespace DataProcessing
{
	namespace ReaderProperties
	{
		/**
		 * @brief Class for collecting the non-graphical properties of an element.
		 * This class use the ECquery system for retreiving information from the Bentley manager
		 * and store them in a vector of IfcReaderPropertiesBundle.
		 * 
		 * @see IfcReaderPropertiesBundle
		 */
		class PropertiesReaderProcessor
		{
		public:
			/**
			 * @brief 
			 * 
			 * @param currentElem the current element
			 * @param ifcGraphicPropertiesBundle the pointer to the ifcGraphicPropertiesBundle
			 * @return vector<IfcReaderPropertiesBundle*> 
			 */
			vector<IfcReaderPropertiesBundle*> processElementReaderProperties(ElementHandleCR currentElem, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle = nullptr);

			/**
			 * @brief Get the Instance object
			 * 
			 * @return PropertiesReaderProcessor* 
			 */
			static PropertiesReaderProcessor* getInstance()
			{
				call_once(initInstanceFlag, &PropertiesReaderProcessor::initPropertiesReaderProcessor);
				return _PropertiesReaderProcessor;
			};

			/**
			 * @brief Get the Element Class Name 
			 * 
			 * @return string 
			 */
			string getElementClassName();
		private:
			PropertiesReaderProcessor();

			//! Element Class Name
			string _elemClassName;

			Logging::Logger* _logger = Logging::Logger::getLogger();

			//! Handles persistance of ECInstances
			DgnECManagerR ecMgr = DgnECManager::GetManager();

			static PropertiesReaderProcessor* _PropertiesReaderProcessor;
			static once_flag initInstanceFlag;

			//! Instance creator
			static void initPropertiesReaderProcessor()
			{
				_PropertiesReaderProcessor = new PropertiesReaderProcessor();
			}

			//! Mapper of properties for each ECInstance inside the IfcReaderPropertiesBundle
			void mapECPropertiesToReaderProperties(DgnElementECInstanceP dgnElementECInstanceP, IfcReaderPropertiesBundle *&IfcReaderPropertiesBundle);
		};
	}
}
/** @} */ // end of Data Processing
