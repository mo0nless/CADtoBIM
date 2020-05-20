#pragma once

#include "../enhancer/headers/GraphicsProcessorEnhancer.h"

class GraphicElementTool: public ElementGraphicsTool
{
public:
	GraphicElementTool();

private:
	//! Whether to collect open curves.
	virtual bool _CollectCurves() override;

	//! Whether to collect closed curves, regions, surfaces, and open meshes.
	virtual bool _CollectSurfaces() override;

	//! Whether to collect solids and closed meshes.
	virtual bool _CollectSolids() override;

	//! Whether to collect text as bounding shapes.
	virtual bool _CollectTextBoundaries() override;

	//! Whether to collect geometry output from component elements. (ex. geometry from normal cells)
	virtual bool _CollectComplexComponents() override;

	//! Allow tools to override the default draw purpose supplied to the geometry collector...
	virtual DrawPurpose _GetCollectDrawPurpose() override;

	//! Collect element graphics for this element. Allows sub-classes to override the default processor implementation.
	virtual void _DoCollectElementGraphics(ElementHandleCR eh) override;

	//! Geometry collector callback for brep entities. Return SUCCESS to ignore this geometry.
	virtual BentleyStatus _OnProcessSolidKernelEntity(ISolidKernelEntityPtr& geomPtr, DisplayPathCR path) override;

	//! Geometry collector callback for primitive solids and surfaces. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet or solid brep.
	virtual BentleyStatus _OnProcessSolidPrimitive(ISolidPrimitivePtr& geomPtr, DisplayPathCR path) override;

	//! Geometry collector callback for bspline surfaces. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet brep.
	virtual BentleyStatus _OnProcessBsplineSurface(MSBsplineSurfacePtr& geomPtr, DisplayPathCR path) override;

	//! Geometry collector callback for meshes. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet or solid brep. NOTE: Avoid converting very large meshes into breps!
	virtual BentleyStatus _OnProcessPolyface(PolyfaceHeaderPtr& geomPtr, DisplayPathCR path) override;

	//! Geometry collector callback for open/closed curves and regions. Return SUCCESS to ignore this geometry. Return ERROR to process as a wire or sheet brep.
	virtual BentleyStatus _OnProcessCurveVector(CurveVectorPtr& geomPtr, DisplayPathCR path) override;

};
