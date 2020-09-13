#pragma once
#if !defined (PROGRESS_BAR_H_INCLUDED_)
#define PROGRESS_BAR_H_INCLUDED_


#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn/MdlApi/msdialog.fdf>

///	<summary>
///	Base class for Completion Bar implementations.
///	</summary>
struct CompletionBar
{
	static constexpr bool AutoClose = true;

	///	<summary>
	///	Constructor to be called by inheriting classes.
	///	</summary>
	CompletionBar (bool autoClose)
	: autoClose (autoClose), completionBarDbP (nullptr)
	{
	}
	///	<summary>
	///	Destructor closes Completion Bar automatically if requested.
	///	</summary>
	virtual ~CompletionBar ()
	{
		if (autoClose)
			Close ();
	}
	///	<summary>
	///	Abstract method must be overridden by implementation class.
	///	</summary>
	virtual MSDialogP	GetDialog	(WCharCP message) = 0;
	///	<summary>
	///	Open and initialise a Completion Bar.
	///	</summary>
	void Open (WCharCP message, int perc = 0)
	{
		MSDialogP   dbP {GetDialog (message)};

		if (message)
			mdlOutput_printf (MSG_ERROR, message);

		if (dbP)
		{
			CompletionBarInfo       data;
			data.msgTextW = nullptr;
			data.percentComplete = 0;
			mdlDialog_hookDialogSendUserMsg (dbP, CMPLBARID_ResetCompletionBar, &data);
			mdlDialog_hookDialogSendUserMsg (dbP, GENERICID_CompletionBar, 0);
		}

		completionBarDbP = dbP;
		mdlDialog_completionBarUpdate (completionBarDbP, nullptr,  perc);
		mdlSystem_startBusyCursor();
	}
	void Open (WStringCR message, int perc = 0)
	{
		Open (message.c_str ());
	}
	///	<summary>
	///	Send a message to an existing Completion Bar.
	///	</summary>
	void Update (WStringCR message, int percentComplete)
	{
		Update (message.c_str (), percentComplete);
	}
	void Update (WCharCP message, int percentComplete)
	{
		if (completionBarDbP)
			mdlDialog_completionBarUpdate (completionBarDbP, message,  percentComplete);
	}
	///	<summary>
	///	Close an existing Completion Bar.
	///	</summary>
	void Close ()
	{
		if (completionBarDbP)
		{
			mdlDialog_completionBarClose (completionBarDbP);
			mdlDialog_hookDialogSendUserMsg (completionBarDbP, -GENERICID_CompletionBar, 0);

			mdlOutput_error (L"");
			completionBarDbP = nullptr;

			mdlSystem_stopBusyCursor();
		}
	}

protected:
	MSDialogP   completionBarDbP = nullptr;
	///	<summary>
	///	Member variable signals the destructor to close the Completion Bar dialog.
	///	</summary>
	bool		autoClose = false;
};
///	<summary>
///	DialogCompletionBar class shows a Completion Bar in its own dialog.
///	</summary>
struct DialogCompletionBar : CompletionBar
{
	///	<summary>
	///	Constructor calls the base class constructor.
	///	</summary>
	///	<remarks>Defaults to closing Completion Bar automatically in destructor.</remarks>
	DialogCompletionBar (bool autoClose = AutoClose) : CompletionBar (autoClose) {}
	///	<summary>
	///	Return a pointer to a new Completion Bar dialog.
	///	</summary>
	MSDialogP GetDialog (WCharCP message) override
	{
		return mdlDialog_completionBarOpen  (message);
	}
};
///	<summary>
///	StatusCompletionBar class shows a Completion Bar in MicroStation's status panel, usually lower-right in MicroStation's window.
///	</summary>
struct StatusCompletionBar : CompletionBar
{
	///	<summary>
	///	Constructor calls the base class constructor.
	///	</summary>
	///	<remarks>Defaults to closing Completion Bar automatically in destructor.</remarks>
	StatusCompletionBar (bool autoClose = AutoClose) : CompletionBar (autoClose) {}
	///	<summary>
	///	Get MicroStation's Command Status dialog.
	///	</summary>
	MSDialogP GetDialog (WCharCP unused) override
	{
		return mdlDialog_find (DIALOGID_CommandStatus, nullptr);
	}
};

#endif	//	!defined (PROGRESS_BAR_H_INCLUDED_)
