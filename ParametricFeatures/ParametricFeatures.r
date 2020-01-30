//--------------------------------------------------------------------------------------+
//
//    $Source: ParametricFeatures.r $
//
//    $Copyright: (c) 2019 Bentley Systems, Incorporated. All rights reserved. $
//
//--------------------------------------------------------------------------------------+

//--------------------------------------------------------------------------------------
//    Include Files
//--------------------------------------------------------------------------------------
#include    <Mstn\MdlApi\rscdefs.r.h>
#include    <Mstn\MdlApi\cmdclass.r.h>

//-------------------------------------------------------------------------------------
//    Register Application and DLL
//-------------------------------------------------------------------------------------
#define  DLLAPP_ParametricFeatures       1

DllMdlApp DLLAPP_ParametricFeatures =
{
    L"ParametricFeatures", L"ParametricFeatures"          // taskid, dllName
}

//-------------------------------------------------------------------------------------
//    Local Defines
//-------------------------------------------------------------------------------------
#define	CT_NONE		        0
#define CT_MAIN		        1

//-------------------------------------------------------------------------------------
//    Main commands
//    {  1, CT_NONE,	    SHOW, NONE,         "CMD_HELLO_WORLD" },  
//-------------------------------------------------------------------------------------
CommandTable	CT_MAIN =
{ 
    {  1, CT_NONE,	    MANIPULATION, NONE,         "CMD_TREE"},  
    {  2, CT_NONE,	    MANIPULATION, NONE,         "CMD_SHAPE"},  
	{  3, CT_NONE,	    INPUT, NONE,         "CMD_PARAMETRICFEATURES_EXIT"},
};
