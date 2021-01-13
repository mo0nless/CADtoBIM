#pragma once

#include "../../../stdafx.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/SmartFeatureTypeEnumUtils.h"

#include "../../../ifc/bundle/headers/IfcGraphicPropertiesBundle.h"
#include "../../../data_processing/modeler/properties/smart_feature/headers/SmartFeatureContainer.h"

#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"
#include "../../../common/models/headers/SessionManager.h"


#include <regex>

/** @ingroup data_processing Data Processing
*  @{
*/

using namespace Ifc::Bundle;
using namespace Common::Utilities;
using namespace Common::Models;

namespace DataProcessing
{
	namespace ReaderProperties
	{
		/*====================================================================================+
		* Class for collecting the non-graphical properties of an element.
		* This class use the ECquery system for retreiving information from the Bentley manager
		* and store them in a vector of ReaderPropertiesBundle.
		* @see ReaderPropertiesBundle
		+===============+===============+===============+===============+===============+======*/
		class PropertiesReaderProcessor
		{
		public:
			//! The public method for Processing Element Properties finding ECInstances.
			//! @param[in] the current element
			//! @param[in] the pointer to the ifcGraphicPropertiesBundle
			//! @return a vector of ReaderPropertiesBundle pointers
			vector<ReaderPropertiesBundle*> processElementReaderProperties(ElementHandleCR currentElem, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle = nullptr);

			static PropertiesReaderProcessor* getInstance()
			{
				call_once(initInstanceFlag, &PropertiesReaderProcessor::initPropertiesReaderProcessor);
				return _PropertiesReaderProcessor;
			};
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

			//! Mapper of properties for each ECInstance inside the ReaderPropertiesBundle
			void mapECPropertiesToReaderProperties(DgnElementECInstanceP dgnElementECInstanceP, ReaderPropertiesBundle *&ReaderPropertiesBundle);
		};
	}
}
/** @} */ // end of Data Processing
