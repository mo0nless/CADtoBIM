#include "../headers/GraphicElementTool.h"


GraphicElementTool::GraphicElementTool()
{
}

//! Whether to collect open curves.
void GraphicElementTool::_OnRestartTool() 
{ 
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;

	outfile.open(filePath, std::ios_base::app);
	outfile << " _OnRestartTool" << std::endl;

	outfile.close();
}

StatusInt GraphicElementTool::_OnElementModify(EditElementHandleR eeh)
{
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;

	outfile.open(filePath, std::ios_base::app);
	outfile << " _OnElementModify" << std::endl;

	outfile.close();
	return StatusInt();
}

//! Whether to collect open curves.
bool GraphicElementTool::_CollectCurves() { 
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;

	outfile.open(filePath, std::ios_base::app);
	outfile << " _CollectCurves" << std::endl;

	outfile.close();

	return true; 
}

//! Whether to collect closed curves, regions, surfaces, and open meshes.
bool GraphicElementTool::_CollectSurfaces() { 
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;

	outfile.open(filePath, std::ios_base::app);
	outfile << " _CollectSurfaces" << std::endl;

	outfile.close();

	return true; 
}

//! Whether to collect solids and closed meshes.
bool GraphicElementTool::_CollectSolids() { 
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;

	outfile.open(filePath, std::ios_base::app);
	outfile << " _CollectSolids" << std::endl;

	outfile.close();

	return true; 
}

//! Whether to collect text as bounding shapes.
bool GraphicElementTool::_CollectTextBoundaries() { 
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;

	outfile.open(filePath, std::ios_base::app);
	outfile << " _CollectTextBoundaries" << std::endl;

	outfile.close();
	return false; 
}

//! Whether to collect geometry output from component elements. (ex. geometry from normal cells)
bool GraphicElementTool::_CollectComplexComponents() { 
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;

	outfile.open(filePath, std::ios_base::app);
	outfile << " _CollectComplexComponents" << std::endl;

	outfile.close();

	//return ComponentMode::Innermost != _GetComponentMode(); 
	return true;
}

//! Allow tools to override the default draw purpose supplied to the geometry collector...
DrawPurpose GraphicElementTool::_GetCollectDrawPurpose() { return DrawPurpose::CaptureGeometry; }

//! Collect element graphics for this element. Allows sub-classes to override the default processor implementation.
void GraphicElementTool::_DoCollectElementGraphics(ElementHandleCR eh){

	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	outfile  << " _DoCollectElementGraphics" << std::endl;
	outfile << eh.GetElementId() << " --------" << std::endl;
	outfile << eh.GetElementDescrCP() << " --------" << std::endl;
	outfile.close();

	//ISolidPrimitive::

	//eh.getdi

	//_OnProcessSolidPrimitive(SolidHandler::ElementToSolidPrimitive(eh, true), NULL);
	//this->onpro

}

//! Geometry collector callback for brep entities. Return SUCCESS to ignore this geometry.
BentleyStatus GraphicElementTool::_OnProcessSolidKernelEntity(ISolidKernelEntityPtr& geomPtr, DisplayPathCR path)
{
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;

	outfile.open(filePath, std::ios_base::app);
	outfile << " _OnProcessSolidKernelEntity" << std::endl;
	outfile << path.GetHeadElem()->GetElementId() << " --------" << std::endl;
	outfile << path.GetChildElem()->GetElementId() << " --------" << std::endl;
	outfile << path.GetComponentElem()->GetElementId() << " --------" << std::endl;
	outfile << path.GetSharedChildElem()->GetElementId() << " --------" << std::endl;
	outfile << path.GetTailElem()->GetElementId() << " --------" << std::endl;
	outfile.close();
	return SUCCESS;
}

//! Geometry collector callback for primitive solids and surfaces. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet or solid brep.
BentleyStatus GraphicElementTool::_OnProcessSolidPrimitive(ISolidPrimitivePtr& geomPtr, DisplayPathCR path)
{


	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;	

	outfile.open(filePath, std::ios_base::app);
	outfile << " _OnProcessSolidPrimitive" << std::endl;
	outfile << path.GetHeadElem()->GetElementId() << " --------" << std::endl;
	outfile << path.GetChildElem()->GetElementId() << " --------" << std::endl;
	outfile << path.GetComponentElem()->GetElementId() << " --------" << std::endl;
	outfile << path.GetSharedChildElem()->GetElementId() << " --------" << std::endl;
	outfile << path.GetTailElem()->GetElementId() << " --------" << std::endl;
	outfile.close();

	return SUCCESS;
}

//! Geometry collector callback for bspline surfaces. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet brep.
BentleyStatus GraphicElementTool::_OnProcessBsplineSurface(MSBsplineSurfacePtr& geomPtr, DisplayPathCR path)
{
	return SUCCESS;
}

//! Geometry collector callback for meshes. Return SUCCESS to ignore this geometry. Return ERROR to process as a sheet or solid brep. NOTE: Avoid converting very large meshes into breps!
BentleyStatus GraphicElementTool::_OnProcessPolyface(PolyfaceHeaderPtr& geomPtr, DisplayPathCR path)
{
	return SUCCESS;
}

//! Geometry collector callback for open/closed curves and regions. Return SUCCESS to ignore this geometry. Return ERROR to process as a wire or sheet brep.
BentleyStatus GraphicElementTool::_OnProcessCurveVector(CurveVectorPtr& geomPtr, DisplayPathCR path)
{
	return SUCCESS;
}
