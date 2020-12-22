#include "../headers/GraphicsProcessor.h"

GraphicsProcessor::GraphicsProcessor()	
{
	/*WString myString;
	myString.Sprintf(L"Starting Processig the Graphics Component...");
	mdlOutput_messageCenter(DgnPlatform::OutputMessagePriority::Debug, myString.c_str(), myString.c_str(), DgnPlatform::OutputMessageAlert::None);*/

	this->mGraphicsProcessorHelper = GraphicsProcessorHelper();
}

GraphicsProcessorHelper* GraphicsProcessor::getGraphicsProcessorHelper()
{
	return &this->mGraphicsProcessorHelper;
}


//! Process surfaces and solids not handled directly or are clipped through _ProcessFaceta.
//! @param[in] isPolyface facets are from a call to DrawPolyface, ex. mesh element.
//! @return true to output facets for surface and solid geometry. If returning false,
//! edge and face isoline curves will be output through _ProcessCurveVector.
//! @remarks When both _ProcessAsFacets and _ProcessAsBody return true, _ProcessAsBody has precedence.
//! @note When returning true you also need to implement _ProcessFacets.
bool GraphicsProcessor::_ProcessAsFacets(bool isPolyface) const { return true; }

//! Process surfaces and solids not handled directly or are clipped through _ProcessBody.
//! @param[in] isCurved Graphics output would contain non-linear edge and/or non-planar face geometry.
//! @return true to output solid kernel entities for surface and solid geometry. If returning false,
//! facets will be output if _ProcessAsFacets returns true, otherwise edge and face isoline curves will
//! be output through _ProcessCurveVector.
//! @remarks Requires host implementation of SolidsKernelAdmin methods that take or return a ISolidKernelEntity.
//! @note When returning true you also need to implement _ProcessBody.
//! @see DgnPlatformLib::Host::SolidsKernelAdmin
bool GraphicsProcessor::_ProcessAsBody(bool isCurved) const { return true; }

//! Collect output as text.
//! @param[in] text The text data.
//! @return SUCCESS if handled, ERROR to output glyph graphics through _ProcessCurveVector.
BentleyStatus GraphicsProcessor::_ProcessTextString(TextStringCR text) { 

	_logger->logDebug(__FILE__, __LINE__, __func__);

	if (!mGraphicsProcessorHelper.processTextString(text))
	{
		WString myString;
		myString.Sprintf(L"_ProcessTextString");

		_logger->logWarning(__FILE__, __LINE__, __func__, "!- TextString not processed through Graphic Processor -!");

		NotificationMessage::send(
			mGraphicsProcessorHelper.getCurrentElementHandle(),
			myString,
			OutputMessagePriority::Warning
		);

		return ERROR;
	}

	return SUCCESS;
} // Don't export glyph geometry...

//! Collect output as a single curve component.
//! @param[in] curve The curve data.
//! @param[in] isClosed The data is from a closed path or region instead of a physically closed path.
//! @param[in] isFilled A closed path or region should have opaque fill.
//! @remarks All curve geometry can be handled through _ProcessCurveVector.
//! @see _ProcessCurveVector.
BentleyStatus GraphicsProcessor::_ProcessCurvePrimitive(ICurvePrimitiveCR curve, bool isClosed, bool isFilled){
	return ERROR; 
}

//! Collect output as a CurveVector.
//! @param[in] curves The curve data.
//! @param[in] isFilled A closed path or region should have opaque fill.
//! @return SUCCESS if handled, ERROR to output individual curves through _ProcessCurvePrimitive.
#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
BentleyStatus GraphicsProcessor::_ProcessCurveVector(CurveVectorCR curves, bool isFilled)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	if(!mGraphicsProcessorHelper.processShapesCurvesVector(curves, isFilled))
	{
		WString myString;
		myString.Sprintf(L"_ProcessCurveVector");

		_logger->logWarning(__FILE__, __LINE__, __func__, "!- Curve Vector not processed through Graphic Processor -!");

		NotificationMessage::send(
			mGraphicsProcessorHelper.getCurrentElementHandle(),
			myString,
			OutputMessagePriority::Warning
		);

		return ERROR;
	}
		
	return SUCCESS;
}
#pragma warning( pop ) 


