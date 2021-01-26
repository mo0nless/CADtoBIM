#pragma once

/**
 * @file InitializationHelper.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../logging/headers/Logger.h"
#include "../../graphic_properties/headers/GraphicsProcessor.h"
#include "../../reader_properties/headers/PropertiesReaderProcessor.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/models/headers/SessionManager.h"
#include "../../../modeler/data_writer/headers/ModelerDataWriterManager.h"
#include <DgnView/SelectionSetManager.h>   

/** @ingroup data_processing Data Processing
*  @{
*/

using namespace DataProcessing::GraphicsProperties;
using namespace DataProcessing::ReaderProperties;
using namespace Common::Utilities;
using namespace Common::Models;
using namespace Common;
using namespace Modeler::DataWriter;
using namespace std;

namespace DataProcessing
{
	namespace Initialization
	{
		/**
		 * @brief Initialization Helper class to parse the geometry of the elements collected
		 * 
		 */
		class InitializationHelper
		{
		public:
			/**
			 * @brief Construct a new Initialization Helper object
			 * 
			 * @param allGraphicElements 
			 */
			InitializationHelper(vector<PersistentElementRefP> allGraphicElements);

			/**
			 * @brief Process elements collected
			 * 
			 */
			void processDgnGraphicsElements();

			/**
			 * @brief Get the Ifc Element Bundle Vector object containing the geometry and properties
			 * 
			 * @return vector<IfcElementBundle*>& 
			 */
			vector<IfcElementBundle*>& getIfcElementBundleVector();

			/**
			 * @brief Set the Ifc Export Settings object
			 * 
			 * @param brepTypeExport BSpline = 0, Meshes = 1
			 * @param activateBRepExport 
			 * @param selectedElementsExport
			 * @param selectedElementsExport
			 */
			void setIfcExportSettings(int brepTypeExport, bool activateBRepExport, bool selectedElementsExport, bool activeLevelElementsExport);

		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			/**
			 * @brief Create a Smart Feature Container object
			 * 
			 * @param currentElem the element
			 * @return SmartFeatureContainer* 
			 */
			SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem);

			/**
			 * @brief Iterates to all sub-geometry that belongs to the ElementRef
			 * 
			 * @param elementRefP the element ref pointer
			 * @param ifcElementBundle the Element bundle where to store all the sub-geometry
			 * @return StatusInt 
			 */
			StatusInt iterateSubElements(ElementRefP elementRefP, IfcElementBundle*& ifcElementBundle);

			void processSingleElementRef(ElementRefP elementRef);
			
			DgnModelP _dgnModel;

			ModelerDataWriterManager* _modelerDataWriterManager;
			PropertiesReaderProcessor* _propertiesReaderProcessor;

			int _brepTypeExport;
			bool _activateBRepExport;
			bool _selectedElementsExport;
			bool _activeLevelElementsExport;

			Utilities::DialogCompletionBar* _progressBar;

			vector<PersistentElementRefP> _allGraphicElements;

			vector<IfcElementBundle*> _ifcElementBundleVector;
		};
	}
}
/** @} */ // end of Data Processing