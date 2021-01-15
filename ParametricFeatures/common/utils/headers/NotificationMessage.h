#pragma once

/**
 * @file NotificationMessage.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <DgnPlatform/DisplayHandler.h>
#include <Mstn/ElementPropertyUtils.h>
#include <Mstn/MdlApi/dlogbox.r.h>
#include <DgnPlatform/NotificationManager.h>
#include "StringUtils.hpp"

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

using namespace Common::Utilities;

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief Handle notification messages in the bentley message center
		 * 
		 */
		struct NotificationMessage
		{
			/**
			 * @brief Send a message
			 * 
			 * @param element 
			 * @param functionName 
			 * @param messagePriority 
			 */
			static void send(ElementHandle element, WString functionName, OutputMessagePriority messagePriority)
			{
				WString elDescr, myString;

				element.GetHandler().GetDescription(element, elDescr, 100);

				myString.Sprintf(L"Function '%s' ERROR processing the element: %s - %d", 
					StringUtils::getNormalizedString(functionName), 
					StringUtils::getNormalizedString(elDescr), 
					element.GetElementId());

				NotifyMessageDetails message = NotifyMessageDetails(
					messagePriority,
					functionName.c_str(),
					myString.c_str()
				);
				NotificationManager::OutputMessage(message);
			}

			/**
			 * @brief Send a message
			 * 
			 * @param stringValue 
			 * @param messagePriority 
			 */
			static void send(WString stringValue, OutputMessagePriority messagePriority)
			{
				NotifyMessageDetails message = NotifyMessageDetails(
					messagePriority,
					stringValue.c_str()
				);

				NotificationManager::OutputMessage(message);
			}

			/**
			 * @brief Create a Notification Message object
			 * 
			 * @param messageType 
			 * @param message 
			 * @param messageBoxIconType 
			 * @return NotificationManager::MessageBoxValue 
			 */
			static NotificationManager::MessageBoxValue createNotificationMessage(NotificationManager::MessageBoxType messageType, string message, NotificationManager::MessageBoxIconType messageBoxIconType)
			{
				return NotificationManager::OpenMessageBox(messageType, StringUtils::getWString(message).c_str(), messageBoxIconType);
			}
			
			/**
			 * @brief Create a Error Notification Message object
			 * 
			 * @param message 
			 * @return NotificationManager::MessageBoxValue 
			 */
			static NotificationManager::MessageBoxValue createErrorNotificationMessage(string message)
			{
				return createNotificationMessage(NotificationManager::MessageBoxType::MESSAGEBOX_TYPE_MediumAlert,
					message, NotificationManager::MessageBoxIconType::MESSAGEBOX_ICON_Critical);
			}
		};
	}
}