#pragma once

/**
 * @file ListModelManager.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief http://www.la-solutions.co.uk/content/CONNECT/MicroStationAPI/MicroStationAPI-ListModelHook.htm
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MdlApi\dlogbox.r.h>
#include <Mstn\MdlApi\dlogitem.h>
#include <Mstn\MdlApi\DialogItems.h>
#include <Mstn/MdlApi/miscilib.fdf>
#include <Mstn/MdlApi/listmodel.fdf>

namespace DialogInterface
{
	/**
	 * @brief Class Handler. Specialise instantiated class by the non-type template parameter  RType (resource type)
	 * 
	 * @tparam RType 
	 * @remark This class inherits and implement the Bentley DialogHookHandler Interface
	 * @see DialogHookHandler
	 */
	template <int RType>
	struct ListModelManager : DialogItemHookHandler
	{
		ListModelManager(MSDialogP dbP, DialogItemP diP)
			: DialogItemHookHandler(dbP, diP)
		{
		}
		virtual ~ListModelManager() {}
		/**
		 * @brief Deallocate a ListModel assigned to this dialog item.
		 * 
		 * @return true 
		 * @return false 
		 */

		virtual bool _OnDestroy() override;
		/**
		 * @brief Assign a ListModel to this dialog item.
		 * 
		 * @param listModel 
		 * @return true 
		 * @return false 
		 */

		bool AssignListModel(ListModelP listModel);
		/**
		 * @brief Get the List Model object. Get the ListModel assigned to this dialog item.
		 * 
		 * @return ListModelP 
		 */
		ListModelP  GetListModel();

		/**
		 * @brief DestroyListModel is a utility function that destroys any ListModel
		 * 
		 * @param listModel 
		 * @return true 
		 * @return false 
		 */
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