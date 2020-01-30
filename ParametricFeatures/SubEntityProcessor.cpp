#include "headers\ParametricFeatures.h"

USING_NAMESPACE_BENTLEY_DGNPLATFORM;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT;

/*=================================================================================**//**
* Example showing how to use LocateSubEntityTool to write a tool to identify
* faces, edges, or vertices of a solid or surface. This tool doesn't modify the
* element and allows both locked elements and reference elements to be selected.
* Accepting locked/reference elements would be appropriate for a query tool like
* measure distance, area, volume.
*
* @bsiclass                                                               Bentley Systems
+===============+===============+===============+===============+===============+======*/
struct          SubEntityProcessor : LocateSubEntityTool
{
protected:

	/*---------------------------------------------------------------------------------**//**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	SubEntityProcessor(int cmdName) 
	{ 
		SetCmdName(cmdName, 0); 
	}

	/*---------------------------------------------------------------------------------**//**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	virtual StatusInt _OnElementModify(EditElementHandleR eeh) override { return ERROR; } // Example doesn't modify elements...
	virtual StatusInt _OnPreElementModify(EditElementHandleR eeh) override { return ERROR; } // Example doesn't modify elements, don't copy styles, etc. from reference to active...
	virtual bool _IsModifyOriginal() override { return false; } // Allow sub-entity selection of elements in reference attachments...

	/*---------------------------------------------------------------------------------**//**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	virtual ISubEntity::SubEntityType _GetSubEntityTypeMask() override { return (ISubEntity::SubEntityType) (ISubEntity::SubEntityType_Face | ISubEntity::SubEntityType_Edge | ISubEntity::SubEntityType_Vertex); }
	virtual bool _RequireSubEntitySupport() override { return true; } // Only allow elements having the requested sub-entity to be selected...

	/*---------------------------------------------------------------------------------**//**
	* Install a new instance of the tool. Will be called in response to external events
	* such as undo or by the base class from _OnReinitialize when the tool needs to be
	* reset to it's initial state.
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	virtual void _OnRestartTool() override
	{
		InstallNewInstance(GetToolId());
	}

public:

	/*---------------------------------------------------------------------------------**//**
	* Method to create and install a new instance of the tool. If InstallTool returns ERROR,
	* the new tool instance will be freed/invalid. Never call delete on RefCounted classes.
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	static void InstallNewInstance(int toolId)
	{
		SubEntityProcessor* tool = new SubEntityProcessor(toolId);

		tool->InstallTool();
	}

}; // TestSubEntityTool

/*---------------------------------------------------------------------------------**//**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
Public void startExampleLocateSubEntityTool(WCharCP unparsed)
{
	// NOTE: Call the method to create/install the tool, RefCounted classes don't have public constructors...
	SubEntityProcessor::InstallNewInstance(3);//CMDNAME_ExampleSubEntityTool);
}
