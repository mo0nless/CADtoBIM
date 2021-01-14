/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/DialogBoxes/DialogBoxDemo/Dialog.r $
|
|  $Copyright: (c) 2016 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   $Workfile:   Dialog.r  $
|   $Revision: 1.2 $
|   $Date: 2001/05/29 14:32:43 $
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   Function -                                                          |
|                                                                       |
|   Dialog Box demonstration application dialog resources               |
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   Include Files                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
#include <Mstn\MdlApi\dlogbox.r.h>    /* dlog box manager resource constants & structs */
#include <Mstn\MdlApi\dlogids.r.h>    /* MicroStation resource IDs */
#include <Mstn\MdlApi\keys.r.h>

#include "DialogIds.h"
#include "DialogTxt.h"

/*----------------------------------------------------------------------+
|                                                                       |
|   Local Defines                                                       |
|                                                                       |
+----------------------------------------------------------------------*/

/*----------------------------------------------------------------------+
|                                                                       |
|   Main Dialog Demo Dialog Box                                         |
|                                                                       |
+----------------------------------------------------------------------*/
#define  OVERALLWIDTH   63*XC
#define  OVERALLHEIGHT  40*YC/*29*YC*/

#define  X1     3  * XC                         /* 1st column alignment */
#define  X2     12 * XC                         /* 2nd column of examples */
#define  X3     15 * XC
#define  X22    22 * XC
#define  X35    32 * XC

#define  X4     45 * XC             /* scroll bar text value */
#define  W1     (6*XC)              /* scroll bar text value width */
#define  X5     (X4 + W1 + 2*XC)    /* scroll bar */
#define  W3     (8*XC)              /* scroll bar width */

#define  X6 (8 * XC)                /* text Color #: */
#define  W2 (5*XC)                  /* text color #: width */
#define  X7 (X6 + W1 + 2*XC)        /* color picker */

#define  BW1    15 * XC             /* Width for Option Buttons */
#define  BW2    8 * XC              /* Width for Pushbuttons */

#define  Y1     GENY(2.8)           /* Label position */
#define  Y2     GENY(4)             /* Option Button 1 */
#define  Y25    GENY(5)             /* Option Button 2 */
#define  Y3     GENY(7)             /* Toggle Button 1 */
#define  Y35    GENY(8)             /* Toggle Button 2 */
#define  Y4     GENY(9)             /* PushButton 2 */
#define  Y45    GENY(11.5)          /* ColorPicker */
#define  Y5     GENY(13)            /* Text Example */
#define  Y6     GENY(16.2)          /* ListBox Example */
#define  Y7     GENY(13.5)          /* Scrollbar, Text */

