#pragma once

#include "../data_processing/initialization/headers/Initialization.h"
#include "../common/utils/headers/ExplorerStructure.h"
#include "../ifc/main/headers/IfcGeneralInformation.h"


#include <string>
#include <UI\Layout\Margins.h>
#include <UI\Layout\StackLayout.h>

#include <Mstn\DocumentManager.h>

#include "ListModelManager.h"
#include <Mstn/ISessionMgr.h>
#include <Mstn/MdlApi/MSDialog.h>
#include <Mstn/MdlApi/GuiLayout.h>
#include <Mstn/MdlApi/GuiLayoutProperties.h>

#include "DialogIds.h"

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT
USING_NAMESPACE_BENTLEY_UIFRAMEWORK

using namespace Common::Utilities;
using namespace DataProcessing::Initialization;
using namespace Ifc::Main;

/*----------------------------------------------------------------------+
|                                                                       |
|   Public Global variables                                             |
|                                                                       |
+----------------------------------------------------------------------*/
/* The following variable is referenced in C expression strings used by
the text, option button, and toggle button items defined in Dialog.r.
The initial external state of the Text item and the Browse button
(they are both looking at the same application variable).*/
static UserGeneralInfo userGeneralInfo = { L" " , L" ", L" ", 14, L" "};
static bool dlog_ToggleSingleElementButton = false;

static int dlog_colorNumber = 5;
static int dlog_scrollNumber = 500;
//static int dlog_optionbtnNumber1 = 0;
static int dlog_optionbtnNumber2 = 0;

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning( disable : 4101)

namespace DialogInterface
{
	namespace DialogHooks
	{
		/*----------------------------------------------------------------------+
		|                                                                       |
		|   Hooks Handlers														|
		|                                                                       |
		+----------------------------------------------------------------------*/
		class Handler : public DialogHookHandler
		{
		public:
			Handler::Handler(MSDialogP dbP) : DialogHookHandler(dbP) {};

			static void Handler::HookResolve(DialogMessage * dmP)
			{
				/* Handle the create message and say we are interested in:  */
				/*  1) Item draw messages (Updates)                         */
				/*  2) Mouse events                                         */
				/*  3) Keystroke events                                     */
				/*  4) Dialog box focus changes                             */
				/*  5) Dialig item focus changes                            */
				/*  6) Dialog box resize events                             */
				if (DITEM_MESSAGE_HOOKRESOLVE == dmP->messageType)
				{
					dmP->u.hookResolve.hookHandlerP = new Handler(dmP->db);
					dmP->msgUnderstood = true;
				}
			}
		private:
			// Dialog Hook Handler Method override
			virtual bool _OnCreate(DialogCreateArgsR create) override
			{
				// OnCreate processing
				create.interests.updates = TRUE;
				create.interests.mouses = TRUE;
				create.interests.keystrokes = TRUE;
				create.interests.dialogFocuses = TRUE;
				create.interests.itemFocuses = TRUE;
				create.interests.resizes = TRUE;

				return true;
			}
		};

		class ItemBoxHadler : ListModelManager<RTYPE_ListBox>
		{
		public:
			// Dialog Hook replacement function
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new ItemBoxHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			// Item Hook Handler Constructor
			ItemBoxHadler(MSDialogP dbP, DialogItemP diP) : ListModelManager<RTYPE_ListBox>(dbP, diP) { this->dbP = dbP; this->diP = diP; }
			// Item Hook Handler Method override		

		private:
			MSDialogP dbP;
			DialogItemP diP;

			virtual bool _OnCreate(DialogItemCreateArgsR create) override
			{
				refreshListBoxList();

				// OnCreate processing 
				return true;
			}

			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged)
			{
				return true;
			}

			virtual bool _OnSynchronize(DialogItemSynchronizeArgsR synchronize)
			{
				refreshListBoxList();

				return true;
			}

