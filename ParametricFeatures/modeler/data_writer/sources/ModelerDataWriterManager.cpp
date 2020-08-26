#include "../headers/ModelerDataWriterManager.h"

ModelerDataWriterManager::ModelerDataWriterManager(bool printDataEnabled)
{
	this->_dataOutputFilePath = SessionManager::getInstance()->getDataOutputFilePath();
	this->_printDataEnabled = printDataEnabled;
}

#pragma region Primitives

void ModelerDataWriterManager::writeGeneralPropertiesToFile(DRange3d & range, DVec3d & vectorRotation, DPoint4d & qRotation, Transform & localToWorld)
{
	if (!this->_printDataEnabled) {
		return;
	}
	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);

	this->_outFile << fixed;
	this->_outFile << "Range [XLength] = " << range.XLength() << endl;
	this->_outFile << "Range [YLength] = " << range.YLength() << endl;
	this->_outFile << "Range [ZLength] = " << range.ZLength() << endl;
	this->_outFile << endl;

	this->_outFile << "Quaternion Rotation" << endl;
	this->_outFile << "qRotation [X] = " << qRotation.x << endl;
	this->_outFile << "qRotation [Y] = " << qRotation.y << endl;
	this->_outFile << "qRotation [Z] = " << qRotation.z << endl;
	this->_outFile << "qRotation [W] = " << qRotation.w << endl;
	this->_outFile << endl;

	this->_outFile << "Vector Rotation Axis Local to World" << endl;
	this->_outFile << "vRotation [X] = " << vectorRotation.x << endl;
	this->_outFile << "vRotation [Y] = " << vectorRotation.y << endl;
	this->_outFile << "vRotation [Z] = " << vectorRotation.z << endl;
	this->_outFile << endl;

	this->_outFile << "Origin [X] = " << localToWorld.Origin().x << endl;
	this->_outFile << "Origin [Y] = " << localToWorld.Origin().y << endl;
	this->_outFile << "Origin [Z] = " << localToWorld.Origin().z << endl;

	this->_outFile << endl;

	this->_outFile.close();
}

void ModelerDataWriterManager::writeBoxDataToFile(DgnBoxDetail boxDetails)
{
	if (!this->_printDataEnabled) {
		return;
	}
	bvector<DPoint3d> corners;
	Transform localToWorld, locTWor, worldToLocal;
	DRange3d range;
	DVec3d vectorRotation;
	DPoint4d qRotation;
	double ax, ay, bx, by;


	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "-------- BOX --------" << endl;
	this->_outFile.close();

	boxDetails.GetCorners(corners);
	boxDetails.GetRange(range);
	boxDetails.GetNonUniformTransform(localToWorld, ax, ay, bx, by);

	boxDetails.TryGetConstructiveFrame(locTWor, worldToLocal);

	localToWorld.Matrix().GetRotationAngleAndVector(vectorRotation);
	localToWorld.Matrix().GetQuaternion(qRotation, false);

	writeGeneralPropertiesToFile(range, vectorRotation, qRotation, localToWorld);

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << fixed;

	this->_outFile << "Range High = " << range.high.x << endl;
	this->_outFile << "Range Low = " << range.low.x << endl;
	this->_outFile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << endl;
	this->_outFile << "DiagonalDistance = " << range.DiagonalDistance() << endl;
	this->_outFile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << endl;

	for (size_t i = 1; i <= corners.size(); i++)
	{
		this->_outFile << "Corner [" << i << "] - " << "[X] = " << corners.at(i - 1).x << endl;
		this->_outFile << "Corner [" << i << "] - " << "[Y] = " << corners.at(i - 1).y << endl;
		this->_outFile << "Corner [" << i << "] - " << "[Z] = " << corners.at(i - 1).z << endl;
		this->_outFile << endl;
	}

	this->_outFile << "Vector of BASE plane X [X] = " << boxDetails.m_vectorX.x << endl;
	this->_outFile << "Vector of BASE plane X [Y] = " << boxDetails.m_vectorX.y << endl;
	this->_outFile << "Vector of BASE plane X [Z] = " << boxDetails.m_vectorX.z << endl;
	this->_outFile << endl;


	this->_outFile << "Vector of BASE plane Y [X] = " << boxDetails.m_vectorY.x << endl;
	this->_outFile << "Vector of BASE plane Y [Y] = " << boxDetails.m_vectorY.y << endl;
	this->_outFile << "Vector of BASE plane Y [Z] = " << boxDetails.m_vectorY.z << endl;
	this->_outFile << endl;

	this->_outFile << "Base Rectangel is from Origin to (ax,ay,0). Top is from (0,0,1) to (ax,ay,1)" << endl;
	this->_outFile << "AX base rectangle x size = " << ax << endl;
	this->_outFile << "AY top rectangle y size = " << ay << endl;
	this->_outFile << "BX top rectangle x size = " << bx << endl;
	this->_outFile << "BY top rectangle y size = " << by << endl;
	this->_outFile << endl;

	this->_outFile << "Origin of BASE rectangle [X] = " << boxDetails.m_baseOrigin.x << endl;
	this->_outFile << "Origin of BASE rectangle [Y] = " << boxDetails.m_baseOrigin.y << endl;
	this->_outFile << "Origin of BASE rectangle [Z] = " << boxDetails.m_baseOrigin.z << endl;
	this->_outFile << endl;

	this->_outFile << "Origin of TOP rectangle [X] = " << boxDetails.m_topOrigin.x << endl;
	this->_outFile << "Origin of TOP rectangle [Y] = " << boxDetails.m_topOrigin.y << endl;
	this->_outFile << "Origin of TOP rectangle [Z] = " << boxDetails.m_topOrigin.z << endl;
	this->_outFile << endl;

	this->_outFile << "Size at the BASE [X] = " << boxDetails.m_baseX << endl;
	this->_outFile << "Size at the BASE [Y] = " << boxDetails.m_baseY << endl;
	this->_outFile << endl;

	this->_outFile << "Size at the TOP [X] = " << boxDetails.m_topX << endl;
	this->_outFile << "Size at the TOP [Y] = " << boxDetails.m_topY << endl;

	this->_outFile << endl;

	this->_outFile << "True if the end cap is enabled = " << boxDetails.m_capped << endl;

	this->_outFile << "-------- END OF BOX DATA --------" << endl;
	this->_outFile.close();
}

