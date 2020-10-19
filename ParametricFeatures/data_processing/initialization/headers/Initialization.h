#pragma once

#include "../headers/InitializationHelper.h"
#include "../../../ifc/main/headers/IfcBuilder.h"
#include "../../../common/utils/headers/ExplorerStructure.h"
#include "../../../common/utils/headers/NotificationMessage.h"

struct Initialization
{
	static StatusInt startIfcConverter()
	{
		NotificationManager::SetDispatchEvents(true);

		ExplorerStructure::createFilesStructure();
		Logs::Logger::getLogger()->logInfo(__FILE__, __LINE__, __func__, "!!-- Starting application --!!");

		string fileName = StringUtils::getNormalizedString(ISessionMgr::GetActiveDgnFile()->GetFileName());
		SessionManager::getInstance()->setDgnFileName(fileName);
		fileName = SessionManager::getInstance()->getDgnFileName();

		std::ostringstream stringStream;
		stringStream << "Do you want to convert the active " << fileName;
		stringStream << " to IFC? ";
		stringStream << endl;

		string mainNotificationMessage = stringStream.str();

		/*NotificationManager::MessageBoxValue mainNotification = createNotificationMessage(NotificationManager::MessageBoxType::MESSAGEBOX_TYPE_YesNo,
		mainNotificationMessage, NotificationManager::MessageBoxIconType::MESSAGEBOX_ICON_Question);*/


		string statusMessage;

		if (true)//(NotificationManager::MessageBoxValue::MESSAGEBOX_VALUE_Yes == mainNotification)
		{

			statusMessage = "Start IFC Conversion";
			NotificationMessage::send(StringUtils::getWString(statusMessage), OutputMessagePriority::Debug);

			vector<DictionaryProperties*> propsDictVec;
			vector<SmartFeatureContainer*> smartFeatureContainerVector;

			string errorMessageModelProcessing = "Error at processing the dgn model";

			try {
				InitializationHelper* initializationHelper = new InitializationHelper();
				initializationHelper->processDgnGraphicsElements(propsDictVec, smartFeatureContainerVector);
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
				ifcBuilder->buildIfc(propsDictVec, smartFeatureContainerVector);
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
};