			void refreshListBoxList()
			{
				IfcGeneralInformation::resetInstance();
				Initialization::collectsAllElements();

				ListModelP listModel = this->GetListModel();
				if (NULL == listModel)
					listModel = mdlListModel_create(2);
				else
					mdlListModel_empty(listModel, TRUE);


				for (auto elemRef : Initialization::allGraphicElements)
				{
					ListRowP pRow = mdlListRow_create(listModel);
					ListCellP pCell;
					WChar buffer[80];
					WString elDescr, elemID;

					ElementHandle currentElem(elemRef);
					currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
					elemID.Sprintf(L"%d", currentElem.GetElementId());

					if (NULL != (pCell = mdlListRow_getCellAtIndex(pRow, 0)))
					{
						mdlListCell_setStringValue(pCell, elemID.c_str(), true);
						//mdlListCell_setPointerValue(pCell, elemRef);
					}
					if (NULL != (pCell = mdlListRow_getCellAtIndex(pRow, 1)))
					{
						mdlListCell_setStringValue(pCell, elDescr.c_str(), true);
					}

					/*-----------------------------------------------------------------------
					* @return Index of new row or MDLERR_ADDRNOTVALID if pModel is invalid, *
					* MDLERR_INSFMEMORY if there was not enough memory to insert the row.	*
					* -1 is append after the last row										*
					-----------------------------------------------------------------------*/
					if (0 > mdlListModel_insertRow(listModel, pRow, -1))
						BeAssert(0);
				}

				this->AssignListModel(listModel);

			}
		};

#pragma region BUTTONS
		class StartButtonHadler : DialogItemHookHandler
		{
		public:
			// Dialog Hook replacement function
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new StartButtonHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			// Item Hook Handler Constructor
			StartButtonHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			// Item Hook Handler Method override
		private:
			virtual bool _OnButton(DialogItemButtonArgsR button) override
			{
				//Synch with all the TEXT elements through the SYNONYMID to notify the change
				mdlDialog_synonymsSynch(NULL, SYNONYMID_ActorInfo, NULL);

				//Get the latest update before start conversion
				ExplorerStructure::getInstance()->updateFileNameFilePath();

				WString name, sname, email;
				name = userGeneralInfo.actorName;
				sname = userGeneralInfo.actorSurName;
				email = userGeneralInfo.actorEmail;

				IfcGeneralInformation* ifcGInfo = IfcGeneralInformation::getInstance();
				ifcGInfo->setActorRole(Ifc4::IfcRoleEnum::Value(userGeneralInfo.actorRole));
				ifcGInfo->setActorName(StringUtils::getString(name));
				ifcGInfo->setActorSurName(StringUtils::getString(sname));
				ifcGInfo->setActorEmail(StringUtils::getString(email));

				Initialization::startIfcConverter();

				IfcGeneralInformation::resetInstance();

				return true;
			}
		};

		class BrowseButtonHadler : DialogItemHookHandler
		{
		public:
			// Dialog Hook replacement function
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new BrowseButtonHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			// Item Hook Handler Constructor
			BrowseButtonHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			// Item Hook Handler Method override
		private:
			virtual bool _OnCreate(DialogItemCreateArgsR create) override
			{
				WString path = StringUtils::getWString(ExplorerStructure::mainFolderPath);

				//Copy the NEW path in the TEXT's published variable
				wcscpy_s(userGeneralInfo.browsedFolder, path.GetWCharCP());

				//Synch with the TEXT element through the SYNONYMID to notify the change
				mdlDialog_synonymsSynch(NULL, SYNONYMID_DialogBrowse, NULL);

				return true;
			}

			virtual bool _OnButton(DialogItemButtonArgsR button) override
			{
				ExplorerStructure::mainFolderPath = ExplorerStructure::getInstance()->BrowseFolder(ExplorerStructure::mainFolderPath);

				//Copy the NEW path in the TEXT's published variable
				WString path = StringUtils::getWString(ExplorerStructure::mainFolderPath);
				wcscpy_s(userGeneralInfo.browsedFolder, path.GetWCharCP());

				//Synch with the TEXT element through the SYNONYMID to notify the change
				mdlDialog_synonymsSynch(NULL, SYNONYMID_DialogBrowse, NULL);

				return true;
			}
		};

#pragma endregion

