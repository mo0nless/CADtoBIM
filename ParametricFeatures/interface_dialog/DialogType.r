#include <Mstn\MicroStation.r.h>
#include <RmgrTools\Tools\datadef.r.h>
#include <RmgrTools\Tools\cexprrsc.r.h>


CexprName 0 = {"ifcgeneralinfo"};
CexprName 1 = {"actorName"};
CexprName 2 = {"actorSurName"};
CexprName 3 = {"actorEmail"};
CexprName 4 = {"actorRole"};
CexprName 5 = {"browsedFolder"};


CexprNamedStructures 1 =
    {{
    {0,  	0,	337237019},	/*  ifcgeneralinfo  */
    }};

/*    struct ifcgeneralinfo    */
CexprType 0 = {18,	2048,	0,	0,	0};
CexprType 1 = {4,	4,	0,	65535,	0};


CexprMemberList 0 =
    {{
    {0xc000ff08, 	0,	1, 	0x4c00c9b3}, 	/*  actorName  */
    {0xc000ff08, 	510,	2, 	0x180653b3}, 	/*  actorSurName  */
    {0xc000ff08, 	1020,	3, 	0x2701937a}, 	/*  actorEmail  */
    {0x1, 	1532,	4, 	0x5f00ca09}, 	/*  actorRole  */
    {0xc000ff08, 	1536,	5, 	0x4c0d2e5c}, 	/*  browsedFolder  */
    }};
