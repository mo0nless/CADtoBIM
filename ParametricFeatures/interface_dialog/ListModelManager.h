#pragma once

#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MdlApi\dlogbox.r.h>
#include <Mstn\MdlApi\dlogitem.h>
#include <Mstn\MdlApi\DialogItems.h>
#include <Mstn/MdlApi/miscilib.fdf>
#include <Mstn/MdlApi/listmodel.fdf>

namespace DialogInterface
{
	template <int RType>
	struct ListModelManager : DialogItemHookHandler
	{
		ListModelManager(MSDialogP dbP, DialogItemP diP)
			: DialogItemHookHandler(dbP, diP)
		{
		}
		virtual ~ListModelManager() {}
		/// Deallocate a ListModel assigned to this dialog item.
		virtual bool _OnDestroy() override;
		/// Assign a ListModel to this dialog item.
		bool AssignListModel(ListModelP listModel);
		/// Get the ListModel assigned to this dialog item.
		ListModelP  GetListModel();

		///  DestroyListModel is a utility function that destroys any ListModel
		bool DestroyListModel(ListModelP listModel)
		{
			if (listModel)
			{
				mdlListModel_destroy(listModel, true);
				return true;
			}
			//else
			return false;
		}
	};

	ListModelP ListModelManager<RTYPE_ComboBox>::GetListModel()
	{
		/// GetRawItem() is a member of the base class DialogItemHookHandler
		return mdlDialog_comboBoxGetListModelP(GetRawItem());
	}

	ListModelP ListModelManager<RTYPE_ListBox>::GetListModel()
	{
		return mdlDialog_listBoxGetListModelP(GetRawItem());
	}

	//Similarly for the specialised AssignListModel implementation
	bool ListModelManager<RTYPE_ComboBox>::AssignListModel(ListModelP listModel)
	{
		return SUCCESS == mdlDialog_comboBoxSetListModelP(GetRawItem(), listModel);
	}

	bool ListModelManager<RTYPE_ListBox>::AssignListModel(ListModelP listModel)
	{
		const int& Unused{ 0 };
		return SUCCESS == mdlDialog_listBoxSetListModelP(GetRawItem(), listModel, Unused);
	}

	//And the templatised _OnDestroy implementation
	bool ListModelManager<RTYPE_ComboBox>::_OnDestroy()
	{
		return DestroyListModel(GetListModel());
	}

	bool ListModelManager<RTYPE_ListBox>::_OnDestroy()
	{
		return DestroyListModel(GetListModel());
	}
}