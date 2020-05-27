#include "../headers/GraphicElementTool.h"


GraphicElementTool::GraphicElementTool()
{
}

//! Whether to collect open curves.
bool GraphicElementTool::_CollectCurves() { return true; }

//! Whether to collect closed curves, regions, surfaces, and open meshes.
bool GraphicElementTool::_CollectSurfaces() { return true; }

//! Whether to collect solids and closed meshes.
bool GraphicElementTool::_CollectSolids() { return true; }

//! Whether to collect text as bounding shapes.
bool GraphicElementTool::_CollectTextBoundaries() { return false; }

//! Whether to collect geometry output from component elements. (ex. geometry from normal cells)
bool GraphicElementTool::_CollectComplexComponents() { return ComponentMode::None != _GetComponentMode(); }

//! Allow tools to override the default draw purpose supplied to the geometry collector...
DrawPurpose GraphicElementTool::_GetCollectDrawPurpose() { return DrawPurpose::CaptureGeometry; }

//! Collect element graphics for this element. Allows sub-classes to override the default processor implementation.
void GraphicElementTool::_DoCollectElementGraphics(ElementHandleCR eh){}

//! Geometry collector callback for brep entities. Return SUCCESS to ignore this geometry.
BentleyStatus GraphicElementTool::_OnProcessSolidKernelEntity(ISolidKernelEntityPtr& geomPtr, DisplayPathCR path)
{
	return ERROR;
}

//! Geometry collector callback for primitive solids and surfaces. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet or solid brep.
BentleyStatus GraphicElementTool::_OnProcessSolidPrimitive(ISolidPrimitivePtr& geomPtr, DisplayPathCR path)
{
	return ERROR;
}

//! Geometry collector callback for bspline surfaces. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet brep.
BentleyStatus GraphicElementTool::_OnProcessBsplineSurface(MSBsplineSurfacePtr& geomPtr, DisplayPathCR path)
{
	return ERROR;
}

//! Geometry collector callback for meshes. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet or solid brep. NOTE: Avoid converting very large meshes into breps!
BentleyStatus GraphicElementTool::_OnProcessPolyface(PolyfaceHeaderPtr& geomPtr, DisplayPathCR path)
{
	return ERROR;
}

//! Geometry collector callback for open/closed curves and regions. Return SUCCESS to ignore this geometry. Return ERROR to process as a wire or sheet brep.
BentleyStatus GraphicElementTool::_OnProcessCurveVector(CurveVectorPtr& geomPtr, DisplayPathCR path)
{
	return ERROR;
}
