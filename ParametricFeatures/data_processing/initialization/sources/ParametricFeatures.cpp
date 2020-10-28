//--------------------------------------------------------------------------------------+
//
//    $Source: ParametricFeatures.cpp $
// 
//    $Copyright: (c) 2019 Bentley Systems, Incorporated. All rights reserved. $
//
//---------------------------------------------------------------------------------------+

//--------------------------------------------------------------------------------------
//    Include Files
//--------------------------------------------------------------------------------------


//#include "../headers/ParametricFeatures.h"

#include <windows.h>
#include <shellapi.h>

#include "../headers/InitializationHelper.h"
#include "../../../ifc/main/headers/IfcBuilder.h"
#include "../../../interface_dialog/DialogIds.h"

#include "../headers/ParametricFeaturesCmd.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

static int dlogdemo_colorNumber = 5;
static int dlogdemo_scrollNumber = 500;
static int dlogdemo_optionbtnNumber1 = 1;
static int dlogdemo_optionbtnNumber2 = 0;


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)

void SetVersionNumber()
{
	VersionNumber version = { 10, 7, 6, 1 };
	mdlSystem_setMdlAppVersionNumber(mdlSystem_getCurrMdlDesc(), &version);
}

#pragma region INITIALIZATION

void createFolder(string folderPath)
{

	// create main folder
	if (CreateDirectory(folderPath.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		// do something. status/boolean
	}
	else
	{
		// Failed to create directory. return status/boolean and log
	}
}

void createFilesStructure()
{
	//string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

	SessionManager::getInstance()->setDataOutputFilePath(filePath);


	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK) {
		cout << "Error: " << result << "\n";
	}
	else {
		cout << "Path: " << my_documents << "\n";
	}

	string documentsPath = my_documents;

	string mainFolderPath = documentsPath + "\\IfcModels";
	// create main folder
	createFolder(mainFolderPath);

	SessionManager::getInstance()->setOutputFolderPath(mainFolderPath);

	string logFolderPath = mainFolderPath + "\\logs";
	// create logs folder
	createFolder(logFolderPath);

	// get date to create logs by day
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1;
	int year = aTime->tm_year + 1900;

	string currentDayLogFolderPath = logFolderPath + "\\" + to_string(day) + "-" + to_string(month) + "-" + to_string(year);
	// create log folder
	createFolder(currentDayLogFolderPath);
	SessionManager::getInstance()->setCurrentDayLogsFolderPath(currentDayLogFolderPath);


	string re = StringUtils::getNormalizedString(ISessionMgr::GetActiveDgnFile()->GetFileName());


	// get dgn file name
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(re.c_str(), drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);


	//string ifcOutputFileName1 = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/IfcCustomName.ifc";
	string ifcOutputFileName = mainFolderPath + "\\" + fname + ".ifc";

	SessionManager::getInstance()->setIfcOutputFilePath(ifcOutputFileName);

}

NotificationManager::MessageBoxValue createNotificationMessage(NotificationManager::MessageBoxType messageType, string message, NotificationManager::MessageBoxIconType messageBoxIconType)
{
	return NotificationManager::OpenMessageBox(messageType, StringUtils::getWString(message).c_str(), messageBoxIconType);
}

NotificationManager::MessageBoxValue createErrorNotificationMessage(string message)
{
	return createNotificationMessage(NotificationManager::MessageBoxType::MESSAGEBOX_TYPE_MediumAlert,
		message, NotificationManager::MessageBoxIconType::MESSAGEBOX_ICON_Critical);
}