void ModelerDataWriterManager::writeConeDataToFile(DgnConeDetail coneDetails)
{
	if (!this->_printDataEnabled) {
		return;
	}

	DRange3d range;
	DVec3d rotation;
	DPoint4d qRotation;

	Transform localToWorld, worldToLocal;
	double radiusA, radiusB;

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "-------- CONE/CYLINDER/TRUNCATED_CONE --------" << endl;
	this->_outFile.close();

	coneDetails.GetRange(range);
	coneDetails.GetTransforms(localToWorld, worldToLocal, radiusA, radiusB);
	localToWorld.Matrix().GetRotationAngleAndVector(rotation);
	localToWorld.Matrix().GetQuaternion(qRotation, false);

	writeGeneralPropertiesToFile(range, rotation, qRotation, localToWorld);

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);

	this->_outFile << fixed;
	this->_outFile << "Center of BASE Circle [X] = " << coneDetails.m_centerA.x << endl;
	this->_outFile << "Center of BASE Circle [Y] = " << coneDetails.m_centerA.y << endl;
	this->_outFile << "Center of BASE Circle [Z] = " << coneDetails.m_centerA.z << endl;
	this->_outFile << endl;

	this->_outFile << "Center of TOP Circle [X] = " << coneDetails.m_centerB.x << endl;
	this->_outFile << "Center of TOP Circle [Y] = " << coneDetails.m_centerB.y << endl;
	this->_outFile << "Center of TOP Circle [Z] = " << coneDetails.m_centerB.z << endl;
	this->_outFile << endl;

	this->_outFile << "0 Degree Vector of BASE circle (vector 0 Degree) [X] = " << coneDetails.m_vector0.x << endl;
	this->_outFile << "0 Degree Vector of BASE circle (vector 0 Degree) [Y] = " << coneDetails.m_vector0.y << endl;
	this->_outFile << "0 Degree Vector of BASE circle (vector 0 Degree) [Z] = " << coneDetails.m_vector0.z << endl;
	this->_outFile << endl;

	this->_outFile << "0 Degree Vector of BASE circle (vector 90 Degree) [X] = " << coneDetails.m_vector90.x << endl;
	this->_outFile << "0 Degree Vector of BASE circle (vector 90 Degree) [Y] = " << coneDetails.m_vector90.y << endl;
	this->_outFile << "0 Degree Vector of BASE circle (vector 90 Degree) [Z] = " << coneDetails.m_vector90.z << endl;
	this->_outFile << endl;


	this->_outFile << "Radius at BASE = " << coneDetails.m_radiusA << endl;
	this->_outFile << "Radius at TOP = " << coneDetails.m_radiusB << endl;
	this->_outFile << endl;

	this->_outFile << "True if the end cap is enabled = " << coneDetails.m_capped << endl;

	this->_outFile << "--------END OF CONE/CYLINDER/TRUNCATED_CONE DATA--------" << endl;
	this->_outFile.close();


}

