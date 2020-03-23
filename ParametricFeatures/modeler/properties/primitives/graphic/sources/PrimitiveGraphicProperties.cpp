#include "../headers/PrimitiveGraphicProperties.h"

PrimitiveGraphicProperties::PrimitiveGraphicProperties()
{
	this->mPrimitiveTypeEnum = PrimitiveTypeEnum::NONE;
	this->mSlabProperties = nullptr;
	this->mConeProperties = nullptr;
	this->mCylinderProperties = nullptr;
	this->mSphereProperties = nullptr;
	this->mTorusProperties = nullptr;
}

PrimitiveTypeEnum PrimitiveGraphicProperties::getPrimitiveTypeEnum()
{
	return this->mPrimitiveTypeEnum;
}

void PrimitiveGraphicProperties::setPrimitiveTypeEnum(PrimitiveTypeEnum newPrimitiveTypeEnum)
{
	this->mPrimitiveTypeEnum = newPrimitiveTypeEnum;
}

bool PrimitiveGraphicProperties::tryGetSlabProperties(SlabGraphicProperties& slabGraphicPropertiesR)
{

	if (this->mSlabProperties == nullptr) {
		return false;
	}
	slabGraphicPropertiesR = *this->mSlabProperties;
	return true;
}

void PrimitiveGraphicProperties::setSlabProperties(SlabGraphicProperties* newSlabGraphicProperties)
{
	this->mSlabProperties = newSlabGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetConeGraphicProperties(ConeGraphicProperties & coneGraphicPropertiesR)
{

	if (this->mConeProperties == nullptr) {
		return false;
	}
	coneGraphicPropertiesR = *this->mConeProperties;
	return true;
}

void PrimitiveGraphicProperties::setConeGraphicProperties(ConeGraphicProperties * newConeGraphicProperties)
{
	this->mConeProperties = newConeGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetSphereGraphicProperties(SphereGraphicProperties & sphereGraphicPropertiesR)
{
	if (this->mSphereProperties == nullptr) {
		return false;
	}
	sphereGraphicPropertiesR = *this->mSphereProperties;
	return true;
}

void PrimitiveGraphicProperties::setSphereGraphicProperties(SphereGraphicProperties * newSphereGraphicProperties)
{
	this->mSphereProperties = newSphereGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetCylinderGraphicProperties(CylinderGraphicProperties & cylinderGraphicPropertiesR)
{
	if (this->mCylinderProperties == nullptr) {
		return false;
	}
	cylinderGraphicPropertiesR = *this->mCylinderProperties;
	return true;
}

void PrimitiveGraphicProperties::setCylinderGraphicProperties(CylinderGraphicProperties * newCylinderGraphicProperties)
{
	this->mCylinderProperties = newCylinderGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetTorusGraphicProperties(TorusGraphicProperties & torusGraphicPropertiesR)
{
	if (this->mTorusProperties == nullptr) {
		return false;
	}
	torusGraphicPropertiesR = *this->mTorusProperties;
	return true;
}

void PrimitiveGraphicProperties::setTorusGraphicProperties(TorusGraphicProperties * newTorusGraphicProperties)
{
	this->mTorusProperties = newTorusGraphicProperties;
}