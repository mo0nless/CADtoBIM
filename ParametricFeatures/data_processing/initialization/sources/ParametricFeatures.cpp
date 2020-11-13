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

//#include <windows.h>
//#include <shellapi.h>

//#include "../../../interface_dialog/DialogIds.h"
#include "../../../interface_dialog/DialogHooks.h"
//#include "../../../interface_dialog/DialogSymbols.h"


#include "../headers/ParametricFeaturesCmd.h"

//USING_NAMESPACE_BENTLEY
//USING_NAMESPACE_BENTLEY_DGNPLATFORM
//USING_NAMESPACE_BENTLEY_MSTNPLATFORM
//USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)

void SetVersionNumber()
{
	VersionNumber version = { 1, 0, 0, 0 };
	//VersionNumber version = { 10, 7, 6, 1 };
	mdlSystem_setMdlAppVersionNumber(mdlSystem_getCurrMdlDesc(), &version);
}

void loadDialogBox(WCharCP unparsedP) //cmdNumber CMD_dlog
{
	StructureExp::createFilesStructure();

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

Public DialogHookInfo uHooks[] =
{
	{ HOOKID_Dialog,                     (PFDialogHook)DialogHooks::Handler::HookResolve },
	{ HOOKITEMID_ListBox_Dialog,         (PFDialogHook)DialogHooks::ItemBoxHadler::HookResolve },
	{ HOOKITEMID_PullDownMenu_Dialog,    (PFDialogHook)DialogHooks::PullDownMenuHadler::HookResolve },
	{ HOOKITEMID_ScrollBar_Dialog,       (PFDialogHook)DialogHooks::ScrollBarHadler::HookResolve },
	{ HOOKITEMID_StartButton_Dialog,	 (PFDialogHook)DialogHooks::StartButtonHadler::HookResolve },
	{ HOOKITEMID_BrowseButton_Dialog,	 (PFDialogHook)DialogHooks::BrowseButtonHadler::HookResolve },
	{ HOOKITEMID_ExportSelection_Dialog, (PFDialogHook)DialogHooks::ExportToggleHadler::HookResolve },
	{ HOOKITEMID_ActorOption_Dialog,	 (PFDialogHook)DialogHooks::ActorOptionHadler::HookResolve }
};


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

	mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_LONG), "dlog_colorNumber", &dlog_colorNumber);
	mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_LONG), "dlog_scrollNumber", &dlog_scrollNumber);
	//mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_LONG), "dlog_optionbtnNumber1", &dlog_optionbtnNumber1);
	mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_LONG), "dlog_optionbtnNumber2", &dlog_optionbtnNumber2);
	mdlDialog_publishBasicVariable(setP, mdlCExpression_getType(TYPECODE_BOOL), "dlog_ToggleSingleElementButton", &dlog_ToggleSingleElementButton);
	mdlDialog_publishComplexVariable(setP, "ifcgeneralinfo", "ifcGeneralInfo", &ifcGeneralInfo);

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