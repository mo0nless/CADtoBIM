#include "../headers/IfcCreateSolidsOperationBuilder.h"

Ifc4::IfcGeometricRepresentationItem* IfcCreateSolidsOperationBuilder::buildIfcCreateSolidsOperation(IfcElementBundle* leftIfcRepresentationItem, IfcElementBundle* rigthIfcRepresentationItem,
	IfcReaderPropertiesBundle& ifcReaderPropertiesBundle, IfcHierarchyHelper<Ifc4>& file)
{
	IfcElementBundle* ifcElementBundle = nullptr;
	if (leftIfcRepresentationItem != nullptr) {
		ifcElementBundle = leftIfcRepresentationItem;
	}
	else if (rigthIfcRepresentationItem != nullptr) {
		ifcElementBundle = rigthIfcRepresentationItem;
	}

	ShapesGraphicProperties* shapeGraphicProperties = dynamic_cast<ShapesGraphicProperties*>(ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getGraphicProperties());
	//ArcGraphicProperties* curveP = dynamic_cast<ArcGraphicProperties*>(shapeGraphicProperties->getCurvesPrimitivesContainerVector().at(0));
	//DVec3d zAxis = curveP->getDirectionZ();
	//DVec3d xAxis = curveP->getDirectionX();
	//DVec3d yAxis = curveP->getDirectionY();
	DVec3d zAxis = ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getGraphicProperties()->getVectorAxisZ();
	zAxis.Normalize();
	//zAxis.RotateXY(zAxis, 3.14);
	DVec3d xAxis = ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getGraphicProperties()->getVectorAxisX();
	//DVec3d yAxis = ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getGraphicProperties()->getVectorAxisY();
	xAxis.Normalize();
	//yAxis.Normalize();
	DVec3d centroid;
	centroid.Init(shapeGraphicProperties->getCentroid());
	//centroid.x = 0;
	//centroid.y = 0;
	//centroid.z = 0;

	//Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(NumberUtils::convertMicrometersToMetters(centroid.x),
	//	NumberUtils::convertMicrometersToMetters(centroid.y), NumberUtils::convertMicrometersToMetters(centroid.z)),
	//	file.addTriplet<Ifc4::IfcDirection>(0,0,1), file.addTriplet<Ifc4::IfcDirection>(1,0,0));

	//Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(
	//	file.addTriplet<Ifc4::IfcCartesianPoint>(0,0,0),
	//	file.addTriplet<Ifc4::IfcDirection>(zAxis.x, zAxis.y,zAxis.z),
	//	file.addTriplet<Ifc4::IfcDirection>(xAxis.x, xAxis.y, xAxis.z));

	//Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(
	//	file.addTriplet<Ifc4::IfcCartesianPoint>(NumberUtils::convertMicrometersToMetters(centroid.x),
	//	NumberUtils::convertMicrometersToMetters(centroid.y),
	//	NumberUtils::convertMicrometersToMetters(centroid.z)),
	//	new Ifc4::IfcDirection(vector<double>()),
	//	new Ifc4::IfcDirection(vector<double>()));


	Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(NumberUtils::convertCurrentUnitToMeters(centroid.x),
		NumberUtils::convertCurrentUnitToMeters(centroid.y), NumberUtils::convertCurrentUnitToMeters(centroid.z)),
		file.addTriplet<Ifc4::IfcDirection>(zAxis.x, zAxis.y,zAxis.z), file.addTriplet<Ifc4::IfcDirection>(xAxis.x, xAxis.y, xAxis.z));

	switch (CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getClassName()))
	{
	case CreateSolidFunctionsEnum::REVOLVE:
	{
		double sweepRadians = 0;
		for (auto const& modelerProperty : ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getProperties()) {
			if (modelerProperty->getPropertyName() == "Angle") {
				sweepRadians = modelerProperty->getPropertyValue().GetDouble();
			}
		}
		//Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));
		//Ifc4::IfcCircleProfileDef* profileDefinition = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement, 1);
		Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryClosedProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_CURVE, string("Revolve"),
			(Ifc4::IfcCurve*)ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem());
		//Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0,
		//	10), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

		//Ifc4::IfcCircleProfileDef* profileDef = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
		//	boost::none, localPlacement, 3);

		Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), new Ifc4::IfcDirection(vector<double>()));



		Ifc4::IfcGeometricRepresentationItem* result = new Ifc4::IfcRevolvedAreaSolid(profileDef, placement, localAxis1Placement, sweepRadians);
		return result;

	}

	case CreateSolidFunctionsEnum::EXTRUDE:
	{
		DPoint3d rangeLow, rangeHigh;

		double length = 0;
		for (auto const& modelerProperty : ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getProperties()) {
			if (modelerProperty->getPropertyName() == "Distance") {
				length = NumberUtils::convertCurrentUnitToMeters(modelerProperty->getPropertyValue().GetDouble());
			}
			if (modelerProperty->getPropertyName() == "Range Low") {
				rangeLow.x = modelerProperty->getPropertyValue().GetPoint3D().x;
				rangeLow.y = modelerProperty->getPropertyValue().GetPoint3D().y;
				rangeLow.z = modelerProperty->getPropertyValue().GetPoint3D().z;
			}
			if (modelerProperty->getPropertyName() == "Range High") {
				rangeHigh.x = modelerProperty->getPropertyValue().GetPoint3D().x;
				rangeHigh.y = modelerProperty->getPropertyValue().GetPoint3D().y;
				rangeHigh.z = modelerProperty->getPropertyValue().GetPoint3D().z;
			}
		}
		//Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0,
		//	10), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

		//Ifc4::IfcCircleProfileDef* profileDef = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
		//	boost::none, localPlacement,3);

		DVec3d vec;
		vec = vec.FromStartEndNormalize(rangeLow, rangeHigh);

		Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryClosedProfileDef(
			Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
			string("Extrude"),
			(Ifc4::IfcCurve*)ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem());
		
		Ifc4::IfcGeometricRepresentationItem* result =  new Ifc4::IfcExtrudedAreaSolid(profileDef,
			placement, file.addTriplet<Ifc4::IfcDirection>(zAxis.x, zAxis.y, zAxis.z), length);
		return result;

	}

	case CreateSolidFunctionsEnum::THICKEN:
	{
		double length = 0;
		DPoint3d rangeLow,rangeHigh;

		for (auto const& modelerProperty : ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getProperties()) {
			if (modelerProperty->getPropertyName() == "Thickness") {
				length = NumberUtils::convertCurrentUnitToMeters(modelerProperty->getPropertyValue().GetDouble());
			}
			if (modelerProperty->getPropertyName() == "Range Low") {
				rangeLow.x = modelerProperty->getPropertyValue().GetPoint3D().x;
				rangeLow.y = modelerProperty->getPropertyValue().GetPoint3D().y;
				rangeLow.z = modelerProperty->getPropertyValue().GetPoint3D().z;
			}
			if (modelerProperty->getPropertyName() == "Range High") {
				rangeHigh.x = modelerProperty->getPropertyValue().GetPoint3D().x;
				rangeHigh.y = modelerProperty->getPropertyValue().GetPoint3D().y;
				rangeHigh.z = modelerProperty->getPropertyValue().GetPoint3D().z;
			}
		}

		DVec3d vec;
		vec = vec.FromStartEndNormalize(rangeLow, rangeHigh);

		/*Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_CURVE, string("Thicken"), (Ifc4::IfcBoundedCurve*)ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem());*/

		//Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0,
		//	10), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

		Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryClosedProfileDef(
			Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, string("Thicken"),
			(Ifc4::IfcCurve*)ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem());

		//Ifc4::IfcCircleProfileDef* profileDef = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
		//	boost::none, localPlacement, 3);

		Ifc4::IfcGeometricRepresentationItem* result = new Ifc4::IfcExtrudedAreaSolid(profileDef, placement,
			file.addTriplet<Ifc4::IfcDirection>(zAxis.x, zAxis.y, zAxis.z), length);
		return result;

	}

	default:
		return nullptr;
	}

	
}
