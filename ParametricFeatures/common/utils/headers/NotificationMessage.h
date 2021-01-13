#pragma once

#include <DgnPlatform/DisplayHandler.h>
#include <Mstn/ElementPropertyUtils.h>
#include <Mstn/MdlApi/dlogbox.r.h>
#include <DgnPlatform/NotificationManager.h>
#include "StringUtils.hpp"

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

using namespace Common::Utilities;

struct NotificationMessage
{
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

	static void send(WString stringValue, OutputMessagePriority messagePriority)
	{
		NotifyMessageDetails message = NotifyMessageDetails(
			messagePriority,
			stringValue.c_str()
		);

		NotificationManager::OutputMessage(message);
	}

	static NotificationManager::MessageBoxValue createNotificationMessage(NotificationManager::MessageBoxType messageType, string message, NotificationManager::MessageBoxIconType messageBoxIconType)
	{
		return NotificationManager::OpenMessageBox(messageType, StringUtils::getWString(message).c_str(), messageBoxIconType);
	}

	static NotificationManager::MessageBoxValue createErrorNotificationMessage(string message)
	{
		return createNotificationMessage(NotificationManager::MessageBoxType::MESSAGEBOX_TYPE_MediumAlert,
			message, NotificationManager::MessageBoxIconType::MESSAGEBOX_ICON_Critical);
	}
};