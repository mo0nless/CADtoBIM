#pragma once

//#include "../stdafx.h"
#include "DialogIds.h"
//#include "../common/models/headers/SessionManager.h"
#include "../data_processing/initialization/headers/Initialization.h"

#include <Mstn/isessionmgr.h>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MdlApi\dlogitem.h>
#include <Mstn/MdlApi/DialogItem.h>
#include <Mstn\MdlApi\DialogItems.h>
#include <Mstn/MdlApi/MSDialog.h>
#include <Mstn/MdlApi/GuiLayout.h>
#include <UI\Layout\LayoutManager.h>
#include <UI\Layout\LayoutControl.h>
//#include <UI\Layout\GridLayout.h>
#include <UI\Layout\Margins.h>
#include <UI\Layout\StackLayout.h>
#include <UI\UIFramework.h>

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)

namespace DialogHooks 
{
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

		virtual bool _OnInit(DialogInitArgsR init) override
		{
			MSDialogP dbP = this->GetDialog();
			// Create the GuiLayoutHelper that will hold the top-level layout
			GuiLayoutHelper *layoutHelper = GuiLayoutHelper::Create(dbP);
			// Create a vertical Stack layout, which is the top-level layout
			//VStackLayout *vStackLayout = VStackLayout::Create();
			//vStackLayout->SetLayoutMargins(0);

			// Get the MenuBar on the dialog and add it to the vertical Stack layout
			/*DialogItem *diP = dbP->GetItemByTypeAndId(RTYPE_MenuBar, MENUBARID_Dialog);
			if (NULL != diP)
				vStackLayout->AddControl(GuiLayoutControl::Create(layoutHelper, diP,
					SizePolicy(SizePolicyType::SP_Preferred, SizePolicyType::SP_Fixed)));*/
			//// Create a horizontal stack layout, which will hold a ListBox on the left
			//// and a ContainerPanel to the right of it.
			//HStackLayout *hStackLayout1 = HStackLayout::Create();
			//hStackLayout1->AddSpacing(XC);
			//diP = dbP->GetItemByTypeAndId(RTYPE_ListBox, LISTBOXID_Dialog);
			//if (NULL != diP)
			//	hStackLayout1->AddControl(GuiLayoutControl::Create(layoutHelper, diP,
			//		SizePolicy(SizePolicyType::SP_Fixed, SizePolicyType::SP_Preferred)));

			//// Add the horizontal stack layout to the top-level vertical stack layout
			//vStackLayout->AddLayout(hStackLayout1);

			//// Set the vertical stack layout as the top-level layout
			//layoutHelper->SetLayout(vStackLayout);
			// Set the GuiLayoutHelper as the layout helper for the dialog.
			// When the dialog size changes or control sizes/properties change, 
			// the layout manager will automatically be invoked.
			dbP->SetLayoutHelper(layoutHelper);
			return true;
		}
	};

	class ItemBoxHadler : DialogItemHookHandler
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
		ItemBoxHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
		// Item Hook Handler Method override
	private:
		virtual bool _OnCreate(DialogItemCreateArgsR create) override
		{			
			RawItemHdrP listBoxP = this->GetRawItem();

			int          iMember;
			WString        formatStr;

			auto pGraElement = ISessionMgr::GetActiveDgnModelP()->GetGraphicElementsP();
			vector<PersistentElementRefP> elements;

			for (PersistentElementRefP elemRef : *pGraElement)
			{
				elements.push_back(elemRef);
			}

			int numElements = ISessionMgr::GetActiveDgnModelP()->GetElementCount(DgnModelSections::GraphicElements);

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
			// OnCreate processing 
			return true;
		}
		virtual bool _OnDestroy() override
		{
			RawItemHdrP listBoxP = this->GetRawItem();
			StringList	*strListP = mdlDialog_listBoxGetStrListP(listBoxP);

			/* free the string list if it is allocated */
			if (NULL != strListP)
			{
				mdlStringList_destroy(strListP);
			}

			return true;
		}
		virtual bool _OnInit(DialogItemInitArgsR init) override
		{
			return true;
		}

		StringList  *stringListP;
	};

	class ButtonHadler : DialogItemHookHandler
	{
	public:
		// Dialog Hook replacement function
		static void HookResolve(DialogItemMessage *dimP)
		{
			if (DITEM_MESSAGE_HOOKRESOLVE == dimP->messageType)
			{
				dimP->u.hookResolve.hookHandlerP = new ButtonHadler(dimP->db, dimP->dialogItemP);
				dimP->msgUnderstood = true;
			}
		}
		// Item Hook Handler Constructor
		ButtonHadler(MSDialogP dbP, DialogItemP diP) : DialogItemHookHandler(dbP, diP) {}
		// Item Hook Handler Method override
	private:
		virtual bool _OnButton(DialogItemButtonArgsR button) override
		{
			WString myString;
			myString.Sprintf(L"IFC Converter");
			mdlOutput_messageCenter(OutputMessagePriority::Info, myString.c_str(), myString.c_str(), OutputMessageAlert::None);

			Initialization::startIfcConverter();

			return true;
		}
	};

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
			if(stateChanged.reallyChanged)
				mdlDialog_synonymsSynch(NULL, SYNONYMID_DialogScroll, NULL);
			return true;
		}
	};
}