#include <Mstn\MicroStation.r.h>
#include <RmgrTools\Tools\datadef.r.h>
#include <RmgrTools\Tools\cexprrsc.r.h>


CexprName 0 = {"usergeneralinfo"};
CexprName 1 = {"actorName"};
CexprName 2 = {"actorSurName"};
CexprName 3 = {"actorEmail"};
CexprName 4 = {"actorRole"};
CexprName 5 = {"browsedFolder"};
CexprName 6 = {"ifcexportsettings"};
CexprName 7 = {"brepTypeExport"};
CexprName 8 = {"activateBRepExport"};
CexprName 9 = {"selectedElementsExport"};
CexprName 10 = {"activeLevelElementsExport"};


CexprNamedStructures 1 =
    {{
    {0,  	0,	1765325851},	/*  usergeneralinfo  */
    {2,  	6,	1842340545},	/*  ifcexportsettings  */
    }};

/*    struct usergeneralinfo    */
CexprType 0 = {18,	2048,	0,	0,	0};
CexprType 1 = {4,	4,	0,	65535,	0};
/*    struct ifcexportsettings    */
CexprType 2 = {18,	8,	1,	6,	0};
CexprType 3 = {11,	1,	0,	65535,	0};


CexprMemberList 0 =
    {{
    {0xc000ff08, 	0,	1, 	0x4c00c9b3}, 	/*  actorName  */
    {0xc000ff08, 	510,	2, 	0x180653b3}, 	/*  actorSurName  */
    {0xc000ff08, 	1020,	3, 	0x2701937a}, 	/*  actorEmail  */
    {0x1, 	1532,	4, 	0x5f00ca09}, 	/*  actorRole  */
    {0xc000ff08, 	1536,	5, 	0x4c0d2e5c}, 	/*  browsedFolder  */
    }};
CexprMemberList 1 =
    {{
    {0x1, 	0,	7, 	0x1919d0f4}, 	/*  brepTypeExport  */
    {0x3, 	4,	8, 	0x39947f34}, 	/*  activateBRepExport  */
    {0x3, 	5,	9, 	0x1b3f6174}, 	/*  selectedElementsExport  */
    {0x3, 	6,	10, 	0x9afb6174}, 	/*  activeLevelElementsExport  */
    }};
