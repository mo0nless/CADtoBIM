#pragma once

#include "../headers/InitializationHelper.h"
#include "../../../ifc/main/headers/IfcBuilder.h"
#include "../../../ifc/general_information/headers/IfcGeneralInformation.h"
#include "../../../common/utils/headers/ExplorerStructure.h"
#include "../../../common/utils/headers/NotificationMessage.h"
//#include "../../../interface_dialog/ListModelManager.h"

namespace Init
{
	struct Initialization
	{
		static vector<PersistentElementRefP> allGraphicElements;
		//static vector<PersistentElementRefP> selectedGraphicElements;

		static StatusInt startIfcConverter(bool onlySelectedElm = false)
		{
			NotificationManager::SetDispatchEvents(true);

			Logs::Logger::getLogger()->logInfo(__FILE__, __LINE__, __func__, "!!-- Starting application --!!");

			string statusMessage;

			if (true)//(NotificationManager::MessageBoxValue::MESSAGEBOX_VALUE_Yes == mainNotification)
			{

				statusMessage = "Start IFC Conversion";
				NotificationMessage::send(StringUtils::getWString(statusMessage), OutputMessagePriority::Debug);

				/*vector<DictionaryProperties*> propsDictVec;
				vector<SmartFeatureContainer*> smartFeatureContainerVector;*/

				string errorMessageModelProcessing = "Error at processing the dgn model";

				InitializationHelper* initializationHelper = new InitializationHelper(allGraphicElements);

				try {
					initializationHelper->processDgnGraphicsElements();
				}
				catch (exception& ex) {
					Logs::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, ex, errorMessageModelProcessing);

					NotificationMessage::createErrorNotificationMessage(errorMessageModelProcessing);
				}
				catch (...) {
					Logs::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, errorMessageModelProcessing);

					NotificationMessage::createErrorNotificationMessage(errorMessageModelProcessing);

				}


				string errorMessageIfcConversion = "Error at creating the IFC file";

				try {
					IfcBuilder* ifcBuilder = new IfcBuilder();
					ifcBuilder->buildIfc(initializationHelper->getIfcElementBundleVector());
				}
				catch (exception& ex) {
					Logs::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, ex, errorMessageIfcConversion);

					NotificationMessage::createErrorNotificationMessage(errorMessageIfcConversion);
				}
				catch (...) {
					Logs::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, errorMessageIfcConversion);

					NotificationMessage::createErrorNotificationMessage(errorMessageIfcConversion);

				}

				string outputFolderPath = SessionManager::getInstance()->getOutputFolderPath();

				char myDocPath[MAX_PATH];
				strcpy(myDocPath, outputFolderPath.c_str());

				ShellExecute(NULL, "open", myDocPath, NULL, NULL, SW_SHOW);

				statusMessage = "End IFC Conversion";

				NotificationMessage::send(StringUtils::getWString(statusMessage), OutputMessagePriority::Debug);
				Logs::Logger::getLogger()->logInfo(__FILE__, __LINE__, __func__, "!!-- Ended the application process --!!");
			}
			else {
				statusMessage = "Declined IFC Conversion";

				NotificationMessage::send(StringUtils::getWString(statusMessage), OutputMessagePriority::Debug);

				Logs::Logger::getLogger()->logInfo(__FILE__, __LINE__, __func__, "!!-- Declined the start of the application --!!");
			}

			return SUCCESS;
		}

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
