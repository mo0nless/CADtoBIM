#pragma once

/**
 * @file DialogHooks.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
static UserGeneralInfo userGeneralInfo = { L" " , L" ", L" ", 14, L" " };
static IfcExportSettings ifcExportSettings = { 0 , false, false };

static int dlog_colorNumber = 5;
static int dlog_scrollNumber = 500;

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning( disable : 4101)

namespace DialogInterface
{
	/*----------------------------------------------------------------------+
	|                                                                       |
	|   Hooks Handlers														|
	|                                                                       |
	+----------------------------------------------------------------------*/
	namespace DialogHooks
	{
		/**
		 * @brief Class Handler for the main Dialog Box
		 * 
		 * @remark This class inherits and implement the Bentley DialogHookHandler Interface
	     * @see DialogHookHandler
		 */
		class Handler : public DialogHookHandler
		{
		public:
			Handler::Handler(MSDialogP dbP) : DialogHookHandler(dbP) {};

			/**
			 * @brief Dialog Hook replacement function
			 * 
			 * @param dmP 
			 */
			static void Handler::HookResolve(DialogMessage * dmP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dmP->messageType)
				{
					dmP->u.hookResolve.hookHandlerP = new Handler(dmP->db);
					dmP->msgUnderstood = true;
				}
			}
		private:
			/**
			 * @brief Dialog Hook Handler Method override
			 * 
			 * @param create 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnCreate(DialogCreateArgsR create) override
			{
				
				/* Handle the create message and say we are interested in:  */
				/*  1) Item draw messages (Updates)                         */
				/*  2) Mouse events                                         */
				/*  3) Keystroke events                                     */
				/*  4) Dialog box focus changes                             */
				/*  5) Dialig item focus changes                            */
				/*  6) Dialog box resize events                             */

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

		/**
		 * @brief Class Handler for the Item Box
		 * 
		 * @remark This class inherits and implement the Bentley ListModelManager Interface
	     * @see ListModelManager
		 */
		class ItemBoxHadler : ListModelManager<RTYPE_ListBox>
		{
		public:
			/**
			 * @brief Item Box replacement function
			 * 
			 * @param dimP 
			 */
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new ItemBoxHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			/**
			 * @brief Construct a new Item Box Hadler object. 
			 * 
			 * @param dbP 
			 * @param diP 
			 */
			ItemBoxHadler(MSDialogP dbP, DialogItemP diP) : ListModelManager<RTYPE_ListBox>(dbP, diP) { this->dbP = dbP; this->diP = diP; }		

		private:
			MSDialogP dbP;
			DialogItemP diP;

			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param create 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnCreate(DialogItemCreateArgsR create) override
			{
				refreshListBoxList();

				// OnCreate processing 
				return true;
			}

			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param stateChanged 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged)
			{
				//TODO[SB] Add selection by element
				return true;
			}

			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param synchronize 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnSynchronize(DialogItemSynchronizeArgsR synchronize)
			{
				refreshListBoxList();

				return true;
			}


			/**
			 * @brief Refresh the List Box entries
			 * 
			 */
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

		/**
		 * @brief Class Handler for the Start Button
		 * 
		 * @remark This class inherits and implement the Bentley DialogItemHookHandler Interface
	     * @see DialogItemHookHandler
		 */
		class StartButtonHadler : DialogItemHookHandler
		{
		public:
			/**
			 * @brief Start Button Hook replacement function
			 * 
			 * @param dmP 
			 */
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new StartButtonHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}

			/**
			 * @brief Construct a new Start Button Hadler object
			 * 
			 * @param dbP 
			 * @param diP 
			 */
			StartButtonHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			
		private:
			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param button 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnButton(DialogItemButtonArgsR button) override
			{
				//Synch with all the TEXT elements through the SYNONYMID to notify the change
				mdlDialog_synonymsSynch(NULL, SYNONYMID_ActorInfo, NULL);

				mdlDialog_synonymsSynch(NULL, SYNONYMID_ExportSelectionToggle, NULL);

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

				//Start Ifc process conversion 
				Initialization::startIfcConverter(
					ifcExportSettings.brepTypeExport, 
					ifcExportSettings.activateBRepExport, 
					ifcExportSettings.selectedElementsExport
				);

				IfcGeneralInformation::resetInstance();

				return true;
			}
		};

		/**
		 * @brief Class Handler for the Browse Button
		 * 
		 * @remark This class inherits and implement the Bentley DialogItemHookHandler Interface
	     * @see DialogItemHookHandler
		 */
		class BrowseButtonHadler : DialogItemHookHandler
		{
		public:
			/**
			 * @brief Browse Button Hook replacement function
			 * 
			 * @param dmP 
			 */
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new BrowseButtonHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			/**
			 * @brief Construct a new Browse Button Hadler object
			 * 
			 * @param dbP 
			 * @param diP 
			 */
			BrowseButtonHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			
		private:
			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param create 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnCreate(DialogItemCreateArgsR create) override
			{
				WString path = StringUtils::getWString(ExplorerStructure::mainFolderPath);

				//Copy the NEW path in the TEXT's published variable
				wcscpy_s(userGeneralInfo.browsedFolder, path.GetWCharCP());

				//Synch with the TEXT element through the SYNONYMID to notify the change
				mdlDialog_synonymsSynch(NULL, SYNONYMID_DialogBrowse, NULL);

				return true;
			}

			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param button 
			 * @return true 
			 * @return false 
			 */
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

		/**
		 * @brief Class Handler for the Actor Option Button
		 * 
		 * @remark This class inherits and implement the Bentley DialogItemHookHandler Interface
	     * @see DialogItemHookHandler
		 */
		class ActorOptionHadler : DialogItemHookHandler
		{
		public:
			/**
			 * @brief Actor Option Button Hook replacement function
			 * 
			 * @param dmP 
			 */
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new ActorOptionHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			/**
			 * @brief Construct a new Actor Option Hadler object
			 * 
			 * @param dbP 
			 * @param diP 
			 */
			ActorOptionHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			
		private:
			//Creation flag
			bool created = false;

			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param create 
			 * @return true 
			 * @return false 
			 */
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

			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnDestroy() override
			{
				//mdlDialog_optionButtonDeleteAll(GetDialogItem()->rawItemP);

				return true;
			}

			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param stateChanged 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged) override
			{
				//Synch with all the TEXT elements through the SYNONYMID to notify the change
				mdlDialog_synonymsSynch(NULL, SYNONYMID_ActorInfo, NULL);

				IfcGeneralInformation::getInstance()->setActorRole(Ifc4::IfcRoleEnum::Value(userGeneralInfo.actorRole));

				return true;
			}
		};

		/**
		* @brief Class Handler for the Export Toggle Button
		*
		* @remark This class inherits and implement the Bentley DialogItemHookHandler Interface
		* @see DialogItemHookHandler
		*/
		class ExportToggleHadler : DialogItemHookHandler
		{
		public:
			/**
			* @brief Export Toggle Button Hook replacement function
			*
			* @param dimP
			*/
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new ExportToggleHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			/**
			* @brief Construct a new Export Toggle Hadler object
			*
			* @param dbP
			* @param diP
			*/
			ExportToggleHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}

		private:
			/**
			* @brief Item Hook Handler Method override
			*
			* @param allCreated
			* @return true
			* @return false
			*/
			virtual bool _OnAllCreated(DialogItemAllCreatedArgsR allCreated)
			{
				/* set the enabled state of the toggle button */
				//mdlDialog_itemSetEnabledState(GetDialog(), GetDialogItem()->GetItemIndex(), ifcExportSettings.selectedElementsExport, FALSE);
				GetDialogItem()->SetEnabled(ifcExportSettings.selectedElementsExport);

				return true;
			}

			/**
			* @brief Item Hook Handler Method override
			*
			* @param stateChanged
			* @return true
			* @return false
			*/
			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged)
			{
				ifcExportSettings.selectedElementsExport = !ifcExportSettings.selectedElementsExport;

				GetDialogItem()->SetEnabled(ifcExportSettings.selectedElementsExport);

				mdlDialog_synonymsSynch(NULL, SYNONYMID_ExportSelectionToggle, NULL);

				return true;
			}
		};


		/**
		* @brief Class Handler for the BRep Export Toggle Button
		*
		* @remark This class inherits and implement the Bentley DialogItemHookHandler Interface
		* @see DialogItemHookHandler
		*/
		class BRepToggleHadler : DialogItemHookHandler
		{
		public:
			/**
			* @brief BRep Export Toggle Button Hook replacement function
			*
			* @param dimP
			*/
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new BRepToggleHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			/**
			* @brief Construct a new BRep Export Toggle Hadler object
			*
			* @param dbP
			* @param diP
			*/
			BRepToggleHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}

		private:
			/**
			* @brief Item Hook Handler Method override
			*
			* @param allCreated
			* @return true
			* @return false
			*/
			virtual bool _OnAllCreated(DialogItemAllCreatedArgsR allCreated)
			{
				/* set the enabled state of the toggle button */
				//mdlDialog_itemSetEnabledState(GetDialog(), GetDialogItem()->GetItemIndex(), ifcExportSettings.activateBRepExport, FALSE);
				GetDialogItem()->SetEnabled(ifcExportSettings.activateBRepExport);

				return true;
			}

			/**
			* @brief Item Hook Handler Method override
			*
			* @param stateChanged
			* @return true
			* @return false
			*/
			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged)
			{
				ifcExportSettings.activateBRepExport = !ifcExportSettings.activateBRepExport;

				GetDialogItem()->SetEnabled(ifcExportSettings.activateBRepExport);

				mdlDialog_synonymsSynch(NULL, SYNONYMID_ExportSelectionToggle, NULL);

				return true;
			}
		};

		/**
		* @brief Class Handler for the BRep Option Button
		*
		* @remark This class inherits and implement the Bentley DialogItemHookHandler Interface
		* @see DialogItemHookHandler
		*/
		class BRepOptionHadler : DialogItemHookHandler
		{
		public:
			/**
			* @brief BRep Option Button Hook replacement function
			*
			* @param dmP
			*/
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new BRepOptionHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			/**
			* @brief Construct a new BRep Option Hadler object
			*
			* @param dbP
			* @param diP
			*/
			BRepOptionHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}

		private:
			
			/**
			* @brief Item Hook Handler Method override
			*
			* @param stateChanged
			* @return true
			* @return false
			*/
			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged) override
			{

				//Synch with all the TEXT elements through the SYNONYMID to notify the change
				mdlDialog_synonymsSynch(NULL, SYNONYMID_ExportSelectionToggle, NULL);

				return true;
			}
		};