StatusInt GetSmartFeatureTree()//(WCharCP unparsedP)
							   //void GetSmartFeatureTree()
{
	NotificationManager::SetDispatchEvents(true);

	createFilesStructure();
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

			createErrorNotificationMessage(errorMessageModelProcessing);
		}
		catch (...) {
			Logs::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, errorMessageModelProcessing);

			createErrorNotificationMessage(errorMessageModelProcessing);

		}


		string errorMessageIfcConversion = "Error at creating the IFC file";

		try {
			IfcBuilder* ifcBuilder = new IfcBuilder();
			ifcBuilder->buildIfc(propsDictVec, smartFeatureContainerVector);
		}
		catch (exception& ex) {
			Logs::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, ex, errorMessageIfcConversion);

			createErrorNotificationMessage(errorMessageIfcConversion);
		}
		catch (...) {
			Logs::Logger::getLogger()->logFatal(__FILE__, __LINE__, __func__, errorMessageIfcConversion);

			createErrorNotificationMessage(errorMessageIfcConversion);

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
#pragma endregion

#pragma region LOAD/UNLOAD

void loadDialogBox(WCharCP unparsedP) //cmdNumber CMD_DLOGDEMO
{
	/* Open Dialog Box */
	//mdlDialog_open(NULL, DIALOGID_Dialog);

	/*-------------------------------------------------------------
	| Open our main dialog box with the function mdlDialog_open.
	| The NULL parameter means to look for the Dialog Box resource
	| in the file that the application is from.
	+-------------------------------------------------------------*/
	if (NULL == mdlDialog_open(NULL, DIALOGID_Dialog))
	{
		/* On error, output a message and unload the application */
		//mdlOutput_rscPrintf(MSG_ERROR, NULL, MESSAGELISTID_Msgs, MSGID_DialogOpen);
		/*mdlDialog_cmdNumQueueExt (FALSE, CMD_MDL_UNLOAD,
		mdlSystem_getCurrTaskID(), TRUE, TRUE);*/
		Bentley::WString cmdStr("mdl unload ");
		cmdStr.append(mdlSystem_getCurrTaskID());
		mdlInput_sendKeyin(cmdStr.GetWCharCP(), true, INPUTQ_EOQ, NULL);
	}
}

/*=================================================================================**//**
* @description  Unload this application
* @param[in] unparsed Additional input supplied after command string.
+===============+===============+===============+===============+===============+======*/
void unLoadDialogBox(WCharCP unparsedP)
{
	auto taskID = mdlSystem_getCurrTaskID();
	mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, taskID, INPUTQ_HEAD); //INPUTQ_EOQ
	return;
}

#pragma endregion

#pragma region DIALOG

/*---------------------------------------------------------------------------------**//**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
void dialogDemo_dialogHook(DialogMessage *dmP)
{
	dmP->msgUnderstood = TRUE;

	switch (dmP->messageType)
	{
		/* Handle the create message and say we are interested in:  */
		/*  1) Item draw messages (Updates)                         */
		/*  2) Mouse events                                         */
		/*  3) Keystroke events                                     */
		/*  4) Dialog box focus changes                             */
		/*  5) Dialig item focus changes                            */
		/*  6) Dialog box resize events                             */
	case DIALOG_MESSAGE_CREATE:
		dmP->u.create.interests.updates = TRUE;
		dmP->u.create.interests.mouses = TRUE;
		dmP->u.create.interests.keystrokes = TRUE;
		dmP->u.create.interests.dialogFocuses = TRUE;
		dmP->u.create.interests.itemFocuses = TRUE;
		dmP->u.create.interests.resizes = TRUE;
		break;

	case DIALOG_MESSAGE_INIT:

	case DIALOG_MESSAGE_DESTROY:

	case DIALOG_MESSAGE_UPDATE:

	case DIALOG_MESSAGE_BUTTON:

	case DIALOG_MESSAGE_KEYSTROKE:

	case DIALOG_MESSAGE_FOCUSIN:

	case DIALOG_MESSAGE_FOCUSOUT:

	case DIALOG_MESSAGE_ITEMFOCUSIN:

	case DIALOG_MESSAGE_ITEMFOCUSOUT:

	case DIALOG_MESSAGE_ACTIONBUTTON:

	case DIALOG_MESSAGE_USER:

	default:
		dmP->msgUnderstood = FALSE;
		break;
	}
}

