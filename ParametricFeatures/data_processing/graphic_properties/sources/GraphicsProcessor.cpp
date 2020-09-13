#include "../headers/GraphicsProcessor.h"

GraphicsProcessor::GraphicsProcessor()	
{
	filePath = SessionManager::getInstance()->getDataOutputFilePath();

	WString myString;
	myString.Sprintf(L"Starting Processig the Graphics Component...");
	mdlOutput_messageCenter(DgnPlatform::OutputMessagePriority::Debug, myString.c_str(), myString.c_str(), DgnPlatform::OutputMessageAlert::None);

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
BentleyStatus GraphicsProcessor::_ProcessTextString(TextStringCR text) { return SUCCESS; } // Don't export glyph geometry...

//! Collect output as a single curve component.
//! @param[in] curve The curve data.
//! @param[in] isClosed The data is from a closed path or region instead of a physically closed path.
//! @param[in] isFilled A closed path or region should have opaque fill.
//! @remarks All curve geometry can be handled through _ProcessCurveVector.
//! @see _ProcessCurveVector.
BentleyStatus GraphicsProcessor::_ProcessCurvePrimitive(ICurvePrimitiveCR curve, bool isClosed, bool isFilled){	return ERROR; }

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
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	mGraphicsProcessorHelper.processShapesCurvesVector(curves, isFilled);
		
	return SUCCESS;
}
#pragma warning( pop ) 


//! Collect output as a bspline surface.
//! @param[in] surface The bspline surface data.
//! @return SUCCESS if handled, return ERROR to output according to _ProcessBody, _ProcessFacets, and _ProcessCurveVector rules.
BentleyStatus GraphicsProcessor::_ProcessSurface(MSBsplineSurfaceCR surface)
{	
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	//TODO[SB] return ERROR _ProcessSurface
	return ERROR;

	mGraphicsProcessorHelper.processMSBsplineSurface(surface);

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
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	//TODO[SB] MESH PROCESSIG NOT ACTIVE
	bool meshProcessing = false;
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
	mGraphicsProcessorHelper.processPolyfaceFacets(meshData, isFilled, m_currentTransform);

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
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	mGraphicsProcessorHelper.processSolidPrimitives(primitive);

	return SUCCESS;
}

void GraphicsProcessor::_AnnounceElemDisplayParams(ElemDisplayParamsCR displayParams)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);


	//ElemDisplayParamsCR d = displayParams;
	//ElemDisplayParamsCP d = &displayParams;

	this->mGraphicsProcessorHelper.getElementBundle()->setColor(displayParams.GetLineColorTBGR());
	this->mGraphicsProcessorHelper.getElementBundle()->setTransparency(displayParams.GetTransparency());

	//string filepath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	string filepath = SessionManager::getInstance()->getDataOutputFilePath();
	ofstream outfile;
	outfile.open(filePath, ios_base::app);

	UInt32 color;

	color = displayParams.GetLineColorTBGR();
	int blue1 = (color >> 16) & 0xFF;
	int green1 = (color >> 8) & 0xFF;
	int red1 = color & 0xFF;

	outfile << "RGB1 =" << red1 << "," << green1 << "," << blue1 << endl;

	//outfile.close();


	outfile << "transparency =" << displayParams.GetTransparency() << endl;

	auto level = displayParams.GetLevel();

	auto model = ISessionMgr::GetActiveDgnModelRefP();
	UInt colorOut;
	bool ov;
	mdlLevel_getColor(&colorOut, &ov, model, level);
	outfile << "level " << level << " , " << &colorOut << endl;
	outfile << "level color"<< colorOut<<" , "<<& colorOut << endl;

		int blue3 = (colorOut >> 16) & 0xFF;
		int green3 = (colorOut >> 8) & 0xFF;
		int red3 = colorOut & 0xFF;

		outfile << "colorOut RGB =" << red3 << "," << green3 << "," << blue3 << endl;

	outfile << "level  =" << displayParams.GetLevel() << endl;
	//displayParams.GetMaterial()->

	//if (!displayParams.IsLineColorTBGR()) {
	//	color = displayParams.GetLineColorTBGR();
	//	int blue3 = (color >> 16) & 0xFF;
	//	int green3 = (color >> 8) & 0xFF;
	//	int red3 = color & 0xFF;

	//	outfile << "RGB3 =" << red3 << "," << green3 << "," << blue3 << endl;
	//}
	//else {
	//	color = displayParams.GetLineColor();
	//	auto rez = ISessionMgr::GetActiveDgnFile()->GetColorMapP();

	//	auto colorDefinition = rez->GetColor(color);
	//	auto rgbColorDefinition = colorDefinition.m_rgb;
	//	int blue2 = rgbColorDefinition.blue & 0xFF;
	//	int green2 = rgbColorDefinition.green & 0xFF;
	//	int red2 = rgbColorDefinition.red & 0xFF;

	//	outfile << "RGB2 =" << red2 << "," << green2 << "," << blue2 << endl;
	//}
	outfile.close();
}

void GraphicsProcessor::_AnnounceTransform(TransformCP trans)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	if (trans) {
		m_currentTransform = *trans;

	}
	else {
		m_currentTransform.InitIdentity();

	}
}

