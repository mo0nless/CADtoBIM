#pragma once
#if !defined (PROGRESS_BAR_H_INCLUDED_)
#define PROGRESS_BAR_H_INCLUDED_

/**
 * @file ProgressBar.hpp
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn/MdlApi/msdialog.fdf>

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief Base class for Completion Bar implementations.
		 * 
		 */
		struct CompletionBar
		{
			static constexpr bool AutoClose = true;
			int numGraphicElement = 0;

			/**
			 * @brief Construct a new Completion Bar object, to be called by inheriting classes.
			 * 
			 * @param autoClose 
			 */
			CompletionBar(bool autoClose)
				: autoClose(autoClose), completionBarDbP(nullptr)
			{
			}
			
			/**
			 * @brief Destroy the Completion Bar object. Destructor closes Completion Bar automatically if requested.
			 * 
			 */
			virtual ~CompletionBar()
			{
				if (autoClose)
					Close();
			}
			
			/**
			 * @brief Get the Dialog object. Abstract method must be overridden by implementation class.
			 * 
			 * @param message 
			 * @return MSDialogP 
			 */
			virtual MSDialogP GetDialog(WCharCP message) = 0;
			
			/**
			 * @brief Open and initialise a Completion Bar.
			 * 
			 * @param message 
			 * @param percentage
			 */
			void Open(WCharCP message, int percentage = 0)
			{
				MSDialogP dbP{ GetDialog(message) };

				if (message)
					mdlOutput_printf(MSG_ERROR, message);

				if (dbP)
				{
					CompletionBarInfo       data;
					data.msgTextW = nullptr;
					data.percentComplete = 0;
					mdlDialog_hookDialogSendUserMsg(dbP, CMPLBARID_ResetCompletionBar, &data);
					mdlDialog_hookDialogSendUserMsg(dbP, GENERICID_CompletionBar, 0);
				}

				completionBarDbP = dbP;
				mdlDialog_completionBarUpdate(completionBarDbP, nullptr, percentage);
				mdlSystem_startBusyCursor();
			}
			/**
			 * @brief Open and initialise a Completion Bar.
			 * 
			 * @param message 
			 * @param percentage
			 */
			void Open(WStringCR message, int percentage = 0)
			{
				Open(message.c_str());
			}
			
			/**
			 * @brief Send a message to an existing Completion Bar.
			 * 
			 * @param message 
			 * @param percentComplete 
			 */
			void Update(WStringCR message, int percentComplete)
			{
				Update(message.c_str(), percentComplete);
			}

			/**
			 * @brief Send a message to an existing Completion Bar.
			 * 
			 * @param message 
			 * @param percentComplete 
			 */
			void Update(WCharCP message, int percentComplete)
			{
				if (completionBarDbP)
					mdlDialog_completionBarUpdate(completionBarDbP, message, percentComplete);
			}

			/**
			 * @brief Close an existing Completion Bar.
			 * 
			 */
			void Close()
			{
				if (completionBarDbP)
				{
					mdlDialog_completionBarClose(completionBarDbP);
					mdlDialog_hookDialogSendUserMsg(completionBarDbP, -GENERICID_CompletionBar, 0);

					mdlOutput_error(L"");
					completionBarDbP = nullptr;

					mdlSystem_stopBusyCursor();
				}
			}

		protected:
			MSDialogP completionBarDbP = nullptr;
			/**
			 * @brief Member variable signals the destructor to close the Completion Bar dialog.
			 * 
			 */
			bool autoClose = false;
			int globalIndex = 0;
			mutable boost::shared_mutex _mutex;
		};
		
		/**
		 * @brief DialogCompletionBar class shows a Completion Bar in its own dialog.
		 * 
		 */
		struct DialogCompletionBar : CompletionBar
		{
			/**
			 * @brief Construct a new Dialog Completion Bar object. Constructor calls the base class constructor.
			 * 
			 * @param autoClose 
			 * @remark Defaults to closing Completion Bar automatically in destructor.
			 */
			DialogCompletionBar(bool autoClose = AutoClose) : CompletionBar(autoClose) {}

			/**
			 * @brief Get the Dialog object. Return a pointer to a new Completion Bar dialog.
			 * 
			 * @param message 
			 * @return MSDialogP 
			 */
			MSDialogP GetDialog(WCharCP message) override
			{
				return mdlDialog_completionBarOpen(message);
			}
			void Update(WStringCR message)
			{
				boost::unique_lock<boost::shared_mutex> guard(_mutex);
				int percentComplete = 100 * globalIndex / numGraphicElement;
				CompletionBar::Update(message.c_str(), percentComplete);
			}
			/**
			 * @brief Increment the index of the progressbar
			 * 
			 */
			void IncrementIndex()
			{
				boost::unique_lock<boost::shared_mutex> guard(_mutex);
				globalIndex += 1;
			}

			/**
			 * @brief Get the Index of the progressbar
			 * 
			 * @return int 
			 */
			int GetIndex()
			{
				boost::shared_lock<boost::shared_mutex> guard(_mutex);
				return globalIndex;
			}
		};
		
		/**
		 * @brief StatusCompletionBar class shows a Completion Bar in MicroStation's status panel, usually lower-right in MicroStation's window.
		 * 
		 */
		struct StatusCompletionBar : CompletionBar
		{
			/**
			 * @brief Construct a new Status Completion Bar object. Constructor calls the base class constructor.
			 * 
			 * @param autoClose 
			 * @remark Defaults to closing Completion Bar automatically in destructor.
			 */
			StatusCompletionBar(bool autoClose = AutoClose) : CompletionBar(autoClose) {}

			/**
			 * @brief Get the Dialog object. Get MicroStation's Command Status dialog.
			 * 
			 * @param unused 
			 * @return MSDialogP 
			 */
			MSDialogP GetDialog(WCharCP unused) override
			{
				return mdlDialog_find(DIALOGID_CommandStatus, nullptr);
			}
		};
	}
}
#endif	//	!defined (PROGRESS_BAR_H_INCLUDED_)
