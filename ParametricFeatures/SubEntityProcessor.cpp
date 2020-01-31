#include "headers\ParametricFeatures.h"

/*=================================================================================**//**
* Example showing how to use LocateSubEntityTool to write a tool to identify
* faces, edges, or vertices of a solid or surface. This tool doesn't modify the
* element and allows both locked elements and reference elements to be selected.
* Accepting locked/reference elements would be appropriate for a query tool like
* measure distance, area, volume.
*
* @bsiclass                                                               Bentley Systems
+===============+===============+===============+===============+===============+======*/
class  SubEntityProcessor : LocateSubEntityTool
{
public:
	SubEntityProcessor();
private:

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

};
