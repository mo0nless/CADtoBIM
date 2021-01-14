#pragma once

#include "CurveGraphicProperties.h"

using namespace Modeler::Curves;

namespace Modeler
{
	namespace Curves
	{
		class ArcGraphicProperties : public CurveGraphicProperties
		{

		private:
			double mRadiusX;
			double mRadiusY;

			double mLength;

			double mSweepAngle;
			double mStartAngle;

			DVec3d mCenter;

			DVec3d mDirectionX;
			DVec3d mDirectionY;
			DVec3d mDirectionZ;

			bool mIsCircular;
			bool mIsFullEllipse;

		public:
			ArcGraphicProperties();

			void setDirectionXY(DVec3d newDirectionX, DVec3d newDirectionY);

			DVec3d getDirectionX();
			DVec3d getDirectionY();
			DVec3d getDirectionZ();

			bool getIsCircular();
			void setIsCircular(bool value);

			bool getIsFullEllipse();
			void setIsFullEllipse(bool value);

			void setLength(double newLength);
			double getLength();

			void setRadiusXY(double newRadiusX, double newRadiusY);
			double getRadiusX();
			double getRadiusY();

			void setCenterOut(DPoint3d newCenter);
			DVec3d getCenterOut();

			void setStartAngle(double newStartAngle);
			double getStartAngle();

			void setSweepAngle(double newSweepAngle);
			double getSweepAngle();
		};
	}
}