void ModelerDataWriterManager::writeExtrusionDataToFile(DgnExtrusionDetail extrusionDetails)
{
	if (!this->_printDataEnabled) {
		return;
	}

	DRange3d range;
	DPoint4d qRotation;
	Transform localToWorld, worldToLocal;
	DVec3d curveStart, curveEnd, rotation;
	
	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << endl;
	this->_outFile << "---------------------------EXTRUSION COMPONENTS----------------------------" << endl;
	this->_outFile << endl;
	this->_outFile.close();

	extrusionDetails.GetRange(range);
	extrusionDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
	//extrusionDetails.TryGetZExtrusionFrame(localToWorld, worldToLocal);
	//extrusionDetails.TryGetExtrusionFrame(localToWorld, worldToLocal);
	extrusionDetails.m_baseCurve->GetStartEnd(curveStart, curveEnd);
	localToWorld.Matrix().GetRotationAngleAndVector(rotation);
	localToWorld.Matrix().GetQuaternion(qRotation, false);

	writeGeneralPropertiesToFile(range, rotation, qRotation, localToWorld);

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);

	this->_outFile << fixed;
	this->_outFile << "Range High = " << range.high.x << endl;
	this->_outFile << "Range Low = " << range.low.x << endl;
	this->_outFile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << endl;
	this->_outFile << "DiagonalDistance = " << range.DiagonalDistance() << endl;
	this->_outFile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << endl;

	this->_outFile << "Vector of Extrusion [X] = " << extrusionDetails.m_extrusionVector.x << endl;
	this->_outFile << "Vector of Extrusion [Y] = " << extrusionDetails.m_extrusionVector.y << endl;
	this->_outFile << "Vector of Extrusion [Z] = " << extrusionDetails.m_extrusionVector.z << endl;
	this->_outFile << endl;

	this->_outFile << "Vector of Extrusion [X] = " << extrusionDetails.m_extrusionVector.x << endl;
	this->_outFile << "Vector of Extrusion [Y] = " << extrusionDetails.m_extrusionVector.y << endl;
	this->_outFile << "Vector of Extrusion [Z] = " << extrusionDetails.m_extrusionVector.z << endl;
	this->_outFile << endl;

	this->_outFile << "Curve Start Point of Extrusion [X] = " << curveStart.x << endl;
	this->_outFile << "Curve Start Point of Extrusion [Y] = " << curveStart.y << endl;
	this->_outFile << "Curve Start Point of Extrusion [Z] = " << curveStart.z << endl;
	this->_outFile << endl;

	this->_outFile << "Curve End Point of Extrusion [X] = " << curveEnd.x << endl;
	this->_outFile << "Curve End Point of Extrusion [Y] = " << curveEnd.y << endl;
	this->_outFile << "Curve End Point of Extrusion [Z] = " << curveEnd.z << endl;
	this->_outFile << endl;

	this->_outFile << "True if the curve element has a single element and it's a primitive = " << extrusionDetails.m_baseCurve->HasSingleCurvePrimitive() << endl;
	this->_outFile << endl;
	this->_outFile << "True if the end cap is enabled = " << extrusionDetails.m_capped << endl;

	this->_outFile << endl;
	this->_outFile << "---------------------------END OF EXTRUSION COMPONENTS----------------------------" << endl;
	this->_outFile << endl;
	this->_outFile.close();

}