DialogBoxRsc DIALOGID_Dialog =
    {
    DIALOGATTR_DEFAULT,
    OVERALLWIDTH, OVERALLHEIGHT,
    NOHELP, LHELPCMD, HOOKID_Dialog, NOPARENTID,
    TXT_MainDialogBox,
	{
	BEGIN_VSTACK_LAYOUT(0, "")
		//{{0, 0, 0, 0},      MenuBar,      MENUBARID_Dialog, ON, 0, "", ""},
		SPACING (SECTION_GAP)

		//{{0, 5*YC, 0, 0}, Separator, 0, ON, SEPARATOR_HORIZONTAL, "", ""},
		
		BEGIN_GRID_LAYOUT(GRIDLAYOUTID_3ColumnsOuter, "")
			GRID_ROW(0, "")	
				LAYOUT_LABEL_NEXT_RIGHT(0,"")		
				{AUTO_XYWH,    Text,       PATHTEXTID_Dialog, ON, TEXT_MASK_LABELABOVE, "", ""},	//{AUTO_XY, 0, 0}
				{AUTO_XYWH,  PushButton,   BROWSEBUTTONID_Dialog, ON, 0, "", ""}, 
			END_ROW
		END_LAYOUT

		SPACING (SECTION_GAP)	
		{{0, 3*YC, 0, 0}, Separator, 0, ON, SEPARATOR_HORIZONTAL, "", ""},
		SPACING (SECTION_GAP)

		//{{0, 0, 30*XC,15*YC}, GroupBox, 0, ON, 0, "Properties", ""},
		BEGIN_GRID_LAYOUT(GRIDLAYOUTID_4ColumnsOuter, "")			
			GRID_ROW(0, "")
				LAYOUT_LABEL_NEXT_LEFT(0,"")		
				{{AUTO_XY, 0, 0},    Text, ACTORNAMETEXTID_Dialog, ON, 0, "", ""},	
				LAYOUT_LABEL_NEXT_LEFT(0,"")
				{AUTO_XYWH,  OptionButton, OPTIONROLEACTORID_Dialog, ON, 0, "", ""},
			END_ROW
			GRID_ROW(0,"")
				LAYOUT_LABEL_NEXT_LEFT(0,"")
				{{AUTO_XY, 0, 0},    Text, ACTORSURNAMETEXTID_Dialog, ON, 0, "", ""},	
				LAYOUT_LABEL_NEXT_LEFT(0,"")
				{{AUTO_XY, 0, 0},    Text, ACTOREMAILTEXTID_Dialog, ON, 0, "", ""},	
				//{AUTO_XYWH, OptionButton, OPTIONBUTTONID_Dialog2, ON, 0, "", ""},
			END_ROW
		END_LAYOUT	

		SPACING (SECTION_GAP)

		/* //DEBUG PURPOSE
		//BEGIN_HSTACK_LAYOUT(0,"")
			//SPACING (SECTION_GAP)
				BEGIN_GRID_LAYOUT(GRIDLAYOUTID_2ColumnsOuter, "")
					GRID_ROW(0, "")
					{AUTO_XYWH,    ToggleButton, ELEMENT_S_TOGGLEID_Dialog, ON, 0, "", ""},
					END_ROW
					GRID_ROW(0, "")
					{AUTO_XYWH,   ToggleButton, TOGGLEID_Dialog2, ON, 0, "", ""},
					END_ROW
					GRID_ROW(0, "")
					{AUTO_XYWH,    ToggleButton, TOGGLEID_Dialog3, ON, 0, "", ""},
					END_ROW
				END_LAYOUT	       
		//STRETCH(1)
		//END_LAYOUT
	
		SPACING (SECTION_GAP)

		BEGIN_HSTACK_LAYOUT (0, "")
			SPACING (SECTION_GAP)
			LAYOUT_LABEL_NEXT_RIGHT(0,"")
			{{AUTO_XY, W2, 0},  Text,           TEXTID_DialogColor, ON, 0, "", ""},
			SPACING (SECTION_GAP)
			{AUTO_XYWH,   ColorPicker,    COLORPICKERID_Dialog, ON, 0, "", ""},
			STRETCH(1)
		END_LAYOUT

		SPACING (SECTION_GAP)

		BEGIN_HSTACK_LAYOUT (HSTACKLAYOUTID_Standard, "")
			//SPACING (SECTION_GAP)
			LAYOUT_LABEL_NEXT_RIGHT(0,"")
			{{AUTO_XY, W1, 0},   Text,           TEXTID_DialogScroll, ON, 0, "", ""},
			SPACING (SECTION_GAP)
			STRETCH(1)
			{{AUTO_XY, W3, 0},   ScrollBar,      SCROLLBARID_Dialog, ON, 0, "", ""},
			STRETCH(1)
		END_LAYOUT
		*/

		SPACING (SECTION_GAP)
		SPACING (SECTION_GAP)
		SPACING (SECTION_GAP)
		SPACING (SECTION_GAP)
		SPACING (SECTION_GAP)


		BEGIN_VSTACK_LAYOUT (VSTACKLAYOUTID_SmallMargin, "") //0
			//SPACING (SECTION_GAP)
			{AUTO_XYWH,    ListBox,        LISTBOXID_Dialog, ON, 0,"", ""},		
		END_LAYOUT

		SPACING (SECTION_GAP)

		{{0, 3*YC, 0, 0}, Separator, 0, ON, SEPARATOR_HORIZONTAL, "", ""},

		BEGIN_HSTACK_LAYOUT (HSTACKLAYOUTID_MyStack, "")
			SPACING (SECTION_GAP)//STRETCH(1)
			{AUTO_XYWH,  PushButton,   STARTBUTTONID_Dialog, ON, 0, "", ""},
			SPACING (SECTION_GAP)//STRETCH(1)
		END_LAYOUT
	END_LAYOUT
	}
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Item Resource Specifications                                        |
|                                                                       |
+----------------------------------------------------------------------*/
HStackLayoutRsc HSTACKLAYOUTID_MyStack =
    {
    {XC,XC,XC,XC},
    BUTTON_HSPACING
    };
/*----------------------------------------------------------------------+
|                                                                       |
|   Color Picker Item Resource                                          |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_ColorPickerRsc COLORPICKERID_Dialog =
    {
    NOCMD, LCMD, SYNONYMID_DialogColor, NOHELP, LHELPCMD,
    NOHOOK, NOARG,
    TEXTID_DialogColor, NOMASK,
    "",
    "dlog_colorNumber"
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Level Map Item Resource                                             |
|                                                                       |
+----------------------------------------------------------------------*/
//DItem_LevelMapRsc LEVELMAPID_Dialog =
//    {
//    NOHELP, LHELPCMD,
//    TXT_LevelMap,
//    "",     /* accessStr would go here */
//    ""      /* activeLevelaccessStr would go here */
//    };

/*----------------------------------------------------------------------+
|                                                                       |
|   List Box Item Resource                                              |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_ListBoxRsc LISTBOXID_Dialog =
    {
    NOHELP, LHELPCMD, HOOKITEMID_ListBox_Dialog, 
	NOARG,
    LISTATTR_RESIZABLECOLUMNS,//0, 
	4, 
	0,//4,//1,
    TXT_ListBox,
    {
        {25*XC, 45, ALIGN_LEFT, "Element ID"},
        {25*XC, 45, ALIGN_LEFT, "Description"},
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Menu Bar Button Item Resource                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_MenuBarRsc MENUBARID_Dialog =
    {
    NOHOOK, NOARG,
    {
    {PulldownMenu,	PULLDOWNMENUID_Dialog1},
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Text Pull-down Menu Item Resources                                  |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_PulldownMenuRsc PULLDOWNMENUID_Dialog1 =
    {
    NOHELP, OHELPTASKIDCMD, HOOKITEMID_PullDownMenu_Dialog,
    ON | ALIGN_LEFT,
    TXT_PullDown,
{
/*{TXT_PulldownColorPicker, NOACCEL, ON, NOMARK,
        PulldownCPickerMenu, PULLDOWNCPICKERMENUID_Dialog,
        NOHELP, OHELPTASKIDCMD,
        NOHOOK, 0, NOCMD, OTASKID, ""},*/
{TXT_PulldownOption, NOACCEL, ON, NOMARK,
        PulldownOptionMenu, PULLDOWNOPTIONMENUID_Dialog,
        NOHELP, OHELPTASKIDCMD,
            NOHOOK, 1, NOCMD, OTASKID, ""},
{TXT_TextSubMenu, NOACCEL, ON, NOMARK,
        PulldownMenu, PULLDOWNMENUID_Dialog2,
        NOHELP, OHELPTASKIDCMD,
            NOHOOK, 2, NOCMD, OTASKID, ""},
{TXT_PulldownText, 'N'|VBIT_CTRL, ON, NOMARK,
        0, NOSUBMENU, NOHELP, OHELPTASKIDCMD,
        NOHOOK, 3, NOCMD, OTASKID, ""},
}
    };

