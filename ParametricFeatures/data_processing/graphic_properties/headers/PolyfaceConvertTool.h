/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/Elements/Polyfacetool/PolyfaceConvertTool.cpp $
|
|  $Copyright: (c) 2017 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
#include "..\include\dgnplatform\MeshHeaderHandler.h"
#include "..\include\DgnPlatform\ElementGraphics.h"

USING_NAMESPACE_BENTLEY_DGNPLATFORM;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM;

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