/*---------------------------------------------------------------------------------**//**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
static void dialogDemo_listBoxHook(DialogItemMessage *dimP)
{
	RawItemHdr	*listBoxP = dimP->dialogItemP->rawItemP;

	dimP->msgUnderstood = TRUE;
	switch (dimP->messageType)
	{
	case DITEM_MESSAGE_CREATE:
	{
		StringList  *stringListP;
		int          iMember;
		WString        formatStr;

		auto pGraElement = ISessionMgr::GetActiveDgnModelP()->GetGraphicElementsP();
		vector<PersistentElementRefP> elements;
		int numElements = 0;
		for (PersistentElementRefP elemRef : *pGraElement)
		{
			elements.push_back(elemRef);
		}

		numElements = ISessionMgr::GetActiveDgnModelP()->GetElementCount(DgnModelSections::GraphicElements);

		/* This list box will have numElements rows and 2 columns, so it needs
		(numElements * 2) cells created in the string list. */
		int numSpace = (numElements * 2);
		stringListP = mdlStringList_create(numSpace, 1);
		mdlDialog_listBoxSetStrListP(listBoxP, stringListP, 1);

		mdlResource_loadWString(formatStr, NULL, STRINGID_Messages, MSGID_ListBox);

		int elementIndex = 0;
		for (iMember = 0; iMember < numSpace; iMember++)
		{
			WChar   buffer[80];
			WString elDescr;

			auto elemRef = elements.at(elementIndex);
			ElementHandle currentElem(elemRef);

			currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);

			_swprintf(buffer, formatStr.GetWCharCP(), currentElem.GetElementId());

			mdlStringList_setMember(stringListP, iMember, buffer, NULL);

			iMember += 1;
			mdlStringList_setMember(stringListP, iMember, elDescr.GetWCharCP(), NULL);
			elementIndex++;
		}
		break;
	}

	case DITEM_MESSAGE_DESTROY:
	{
		StringList	*strListP = mdlDialog_listBoxGetStrListP(listBoxP);

		/* free the string list if it is allocated */
		if (NULL != strListP)
		{
			mdlStringList_destroy(strListP);
		}

		break;
	}

	default:
		dimP->msgUnderstood = FALSE;
		break;
	}
}

/*---------------------------------------------------------------------------------**//**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
static void dialogDemo_pushButton1(DialogItemMessage *dimP)
{
	dimP->msgUnderstood = TRUE;

	switch (dimP->messageType)
	{
	case DITEM_MESSAGE_BUTTON:
	{
		WString myString;
		myString.Sprintf(L"IFC Converter");
		mdlOutput_messageCenter(OutputMessagePriority::Info, myString.c_str(), myString.c_str(), OutputMessageAlert::None);

		GetSmartFeatureTree();
	}
	break;

	default:
		dimP->msgUnderstood = FALSE;
		break;
	}
}

/*---------------------------------------------------------------------------------**//**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
static void dialogDemo_pullDownMenuHook(DialogItemMessage *dimP)
{
	dimP->msgUnderstood = TRUE;

	switch (dimP->messageType)
	{
	case DITEM_MESSAGE_BUTTON:
		break;

	default:
		dimP->msgUnderstood = FALSE;
		break;
	}
}

/*---------------------------------------------------------------------------------**//**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
static void dialogDemo_scrollBarHook(DialogItemMessage *dimP)
{
	dimP->msgUnderstood = TRUE;

	switch (dimP->messageType)
	{
		/* Handle state changed message and synchronize all scroll bar	*/
		/* related items if the value of the scroll bar access string	*/
		/* really did change                                            */
	case DITEM_MESSAGE_STATECHANGED:
		if (dimP->u.stateChanged.reallyChanged)
			mdlDialog_synonymsSynch(NULL, SYNONYMID_DialogScroll, NULL);
		break;

	default:
		dimP->msgUnderstood = FALSE;
		break;
	}
}

Public DialogHookInfo uHooks[] =
{
	{ HOOKID_Dialog,                     (PFDialogHook)dialogDemo_dialogHook },
	{ HOOKITEMID_ListBox_Dialog,         (PFDialogHook)dialogDemo_listBoxHook },
	{ HOOKITEMID_PullDownMenu_Dialog,    (PFDialogHook)dialogDemo_pullDownMenuHook },
	{ HOOKITEMID_ScrollBar_Dialog,       (PFDialogHook)dialogDemo_scrollBarHook },
	{ HOOKITEMID_Button_StandardAction,		 (PFDialogHook)dialogDemo_pushButton1 }
};

#pragma endregion


