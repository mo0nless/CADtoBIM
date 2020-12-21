#include "..\headers\IfcSurfaceEnhancer.h"

void IfcSurfaceEnhancer::enhance(IfcHierarchyHelper<Ifc4>& file, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties, IfcElementBundle*& ifcElementBundle,
	GraphicGeomBundle* elementBundle, bool addToIfcElementBundle)
{
	boost::unique_lock<boost::shared_mutex> guard(_mutex);
	_logger->logDebug(__FILE__, __LINE__, __func__);

	if (msBsplineSurfaceGraphicProperties != nullptr) {
		Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildIfcSurface(*msBsplineSurfaceGraphicProperties, file, elementBundle);
		if (ifcRepresentationItem != nullptr)
		{
			auto bundle = new IfcGraphicPropertiesBundle(elementBundle->getGraphicProperties(),
				ifcRepresentationItem, elementBundle->getElementHandle());
			bundle->setColor(elementBundle->getColor());
			bundle->setFillColor(elementBundle->getFillColor());
			bundle->setLineColor(elementBundle->getLineColor());
			bundle->setTransparency(elementBundle->getTransparency());
			bundle->setMaterial(elementBundle->getMaterial());
			bundle->setLevelHandle(elementBundle->getLevelHandle());
			bundle->setRepresentationTypeIdentifier("AdvancedSurface", "Body");
			ifcElementBundle->addIfcGraphicPropertiesBundle(bundle);
		}
		else {
			_logger->logWarning(__FILE__, __LINE__, __func__,"ifcRepresentationItem is NULL");
		}
	}
}

Ifc4::IfcBSplineSurface* IfcSurfaceEnhancer::buildIfcSurface(MSBsplineSurfaceGraphicProperties & msBsplineSurfaceGraphicProperties, IfcHierarchyHelper<Ifc4>& file, GraphicGeomBundle * elementBundle)
{
	
	_logger->logDebug(__FILE__, __LINE__, __func__);

	//Create IfcCartesianPoint List 
	IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>* tempCartesianPointList = new IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>();
	
	//Get the control point UV of the FACE surface
	vector<vector<DPoint3d>> controlPointsPatch = msBsplineSurfaceGraphicProperties.getControlPoints();
	for (auto vCP : controlPointsPatch)
	{
		vector<Ifc4::IfcCartesianPoint*> cartesianPointsUV;

		for (auto p : vCP)
		{
			Ifc4::IfcCartesianPoint * crtP = IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(p);
			cartesianPointsUV.push_back(crtP);
		}
		tempCartesianPointList->push(cartesianPointsUV);
	}

	//Collect all the UV IfcCartesianPoint for the surface
	boost::shared_ptr<IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>> controlPoints(tempCartesianPointList);

	Ifc4::IfcBSplineSurface* bSplineSurface = nullptr;

	if (msBsplineSurfaceGraphicProperties.hasValidKnots && msBsplineSurfaceGraphicProperties.hasValidWeights)
		bSplineSurface = new Ifc4::IfcRationalBSplineSurfaceWithKnots(
			msBsplineSurfaceGraphicProperties.getUDegree(),
			msBsplineSurfaceGraphicProperties.getVDegree(),
			controlPoints,
			Ifc4::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
			msBsplineSurfaceGraphicProperties.getUIsCLosed(),
			msBsplineSurfaceGraphicProperties.getVIsCLosed(),
			msBsplineSurfaceGraphicProperties.getIsSelfIntersect(),
			msBsplineSurfaceGraphicProperties.getUKnotsMultiplicity(),
			msBsplineSurfaceGraphicProperties.getVKnotsMultiplicity(),
			msBsplineSurfaceGraphicProperties.getUKnots(),
			msBsplineSurfaceGraphicProperties.getVKnots(),
			Ifc4::IfcKnotType::IfcKnotType_UNSPECIFIED,
			msBsplineSurfaceGraphicProperties.getWeights()
		);
	else if (msBsplineSurfaceGraphicProperties.hasValidKnots)
		bSplineSurface = new Ifc4::IfcRationalBSplineSurfaceWithKnots(
			msBsplineSurfaceGraphicProperties.getUDegree(),
			msBsplineSurfaceGraphicProperties.getVDegree(),
			controlPoints,
			Ifc4::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
			msBsplineSurfaceGraphicProperties.getUIsCLosed(),
			msBsplineSurfaceGraphicProperties.getVIsCLosed(),
			msBsplineSurfaceGraphicProperties.getIsSelfIntersect(),
			msBsplineSurfaceGraphicProperties.getUKnotsMultiplicity(),
			msBsplineSurfaceGraphicProperties.getVKnotsMultiplicity(),
			msBsplineSurfaceGraphicProperties.getUKnots(),
			msBsplineSurfaceGraphicProperties.getVKnots(),
			Ifc4::IfcKnotType::IfcKnotType_UNSPECIFIED,
			msBsplineSurfaceGraphicProperties.getWeights()
		);
	else
		bSplineSurface = new Ifc4::IfcBSplineSurface(
			msBsplineSurfaceGraphicProperties.getUDegree(),
			msBsplineSurfaceGraphicProperties.getVDegree(),
			controlPoints,
			Ifc4::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
			msBsplineSurfaceGraphicProperties.getUIsCLosed(),
			msBsplineSurfaceGraphicProperties.getVIsCLosed(),
			msBsplineSurfaceGraphicProperties.getIsSelfIntersect()
		);

	return bSplineSurface;
}
