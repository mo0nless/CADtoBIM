#pragma once

#include "../enhancer/headers/GraphicsProcessorEnhancer.h"

/// @addtogroup ElementProperties
/// @beginGroup

/*=================================================================================**//**
* Class for collecting graphical output of an element's Draw method.
* This class inherits and implement the Bentley IElementGraphicsProcessor Interface
* @see ElementGraphicsOutput
* @bsiclass                                                     
+===============+===============+===============+===============+===============+======*/
class GraphicsProcessor : public IElementGraphicsProcessor
{
public:
	//! Default constructor of the class
	//! @remark This class inherits and implement the Bentley IElementGraphicsProcessor Interface
	GraphicsProcessor();
	GraphicsProcessorEnhancer* getGraphicsProcessorEnhancer();
private:

	virtual BentleyStatus _ProcessTextString(TextStringCR text) override;
	virtual BentleyStatus _ProcessCurvePrimitive(ICurvePrimitiveCR curve, bool isClosed, bool isFilled) override;
	virtual BentleyStatus _ProcessCurveVector(CurveVectorCR curves, bool isFilled) override;
	virtual bool _ProcessAsFacets(bool isPolyface) const override;
	virtual bool _ProcessAsBody(bool isCurved) const override;
	virtual BentleyStatus _ProcessSurface(MSBsplineSurfaceCR surface) override;
	virtual BentleyStatus _ProcessBody(ISolidKernelEntityCR entity, IFaceMaterialAttachmentsCP attachments) override;
	virtual BentleyStatus _ProcessFacets(PolyfaceQueryCR meshData, bool isFilled) override;
	virtual BentleyStatus _ProcessSolidPrimitive(ISolidPrimitiveCR primitive) override;

	virtual void _AnnounceElemDisplayParams(ElemDisplayParamsCR displayParams) override;
	
	//! Supply the current context that is processing the geometry.
	//! @param[in] context The current view context.
	//virtual void _AnnounceContext(ViewContextR context)  override;

	//! Supply the current transform that subsequent geometry is displayed through.
	//! @param[in] trans The transform to apply to subsequent process calls.
	virtual void _AnnounceTransform(TransformCP trans)  override;


	
	std::string filePath;

	GraphicsProcessorEnhancer mGraphicsProcessorEnhancer;
	Transform m_currentTransform;

	SolidLocationDetail mSolidDetails;
};
/// @endGroup
