/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/DialogBoxes/DialogBoxDemo/DialogIds.h $
|
|  $Copyright: (c) 2016 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   $Workfile:   DialogIds.h  $
|   $Revision: 1.2 $
|   $Date: 2001/05/29 14:32:43 $
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   Dlogdids.h -- Dialog Box Demonstration Resource Id's                |
|                                                                       |
+----------------------------------------------------------------------*/
#if !defined (__dlogdidsH__)
#define __dlogdidsH__

#include <Mstn\MicroStation.r.h>

/*----------------------------------------------------------------------+
|                                                                       |
|   Dialog Box IDs                                                      |
|                                                                       |
+----------------------------------------------------------------------*/
#define DIALOGID_Dialog         1
#define DIALOGID_DialogPalette  2
#define TOOLBOXID_Dialog1       3
#define TOOLBOXID_Dialog2       4
#define BASEID_Dialog           (DIALOGID_Dialog * 100)

/*----------------------------------------------------------------------+
|                                                                       |
|   CmdItemListRsc IDs                                                  |
|                                                                       |
+----------------------------------------------------------------------*/
enum CmdItemListId
{
    ItemList_DialogPal2Sub3 = 1,
    ItemList_DialogPal2Sub4,
    ItemList_DialogPal2Sub5,
};

/*----------------------------------------------------------------------+
|                                                                       |
|   Dialog Item IDs                                                     |
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   Option Button IDs                                                   |
|                                                                       |
+----------------------------------------------------------------------*/
#define OPTIONROLEACTORID_Dialog  1
#define OPTIONBUTTONID_EXPORT_BREP_Dialog  2

/*----------------------------------------------------------------------+
|                                                                       |
|   Toggle Button IDs                                                   |
|                                                                       |
+----------------------------------------------------------------------*/
#define TOGGLEID_SELECTED_ELEMENTS_Dialog        1
#define TOGGLEID_BREP_EXPORT_Dialog        2
#define TOGGLEID_ACTIVELEVELS_Dialog        3

/*----------------------------------------------------------------------+
|                                                                       |
|   Push Button IDs                                                     |
|                                                                       |
+----------------------------------------------------------------------*/
#define STARTBUTTONID_Dialog    1
#define BROWSEBUTTONID_Dialog    2

/*----------------------------------------------------------------------+
|                                                                       |
|   ListBox Item ID                                                     |
|                                                                       |
+----------------------------------------------------------------------*/
#define LISTBOXID_Dialog        1

/*----------------------------------------------------------------------+
|                                                                       |
|   Color Picker ID                                                     |
|                                                                       |
+----------------------------------------------------------------------*/
#define COLORPICKERID_Dialog    1

/*----------------------------------------------------------------------+
|                                                                       |
|   Text IDs                                                            |
|                                                                       |
+----------------------------------------------------------------------*/
#define PATHTEXTID_Dialog			1
#define TEXTID_DialogColor			2
#define TEXTID_DialogScroll			3
#define ACTORNAMETEXTID_Dialog		4
#define ACTORSURNAMETEXTID_Dialog	5
#define ACTOREMAILTEXTID_Dialog		6

/*----------------------------------------------------------------------+
|                                                                       |
|   Menubar IDs                                                         |
|                                                                       |
+----------------------------------------------------------------------*/
#define MENUBARID_Dialog        1

/*----------------------------------------------------------------------+
|                                                                       |
|   Pulldown Menu IDs                                                   |
|                                                                       |
+----------------------------------------------------------------------*/
#define PULLDOWNMENUID_Dialog1      1
#define PULLDOWNMENUID_Dialog2      2

#define PULLDOWNOPTIONMENUID_Dialog     1
#define PULLDOWNCPICKERMENUID_Dialog    1

/*----------------------------------------------------------------------+
|                                                                       |
|   Scroll Bar ID                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
#define SCROLLBARID_Dialog      1

/*----------------------------------------------------------------------+
|                                                                       |
|   Level Map ID                                                        |
|                                                                       |
+----------------------------------------------------------------------*/
#define LEVELMAPID_Dialog       1

