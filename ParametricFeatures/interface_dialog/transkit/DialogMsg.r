/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/DialogBoxes/DialogBoxDemo/transkit/DialogMsg.r $
|
|  $Copyright: (c) 2015 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   $Logfile:   J:/mdl/examples/Dialog/english/DialogMsg.r_v  $
|   $Workfile:   DialogMsg.r  $
|   $Revision: 1.2 $
|   $Date: 2001/05/29 14:32:43 $
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   Function -                                                          |
|                                                                       |
|   Dialog Box demonstration application messages                       |
|                                                                       |
+----------------------------------------------------------------------*/
#include <Mstn\MdlApi\dlogbox.r.h>
#include <Mstn\MdlApi\dlogids.r.h>
#include "..\DialogIds.h"

MessageList STRINGID_Messages =
{
    {
    { MSGID_CommandTable,   "Unable to load command table" },
    //{ MSGID_ListBox,        "Listbox line %d, column %d" },
    { MSGID_ListBox,        "%d" },
    }
};
