#include "..\headers\IfcSurfaceEnhancer.h"

void IfcSurfaceEnhancer::enhance(IfcHierarchyHelper<Ifc4>& file, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties, IfcElementBundle*& ifcElementBundle,
	IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle, bool addToIfcElementBundle)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	if (msBsplineSurfaceGraphicProperties != nullptr) {
		Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildIfcSurface(*msBsplineSurfaceGraphicProperties, file, ifcGraphicPropertiesBundle);
		if (ifcRepresentationItem != nullptr)
		{
			ifcGraphicPropertiesBundle->setIfcRepresentationTypeIdentifier("AdvancedSurface", "Body");
			ifcGraphicPropertiesBundle->setIfcRepresentationItem(ifcRepresentationItem);
		}
		else {
			_logger->logWarning(__FILE__, __LINE__, __func__,"ifcRepresentationItem is NULL");
		}
	}
}

Ifc4::IfcBSplineSurface* IfcSurfaceEnhancer::buildIfcSurface(MSBsplineSurfaceGraphicProperties & msBsplineSurfaceGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle * ifcGraphicPropertiesBundle)
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