#pragma region UNUSED HOOKS FUNCTION

		/**
		 * @brief Class Handler for the Pull Down menu Button
		 * 
		 * @remark This class inherits and implement the Bentley DialogItemHookHandler Interface
	     * @see DialogItemHookHandler
		 */
		class PullDownMenuHadler : DialogItemHookHandler
		{
		public:
			/**
			 * @brief Pull Down menu Button Hook replacement function
			 * 
			 * @param dmP 
			 */
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new PullDownMenuHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			/**
			 * @brief Construct a new Pull Down Menu Hadler object
			 * 
			 * @param dbP 
			 * @param diP 
			 */
			PullDownMenuHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			
		private:
			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param button 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnButton(DialogItemButtonArgsR button) override
			{
				return true;
			}
		};

		/**
		 * @brief Class Handler for the Scroll Bar
		 * 
		 * @remark This class inherits and implement the Bentley DialogItemHookHandler Interface
	     * @see DialogItemHookHandler
		 */
		class ScrollBarHadler : DialogItemHookHandler
		{
		public:
			/**
			 * @brief Scroll Bar Hook replacement function
			 * 
			 * @param dimP 
			 */
			static void HookResolve(DialogItemMessage *dimP)
			{
				if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
				{
					dimP->u.hookResolve.hookHandlerP = new ScrollBarHadler(dimP->db, dimP->dialogItemP);
					dimP->msgUnderstood = true;
				}
			}
			/**
			 * @brief Construct a new Scroll Bar Hadler object
			 * 
			 * @param dbP 
			 * @param diP 
			 */
			ScrollBarHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
			
		private:
			/**
			 * @brief Item Hook Handler Method override
			 * 
			 * @param stateChanged 
			 * @return true 
			 * @return false 
			 */
			virtual bool _OnStateChanged(DialogItemStateChangedArgsR stateChanged)
			{
				/* Handle state changed message and synchronize all scroll bar	*/
				/* related items if the value of the scroll bar access string	*/
				/* really did change                                            */
				if (stateChanged.reallyChanged)
					mdlDialog_synonymsSynch(NULL, SYNONYMID_DialogScroll, NULL);
				return true;
			}
		};

		
#pragma endregion

	}
}