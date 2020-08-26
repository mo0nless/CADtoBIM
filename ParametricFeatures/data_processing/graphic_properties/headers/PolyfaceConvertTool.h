/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/Elements/Polyfacetool/PolyfaceConvertTool.cpp $
|
|  $Copyright: (c) 2017 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
//#include "../../stdafx.h"
#include "..\include\dgnplatform\MeshHeaderHandler.h"
#include "..\include\DgnPlatform\ElementGraphics.h"
//#include "..\include\DgnView\LocateSubEntityTool.h"

USING_NAMESPACE_BENTLEY_DGNPLATFORM;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM;
//USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT;

/*=================================================================================**/ /**
* Example showing how to use IElementGraphicsProcessor.
*
* @bsiclass                                                               Bentley Systems
+===============+===============+===============+===============+===============+======*/
struct MeshProcessor : public IElementGraphicsProcessor
{
	bvector<PolyfaceHeaderPtr> &m_output;
	IFacetOptionsP m_options;
	Transform m_currentTransform;

	/*---------------------------------------------------------------------------------**/ /**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	MeshProcessor(bvector<PolyfaceHeaderPtr> &output, IFacetOptionsP options)
		: m_output(output), m_options(options)
	{
	}

	/*---------------------------------------------------------------------------------**/ /**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	virtual IFacetOptionsP _GetFacetOptionsP()
	{
		return m_options;
	}
	/*---------------------------------------------------------------------------------**/ /**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	virtual bool _ProcessAsFacets(bool isPolyface) const override
	{
		return true;
	}
	/*---------------------------------------------------------------------------------**/ /**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	virtual bool _ProcessAsBody(bool isCurved) const
	{
		return false;
	}
	/*---------------------------------------------------------------------------------**/ /**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	virtual void _AnnounceTransform(TransformCP trans) override
	{
		if (trans)
			m_currentTransform = *trans;
		else
			m_currentTransform.InitIdentity();
	}

	/*---------------------------------------------------------------------------------**/ /**
	* @bsimethod                                                              Bentley Systems
	+---------------+---------------+---------------+---------------+---------------+------*/
	virtual BentleyStatus _ProcessFacets(PolyfaceQueryCR facets, bool isFilled = false) override
	{
		PolyfaceHeaderPtr header = PolyfaceHeader::CreateVariableSizeIndexed();
		header->CopyFrom(facets);
		header->Transform(m_currentTransform);
		m_output.push_back(header);
		return SUCCESS;
	}
};

#if false
/*---------------------------------------------------------------------------------**/ /**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
bool ElementToApproximateFacets(ElementHandleCR source,
	bvector<PolyfaceHeaderPtr> &output,
	IFacetOptionsP options)
{
	output.clear();
	MeshProcessor dest(output, options);
	ElementGraphicsOutput::Process(source, dest);
	return output.size() > 0 ? true : false;
}

/*=================================================================================**/ /**
* Example showing how to convert an existing element to a mesh.
*
* Demonstrates using the RedrawElems class for element dynamics.
*
* @bsiclass                                                               Bentley Systems
+===============+===============+===============+===============+===============+======*/
struct PolyfaceConvertTool : ElementGraphicsTool
{
//	DEFINE_T_SUPER(ElementGraphicsTool)
//protected:
//	PolyfaceConvertTool(int toolId) { SetCmdName(toolId, 0); }
//
//	virtual bool _SetupForModify(DgnButtonEventCR, bool isDynamics) override;
//	virtual StatusInt _OnElementModify(EditElementHandleR) override; // pure virtual method, sub-class must override!
//	virtual void _OnPostInstall() override;
//	virtual void _OnRestartTool() override { InstallNewInstance(GetToolId()); }
//	virtual bool _NeedAcceptPoint() override { return true; }
//	virtual bool _WantDynamics() override { return false; }
//	virtual bool _OnPostLocate(HitPathCP path, WStringR cantAcceptReason) override;
//	virtual bool _CollectCurves() override { return false; }
//	virtual bool _CollectSurfaces() override { return true; }
//	virtual bool _CollectSolids() override { return true; }
protected:
	bool CreateElement(ElementAgendaR agenda, EditElementHandleCR sourceEh);
	void SetupAndPromptForNextAction();
	bool IsValidForOperation(ElementHandleCR eh, size_t index);

public:
	static void InstallNewInstance(int toolId);

}; // PolyfaceConvertTool