void ModelerDataWriterManager::writeRotationalSweepDataToFile(DgnRotationalSweepDetail rotSweepDetails)
{

	if (!this->_printDataEnabled) {
		return;
	}

	DRange3d range;
	DVec3d rotation;
	DPoint4d qRotation;

	Transform localToWorld;
	Transform worldToLocal;

	DVec3d curveStart;
	DVec3d curveEnd;

	DVec3d rotationAxes;
	double sweepRadians;
	DPoint3d centerRotation;

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "-------- ROTATIONAL_SWEEP --------" << endl;
	this->_outFile.close();

	rotSweepDetails.GetRange(range);
	//rotSweepDetails.GetTransforms(localToWorld, worldToLocal);
	rotSweepDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);

	rotSweepDetails.TryGetRotationAxis(centerRotation, rotationAxes, sweepRadians);
	localToWorld.Matrix().GetRotationAngleAndVector(rotation);
	localToWorld.Matrix().GetQuaternion(qRotation, false);
	rotSweepDetails.m_baseCurve->GetStartEnd(curveStart, curveEnd);

	writeGeneralPropertiesToFile(range, rotation, qRotation, localToWorld);

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);

	this->_outFile << fixed;
	this->_outFile << "Range High = " << range.high.x << endl;
	this->_outFile << "Range Low = " << range.low.x << endl;
	this->_outFile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << endl;
	this->_outFile << "DiagonalDistance = " << range.DiagonalDistance() << endl;
	this->_outFile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << endl;

	this->_outFile << "Center Point Rotation [X] = " << centerRotation.x << endl;
	this->_outFile << "Center Point Rotation [Y] = " << centerRotation.y << endl;
	this->_outFile << "Center Point Rotation [Z] = " << centerRotation.z << endl;
	this->_outFile << endl;

	this->_outFile << "Axes Rotation [X] = " << rotationAxes.x << endl;
	this->_outFile << "Axes Rotation [Y] = " << rotationAxes.y << endl;
	this->_outFile << "Axes Rotation [Z] = " << rotationAxes.z << endl;
	this->_outFile << endl;

	this->_outFile << "Axes of Rotation Direction (Ray3D) [X] = " << rotSweepDetails.m_axisOfRotation.direction.x << endl;
	this->_outFile << "Axes of Rotation Direction (Ray3D) [Y] = " << rotSweepDetails.m_axisOfRotation.direction.y << endl;
	this->_outFile << "Axes of Rotation Direction (Ray3D) [Z] = " << rotSweepDetails.m_axisOfRotation.direction.z << endl;
	this->_outFile << endl;

	this->_outFile << "Axes of Rotation Origin (Ray3D) [X] = " << rotSweepDetails.m_axisOfRotation.origin.x << endl;
	this->_outFile << "Axes of Rotation Origin (Ray3D) [Y] = " << rotSweepDetails.m_axisOfRotation.origin.y << endl;
	this->_outFile << "Axes of Rotation Origin (Ray3D) [Z] = " << rotSweepDetails.m_axisOfRotation.origin.z << endl;
	this->_outFile << endl;

	this->_outFile << "Curve Start Point of Swept [X] = " << curveStart.x << endl;
	this->_outFile << "Curve Start Point of Swept [Y] = " << curveStart.y << endl;
	this->_outFile << "Curve Start Point of Swept [Z] = " << curveStart.z << endl;
	this->_outFile << endl;

	this->_outFile << "Curve End Point of Swept [X] = " << curveEnd.x << endl;
	this->_outFile << "Curve End Point of Swept [Y] = " << curveEnd.y << endl;
	this->_outFile << "Curve End Point of Swept [Z] = " << curveEnd.z << endl;
	this->_outFile << endl;

	this->_outFile << "Sweep Radians = " << sweepRadians << endl;
	this->_outFile << "Major Circle Sweep Angle = " << rotSweepDetails.m_sweepAngle << endl;
	this->_outFile << "Number of 'v' Rules (Radial Around) to Display in Wireframe = " << rotSweepDetails.m_numVRules << endl;
	this->_outFile << endl;

	this->_outFile << "Is it a closed volume = " << rotSweepDetails.IsClosedVolume() << endl;
	this->_outFile << "True if the end cap is enabled = " << rotSweepDetails.m_capped << endl;

	double radius;
	rotSweepDetails.GetRadius(radius, DgnRotationalSweepDetail::RadiusType::Centroidal);

	double radius_Max;
	rotSweepDetails.GetRadius(radius_Max, DgnRotationalSweepDetail::RadiusType::Maximum);

	double radius_Min;
	rotSweepDetails.GetRadius(radius_Min, DgnRotationalSweepDetail::RadiusType::Minimum);

	this->_outFile << "Radius min= " << radius_Min << endl;
	this->_outFile << "Radius max= " << radius_Max << endl;
	this->_outFile << "Radius cen= " << radius << endl;

	this->_outFile << "--------END OF ROTATIONAL_SWEEP DATA--------" << endl;
	this->_outFile.close();
}

