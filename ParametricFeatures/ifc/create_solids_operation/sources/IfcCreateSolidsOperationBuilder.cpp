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
	ArcGraphicProperties* curveP = dynamic_cast<ArcGraphicProperties*>(shapeGraphicProperties->getCurvesPrimitivesContainerVector().at(0));
	DVec3d zAxis = curveP->getDirectionZ();
	DVec3d xAxis = curveP->getDirectionX();
	DVec3d yAxis = curveP->getDirectionY();
	/*DVec3d zAxis = ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getGraphicProperties()->getVectorAxisZ();
	DVec3d xAxis = ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getGraphicProperties()->getVectorAxisX();
	DVec3d yAxis = ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getGraphicProperties()->getVectorAxisY();*/
	DVec3d centroid;
	centroid.x = 0;
	centroid.y = 0;
	centroid.z = 0;

	Ifc4::IfcAxis2Placement3D* placement = new Ifc4::IfcAxis2Placement3D(file.addTriplet<Ifc4::IfcCartesianPoint>(NumberUtils::convertCurrentUnitToMeters(centroid.x),
		NumberUtils::convertCurrentUnitToMeters(centroid.y), NumberUtils::convertCurrentUnitToMeters(centroid.z)),
		file.addTriplet<Ifc4::IfcDirection>(zAxis.x, zAxis.y,zAxis.z), file.addTriplet<Ifc4::IfcDirection>(xAxis.x, xAxis.y, xAxis.z));

	switch (CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getCassName()))
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
		Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_CURVE, std::string("Revolve"),
			(Ifc4::IfcBoundedCurve*)ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem());
		Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1,0,0));



		Ifc4::IfcGeometricRepresentationItem* result = new Ifc4::IfcRevolvedAreaSolid(profileDef, placement, localAxis1Placement, sweepRadians);
		return result;

	}

	case CreateSolidFunctionsEnum::EXTRUDE:
	{
		double length = 0;
		for (auto const& modelerProperty : ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getProperties()) {
			if (modelerProperty->getPropertyName() == "Distance") {
				length = NumberUtils::convertCurrentUnitToMeters(modelerProperty->getPropertyValue().GetDouble());
			}
		}
		Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_CURVE,std::string("Extrude"),(Ifc4::IfcBoundedCurve*)ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem());
		
		Ifc4::IfcGeometricRepresentationItem* result =  new Ifc4::IfcExtrudedAreaSolid(profileDef, placement, file.addTriplet<Ifc4::IfcDirection>(yAxis.x, yAxis.y, yAxis.z), length);
		return result;

	}

	case CreateSolidFunctionsEnum::THIKEN:
	{
		double length = 0;
		Point3d rangeLow;

		for (auto const& modelerProperty : ifcReaderPropertiesBundle.getReaderPropertiesBundle()->getProperties()) {
			if (modelerProperty->getPropertyName() == "Thickness") {
				length = NumberUtils::convertCurrentUnitToMeters(modelerProperty->getPropertyValue().GetDouble());
			}
			if (modelerProperty->getPropertyName() == "Range Low") {
				rangeLow.x = modelerProperty->getPropertyValue().GetPoint3D().x;
				rangeLow.y = modelerProperty->getPropertyValue().GetPoint3D().y;
				rangeLow.z = modelerProperty->getPropertyValue().GetPoint3D().z;
			}
		}

		Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_CURVE, std::string("Thicken"), (Ifc4::IfcBoundedCurve*)ifcElementBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem());

		Ifc4::IfcGeometricRepresentationItem* result = new Ifc4::IfcExtrudedAreaSolid(profileDef, placement, file.addTriplet<Ifc4::IfcDirection>(zAxis.x, zAxis.y, zAxis.z), length);
		return result;

	}

	default:
		return nullptr;
	}

	
}
