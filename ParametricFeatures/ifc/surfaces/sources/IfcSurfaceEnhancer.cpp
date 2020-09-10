#include "..\headers\IfcSurfaceEnhancer.h"

void IfcSurfaceEnhancer::enhance(IfcHierarchyHelper<Ifc4>& file, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties, IfcElementBundle*& ifcElementBundle,
	ElementBundle* elementBundle, bool addToIfcElementBundle)
{
	if (msBsplineSurfaceGraphicProperties != nullptr) {
		Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildIfcSurface(*msBsplineSurfaceGraphicProperties, file, elementBundle);
		if (ifcRepresentationItem != nullptr)
		{
			auto bundle = new IfcGraphicPropertiesBundle(elementBundle->getGraphicProperties(),
				ifcRepresentationItem, elementBundle->getElementHandle());
			bundle->setColor(elementBundle->getColor());
			bundle->setTransparency(elementBundle->getTransparency());
			bundle->setMaterial(elementBundle->getMaterial());
			ifcElementBundle->addIfcGraphicPropertiesBundle(bundle);
			//ifcTemplatedEntityList->push(ifcRepresentationItem);
		}
	}
}

Ifc4::IfcBSplineSurface* IfcSurfaceEnhancer::buildIfcSurface(MSBsplineSurfaceGraphicProperties & msBsplineSurfaceGraphicProperties, IfcHierarchyHelper<Ifc4>& file, ElementBundle * elementBundle)
{
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