//! Collect output as a bspline surface.
//! @param[in] surface The bspline surface data.
//! @return SUCCESS if handled, return ERROR to output according to _ProcessBody, _ProcessFacets, and _ProcessCurveVector rules.
BentleyStatus GraphicsProcessor::_ProcessSurface(MSBsplineSurfaceCR surface)
{	
	_logger->logDebug(__FILE__, __LINE__, __func__);

	//TODO[SB] return ERROR _ProcessSurface
	_logger->logWarning(__FILE__, __LINE__, __func__, "!- Surface not processed through Graphic Processor -!");
	return ERROR;

	if(!mGraphicsProcessorHelper.processMSBsplineSurface(surface))
	{
		WString myString;
		myString.Sprintf(L"_ProcessSurface");

		_logger->logWarning(__FILE__, __LINE__, __func__, "!- Surface not processed through Graphic Processor -!");

		NotificationMessage::send(
			mGraphicsProcessorHelper.getCurrentElementHandle(),
			myString,
			OutputMessagePriority::Warning
		);

		return ERROR;
	}

	//return SUCCESS;
}

//! Collect output for surfaces and solids using a solid kernel entity.
//! @param[in] entity The solid kernel entity.
//! @param[in] attachments Optional face color/material attachment information.
//! @note Requires host implementation of SolidsKernelAdmin methods that take or return a ISolidKernelEntity.
//! @remarks Only called if _ProcessAsBody returns true.
//! @return SUCCESS if handled.
#pragma warning( push )
#pragma warning( disable : 4267)
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning( disable : 4101)
BentleyStatus GraphicsProcessor::_ProcessBody(ISolidKernelEntityCR entity, IFaceMaterialAttachmentsCP attachments) 
{	
	_logger->logDebug(__FILE__, __LINE__, __func__);

	//TODO[SB] MESH PROCESSIG NOT ACTIVE
	bool meshProcessing = true;
	if(meshProcessing)
		_logger->logInfo(__FILE__, __LINE__, __func__, "!- Triangulated Mesh Graphic Processor -!");

	mGraphicsProcessorHelper.processBodySolid(entity, meshProcessing);

	return SUCCESS;
}

//! Collect output for surfaces and solids as facets.
//! @param[in] meshData The indexed polyface data.
//! @param[in] isFilled The wireframe display of the mesh has opaque fill.
//! @remarks Only called if _ProcessAsFacets returns true.
//! @return SUCCESS if handled.
BentleyStatus GraphicsProcessor::_ProcessFacets(PolyfaceQueryCR meshData, bool isFilled) 
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	if (!mGraphicsProcessorHelper.processPolyfaceFacets(meshData, isFilled, m_currentTransform))
	{
		WString myString;
		myString.Sprintf(L"_ProcessFacets");

		_logger->logWarning(__FILE__, __LINE__, __func__, "!- Polyface not processed through Graphic Processor -!");

		NotificationMessage::send(
			mGraphicsProcessorHelper.getCurrentElementHandle(),
			myString,
			OutputMessagePriority::Warning
		);

		return ERROR;
	}

	return SUCCESS;
}

//! Collect output as a solid primitive.
//! @param[in] primitive The solid primitive data.
//! @return SUCCESS if handled, return ERROR to output according to _ProcessBody, _ProcessFacets, and _ProcessCurveVector rules.
#pragma warning( push )
#pragma warning( disable : 4267)
#pragma warning( disable : 4700)
BentleyStatus GraphicsProcessor::_ProcessSolidPrimitive(ISolidPrimitiveCR primitive)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	if (!mGraphicsProcessorHelper.processSolidPrimitive(primitive))
	{
		WString myString;
		myString.Sprintf(L"_ProcessSolidPrimitive");

		_logger->logWarning(__FILE__, __LINE__, __func__, "!- primitive not processed through Graphic Processor -!");
		
		NotificationMessage::send(
			mGraphicsProcessorHelper.getCurrentElementHandle(),
			myString,
			OutputMessagePriority::Warning
		);

		return ERROR;
	}


	return SUCCESS;
}

