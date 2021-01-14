#pragma once

/**
 * @file Initialization.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../headers/InitializationHelper.h"
#include "../../../ifc/main/headers/IfcBuilder.h"
#include "../../../common/utils/headers/ExplorerStructure.h"
#include "../../../common/utils/headers/NotificationMessage.h"



/** @defgroup data_processing Data Processing
*  @{
*/

using namespace Ifc::Main;

namespace DataProcessing
{
	namespace Initialization
	{
		/**
		 * @brief Intialiazation class that collect element and start the process of conversion
		 * 
		 */
		struct Initialization
		{
			static vector<PersistentElementRefP> allGraphicElements;

			/**
			 * @brief Method that start the process of conversion
			 * 
			 * @return StatusInt 
			 */
			static StatusInt startIfcConverter()
			{
				NotificationManager::SetDispatchEvents(true);

				Logging::Logger::getLogger()->logInfo(__FILE__, __LINE__, __func__, "!!-- Starting application --!!");

				string statusMessage = "Start IFC Conversion";

				NotificationMessage::send(StringUtils::getWString(statusMessage), OutputMessagePriority::Debug);

				string errorMessageModelProcessing = "Error at processing the dgn model";

				InitializationHelper* initializationHelper = new InitializationHelper(allGraphicElements);

				try {
					initializationHelper->processDgnGraphicsElements();
				}
				catch (exception& ex) {
					Logging::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, ex, errorMessageModelProcessing);

					NotificationMessage::createErrorNotificationMessage(errorMessageModelProcessing);
				}
				catch (...) {
					Logging::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, errorMessageModelProcessing);

					NotificationMessage::createErrorNotificationMessage(errorMessageModelProcessing);

				}


				string errorMessageIfcConversion = "Error at creating the IFC file";

				try {
					IfcBuilder* ifcBuilder = new IfcBuilder();
					ifcBuilder->buildIfc(initializationHelper->getIfcElementBundleVector());
				}
				catch (exception& ex) {
					Logging::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, ex, errorMessageIfcConversion);

					NotificationMessage::createErrorNotificationMessage(errorMessageIfcConversion);
				}
				catch (...) {
					Logging::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, errorMessageIfcConversion);

					NotificationMessage::createErrorNotificationMessage(errorMessageIfcConversion);

				}

				string outputFolderPath = SessionManager::getInstance()->getOutputFolderPath();

				char myDocPath[MAX_PATH];
				strcpy(myDocPath, outputFolderPath.c_str());

				ShellExecute(NULL, "open", myDocPath, NULL, NULL, SW_SHOW);

				statusMessage = "End IFC Conversion";

				NotificationMessage::send(StringUtils::getWString(statusMessage), OutputMessagePriority::Debug);
				Logging::Logger::getLogger()->logInfo(__FILE__, __LINE__, __func__, "!!-- Ended the application process --!!");


				return SUCCESS;
			}

			/**
			 * @brief Method to collect all elements 
			 * 
			 */
			static void collectsAllElements()
			{
				allGraphicElements.clear();

				auto pGraElement = ISessionMgr::GetActiveDgnModelP()->GetGraphicElementsP();

				for (PersistentElementRefP elemRef : *pGraElement)
				{
					//ElementHandle currentElem(elemRef);
					allGraphicElements.push_back(elemRef);
				}
			};
		};

		vector<PersistentElementRefP> Initialization::allGraphicElements;
	}
}
/** @} */ // end of Data Processing