DItem_PulldownMenuRsc PULLDOWNMENUID_Dialog2 =
    {
    NOHELP, OHELPTASKIDCMD, HOOKITEMID_PullDownMenu_Dialog,
    ON | ALIGN_LEFT,
    TXT_PullDown2,
{
{TXT_PullText21, NOACCEL, ON, NOMARK,
        0, NOSUBMENU, NOHELP, OHELPTASKIDCMD,
        NOHOOK, 0, NOCMD, OTASKID, ""},
{TXT_PullText22, 'S'|VBIT_CTRL, ON, NOMARK,
        0, NOSUBMENU, NOHELP, OHELPTASKIDCMD,
            NOHOOK, 1, NOCMD, OTASKID, ""},
}
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Option Pull-down Menu Item Resources                                |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_PulldownOptionMenuRsc PULLDOWNOPTIONMENUID_Dialog =
    {
    NOSYNONYM, NOHELP, LHELPCMD, NOHOOK,
    ON | ALIGN_LEFT,
    TXT_PullDown_Option,
    "", /* Access string would go here */
{
    {NOTYPE, NOICON, NOCMD, LCMD, 0, NOMASK, ON, TXT_PullOption1 },
    {NOTYPE, NOICON, NOCMD, LCMD, 1, NOMASK, ON, TXT_PullOption2 },
    {NOTYPE, NOICON, NOCMD, LCMD, 2, NOMASK, ON, TXT_PullOption3 },
}
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Colorpicker Pull-down Menu Item Resource                            |
|                                                                       |
+----------------------------------------------------------------------*/
/*DItem_PulldownCPickerMenuRsc PULLDOWNCPICKERMENUID_Dialog =
    {
    NOSYNONYM, NOHELP, LHELPCMD,
    NOHOOK, ON,
    NOCMD, LCMD, NOMASK,
    TXT_Pulldown_Colorpicker,
    ""
    };*/

/*----------------------------------------------------------------------+
|                                                                       |
|   Option Button Item Resources                                        |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_OptionButtonRsc  OPTIONROLEACTORID_Dialog =
    {
    SYNONYMID_ActorInfo, NOHELP, LHELPCMD, HOOKITEMID_ActorOption_Dialog, NOARG,
    TXT_OptionRoleActor,
    "userGeneralInfo.actorRole",
    {
    /*{NOTYPE, NOICON, NOCMD, LCMD, 0, NOMASK, ON, TXT_Option11},
    {NOTYPE, NOICON, NOCMD, LCMD, 1, NOMASK, ON, TXT_Option12},
    {NOTYPE, NOICON, NOCMD, LCMD, 2, NOMASK, ON, TXT_Option13},*/
    }
    };