		class ActorOptionHadler : DialogItemHookHandler
		{
		public:
			// Dialog Hook replacement function
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new ActorOptionHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			// Item Hook Handler Constructor
			ActorOptionHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			// Item Hook Handler Method override
		private:
			bool created = false;
			virtual bool _OnCreate(DialogItemCreateArgsR create) override
			{
				if (!created)
				{
					int MAX = (int)Ifc4::IfcRoleEnum::IfcRole_USERDEFINED;
					for (int index = 0; index < (MAX + 1); index++)
					{
						Ifc4::IfcRoleEnum::Value valEnum = Ifc4::IfcRoleEnum::Value(index);
						string v = Ifc4::IfcRoleEnum::ToString(valEnum);
						bool bPtr = true;
						UInt32 value = index;
						int commandSource = LCMD;

						mdlDialog_optionButtonInsSubItem(
							StringUtils::getWString(v).c_str(), NULL, NULL, NULL,
							&commandSource,
							&value, NULL,
							&bPtr, NULL,
							GetDialogItem()->rawItemP,
							index
						);
					}

					IfcGeneralInformation* ifcGInfo = IfcGeneralInformation::getInstance();

					WString name, sname, email;

					name = StringUtils::getWString(ifcGInfo->getActorName());
					sname = StringUtils::getWString(ifcGInfo->getActorSurName());
					email = StringUtils::getWString(ifcGInfo->getActorEmail());

					//Copy the NEW path in the TEXT's published variable
					wcscpy_s(userGeneralInfo.actorName, name.GetWCharCP());
					wcscpy_s(userGeneralInfo.actorSurName, sname.GetWCharCP());
					wcscpy_s(userGeneralInfo.actorEmail, email.GetWCharCP());

					//Synch with all the TEXT elements through the SYNONYMID to notify the change
					mdlDialog_synonymsSynch(NULL, SYNONYMID_ActorInfo, NULL);
					ifcGInfo->setActorRole(Ifc4::IfcRoleEnum::Value(userGeneralInfo.actorRole));

					created = true;
				}

				return true;
			}

			virtual bool _OnDestroy() override
			{
				//mdlDialog_optionButtonDeleteAll(GetDialogItem()->rawItemP);

				return true;
			}

			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged) override
			{
				//Synch with all the TEXT elements through the SYNONYMID to notify the change
				mdlDialog_synonymsSynch(NULL, SYNONYMID_ActorInfo, NULL);

				IfcGeneralInformation::getInstance()->setActorRole(Ifc4::IfcRoleEnum::Value(userGeneralInfo.actorRole));

				return true;
			}
		};

#pragma region UNUSED HOOKS FUNCTION

		class PullDownMenuHadler : DialogItemHookHandler
		{
		public:
			// Dialog Hook replacement function
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new PullDownMenuHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			// Item Hook Handler Constructor
			PullDownMenuHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			// Item Hook Handler Method override
		private:
			virtual bool _OnButton(DialogItemButtonArgsR button) override
			{
				return true;
			}
		};

		class ScrollBarHadler : DialogItemHookHandler
		{
		public:
			// Dialog Hook replacement function
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new ScrollBarHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			// Item Hook Handler Constructor
			ScrollBarHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			// Item Hook Handler Method override
		private:
			/* Handle state changed message and synchronize all scroll bar	*/
			/* related items if the value of the scroll bar access string	*/
			/* really did change                                            */
			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged)
			{
				if (stateChanged.reallyChanged)
					mdlDialog_synonymsSynch(NULL, SYNONYMID_DialogScroll, NULL);
				return true;
			}
		};

		class ExportToggleHadler : DialogItemHookHandler
		{
		public:
			// Dialog Hook replacement function
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new ExportToggleHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			// Item Hook Handler Constructor
			ExportToggleHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			// Item Hook Handler Method override
		private:
			virtual bool _OnAllCreated(DialogItemAllCreatedArgsR allCreated)
			{
				/* set the enabled state of the toggle button */
				//mdlDialog_itemSetEnabledState(GetDialog(), GetDialogItem()->GetItemIndex(), dlog_ToggleSingleElementButton, FALSE);
				GetDialogItem()->SetEnabled(dlog_ToggleSingleElementButton);

				return true;
			}
			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged)
			{
				dlog_ToggleSingleElementButton = !dlog_ToggleSingleElementButton;

				GetDialogItem()->SetEnabled(dlog_ToggleSingleElementButton);

				mdlDialog_synonymsSynch(NULL, SYNONYMID_ToggleSelection, NULL);

				return true;
			}
		};
#pragma endregion

	}
}