/*---------------------------------------------------------------------------------**//**
* @description  MdlMain
* @param        argc      The number of command line parameters sent to the application.
* @param        argv[]    The array of strings sent to the application on the command line.
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
extern "C" DLLEXPORT  void MdlMain(int argc, WCharCP argv[]) 
{
	RscFileHandle   rscFileH;   /* a resource file handle */
	SymbolSet       *setP;      /* a ptr to a "C expression symbol set" */

	/*-----------------------------------------------------------------+
	| mdlResource_openFile:
	|
	| This function opens a resource file, thus making its contents
	| available to the application.  In this case, we need to open
	| MYAPP.MA as a resource file so that we have access to the the
	| string lists for our messages.
	|
	| int mdlResource_openFile
	|   (
	|   RscFileHandle  *rfHandle,      <= Resource File Handle
	|   char           *fileName,      => Name of File to open
	|   ULong           fileAttrMask   => file attributes bit mask
	|   );
	|
	| Resources are defined in .r files
	+-----------------------------------------------------------------*/
	if (mdlResource_openFile(&rscFileH, NULL, RSC_READ) != SUCCESS)
	{
		/* exit this program and unload it */
		mdlSystem_exit(ERROR, /* => status for parent task */
			1);    /* => 1 to unload the program */
	}

	MdlCommandNumber    commandNumbers[] = // Map key-in to function
	{
		{ (CmdHandler)loadDialogBox, CMD_PARAMETRICFEATURES },
		0
	};

	/* Register command numbers to enable you key in a command name to start a command */
	mdlSystem_registerCommandNumbers(commandNumbers);

	/* load our command table, from resources merged into Dialog.ma */
	if (mdlParse_loadCommandTable(NULL) == NULL)
	{
		/*-------------------------------------------------------------+
		|   void mdlOutput_rscPrintf
		|       (
		|       int            fieldID;             => MSG_MESSAGE, etc.
		|       RscFileHandle  resourceFileHandle;  => handle or NULL
		|       long           resourceId;          => ID of string list
		|       int            stringNumber;        => number of string
		|       ...
		|       );
		+-------------------------------------------------------------*/
		mdlOutput_rscPrintf(MSG_ERROR, NULL, STRINGID_Messages, MSGID_CommandTable);

		/* exit this program and unload it */
		mdlSystem_exit(ERROR, /* => status for parent task */
			1);    /* => 1 to unload the program */
	}
	
	/*-----------------------------------------------------------------+
	| To setup variables evaluated within C expression strings:
	|
	| Since we are using a pointer to a structure we need to allocate
	| memory for it.  Because this symbol will be used in a Dialog Box
	| we specify VISIBILITY_DIALOG_BOX.  Then we publish the pointer to
	| our structure so that the Dialog Box Manager becomes aware of it.
	+-----------------------------------------------------------------*/
	setP = mdlCExpression_initializeSet(VISIBILITY_DIALOG_BOX, 0, FALSE);

	mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_LONG), "dlogdemo_colorNumber", &dlogdemo_colorNumber);
	mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_LONG), "dlogdemo_scrollNumber", &dlogdemo_scrollNumber);
	mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_LONG), "dlogdemo_optionbtnNumber1", &dlogdemo_optionbtnNumber1);
	mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_LONG), "dlogdemo_optionbtnNumber2", &dlogdemo_optionbtnNumber2);

	/*-----------------------------------------------------------------+
	| mdlDialog_hookPublish:
	|
	| To make the Dialog Box Manager aware of the function pointers
	| that we have equated to our hook ids we need to publish the
	| DialogHookInfo structure, uHooks (declared at the top of this file).
	+-----------------------------------------------------------------*/
	mdlDialog_hookPublish(sizeof(uHooks) / sizeof(DialogHookInfo), uHooks);

	/*--------------------------------------------------------------
	| Because we want our setting dialog to come up as soon as the
	| application is loaded we open it now by adding the command
	| CMD_OPEN_MYMAINDIALOG to MicroStation's input queue.
	| Use the extended version of mdlDialog_cmdNumberQueue, which
	| is mdlDialog_cmdNumQueueExt since we don't want to journal
	| the command for BASIC macro generation.  The main dialog box
	| will automatically open when this application is loaded so there
	| is no need to add this command to the BASIC program.
	|
	|   void mdlDialog_cmdNumQueueExt
	|   (
	|   BoolInt      localCmd,      => FALSE means use MicroStations cmdtable
	|   long         cmdnum,        => command number to queue
	|   char        *unparsed,      => unparsed (string) part of command
	|   BoolInt      atEndOfQueue,  => FALSE means put at beginning of queue
	|   BoolInt      journal        => TRUE means CAD input journal the command
	|   );
	|
	+---------------------------------------------------------------*/
	mdlDialog_cmdNumQueueExt(TRUE, CMD_PARAMETRICFEATURES, L"", INPUTQ_EOQ, FALSE);
}

#pragma warning( pop ) 