/*----------------------------------------------------------------------+
|                                                                       |
|   Hook IDs                                                            |
|                                                                       |
+----------------------------------------------------------------------*/
#define HOOKID_Dialog           1

#define HOOKITEMID_ListBox_Dialog			(BASEID_Dialog+1)
#define HOOKITEMID_PullDownMenu_Dialog		(BASEID_Dialog+2)
#define HOOKITEMID_ScrollBar_Dialog			(BASEID_Dialog+3)
#define HOOKITEMID_StartButton_Dialog		(BASEID_Dialog+4)
#define HOOKITEMID_BrowseButton_Dialog		(BASEID_Dialog+5)
#define HOOKITEMID_ExportSelection_Dialog   (BASEID_Dialog+7)
#define HOOKITEMID_ExportBrep_Dialog		(BASEID_Dialog+8)
#define HOOKITEMID_ActorOption_Dialog		(BASEID_Dialog+9)
#define HOOKITEMID_BrepTypeOption_Dialog	(BASEID_Dialog+10)
#define HOOKITEMID_ActiveLevelExport_Dialog	(BASEID_Dialog+11)

/*----------------------------------------------------------------------+
|                                                                       |
|   Synonym Id's                                                        |
|                                                                       |
+----------------------------------------------------------------------*/
#define SYNONYMID_DialogColor		1
#define SYNONYMID_DialogScroll		2
#define SYNONYMID_DialogBrowse		3
#define SYNONYMID_ExportSelectionToggle	4
#define SYNONYMID_ActorInfo			5
#define SYNONYMID_RefreshList		6


/*----------------------------------------------------------------------+
|                                                                       |
|   Icon Command Frame Id                                               |
|                                                                       |
+----------------------------------------------------------------------*/
#define ICONCMDFRAMEID_Dialog       1

/*----------------------------------------------------------------------+
|                                                                       |
|   Icon Command Palette Id's                                           |
|                                                                       |
+----------------------------------------------------------------------*/
#define ICONCMDPALETTEID_Dialog1    1
#define ICONCMDPALETTEID_Dialog2    2

/*----------------------------------------------------------------------+
|                                                                       |
|   Icon Command Id's                                                   |
|                                                                       |
+----------------------------------------------------------------------*/
#define ICONCMDID_Dialog1       1
#define ICONCMDID_Dialog2       2
#define ICONCMDID_Dialog3       3
#define ICONCMDID_Dialog4       4

#define ICONCMDID_DialogPal1Sub1    11
#define ICONCMDID_DialogPal1Sub2    12

#define ICONCMDID_DialogPal2Sub1    21
#define ICONCMDID_DialogPal2Sub2    22
#define ICONCMDID_DialogPal2Sub3    23
#define ICONCMDID_DialogPal2Sub4    24
#define ICONCMDID_DialogPal2Sub5    25
#define ICONCMDID_DialogPal2Sub6    26

#define HSTACKLAYOUTID_MyStack          1

/*----------------------------------------------------------------------+
|                                                                       |
|   Message List ID's                                                   |
|                                                                       |
+----------------------------------------------------------------------*/
enum
{
    STRINGID_Messages = 1,
    MSGID_CommandTable,
	MSGID_ListBox,
};


/*----------------------------------------------------------------------+
|                                                                       |
|   Typedefs for Dialog access strings                                  |
|                                                                       |
+----------------------------------------------------------------------*/
#if !defined (resource)

typedef struct usergeneralinfo
{
	WChar actorName[255];
	WChar actorSurName[255];
	WChar actorEmail[255];
	int actorRole;
	WChar browsedFolder[255];
} UserGeneralInfo;

typedef struct ifcexportsettings
{
	int brepTypeExport;
	bool activateBRepExport;
	bool selectedElementsExport;
	bool activeLevelElementsExport;
} IfcExportSettings;

#endif

#endif /*(__dlogdidsH__)*/