DItem_OptionButtonRsc  OPTIONBUTTONID_Dialog2 =
    {
    NOSYNONYM, NOHELP, LHELPCMD, NOHOOK, NOARG,
    TXT_OptionButton2,
    "dlog_optionbtnNumber2",
    {
    {NOTYPE, NOICON, NOCMD, LCMD, 0, NOMASK, ON, TXT_Option21},
    {NOTYPE, NOICON, NOCMD, LCMD, 1, NOMASK, ON, TXT_Option22},
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   PushButton Item Resources                                           |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_PushButtonRsc STARTBUTTONID_Dialog =
    {
    NOT_DEFAULT_BUTTON, NOHELP, LHELPCMD, //HOOKITEMID_Button_StandardAction,
	HOOKITEMID_StartButton_Dialog,
    0, NOCMD, LCMD, "",
    TXT_StartButton
    };

DItem_PushButtonRsc BROWSEBUTTONID_Dialog =
    {
    NOT_DEFAULT_BUTTON, NOHELP, LHELPCMD, 
	HOOKITEMID_BrowseButton_Dialog,
    1, NOCMD, LCMD, "",
    TXT_BrowseButton
    };


/*----------------------------------------------------------------------+
|                                                                       |
|   Scroll Bar Item Resource                                            |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_ScrollBarRsc SCROLLBARID_Dialog =
    {
    HOOKITEMID_ScrollBar_Dialog, NOARG, 0, 1000, 5, 50, 0.1,
    "dlog_scrollNumber"
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Text Item Resources                                                 |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_TextRsc PATHTEXTID_Dialog =
    {
    NOCMD, LCMD, SYNONYMID_DialogBrowse, NOHELP, LHELPCMD, 
	NOHOOK, NOARG,
    72, "%s", "%s", "", "", 
	NOMASK, 
	NOCONCAT,
    TXT_PathText,
    "userGeneralInfo.browsedFolder"
    };

DItem_TextRsc ACTORNAMETEXTID_Dialog =
    {
    NOCMD, LCMD, SYNONYMID_ActorInfo, NOHELP, LHELPCMD, 
	NOHOOK, NOARG,
    30, "%s", "%s", "", "", 
	NOMASK, 
	NOCONCAT,
    TXT_NameText,
    "userGeneralInfo.actorName"
    };

DItem_TextRsc ACTORSURNAMETEXTID_Dialog =
    {
    NOCMD, LCMD, SYNONYMID_ActorInfo, NOHELP, LHELPCMD, 
	NOHOOK, NOARG,
    30, "%s", "%s", "", "", 
	NOMASK, 
	NOCONCAT,
    TXT_SurNameText,
    "userGeneralInfo.actorSurName"
    };

DItem_TextRsc ACTOREMAILTEXTID_Dialog =
    {
    NOCMD, LCMD, SYNONYMID_ActorInfo, NOHELP, LHELPCMD, 
	NOHOOK, NOARG,
    45, "%s", "%s", "", "", 
	NOMASK, 
	NOCONCAT,
    TXT_EmailText,
    "userGeneralInfo.actorEmail"
    };

DItem_TextRsc TEXTID_DialogColor =
    {
    NOCMD, LCMD, SYNONYMID_DialogColor, NOHELP, LHELPCMD,
    NOHOOK, NOARG,
    3, "%-ld", "%ld", "0", "253", NOMASK, NOCONCAT,
    TXT_Color,
    "dlog_colorNumber"
    };

DItem_TextRsc TEXTID_DialogScroll =
    {
    NOCMD, LCMD, SYNONYMID_DialogScroll, NOHELP, LHELPCMD,
    NOHOOK, NOARG,
    4, "%-ld", "%ld", "0", "1000", NOMASK, NOCONCAT,
    TXT_ScrollbarValue,
    "dlog_scrollNumber"
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Toggle Button Item Resources                                        |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_ToggleButtonRsc ELEMENT_S_TOGGLEID_Dialog =
    {
    NOCMD, LCMD, 
	SYNONYMID_ToggleSelection,//NOSYNONYM, 
	NOHELP, LHELPCMD, NOHOOK,
    NOARG, NOMASK, NOINVERT,
    TXT_ToggleSingleElementButton,
    "dlog_ToggleSingleElementButton"
    };

DItem_ToggleButtonRsc TOGGLEID_Dialog2 =
    {
    NOCMD, LCMD, NOSYNONYM, NOHELP, LHELPCMD, NOHOOK,
    NOARG, NOMASK, NOINVERT,
    TXT_ToggleButton2,
    ""
    };

DItem_ToggleButtonRsc TOGGLEID_Dialog3 =
    {
    NOCMD, LCMD, NOSYNONYM, NOHELP, LHELPCMD, NOHOOK,
    NOARG, NOMASK, NOINVERT,
    TXT_ToggleButton3,
    ""
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Item Synonyms                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_SynonymsRsc SYNONYMID_DialogColor =
    {
    {
    {Text,        TEXTID_DialogColor},
    {ColorPicker, COLORPICKERID_Dialog},
    }
    };

DItem_SynonymsRsc SYNONYMID_DialogScroll =
    {
    {
    {Text,      TEXTID_DialogScroll},
    {ScrollBar, SCROLLBARID_Dialog},
    }
    };

DItem_SynonymsRsc SYNONYMID_DialogBrowse=
	{
	{
		{Text, PATHTEXTID_Dialog},
		{PushButton, BROWSEBUTTONID_Dialog}
	}
	};

DItem_SynonymsRsc SYNONYMID_ToggleSelection=
	{
	{
		{ToggleButton, ELEMENT_S_TOGGLEID_Dialog},
		{ListBox, LISTBOXID_Dialog},
		{PushButton, STARTBUTTONID_Dialog}
	}
	};


DItem_SynonymsRsc SYNONYMID_ActorInfo=
	{
	{
		{Text, ACTORNAMETEXTID_Dialog},
		{Text, ACTORSURNAMETEXTID_Dialog},
		{Text, ACTOREMAILTEXTID_Dialog},
		{OptionButton, PATHTEXTID_Dialog},
	}
	};

/*----------------------------------------------------------------------+
|                                                                       |
|   Tool Palette Dialog Box                                             |
|                                                                       |
+----------------------------------------------------------------------*/
DialogBoxRsc DIALOGID_DialogPalette =
    {
    /* Recommended attributes for tool palette frame dialog boxes */
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    DIALOGATTR_TOOLBOXCOMMON,
#else
    DIALOGATTR_DEFAULT | DIALOGATTR_NORIGHTICONS | DIALOGATTR_AUTOOPEN,
#endif
    XC, YC, NOHELP, LHELPCMD, NOHOOK, NOPARENTID, TXT_Frame,
{
#if defined (MSVERSION) && (MSVERSION >= 0x550)
{{0, 0, 0, 0}, ToolBox, ICONCMDFRAMEID_Dialog, ON, 0, "", ""},
#else
{{0, 0, 0, 0}, IconCmdFrame, ICONCMDFRAMEID_Dialog, ON, 0, "", ""},
#endif
}
    };

/*----------------------------------------------------------------------+
|                                                                       |
|   Tool Palette Icon Command Frame                                     |
|                                                                       |
+----------------------------------------------------------------------*/
#if defined (MSVERSION) && (MSVERSION >= 0x550)
DItem_ToolBoxRsc ICONCMDFRAMEID_Dialog =
    {
    NOHELP, LHELPCMD, NOHOOK, NOARG, 0, "",
        {
        {{ 0, 0, 0, 0}, IconCmd,    ICONCMDID_Dialog1,  ON,  0,  "",  "owner=\"dlog\""},
        {{ 0, 0, 0, 0}, ToolBox,    TOOLBOXID_Dialog1,  ON,  0,  "",  "owner=\"dlog\""},
        {{ 0, 0, 0, 0}, IconCmd,    ICONCMDID_Dialog2,  ON,  0,  "",  "owner=\"dlog\""},
        {{ 0, 0, 0, 0}, ToolBox,    TOOLBOXID_Dialog2,  ON,  0,  "",  "owner=\"dlog\""},
        {{ 0, 0, 0, 0}, IconCmd,    ICONCMDID_Dialog3,  ON,  0,  "",  "owner=\"dlog\""},
        {{ 0, 0, 0, 0}, IconCmd,    ICONCMDID_Dialog4,  ON,  0,  "",  "owner=\"dlog\""},
        }
    };
#else
DItem_IconCmdFrameRsc ICONCMDFRAMEID_Dialog =
    {
    2, 3, NOHELP, LHELPCMD, "",
        {
        {IconCmd,           ICONCMDID_Dialog1},
        {IconCmdPalette,    ICONCMDPALETTEID_Dialog1},
        {IconCmd,           ICONCMDID_Dialog2},
        {IconCmdPalette,    ICONCMDPALETTEID_Dialog2},
        {IconCmd,           ICONCMDID_Dialog3},
        {IconCmd,           ICONCMDID_Dialog4},
        }
    };
#endif

/*----------------------------------------------------------------------+
|                                                                       |
|   Icon Command Palettes                                               |
|                                                                       |
+----------------------------------------------------------------------*/
#if defined (MSVERSION) && (MSVERSION >= 0x550)
/* Use tool box definition */
DialogBoxRsc TOOLBOXID_Dialog1 =
    {
    DIALOGATTR_TOOLBOXCOMMON,
    0, 0,
    NOHELP, MHELP, 
    NOHOOK, NOPARENTID,
    TXT_Palette1,
{
{{0, 0, 0, 0}, ToolBox, TOOLBOXID_Dialog1, ON, 0, "", ""},
}
    };

DItem_ToolBoxRsc	TOOLBOXID_Dialog1 =
    {
    NOHELP, MHELP, NOHOOK, NOARG, 0, TXT_Palette1,
    {
    {{ 0, 0, 0, 0}, IconCmd, ICONCMDID_DialogPal1Sub1, ON, 0, "", "owner=\"dlog\""},
    {{ 0, 0, 0, 0}, IconCmd, ICONCMDID_DialogPal1Sub2, ON, 0, "", "owner=\"dlog\""},
    }
    };

DialogBoxRsc TOOLBOXID_Dialog2 =
    {
    DIALOGATTR_TOOLBOXCOMMON,
    0, 0,
    NOHELP, MHELP, 
    NOHOOK, NOPARENTID,
    TXT_Palette2,
{
{{0, 0, 0, 0}, ToolBox, TOOLBOXID_Dialog2, ON, 0, "", ""},
}
    };

DItem_ToolBoxRsc    TOOLBOXID_Dialog2 =
    {
    NOHELP, MHELP, NOHOOK, NOARG, 0, TXT_Palette2,
    {
    {{ 0, 0, 0, 0}, IconCmd, ICONCMDID_DialogPal2Sub1, ON, 0, "", "owner=\"dlog\""},
    {{ 0, 0, 0, 0}, IconCmd, ICONCMDID_DialogPal2Sub2, ON, 0, "", "owner=\"dlog\""},
    {{ 0, 0, 0, 0}, IconCmd, ICONCMDID_DialogPal2Sub3, ON, 0, "", "owner=\"dlog\""},
    {{ 0, 0, 0, 0}, IconCmd, ICONCMDID_DialogPal2Sub4, ON, 0, "", "owner=\"dlog\""},
    {{ 0, 0, 0, 0}, IconCmd, ICONCMDID_DialogPal2Sub5, ON, 0, "", "owner=\"dlog\""},
    {{ 0, 0, 0, 0}, IconCmd, ICONCMDID_DialogPal2Sub6, ON, 0, "", "owner=\"dlog\""},
    }
    };

#else
/* Use palette definition */
DItem_IconCmdPaletteRsc	ICONCMDPALETTEID_Dialog1 =
    {
    2, 1, 0, NOHELP, LHELPCMD, NOHOOK, NOARG, TXT_Palette1,
        {
        ICONCMDID_DialogPal1Sub1,
        ICONCMDID_DialogPal1Sub2,
        }
    };

DItem_IconCmdPaletteRsc	ICONCMDPALETTEID_Dialog2 =
    {
    3, 2, 0, NOHELP, LHELPCMD, NOHOOK, NOARG, TXT_Palette2,
        {
        ICONCMDID_DialogPal2Sub1,
        ICONCMDID_DialogPal2Sub2,
        ICONCMDID_DialogPal2Sub3,
        ICONCMDID_DialogPal2Sub4,
        ICONCMDID_DialogPal2Sub5,
        ICONCMDID_DialogPal2Sub6,
        }
    };
#endif

/*----------------------------------------------------------------------+
|                                                                       |
|   Icon Command Resources                                              |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_Dialog1 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_Dialog1}, 
    {EXTATTR_BALLOON, TXT_Balloon_Dialog1}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_Dialog1 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Icon 1 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x06,
    0x00, 0x00, 0x14, 0x00, 0x00, 0x48, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x20, 0x00, 0x00, 0x40, 0x00,
    0x00, 0x80, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x20, 0x00, 0x00, 0x40, 0x00, 0x0f,
    0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_Dialog1 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Icon 1 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,
    0x01, 0x70, 0x00, 0x00, 0x02, 0xe0, 0x00, 0x00,
    0x09, 0xc0, 0x00, 0x00, 0x23, 0x80, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x1c, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
    0x70, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x01,
    0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x07,
    0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x1c,
    0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x70,
    0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x01, 0xc0,
    0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x1c, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x00, 0x07, 0xff, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_DialogPal1Sub1 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_DialogPal1Sub1}, 
    {EXTATTR_BALLOON, TXT_Balloon_DialogPal1Sub1}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_DialogPal1Sub1 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 1 Sub 1 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x40, 0x10, 0x00, 0x80, 0x20, 0x01, 0x00,
    0x40, 0x02, 0x00, 0x80, 0x04, 0x01, 0x00, 0x08,
    0x02, 0x00, 0x10, 0x04, 0x00, 0x20, 0x08, 0x00,
    0x40, 0x10, 0x00, 0x80, 0x20, 0x01, 0x00, 0x40,
    0x02, 0x00, 0x80, 0x04, 0x01, 0x00, 0x08, 0x02,
    0x00, 0x10, 0x04, 0x00, 0x20, 0x08, 0x00, 0x40,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_DialogPal1Sub1 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 1 Sub 1 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x3c, 0x00,
    0x5c, 0x00, 0xb8, 0x00, 0xb8, 0x01, 0x70, 0x02,
    0x70, 0x04, 0xe0, 0x08, 0xe0, 0x11, 0xc0, 0x01,
    0xc0, 0x03, 0x80, 0x03, 0x80, 0x07, 0x00, 0x07,
    0x00, 0x0e, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x1c,
    0x00, 0x38, 0x00, 0x38, 0x00, 0x70, 0x00, 0x70,
    0x00, 0xe0, 0x00, 0xe0, 0x01, 0xc0, 0x01, 0xc0,
    0x03, 0x80, 0x03, 0x80, 0x07, 0x00, 0x07, 0x00,
    0x0e, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x1c, 0x00,
    0x38, 0x00, 0x38, 0x00, 0x70, 0x00, 0x70, 0x00,
    0xe0, 0x00, 0xe0, 0x01, 0xc0, 0x01, 0xc0, 0x03,
    0x80, 0x03, 0x80, 0x07, 0x00, 0x07, 0x00, 0x0e,
    0x00, 0x0e, 0x00, 0x1c, 0x01, 0xff, 0xc1, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc	ICONCMDID_DialogPal1Sub2 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_DialogPal1Sub2}, 
    {EXTATTR_BALLOON, TXT_Balloon_DialogPal1Sub2}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_DialogPal1Sub2 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 1 Sub 2 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3e,
    0x00, 0x40, 0x86, 0x00, 0x82, 0x04, 0x01, 0x00,
    0x04, 0x02, 0x00, 0x08, 0x04, 0x00, 0x10, 0x08,
    0x00, 0x20, 0x10, 0x00, 0x40, 0x20, 0x01, 0x80,
    0x40, 0x06, 0x00, 0x80, 0x18, 0x01, 0x00, 0xe0,
    0x02, 0x02, 0x00, 0x04, 0x08, 0x00, 0x08, 0x10,
    0x00, 0x10, 0x20, 0x00, 0x20, 0x40, 0x00, 0x40,
    0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_DialogPal1Sub2 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 1 Sub 2 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x0f, 0xfc, 0x01,
    0xe0, 0x1f, 0xf8, 0x03, 0xc0, 0x20, 0x30, 0x0f,
    0x80, 0x40, 0x60, 0x17, 0x00, 0x00, 0xc0, 0x0e,
    0x00, 0x01, 0x80, 0x1c, 0x00, 0x03, 0x00, 0x38,
    0x00, 0x06, 0x00, 0x70, 0x00, 0x0c, 0x00, 0xe0,
    0x00, 0x38, 0x01, 0xc0, 0x00, 0xe0, 0x03, 0x80,
    0x03, 0x80, 0x07, 0x00, 0x0e, 0x00, 0x0e, 0x00,
    0x38, 0x00, 0x1c, 0x00, 0xe0, 0x00, 0x38, 0x03,
    0x80, 0x00, 0x70, 0x06, 0x00, 0x00, 0xe0, 0x0c,
    0x00, 0x01, 0xc0, 0x18, 0x00, 0x03, 0x80, 0x30,
    0x00, 0x07, 0x00, 0x60, 0x00, 0x0e, 0x00, 0xc0,
    0x00, 0x1c, 0x01, 0x80, 0x00, 0x38, 0x03, 0x00,
    0x00, 0x70, 0x07, 0xfe, 0x03, 0xf8, 0x0f, 0xfc,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_Dialog2 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_Dialog2}, 
    {EXTATTR_BALLOON, TXT_Balloon_Dialog2}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_Dialog2 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Icon 2 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xe0, 0x00, 0x10, 0x20, 0x00, 0x40,
    0x40, 0x01, 0x00, 0x80, 0x00, 0x02, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x40, 0x00,
    0x01, 0x80, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00,
    0x00, 0x40, 0x00, 0x00, 0x80, 0x00, 0x03, 0xff,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_Dialog2 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Icon 2 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00,
    0x03, 0xff, 0x00, 0x00, 0x04, 0x06, 0x00, 0x00,
    0x08, 0x0c, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00,
    0x00, 0x30, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
    0x00, 0xc0, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x70, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x07,
    0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x70,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01, 0x80,
    0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x00,
    0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x18, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0xff, 0xc0, 0x00, 0x01, 0xff, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_DialogPal2Sub1 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_DialogPal2Sub1}, 
    {EXTATTR_BALLOON, TXT_Balloon_DialogPal2Sub1}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_DialogPal2Sub1 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 1 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00,
    0x80, 0x86, 0x01, 0x02, 0x04, 0x02, 0x00, 0x04,
    0x04, 0x00, 0x08, 0x08, 0x00, 0x10, 0x10, 0x00,
    0x20, 0x20, 0x00, 0x40, 0x40, 0x01, 0x80, 0x80,
    0x06, 0x01, 0x00, 0x18, 0x02, 0x00, 0xe0, 0x04,
    0x02, 0x00, 0x08, 0x08, 0x00, 0x10, 0x10, 0x00,
    0x20, 0x20, 0x00, 0x40, 0x40, 0x00, 0x80, 0xff,
    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_DialogPal2Sub1 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 1 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x06, 0x01,
    0xff, 0x00, 0x7c, 0x03, 0x86, 0x00, 0xb8, 0x07,
    0x0c, 0x00, 0x70, 0x00, 0x18, 0x00, 0xe0, 0x00,
    0x30, 0x01, 0xc0, 0x00, 0x60, 0x03, 0x80, 0x00,
    0xc0, 0x07, 0x00, 0x01, 0x80, 0x0e, 0x00, 0x03,
    0x00, 0x1c, 0x00, 0x0e, 0x00, 0x38, 0x00, 0x38,
    0x00, 0x70, 0x00, 0xe0, 0x00, 0xe0, 0x03, 0x80,
    0x01, 0xc0, 0x0e, 0x00, 0x03, 0x80, 0x18, 0x00,
    0x07, 0x00, 0x30, 0x00, 0x0e, 0x00, 0x60, 0x00,
    0x1c, 0x00, 0xc0, 0x00, 0x38, 0x01, 0x80, 0x00,
    0x70, 0x03, 0x00, 0x00, 0xe0, 0x06, 0x00, 0x01,
    0xc0, 0x0c, 0x00, 0x03, 0x80, 0x18, 0x00, 0x07,
    0x00, 0x3f, 0xc0, 0x0e, 0x00, 0x7f, 0x80, 0x7f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_DialogPal2Sub2 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_DialogPal2Sub2}, 
    {EXTATTR_BALLOON, TXT_Balloon_DialogPal2Sub2}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_DialogPal2Sub2 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 2 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x07,
    0x81, 0x0c, 0x10, 0x84, 0x08, 0x40, 0x80, 0x08,
    0x00, 0x80, 0x10, 0x01, 0x00, 0x20, 0x02, 0x00,
    0x40, 0x04, 0x00, 0x80, 0x08, 0x03, 0x00, 0x10,
    0x0c, 0x01, 0xc0, 0x30, 0x06, 0x01, 0xc0, 0x18,
    0x04, 0x00, 0x20, 0x10, 0x00, 0x80, 0x20, 0x01,
    0x00, 0x40, 0x02, 0x00, 0x80, 0x04, 0x01, 0xff,
    0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_DialogPal2Sub2 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 2 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3f, 0x03, 0xff, 0x01,
    0xff, 0x0f, 0xfe, 0x03, 0x86, 0x18, 0x0c, 0x07,
    0x0c, 0x30, 0x18, 0x00, 0x18, 0x00, 0x30, 0x00,
    0x30, 0x00, 0x60, 0x00, 0x60, 0x00, 0xc0, 0x00,
    0xc0, 0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x03,
    0x00, 0x0e, 0x00, 0x0e, 0x00, 0x38, 0x00, 0x38,
    0x00, 0xe0, 0x00, 0xe0, 0x03, 0x80, 0x03, 0x80,
    0x0e, 0x00, 0x0e, 0x00, 0x38, 0x00, 0x18, 0x00,
    0xe0, 0x00, 0x30, 0x01, 0x80, 0x00, 0x60, 0x03,
    0x00, 0x00, 0xc0, 0x06, 0x00, 0x01, 0x80, 0x0c,
    0x00, 0x03, 0x00, 0x18, 0x00, 0x06, 0x00, 0x30,
    0x00, 0x0c, 0x00, 0x60, 0x00, 0x18, 0x00, 0xc0,
    0x00, 0x3f, 0xc1, 0xff, 0x80, 0x7f, 0x83, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_DialogPal2Sub3 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_DialogPal2Sub3}, 
    {EXTATTR_BALLOON, TXT_Balloon_DialogPal2Sub3}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_DialogPal2Sub3 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 3 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x0f,
    0xc1, 0x0c, 0x10, 0x44, 0x08, 0x40, 0x40, 0x08,
    0x00, 0x80, 0x10, 0x01, 0x00, 0x20, 0x02, 0x00,
    0x40, 0x08, 0x00, 0x80, 0x20, 0x03, 0x00, 0x80,
    0x0c, 0x07, 0x00, 0x30, 0x03, 0x01, 0xc0, 0x03,
    0x04, 0x00, 0x03, 0x10, 0x00, 0x02, 0x20, 0x00,
    0x04, 0x40, 0x00, 0x08, 0x80, 0x00, 0x21, 0xff,
    0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_DialogPal2Sub3 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 3 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x3e, 0x01,
    0xff, 0x00, 0xfe, 0x03, 0x86, 0x03, 0x8c, 0x07,
    0x0c, 0x00, 0x18, 0x00, 0x18, 0x00, 0x30, 0x00,
    0x30, 0x00, 0x60, 0x00, 0x60, 0x00, 0xc0, 0x00,
    0xc0, 0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x03,
    0x00, 0x06, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x38,
    0x00, 0x60, 0x00, 0xe0, 0x01, 0x80, 0x03, 0x80,
    0x03, 0x80, 0x0e, 0x00, 0x03, 0x80, 0x18, 0x00,
    0x03, 0x80, 0x30, 0x00, 0x03, 0x80, 0x60, 0x00,
    0x01, 0x00, 0xc0, 0x00, 0x03, 0x01, 0x80, 0x00,
    0x06, 0x03, 0x00, 0x00, 0x0c, 0x06, 0x00, 0x00,
    0x18, 0x0c, 0x00, 0x30, 0x30, 0x18, 0x00, 0x39,
    0xc0, 0x3f, 0xc0, 0x3f, 0x00, 0x7f, 0x80, 0x18,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

CmdItemListRsc ItemList_DialogPal2Sub3 =
    {{
    {{10*XC, GENY(1), 9*XC, 0}, Text, TEXTID_ActvXScale, ON, 0, "", ""},
    {{10*XC, GENY(2), 9*XC, 0}, Text, TEXTID_ActvYScale, ON, 0, "", ""},
    {{10*XC, GENY(3), 9*XC, 0}, Text, TEXTID_ActvZScale, ON, 0, "", ""},
    }};

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_DialogPal2Sub4 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_DialogPal2Sub4}, 
    {EXTATTR_BALLOON, TXT_Balloon_DialogPal2Sub4}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_DialogPal2Sub4 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 4 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x08,
    0x21, 0x0c, 0x10, 0x44, 0x08, 0x20, 0x80, 0x08,
    0x41, 0x00, 0x10, 0x82, 0x00, 0x21, 0x04, 0x00,
    0x42, 0x08, 0x00, 0x84, 0x10, 0x03, 0x08, 0x20,
    0x0c, 0x0f, 0x80, 0x30, 0x00, 0x81, 0xc0, 0x01,
    0x04, 0x00, 0x02, 0x10, 0x00, 0x04, 0x20, 0x00,
    0x08, 0x40, 0x00, 0x10, 0x80, 0x00, 0x21, 0xff,
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_DialogPal2Sub4 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 4 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xc0, 0x01,
    0xff, 0x01, 0x81, 0x83, 0x86, 0x03, 0x03, 0x07,
    0x0c, 0x06, 0x06, 0x00, 0x18, 0x0c, 0x0c, 0x00,
    0x30, 0x18, 0x18, 0x00, 0x60, 0x30, 0x30, 0x00,
    0xc0, 0x60, 0x60, 0x01, 0x80, 0xc0, 0xc0, 0x03,
    0x01, 0x81, 0x80, 0x0e, 0x03, 0x03, 0x00, 0x38,
    0x06, 0x06, 0x00, 0xe0, 0x0f, 0xfc, 0x03, 0x80,
    0x1f, 0xf8, 0x0e, 0x00, 0x00, 0x30, 0x18, 0x00,
    0x00, 0x60, 0x30, 0x00, 0x00, 0xc0, 0x60, 0x00,
    0x01, 0x80, 0xc0, 0x00, 0x03, 0x01, 0x80, 0x00,
    0x06, 0x03, 0x00, 0x00, 0x0c, 0x06, 0x00, 0x00,
    0x18, 0x0c, 0x00, 0x00, 0x30, 0x18, 0x00, 0x00,
    0x60, 0x3f, 0xc0, 0x00, 0xc0, 0x7f, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

CmdItemListRsc  ItemList_DialogPal2Sub4 = 
    {{
    {{10*XC, GENY(1), 9*XC, 0}, Text, TEXTID_ActvXScale, ON, 0, "", ""},
    {{10*XC, GENY(2), 9*XC, 0}, Text, TEXTID_ActvYScale, ON, 0, "", ""},
    {{10*XC, GENY(3), 9*XC, 0}, Text, TEXTID_ActvZScale, ON, 0, "", ""},
    }};

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_DialogPal2Sub5 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_DialogPal2Sub5}, 
    {EXTATTR_BALLOON, TXT_Balloon_DialogPal2Sub5}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_DialogPal2Sub5 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 5 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x0f,
    0xe1, 0x0c, 0x20, 0x04, 0x08, 0x40, 0x00, 0x08,
    0x80, 0x00, 0x11, 0x00, 0x00, 0x22, 0x00, 0x00,
    0x44, 0x00, 0x00, 0x88, 0x00, 0x03, 0x1f, 0x80,
    0x0c, 0x00, 0x80, 0x30, 0x00, 0x81, 0xc0, 0x01,
    0x04, 0x00, 0x02, 0x10, 0x00, 0x04, 0x20, 0x00,
    0x08, 0x40, 0x00, 0x30, 0x80, 0x18, 0xc1, 0xff,
    0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_DialogPal2Sub5 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 5 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0xc1,
    0xff, 0x00, 0xff, 0x03, 0x86, 0x01, 0x80, 0x07,
    0x0c, 0x03, 0x00, 0x00, 0x18, 0x06, 0x00, 0x00,
    0x30, 0x0c, 0x00, 0x00, 0x60, 0x18, 0x00, 0x00,
    0xc0, 0x30, 0x00, 0x01, 0x80, 0x60, 0x00, 0x03,
    0x00, 0xc0, 0x00, 0x0e, 0x01, 0x80, 0x00, 0x38,
    0x03, 0x00, 0x00, 0xe0, 0x07, 0xf0, 0x03, 0x80,
    0x0f, 0xe0, 0x0e, 0x00, 0x00, 0x60, 0x18, 0x00,
    0x00, 0x60, 0x30, 0x00, 0x00, 0x60, 0x60, 0x00,
    0x00, 0xc0, 0xc0, 0x00, 0x01, 0x81, 0x80, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00,
    0x0c, 0x0c, 0x00, 0x18, 0x18, 0x18, 0x00, 0x3f,
    0xe0, 0x3f, 0xc0, 0x7f, 0xc0, 0x7f, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

CmdItemListRsc ItemList_DialogPal2Sub5 = 
    {{
    {{11*XC, GENY(1), 6*XC, 0}, Text, TEXTID_ArrayNumItems, ON, 0, "", ""},
    {{11*XC, GENY(2), 10*XC, 0}, Text, TEXTID_DeltaAngle, ON, 0, "", ""},
    {{3*XC, GENY(3), 0, 0}, ToggleButton, TOGGLEID_ArrayRotate, ON, 0, "", ""},
    }};

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_DialogPal2Sub6 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_DialogPal2Sub6}, 
    {EXTATTR_BALLOON, TXT_Balloon_DialogPal2Sub6}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_DialogPal2Sub6 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 6 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x02,
    0x01, 0x0c, 0x04, 0x04, 0x08, 0x10, 0x00, 0x08,
    0x20, 0x00, 0x10, 0x40, 0x00, 0x21, 0x00, 0x00,
    0x42, 0x00, 0x00, 0x88, 0x00, 0x03, 0x1f, 0x80,
    0x0c, 0x20, 0x80, 0x30, 0x40, 0x81, 0xc0, 0x81,
    0x04, 0x01, 0x02, 0x10, 0x02, 0x04, 0x20, 0x04,
    0x08, 0x40, 0x08, 0x30, 0x80, 0x08, 0xc1, 0xff,
    0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_DialogPal2Sub6 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Pal 2 Sub 6 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x60, 0x01,
    0xff, 0x00, 0xc0, 0x03, 0x86, 0x01, 0x80, 0x07,
    0x0c, 0x03, 0x00, 0x00, 0x18, 0x06, 0x00, 0x00,
    0x30, 0x0c, 0x00, 0x00, 0x60, 0x18, 0x00, 0x00,
    0xc0, 0x30, 0x00, 0x01, 0x80, 0x60, 0x00, 0x03,
    0x00, 0xc0, 0x00, 0x0e, 0x01, 0x80, 0x00, 0x38,
    0x03, 0x00, 0x00, 0xe0, 0x07, 0xe0, 0x03, 0x80,
    0x0f, 0xe0, 0x0e, 0x00, 0x18, 0x60, 0x18, 0x00,
    0x30, 0x60, 0x30, 0x00, 0x60, 0x60, 0x60, 0x00,
    0xc0, 0xc0, 0xc0, 0x01, 0x81, 0x81, 0x80, 0x03,
    0x03, 0x03, 0x00, 0x06, 0x06, 0x06, 0x00, 0x0c,
    0x0c, 0x0c, 0x00, 0x18, 0x18, 0x18, 0x00, 0x3f,
    0xe0, 0x3f, 0xc0, 0x3f, 0xc0, 0x7f, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc    ICONCMDID_Dialog3 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_Dialog3}, 
    {EXTATTR_BALLOON, TXT_Balloon_Dialog3}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_Dialog3 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Icon 3 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0,
    0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0x00,
    0x01, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x70, 0x00,
    0x00, 0x10, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0x00, 0x01,
    0x00, 0x00, 0x02, 0x00, 0x04, 0x08, 0x00, 0x07,
    0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };

IconCmdLargeRsc ICONCMDID_Dialog3 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Icon 3 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00,
    0x07, 0xff, 0x80, 0x00, 0x1c, 0x01, 0x80, 0x00,
    0x30, 0x01, 0x80, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x06, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
    0x00, 0x18, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
    0x00, 0xe0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00,
    0x3f, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00,
    0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
    0x60, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01,
    0x80, 0x00, 0x80, 0x03, 0x00, 0x01, 0x80, 0x0e,
    0x00, 0x01, 0xff, 0xf8, 0x00, 0x01, 0xff, 0xe0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };

/*----------------------------------------------------------------------+
|                                                                       |
|                                                                       |
|                                                                       |
+----------------------------------------------------------------------*/
DItem_IconCmdRsc	ICONCMDID_Dialog4 =
    {
    NOHELP, OHELPTASKIDCMD, 0, NOCMD, OTASKID , "", ""
#if defined (MSVERSION) && (MSVERSION >= 0x550)
    }
    extendedAttributes
    {{
    {EXTATTR_FLYTEXT, TXT_Flyover_Dialog4}, 
    {EXTATTR_BALLOON, TXT_Balloon_Dialog4}, 
    }
#endif
    };

IconCmdSmallRsc ICONCMDID_Dialog4 =
    {
    23, 23, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Icon 4 SM",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x00, 0x80,
    0x40, 0x01, 0x00, 0x80, 0x02, 0x01, 0x00, 0x04,
    0x02, 0x00, 0x08, 0x04, 0x00, 0x10, 0x08, 0x00,
    0x20, 0x10, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x40,
    0x00, 0x00, 0x80, 0x00, 0x01, 0x00, 0x00, 0x02,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    }
    };
IconCmdLargeRsc ICONCMDID_Dialog4 =
    {
    31, 31, FORMAT_MONOBITMAP, BLACK_INDEX,
    "Icon 4 LG",
    {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x01, 0x80, 0x00, 0x18, 0x03, 0x00, 0x00,
    0x30, 0x06, 0x00, 0x00, 0x60, 0x0c, 0x00, 0x00,
    0xc0, 0x18, 0x00, 0x01, 0x80, 0x30, 0x00, 0x03,
    0x00, 0x60, 0x00, 0x06, 0x00, 0xc0, 0x00, 0x0c,
    0x01, 0x80, 0x00, 0x18, 0x03, 0x00, 0x00, 0x30,
    0x06, 0x00, 0x00, 0x60, 0x0c, 0x00, 0x00, 0xc0,
    0x18, 0x00, 0x01, 0xff, 0xf0, 0x00, 0x03, 0xff,
    0xe0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01,
    0x80, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06,
    0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x18,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x60,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,
    }
    };