void ModelerDataWriterManager::writeRuledSweepDataToFile(DgnRuledSweepDetail ruledSweepDetails)
{
	if (!this->_printDataEnabled) {
		return;
	}

	DRange3d range;
	DVec3d rotation;
	DPoint4d qRotation;

	Transform localToWorld;
	Transform worldToLocal;
	int countCurves = 1;

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "-------- RULED_SWEEP --------" << endl;
	this->_outFile.close();

	ruledSweepDetails.GetRange(range);
	ruledSweepDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
	localToWorld.Matrix().GetRotationAngleAndVector(rotation);
	localToWorld.Matrix().GetQuaternion(qRotation, false);
	writeGeneralPropertiesToFile(range, rotation, qRotation, localToWorld);

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);

	this->_outFile << fixed;
	this->_outFile << "Range High = " << range.high.x << endl;
	this->_outFile << "Range Low = " << range.low.x << endl;
	this->_outFile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << endl;
	this->_outFile << "DiagonalDistance = " << range.DiagonalDistance() << endl;
	this->_outFile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << endl;

	for (CurveVectorPtr cv : ruledSweepDetails.m_sectionCurves)
	{
		DVec3d curveStart;
		DVec3d curveEnd;

		cv->GetStartEnd(curveStart, curveEnd);

		this->_outFile << countCurves << "° " << "Curve Start Point of Swept [X] = " << curveStart.x << endl;
		this->_outFile << countCurves << "° " << "Curve Start Point of Swept [Y] = " << curveStart.y << endl;
		this->_outFile << countCurves << "° " << "Curve Start Point of Swept [Z] = " << curveStart.z << endl;
		this->_outFile << endl;

		this->_outFile << countCurves << "° " << "Curve End Point of Swept [X] = " << curveEnd.x << endl;
		this->_outFile << countCurves << "° " << "Curve End Point of Swept [Y] = " << curveEnd.y << endl;
		this->_outFile << countCurves << "° " << "Curve End Point of Swept [Z] = " << curveEnd.z << endl;
		this->_outFile << endl;

		countCurves += 1;
	}

	this->_outFile << "True if the end cap is enabled = " << ruledSweepDetails.m_capped << endl;
	this->_outFile << "--------END OF RULED_SWEEP DATA--------" << endl;
	this->_outFile.close();

}

void ModelerDataWriterManager::writeSphereDataToFile(DgnSphereDetail sphereDetails)
{
	if (!this->_printDataEnabled) {
		return;
	}

	DRange3d range;
	DVec3d rotation;
	DPoint4d qRotation;
	

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "-------- SPHERE --------" << endl;
	this->_outFile.close();

	sphereDetails.GetRange(range);
	sphereDetails.m_localToWorld.Matrix().GetRotationAngleAndVector(rotation);
	sphereDetails.m_localToWorld.Matrix().GetQuaternion(qRotation, false);

	writeGeneralPropertiesToFile(range, rotation, qRotation, sphereDetails.m_localToWorld);

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);

	this->_outFile << fixed;
	this->_outFile << "Range High = " << range.high.x << endl;
	this->_outFile << "Range Low = " << range.low.x << endl;
	this->_outFile << "Start Latitude LatitudeToVFraction = " << sphereDetails.LatitudeToVFraction(sphereDetails.m_startLatitude) << endl;
	this->_outFile << "latitudeSweep LatitudeToVFraction = " << sphereDetails.LatitudeToVFraction(sphereDetails.m_latitudeSweep) << endl;
	this->_outFile << endl;

	this->_outFile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << endl;
	this->_outFile << "DiagonalDistance = " << range.DiagonalDistance() << endl;
	this->_outFile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << endl;

	this->_outFile << "Origin is SPHERE Center. Columns x,y to Equator at 0 and 90 Degrees Latitude. Column z is to north pole." << endl;
	this->_outFile << "Latitude for Truncation Plane Parallel to the Equator." << endl;
	this->_outFile << "Start Latitude = " << sphereDetails.m_startLatitude << endl;
	this->_outFile << "Latitude Difference from Start Truncation Plane to end Truncation Plane." << endl;
	this->_outFile << "Latitude Sweep = " << sphereDetails.m_latitudeSweep << endl;
	this->_outFile << endl;

	this->_outFile << "True if the end cap is enabled = " << sphereDetails.m_capped << endl;
	
	
	this->_outFile << "--------END OF SPHERE DATA--------" << endl;
	this->_outFile.close();
}

