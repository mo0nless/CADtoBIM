#pragma once

#include "../graphic/headers/BsplineGraphicProperties.h"
#include "../graphic/headers/ArcGraphicProperties.h"
#include "../graphic/headers/InterpolationGraphicProperties.h"
#include "../graphic/headers/LineGraphicProperties.h"
#include "../graphic/headers/AkimaGraphicProperties.h"
#include <vector>

class CurvesPrimitivesContainer
{
public:
	CurvesPrimitivesContainer();

	void insertCurvesGraphicsProperties(ICurveGraphicProperties* newCurveGraphicProperties);
	std::vector<ICurveGraphicProperties*> getCurvesPrimitivesContainerVector();

	void setBoundaryTypeCurvesContainer(int boundaryBentleyType);
	CurvesBoundaryTypeEnum getBoundaryTypeCurvesContainer();

	void setElementContainerDescriptor(std::string newBoundaryDescriptor);
	CurvesContainerTypeEnum getContainerTypeEnum();

	void setIsFilled(bool value);
	bool getIsFilled();

	bool getIsClosed() const;
	void setIsClosed(bool isClosed);

	void setArea(double newArea);
	double getArea();

	DPoint3d getCentroIDxy() const;
	void setCentroIDxy(DPoint3d mCentroID);

	DVec3d getNormal() const;
	void setNormal(DVec3d normal);

	void setDirectionXY(DVec3d newDirX, DVec3d newDirY);
	DVec3d getDirectionX();
	DVec3d getDirectionY();
	DVec3d getDirectionZ();

private:
	bool mIsFilled;
	bool mIsClosed;
	double mArea;
	DPoint3d mCentroIDxy;

	DVec3d mNormal;
	DVec3d mDirectionX;
	DVec3d mDirectionY;
	DVec3d mDirectionZ;
	
	CurvesContainerTypeEnum mContainerDescriptorType;
	CurvesBoundaryTypeEnum mCurvesBoundaryType;
	std::vector<ICurveGraphicProperties*> mCurvesPrimitivesContainer;

};