void GraphicsProcessor::_AnnounceElemDisplayParams(ElemDisplayParamsCR displayParams)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);
	
	UInt32 lineColor, fillColor;
	IntColorDef fillColorDef, lineColorDef;
	WString message;

	DgnColorMapP colorMap = ISessionMgr::GetActiveDgnFile()->GetColorMapP();
	
	if (!displayParams.IsFillColorTBGR())
	{
		fillColor = displayParams.GetFillColorTBGR();
		fillColorDef = colorMap->GetColor(fillColor);

		message.Sprintf(L"Successfull Fill Color TBGR: -- R: %f G: %f B: %f A: %f", fillColorDef.m_rgba.red, fillColorDef.m_rgba.green, fillColorDef.m_rgba.blue);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));

		int blue = (fillColor >> 16) & 0xFF;
		int green = (fillColor >> 8) & 0xFF;
		int red = fillColor & 0xFF;

		message.Sprintf(L"Calculated: -- R: %f G: %f B: %f A: %f", red, green, blue);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));
	}
	else
	{
		fillColor = displayParams.GetFillColor();
		fillColorDef = colorMap->GetColor(fillColor);

		message.Sprintf(L"Successfull Fill Color: -- R: %f G: %f B: %f A: %f", fillColorDef.m_rgba.red, fillColorDef.m_rgba.green, fillColorDef.m_rgba.blue);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));

		int blue = (fillColor >> 16) & 0xFF;
		int green = (fillColor >> 8) & 0xFF;
		int red = fillColor & 0xFF;

		message.Sprintf(L"Calculated: -- R: %f G: %f B: %f A: %f", red, green, blue);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));
	}

	if (!displayParams.IsLineColorTBGR())
	{
		lineColor = displayParams.GetLineColorTBGR();
		lineColorDef = colorMap->GetColor(fillColor);

		message.Sprintf(L"Successfull Line Color TBGR: -- R: %f G: %f B: %f A: %f", lineColorDef.m_rgba.red, lineColorDef.m_rgba.green, lineColorDef.m_rgba.blue, lineColorDef.m_rgba.alpha);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));

		int blue = (lineColor >> 16) & 0xFF;
		int green = (lineColor >> 8) & 0xFF;
		int red = lineColor & 0xFF;

		message.Sprintf(L"Calculated: -- R: %f G: %f B: %f", red, green, blue);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));
	}
	else
	{
		lineColor = displayParams.GetLineColor();
		lineColorDef = colorMap->GetColor(fillColor);

		message.Sprintf(L"Successfull Line Color: -- R: %f G: %f B: %f A: %f", lineColorDef.m_rgba.red, lineColorDef.m_rgba.green, lineColorDef.m_rgba.blue, lineColorDef.m_rgba.alpha);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));

		int blue = (lineColor >> 16) & 0xFF;
		int green = (lineColor >> 8) & 0xFF;
		int red = lineColor & 0xFF;

		message.Sprintf(L"Calculated: -- R: %f G: %f B: %f", red, green, blue);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));
	}
	
	/*try
	{
		displayParams.GetElementClass();
		MaterialCP material = displayParams.GetMaterial();
		MaterialSettingsCR mSettings = material->GetSettings();
		RgbFactor rgbFactor;
		if (mSettings.HasBaseColor())
			rgbFactor = mSettings.GetBaseColor();

		WCharP matName;
		material->GetName(matName);

		this->mGraphicsProcessorHelper.getGraphicGeomBundle()->setMaterial(
			StringUtils::getNormalizedString(matName)
		);

		this->mGraphicsProcessorHelper.getGraphicGeomBundle()->setFillColor(rgbFactor);
		this->mGraphicsProcessorHelper.getGraphicGeomBundle()->setLineColor(lineColorDef);

		message.Sprintf(L"Successfull get Material: %s -- R: %f G: %f B: %f A: %f", matName, rgbFactor.red, rgbFactor.green, rgbFactor.blue);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));		
		
	}
	catch (exception& ex) {
		_logger->logError(__FILE__, __LINE__, __func__, ex, "Error Getting Material " + string(ex.what()));
	}*/
	
	// Since we have an elementRef from the DgnModel, we know that FileLevelCache is never NULL.
	FileLevelCache* fileLevelCache = ISessionMgr::GetActiveDgnModelRefP()->GetFileLevelCacheP();
	LevelHandle level = fileLevelCache->GetLevel(displayParams.GetLevel());

	if (level.IsValid())
	{
		UInt32 color = level.GetByLevelColor().GetColor();
		//this->mGraphicsProcessorHelper.getGraphicGeomBundle()->setColor(color);

		int blue = (color >> 16) & 0xFF;
		int green = (color >> 8) & 0xFF;
		int red = color & 0xFF;

		message.Sprintf(L"Level Color Valid Calculated: -- R: %f G: %f B: %f", red, green, blue);
		_logger->logDebug(__FILE__, __LINE__, __func__, StringUtils::getNormalizedString(message));
	}

	this->mGraphicsProcessorHelper.getIfcGraphicPropertiesBundle()->setColor(displayParams.GetLineColorTBGR());
	this->mGraphicsProcessorHelper.getIfcGraphicPropertiesBundle()->setTransparency(displayParams.GetTransparency());
	
}

void GraphicsProcessor::_AnnounceTransform(TransformCP trans)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	if (trans) {
		m_currentTransform = *trans;

	}
	else {
		m_currentTransform.InitIdentity();

	}
}