/*---------------------------------------------------------------------------------**/ /**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
bool PolyfaceConvertTool::CreateElement(ElementAgendaR agenda, EditElementHandleCR sourceEh)
{
	IFacetOptionsPtr facetOptions = IFacetOptions::New();
	//Set different parameters for facet.
	facetOptions->SetIgnoreFaceMaterialAttachments(true); // Don't separate multi-symbology BReps by face symbology...
	facetOptions->SetChordTolerance(0.0);                 //many different parameters to control the final result mesh
	facetOptions->SetAngleTolerance(0.0);
	facetOptions->SetMaxEdgeLength(0.0);
	facetOptions->SetMaxFacetWidth(0.0);
	facetOptions->SetNormalsRequired(false);
	facetOptions->SetParamsRequired(false);
	facetOptions->SetMaxPerFace(4);
	facetOptions->SetCurvedSurfaceMaxPerFace(4);
	facetOptions->SetEdgeHiding(true);
	facetOptions->SetSmoothTriangleFlowRequired(true);

	bvector<PolyfaceHeaderPtr> meshes;
	if (true == ElementToApproximateFacets(sourceEh, meshes, facetOptions.get()))
	{
		EditElementHandle tmpEeh;

		for (size_t i = 0; i < meshes.size(); i++)
		{
			if (SUCCESS == MeshHeaderHandler::CreateMeshElement(tmpEeh, NULL, *meshes[i], true, *sourceEh.GetModelRef()))
			{
				agenda.Insert(tmpEeh);
			}
		}
	}

	return true;
}

/*---------------------------------------------------------------------------------**/ /**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
bool PolyfaceConvertTool::IsValidForOperation(ElementHandleCR eh, size_t index)
{
	bvector<IElementGraphicsPtr> geomCache;
	PolyfaceHeaderPtr polyface;

	if (SUCCESS != GetElementGraphicsCache(eh, geomCache) || 1 != geomCache.size())
		return false;

	if ((polyface = TryGetAsPolyface(geomCache.front())).IsValid()) //do not accept polyface
		return false;

	if (IsGeometrySolid(geomCache.front()) || IsGeometrySheet(geomCache.front())) //accept all solid & surface
		return true;

	return false;
}


/*---------------------------------------------------------------------------------**/ /**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
void PolyfaceConvertTool::SetupAndPromptForNextAction()
{
	WString msgStr;
	UInt32 msgId;
	size_t size = GetElementAgenda().GetCount();
	if (size == 0)
		msgId = PROMPT_SelectElement;
	else if (size == 1)
		msgId = PROMPT_NextPoint;

	RmgrResource::LoadWString(msgStr, (RscFileHandle)0, STRINGLISTID_Prompts, msgId, GetMdlDesc());
	NotificationManager::OutputPrompt(msgStr.c_str());
}


/*---------------------------------------------------------------------------------**/ /**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
bool PolyfaceConvertTool::_OnPostLocate(HitPathCP path, WStringR cantAcceptReason)
{
	if (path && !IsValidForOperation(ElementHandle(path->GetHeadElem(), path->GetRoot()), GetElementAgenda().size()))
		return false;

	return T_Super::_OnPostLocate(path, cantAcceptReason);
}
/*---------------------------------------------------------------------------------**/ /**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
StatusInt PolyfaceConvertTool::_OnElementModify(EditElementHandleR sourceEh)
{
	ElementAgenda agenda;
	if (CreateElement(agenda, sourceEh))
	{
		size_t count = agenda.GetCount();
		EditElementHandleP firstP = agenda.GetFirstP();
		sourceEh.ReplaceElementDescr(firstP->ExtractElementDescr());
		for (size_t i = 1; i < count; i++)
		{
			firstP++;
			firstP->AddToModel();
		}
		return SUCCESS;
	}
	return ERROR;
}
/*---------------------------------------------------------------------------------**/ /**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
bool PolyfaceConvertTool::_SetupForModify(DgnButtonEventCR, bool isDynamics)
{
	return true;
}
/*---------------------------------------------------------------------------------**/ /**
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
void PolyfaceConvertTool::_OnPostInstall()
{
	AccuSnap::GetInstance().EnableSnap(true); // Enable snapping for create tools.

	__super::_OnPostInstall();
}

/*---------------------------------------------------------------------------------**/ /**
* Method to create and install a new instance of the tool. If InstallTool returns ERROR,
* the new tool instance will be freed/invalid. Never call delete on RefCounted classes.
*
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
void PolyfaceConvertTool::InstallNewInstance(int toolId)
{
	PolyfaceConvertTool *tool = new PolyfaceConvertTool(toolId);

	tool->InstallTool();
}

/*---------------------------------------------------------------------------------**/ /**
* Function that was associated with the command number for starting the tool.
*
* @param[in] unparsed Additional input supplied after command string.
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/
Public void startPolyfaceConvertTool(WCharCP unparsed)
{
	// NOTE: Call the method to create/install the tool, RefCounted classes don't have public constructors...
	PolyfaceConvertTool::InstallNewInstance(CMDNAME_ConvertToPolyfaceTool);
}
#endif