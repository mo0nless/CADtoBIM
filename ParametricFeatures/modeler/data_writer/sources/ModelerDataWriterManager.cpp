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

	/*for (CurveVectorPtr cv : ruledSweepDetails.m_sectionCurves)
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
	}*/

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

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
void ModelerDataWriterManager::writeShapeCurvesVectorDataToFile(CurveVectorCR curvesVector)
{
	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "-------------------CURVE VECTOR---------------------" << endl;
	this->_outFile << "Size: " << curvesVector.size() << endl;
	this->_outFile << fixed;
	this->_outFile << endl;

	DPoint3d center, start, end;
	DVec3d normal;
	double area;

	curvesVector.CentroidNormalArea(center, normal, area);

	switch (curvesVector.GetBoundaryType())
	{
	case CurveVector::BoundaryType::BOUNDARY_TYPE_Inner:
	{
		this->_outFile << endl;
		this->_outFile << "BOUNDARY_TYPE_Inner --------" << endl;
	}
	break;
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_Open:
	{
		this->_outFile << endl;
		this->_outFile << "BOUNDARY_TYPE_Open --------" << endl;
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_Outer:
	{
		this->_outFile << endl;
		this->_outFile << "BOUNDARY_TYPE_Outer --------" << endl;
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_ParityRegion:
	{
		this->_outFile << endl;
		this->_outFile << "BOUNDARY_TYPE_ParityRegion --------" << endl;
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_UnionRegion:
	{
		this->_outFile << endl;
		this->_outFile << "BOUNDARY_TYPE_UnionRegion --------" << endl;
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_None:
	{
		this->_outFile << endl;
		this->_outFile << "BOUNDARY_TYPE_None --------" << endl;
	}
	default:
		break;
	}

	this->_outFile << "Centroid point [X] = " << center.x << endl;
	this->_outFile << "Centroid point [Y] = " << center.y << endl;
	this->_outFile << "Centroid point [Z] = " << center.z << endl;
	this->_outFile << endl;

	this->_outFile << "Normal [X] = " << normal.x << endl;
	this->_outFile << "Normal [Y] = " << normal.y << endl;
	this->_outFile << "Normal [Z] = " << normal.z << endl;
	this->_outFile << endl;

	this->_outFile << "Start Point [X]: " << start.x << endl;
	this->_outFile << "Start Point [Y]: " << start.y << endl;
	this->_outFile << "Start Point [Z]: " << start.z << endl;
	this->_outFile << endl;

	this->_outFile << "End Point [X]: " << end.x << endl;
	this->_outFile << "End Point [Y]: " << end.y << endl;
	this->_outFile << "End Point [Z]: " << end.z << endl;
	this->_outFile << endl;

	this->_outFile.flush();
	this->_outFile.close();
}

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
void ModelerDataWriterManager::writeCurvePrimitiveDataToFile(ICurvePrimitivePtr curvePrimitive)
{
	this->_outFile.open(this->_dataOutputFilePath, ios_base::app, sizeof(string));
	
	/*CurveTopologyId topologyID = curvePrimitive->GetId()->GetCurveTopologyId();

	this->_outFile << "CURVE_PRIMITIVE_ID: " << topologyID.GetType() << endl;
	this->_outFile << endl;*/

	switch (curvePrimitive->GetCurvePrimitiveType())
	{
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_AkimaCurve:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_AkimaCurve --------" << endl;
		this->_outFile << endl;		

		DPoint3d startP, endP;

		curvePrimitive->GetStartEnd(startP, endP);

		this->_outFile << "Start Point [X]: " << startP.x << endl;
		this->_outFile << "Start Point [Y]: " << startP.y << endl;
		this->_outFile << "Start Point [Z]: " << startP.z << endl;
		this->_outFile << endl;

		this->_outFile << "End Point [X]: " << endP.x << endl;
		this->_outFile << "End Point [Y]: " << endP.y << endl;
		this->_outFile << "End Point [Z]: " << endP.z << endl;
		this->_outFile << endl;

	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Arc:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_Arc --------" << endl;
		this->_outFile << endl;

		DEllipse3d ellipse;
		DPoint3d centerOUT, startP, endP;
		DVec3d directionX, directionY;
		double* pQuatXYZW = nullptr;
		double rx, ry, startAngle, sweepAngle;

		if (!curvePrimitive->TryGetArc(ellipse))
			break;

		ellipse.GetDGNFields3d(centerOUT, pQuatXYZW, directionX, directionY, rx, ry, startAngle, sweepAngle);

		ellipse.EvaluateEndPoints(startP, endP);
		
		this->_outFile << "Is Circular: " << ellipse.IsCircular() << endl;
		this->_outFile << "Is Ellipse: " << ellipse.IsFullEllipse() << endl;
		this->_outFile << endl;

		this->_outFile << "Start Point [X]: " << startP.x << endl;
		this->_outFile << "Start Point [Y]: " << startP.y << endl;
		this->_outFile << "Start Point [Z]: " << startP.z << endl;
		this->_outFile << endl;

		this->_outFile << "End Point [X]: " << endP.x << endl;
		this->_outFile << "End Point [Y]: " << endP.y << endl;
		this->_outFile << "End Point [Z]: " << endP.z << endl;
		this->_outFile << endl;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_BsplineCurve:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_BsplineCurve --------" << endl;
		this->_outFile << endl;

		MSBsplineCurvePtr bSpline = curvePrimitive->GetBsplineCurvePtr();
		bvector<DPoint3d> polesControlP;

		Transform lToW, wToL;
		double vertexF, squaredC;
		DPoint3d localStart, localEnd;

		DPoint3d startP, endP;

		bSpline->ExtractEndPoints(startP, endP);

		this->_outFile << "Start Point [X]: " << startP.x << endl;
		this->_outFile << "Start Point [Y]: " << startP.y << endl;
		this->_outFile << "Start Point [Z]: " << startP.z << endl;
		this->_outFile << endl;

		this->_outFile << "End Point [X]: " << endP.x << endl;
		this->_outFile << "End Point [Y]: " << endP.y << endl;
		this->_outFile << "End Point [Z]: " << endP.z << endl;
		this->_outFile << endl;

		if (bSpline != nullptr)
		{
			bool isParabola = bSpline->IsParabola(lToW, wToL, vertexF, localStart, localEnd, squaredC);

			this->_outFile << "Is Closed = " << bSpline->IsClosed() << endl;
			this->_outFile << "Is Parabola = " << isParabola << endl;

			bSpline->GetPoles(polesControlP);

			this->_outFile << "Control Points: " << endl;
			this->_outFile << endl;
		}
		else { break; }
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_CurveVector:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_CurveVector --------" << endl;
		this->_outFile << endl;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_InterpolationCurve:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_InterpolationCurve --------" << endl;
		this->_outFile << endl;

		bvector<DPoint3d> polesControlP;
		DPoint3d startP, endP;

		curvePrimitive->GetStartEnd(startP, endP);

		this->_outFile << "Start Point [X]: " << startP.x << endl;
		this->_outFile << "Start Point [Y]: " << startP.y << endl;
		this->_outFile << "Start Point [Z]: " << startP.z << endl;
		this->_outFile << endl;

		this->_outFile << "End Point [X]: " << endP.x << endl;
		this->_outFile << "End Point [Y]: " << endP.y << endl;
		this->_outFile << "End Point [Z]: " << endP.z << endl;
		this->_outFile << endl;

		if (curvePrimitive->GetInterpolationCurveCP() != nullptr)
		{
			MSInterpolationCurveCP intCurve = curvePrimitive->GetInterpolationCurveCP();
			interpolationParam intParams = intCurve->params;

			this->_outFile << "Interpolation Is Periodic: " << intParams.isPeriodic << endl;
			this->_outFile << "Interpolation Curve Order: " << intParams.order << endl;
			this->_outFile << endl;
		}
	}
	break;
	
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Line:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_Line --------" << endl;
		this->_outFile << endl;

		DPoint3d startP, endP;
		DSegment3d segment;

		if (curvePrimitive->TryGetLine(segment))
		{
			curvePrimitive->GetStartEnd(startP, endP);

			this->_outFile << "Start Point [X]: " << startP.x << endl;
			this->_outFile << "Start Point [Y]: " << startP.y << endl;
			this->_outFile << "Start Point [Z]: " << startP.z << endl;
			this->_outFile << endl;

			this->_outFile << "End Point [X]: " << endP.x << endl;
			this->_outFile << "End Point [Y]: " << endP.y << endl;
			this->_outFile << "End Point [Z]: " << endP.z << endl;
			this->_outFile << endl;

			this->_outFile << "Curve Line String Length: " << segment.Length() << endl;
			this->_outFile << endl;
		}
	}
	break;

	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString: 
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_LineString --------" << endl;
		this->_outFile << "NUMBER OF COMPONENT: " << curvePrimitive->NumComponent() << endl;
		this->_outFile << endl;

		DSegment3d segment;
		size_t startPointIndex = 0;
		DPoint3d startP, endP;

		size_t breakFractionIndex;
		double fraction;

		if (curvePrimitive->GetBreakFraction(breakFractionIndex, fraction))
		{
			this->_outFile << "breakFractionIndex: " << breakFractionIndex << endl;
			this->_outFile << "fraction: " << fraction << endl;
			this->_outFile << endl;
		}

		if (curvePrimitive->TryGetSegmentInLineString(segment, startPointIndex))
		{
			curvePrimitive->GetStartEnd(startP, endP);

			this->_outFile << "Start Point [X]: " << startP.x << endl;
			this->_outFile << "Start Point [Y]: " << startP.y << endl;
			this->_outFile << "Start Point [Z]: " << startP.z << endl;
			this->_outFile << endl;

			this->_outFile << "End Point [X]: " << endP.x << endl;
			this->_outFile << "End Point [Y]: " << endP.y << endl;
			this->_outFile << "End Point [Z]: " << endP.z << endl;
			this->_outFile << endl;

			this->_outFile << "Curve Line String Length: " << segment.Length() << endl;
			this->_outFile << endl;
			this->_outFile << "Control Points: " << segment.Length() << endl;
			this->_outFile << endl;
		}
	}

	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_PartialCurve --------" << endl;
		this->_outFile << endl;		
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PointString:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_PointString --------" << endl;
		this->_outFile << endl;
		
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral:
	{
		this->_outFile << "CURVE_PRIMITIVE_TYPE_Spiral --------" << endl;
		this->_outFile << endl;
	}
	break;
	default:
		break;
	}

	this->_outFile.flush();
	this->_outFile.close();
}

void ModelerDataWriterManager::writeMSBsplineSurfaceDataToFile(MSBsplineSurfaceCR msBsplineSurface)
{
	bvector<DPoint3d> weightPoles, unWeightPoles, polesToParse;
	bvector<double> weights;
	bvector<DPoint3d> polesGrid, gridPoints;
	size_t uIntervals, vIntervals;
	bvector<DPoint2d> uvParams; 
	T_DoubleVector uParams, vParams;
	double uMin, uMax, vMin, vMax;

	msBsplineSurface.GetUnWeightedPoles(unWeightPoles);
	msBsplineSurface.GetPoles(weightPoles);
	msBsplineSurface.GetWeights(weights);

	msBsplineSurface.GetIntervalCounts(uIntervals, vIntervals);
	msBsplineSurface.EvaluateUniformGrid(msBsplineSurface.GetIntNumUPoles(), msBsplineSurface.GetIntNumVPoles(), uvParams, polesGrid);
	msBsplineSurface.EvaluateUniformGrid(msBsplineSurface.GetNumUPoles(), msBsplineSurface.GetNumVPoles(), uParams, vParams, gridPoints);
	msBsplineSurface.GetParameterRegion(uMin, uMax, vMin, vMax);

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "-------- MSBsplineSurfaceCR msBsplineSurface --------" << "Type: " << msBsplineSurface.type << endl;
	this->_outFile << endl;

	this->_outFile << "Number of Bounds: " << msBsplineSurface.GetIntNumBounds() << endl;
	this->_outFile << "Total number of Poles: " << msBsplineSurface.GetNumPoles() << endl;
	this->_outFile << "U number of Poles: " << msBsplineSurface.GetIntNumUPoles() << endl;
	this->_outFile << "V number of Poles: " << msBsplineSurface.GetIntNumVPoles() << endl;
	this->_outFile << "U is Closed: " << msBsplineSurface.GetIsUClosed() << endl;
	this->_outFile << "V is Closed: " << msBsplineSurface.GetIsVClosed() << endl;
	this->_outFile << "Number of UV Poles Get Poles: " << weightPoles.size() << endl;
	this->_outFile << "Grid Poles Number: " << polesGrid.size() << endl;
	this->_outFile << "HasValidPoleCounts: " << msBsplineSurface.HasValidPoleCounts() << endl;
	this->_outFile << "HasValidPoleAllocation: " << msBsplineSurface.HasValidPoleAllocation() << endl;
	this->_outFile << "HasValidWeightAllocation: " << msBsplineSurface.HasValidWeightAllocation() << endl;
	this->_outFile << "HasWeights: " << msBsplineSurface.HasWeights() << endl;
	this->_outFile << endl;

	this->_outFile << "POINT Following the m/n parameters" << endl;

	int uOrder = msBsplineSurface.GetIntUOrder();
	int vOrder = msBsplineSurface.GetIntVOrder();

	int mParam = ((msBsplineSurface.GetIntNumUKnots()) - (uOrder - 1) - 1);
	int nParam = msBsplineSurface.GetIntNumPoles();
	int nParamCalc = ((msBsplineSurface.GetIntNumVKnots()) - (vOrder - 1) - 1);

	this->_outFile << "mParam: " << mParam << endl;
	this->_outFile << "nParam: " << nParam << endl;
	this->_outFile << "nParamCalc: " << nParamCalc << endl;
	this->_outFile << "V_Degree: " << vOrder - 1 << endl;
	this->_outFile << "U_Degree: " << uOrder - 1 << endl;
	this->_outFile << "V_Order: " << vOrder << endl;
	this->_outFile << "U_Order: " << uOrder << endl;
	
	this->_outFile << "POINT Controls with GET POLES STORED : " << endl;
	this->_outFile << "has weight: " << msBsplineSurface.HasWeights() << endl;
	this->_outFile << fixed;
	this->_outFile << endl;
	this->_outFile.close();

}

void ModelerDataWriterManager::writeBodyDataToFile(ISolidKernelEntityCR entity)
{
	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << fixed;

	auto entityType = entity.GetEntityType();
	
	switch (entityType)
	{
	case ISolidKernelEntity::KernelEntityType::EntityType_Solid:
	{
		this->_outFile << "In SolidKernel Entity is: Solid " << ISolidKernelEntity::KernelEntityType::EntityType_Solid << endl;
		this->_outFile << endl;
	}
		break;
	case ISolidKernelEntity::KernelEntityType::EntityType_Sheet: // Is different from a solid IfcShellBasedSurfaceModel
	{
		this->_outFile << "In SolidKernel Entity is: Sheet " << ISolidKernelEntity::KernelEntityType::EntityType_Sheet << endl;
		this->_outFile << endl;
	}
		break;

	case ISolidKernelEntity::KernelEntityType::EntityType_Wire:
	{
		this->_outFile << "In SolidKernel Entity is: Wire " << ISolidKernelEntity::KernelEntityType::EntityType_Wire << endl;
		this->_outFile << endl;
	}
		break;
	case  ISolidKernelEntity::KernelEntityType::EntityType_Minimal:
	{
		this->_outFile << "In SolidKernel Entity is: Minimal " << ISolidKernelEntity::KernelEntityType::EntityType_Wire << endl;
		this->_outFile << endl;
	}
	break;

	default:
		break;
	}

	bvector<ISubEntityPtr> subEntitiesFaces;
	bvector<ISubEntityPtr> subEntitiesEdges;
	bvector<ISubEntityPtr> subEntitiesVertices;

	size_t nFaces = SolidUtil::GetBodyFaces(&subEntitiesFaces, entity);
	size_t nEdges = SolidUtil::GetBodyEdges(&subEntitiesEdges, entity);
	size_t nVertices = SolidUtil::GetBodyVertices(&subEntitiesVertices, entity);
	

	this->_outFile << "-------------------------------- Processing BREP Entiy --------------------------------" << endl;
	this->_outFile << "Entity------------ " << endl;
	this->_outFile << "Edges Entity: " << nEdges << endl;
	this->_outFile << "Faces Entity: " << nFaces << endl;
	this->_outFile << "Vertices Entity: " << nVertices << endl;
	this->_outFile << endl;

	this->_outFile.close();
}
#pragma endregion


void ModelerDataWriterManager::writeElementInfoDataToFile(long elementID, WString elDescr)
{
	this->_outFile.open(this->_dataOutputFilePath, ios_base::app);
	this->_outFile << "===================================================" << endl;
	this->_outFile << "===================================================" << endl;
	this->_outFile << "Element Description: " << static_cast<Utf8String>(elDescr.GetWCharCP()) << endl;
	this->_outFile << "Element ID: " << elementID << endl;
	this->_outFile << "===================================================" << endl;
	this->_outFile << "===================================================" << endl;
	this->_outFile << endl;
	this->_outFile.close();
}

void ModelerDataWriterManager::writeInitializationDataToFile(ModelInfoCP modelInfo)
{
	DPoint3d globalOrigin = modelInfo->GetGlobalOrigin();

	UnitDefinitionCR masterUnit = modelInfo->GetMasterUnit();
	UnitDefinitionCR subUnit = modelInfo->GetSubUnit();

	UnitDefinitionCR storageUnit = modelInfo->GetStorageUnit();
	double uorPerUnit = modelInfo->GetUorPerStorage();

	this->_outFile.open(this->_dataOutputFilePath);
	this->_outFile << "------------------------" << endl;
	this->_outFile << "DgnModelRefP Unit System" << endl;
	this->_outFile << fixed;
	this->_outFile << endl;

	this->_outFile << "UnitSystem::English 1" << endl;
	this->_outFile << "UnitSystem::Metric 2" << endl;
	this->_outFile << "UnitSystem::USSurvey 3" << endl;
	this->_outFile << endl;

	this->_outFile << "UnitBase::Meter 1" << endl;
	this->_outFile << "UnitBase::Degree 2" << endl;
	this->_outFile << endl;

	this->_outFile << "Master unit: " << StringUtils::getNormalizedString(masterUnit.GetLabel()) << endl;
	this->_outFile << "masterUnit System" << (int)masterUnit.GetSystem() << endl;
	this->_outFile << "masterUnit Base" << (int)masterUnit.GetBase() << endl;
	this->_outFile << "masterUnit Numerator" << masterUnit.GetNumerator() << endl;
	this->_outFile << "masterUnit Denominator" << masterUnit.GetDenominator() << endl;
	this->_outFile << "Division Ratio" << (masterUnit.GetNumerator() / masterUnit.GetDenominator()) << endl;
	this->_outFile << endl;

	this->_outFile << "Sub unit: " << StringUtils::getNormalizedString(subUnit.GetLabel()) << endl;
	this->_outFile << "subUnit System" << (int)subUnit.GetSystem() << endl;
	this->_outFile << "subUnit Base" << (int)subUnit.GetBase() << endl;
	this->_outFile << "subUnit Numerator" << subUnit.GetNumerator() << endl;
	this->_outFile << "subUnit Denominator" << subUnit.GetDenominator() << endl;
	this->_outFile << "Division Ratio" << (subUnit.GetNumerator() / subUnit.GetDenominator()) << endl;
	this->_outFile << endl;

	this->_outFile << "Storage unit: " << StringUtils::getNormalizedString(storageUnit.GetLabel()) << endl;
	this->_outFile << "storageUnit System" << (int)storageUnit.GetSystem() << endl;
	this->_outFile << "storageUnit Base" << (int)storageUnit.GetBase() << endl;
	this->_outFile << "storageUnit Numerator" << storageUnit.GetNumerator() << endl;
	this->_outFile << "storageUnit Denominator" << storageUnit.GetDenominator() << endl;
	this->_outFile << "Division Ratio" << (storageUnit.GetNumerator() / storageUnit.GetDenominator()) << endl;
	this->_outFile << endl;

	this->_outFile << "UOR per storage" << uorPerUnit << endl;
	this->_outFile << "AnnotationScaleFactor" << modelInfo->GetAnnotationScaleFactor() << endl;
	this->_outFile << "Global Origin [x,y,z]= " << globalOrigin.x << ", " << globalOrigin.y << ", " << globalOrigin.z << endl;

	this->_outFile << "------------------------" << endl;
	this->_outFile.close();
}

void ModelerDataWriterManager::writeTitleProcessDataToFile(string s)
{
	this->_outFile.open(this->_dataOutputFilePath, ios_base::app, sizeof(string));
	this->_outFile << "------------------- " << s << " -------------------"<< endl;
	this->_outFile << endl;
	this->_outFile.close();
}

void ModelerDataWriterManager::writeSinglePointDataToFile(DPoint3d point, int index)
{
	this->_outFile.open(this->_dataOutputFilePath, ios_base::app, sizeof(string));
	if (index == -1)
	{
		this->_outFile << "Point " << " [X] = " << point.x << endl;
		this->_outFile << "Point " << " [Y] = " << point.y << endl;
		this->_outFile << "Point " << " [Z] = " << point.z << endl;
		this->_outFile << endl;
	}
	else
	{
		this->_outFile << "Point " << index << ": " << " = [" << point.x << ", " << point.y << ", " << point.z << "]" << endl;
	}
	this->_outFile.close();
}

