#include "../headers/ParametricFeatures.h"


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
StatusInt GetSmartFeatureTree(WCharCP unparsedP)
{
	//mdlInput_sendKeyin(L"MsgCenter ClearMessages", true, MSInputQueuePos::INPUTQ_EOQ, L"0");

	NotificationManager::SetDispatchEvents(true);

	WString stringOutMsg;	
	
	string fileName = StringUtils::getNormalizedString(ISessionMgr::GetActiveDgnFile()->GetFileName());
	SessionManager::getInstance()->setDgnFileName(fileName);
	fileName = SessionManager::getInstance()->getDgnFileName();
	WString fname = StringUtils::getWString(fileName);

	stringOutMsg.Sprintf(L"Export the active '%s.dgn' file to IFC?", fname);

	NotificationManager::MessageBoxValue resultUser = NotificationManager::OpenMessageBox(
		NotificationManager::MessageBoxType::MESSAGEBOX_TYPE_YesNo,
		stringOutMsg.c_str(),
		NotificationManager::MessageBoxIconType::MESSAGEBOX_ICON_Question
	);
	
	if (NotificationManager::MessageBoxValue::MESSAGEBOX_VALUE_Yes == resultUser)
	{
		stringOutMsg.clear();
		stringOutMsg.Sprintf(L"Start IFC Conversion");
		NotificationMessage::send(stringOutMsg, OutputMessagePriority::Debug);

		vector<DictionaryProperties*> propsDictVec;
		vector<SmartFeatureContainer*> smartFeatureContainerVector;

		InitializationHelper* initializationHelper = new InitializationHelper();
		initializationHelper->processDgnGraphicsElements(propsDictVec, smartFeatureContainerVector);

		IfcBuilder* ifcBuilder = new IfcBuilder();
		ifcBuilder->buildIfc(propsDictVec, smartFeatureContainerVector);

		string outputFolderPath = SessionManager::getInstance()->getOutputFolderPath();

		char myDocPath[MAX_PATH];
		strcpy(myDocPath, outputFolderPath.c_str());

		ShellExecute(NULL, "open", myDocPath, NULL, NULL, SW_SHOW);

		stringOutMsg.clear();
		stringOutMsg.Sprintf(L"End IFC Conversion");

		NotificationMessage::send(stringOutMsg, OutputMessagePriority::Debug);
	}

	return SUCCESS;
}
#pragma warning( pop ) 


/*=================================================================================**//**
* @description  Unload this application
* @param[in] unparsed Additional input supplied after command string.
+===============+===============+===============+===============+===============+======*/
void UnloadParametricFeatures(WCharCP unparsedP)
{
	auto taskID = mdlSystem_getCurrTaskID();
	mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, taskID, INPUTQ_HEAD); //INPUTQ_EOQ
	return;
}