void ModelerDataWriterManager::writeTorusDataToFile(DgnTorusPipeDetail torusDetails)
{
	if (!this->_printDataEnabled) {
		return;
	}

	DRange3d range;
	DVec3d rotation;
	DPoint4d qRotation, axesQuatRotation;
	RotMatrix rotationAxes;
	DPoint3d centerRotation;

	Transform localToWorld, worldToLocal;

	double radiusA, radiusB, sweepRadians;

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "-------- TORUS --------" << endl;
	this->_outFile.close();

	torusDetails.GetRange(range);
	torusDetails.TryGetFrame(centerRotation, rotationAxes, radiusA, radiusB, sweepRadians);
	torusDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
	localToWorld.Matrix().GetRotationAngleAndVector(rotation);
	localToWorld.Matrix().GetQuaternion(qRotation, false);
	rotationAxes.GetQuaternion(axesQuatRotation, false);

	writeGeneralPropertiesToFile(range, rotation, qRotation, localToWorld);

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);

	this->_outFile << fixed;
	this->_outFile << "Range High = " << range.high.x << endl;
	this->_outFile << "Range Low = " << range.low.x << endl;
	this->_outFile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << endl;
	this->_outFile << "DiagonalDistance = " << range.DiagonalDistance() << endl;
	this->_outFile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << endl;

	this->_outFile << "Axes Coordinates Axes, XY in major Plane, Z through hole" << endl;
	this->_outFile << "Axes Rotation (Quaternion) [X] = " << axesQuatRotation.x << endl;
	this->_outFile << "Axes Rotation (Quaternion) [Y] = " << axesQuatRotation.y << endl;
	this->_outFile << "Axes Rotation (Quaternion) [Z] = " << axesQuatRotation.z << endl;
	this->_outFile << "Axes Rotation (Quaternion) [W] = " << axesQuatRotation.w << endl;
	this->_outFile << endl;

	this->_outFile << "Center Point Rotation [X] = " << centerRotation.x << endl;
	this->_outFile << "Center Point Rotation [Y] = " << centerRotation.y << endl;
	this->_outFile << "Center Point Rotation [Z] = " << centerRotation.z << endl;
	this->_outFile << endl;

	this->_outFile << "Center [X] = " << torusDetails.m_center.x << endl;
	this->_outFile << "Center [Y] = " << torusDetails.m_center.y << endl;
	this->_outFile << "Center [Z] = " << torusDetails.m_center.z << endl;
	this->_outFile << endl;

	this->_outFile << "Vector X [X] = " << torusDetails.m_vectorX.x << endl;
	this->_outFile << "Vector X [Y] = " << torusDetails.m_vectorX.y << endl;
	this->_outFile << "Vector X [Z] = " << torusDetails.m_vectorX.z << endl;
	this->_outFile << endl;

	this->_outFile << "Vector Y [X] = " << torusDetails.m_vectorY.x << endl;
	this->_outFile << "Vector Y [Y] = " << torusDetails.m_vectorY.y << endl;
	this->_outFile << "Vector Y [Z] = " << torusDetails.m_vectorY.z << endl;
	this->_outFile << endl;

	this->_outFile << "Major Radius = " << torusDetails.m_majorRadius << endl;
	this->_outFile << "Minor Radius = " << torusDetails.m_minorRadius << endl;
	this->_outFile << "Sweep Angle = " << torusDetails.m_sweepAngle << endl;
	this->_outFile << "Sweep Radians = " << sweepRadians << endl;
	this->_outFile << endl;

	this->_outFile << "Radius Major (Elbow Radius) = " << radiusA << endl;
	this->_outFile << "Radius Minor (Pipe Diameter) = " << radiusB << endl;
	this->_outFile << endl;

	this->_outFile << "True if the end cap is enabled = " << torusDetails.m_capped << endl;

	this->_outFile << "--------END OF TORUS DATA--------" << endl;
	this->_outFile.close();
}
#pragma endregion
