#include "../headers/PrimitiveGraphicProperties.h"

PrimitiveGraphicProperties::PrimitiveGraphicProperties()
{
	this->mPrimitiveTypeEnum = PrimitiveTypeEnum::NONE;
	this->pSlabProperties = nullptr;
	this->pConeProperties = nullptr;
	this->pCylinderProperties = nullptr;
	this->pSphereProperties = nullptr;
	this->pTorusProperties = nullptr;

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

	if (this->pSlabProperties == nullptr) {
		return false;
	}
	slabGraphicPropertiesR = *this->pSlabProperties;
	return true;
}

void PrimitiveGraphicProperties::setSlabProperties(SlabGraphicProperties* newSlabGraphicProperties)
{
	this->pSlabProperties = newSlabGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetConeGraphicProperties(ConeGraphicProperties & coneGraphicPropertiesR)
{

	if (this->pConeProperties == nullptr) {
		return false;
	}
	coneGraphicPropertiesR = *this->pConeProperties;
	return true;
}

void PrimitiveGraphicProperties::setConeGraphicProperties(ConeGraphicProperties * newConeGraphicProperties)
{
	this->pConeProperties = newConeGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetSphereGraphicProperties(SphereGraphicProperties & sphereGraphicPropertiesR)
{
	if (this->pSphereProperties == nullptr) {
		return false;
	}
	sphereGraphicPropertiesR = *this->pSphereProperties;
	return true;
}

void PrimitiveGraphicProperties::setSphereGraphicProperties(SphereGraphicProperties * newSphereGraphicProperties)
{
	this->pSphereProperties = newSphereGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetCylinderGraphicProperties(CylinderGraphicProperties & cylinderGraphicPropertiesR)
{
	if (this->pCylinderProperties == nullptr) {
		return false;
	}
	cylinderGraphicPropertiesR = *this->pCylinderProperties;
	return true;
}

void PrimitiveGraphicProperties::setCylinderGraphicProperties(CylinderGraphicProperties * newCylinderGraphicProperties)
{
	this->pCylinderProperties = newCylinderGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetTorusGraphicProperties(TorusGraphicProperties & torusGraphicPropertiesR)
{
	if (this->pTorusProperties == nullptr) {
		return false;
	}
	torusGraphicPropertiesR = *this->pTorusProperties;
	return true;
}

void PrimitiveGraphicProperties::setTorusGraphicProperties(TorusGraphicProperties * newTorusGraphicProperties)
{
	this->pTorusProperties = newTorusGraphicProperties;
}

PrimitiveCommonGraphicProperties & PrimitiveGraphicProperties::getPrimitiveCommonGraphicProperties()
{
	return *this->primitiveCommonGraphicProperties;
}

void PrimitiveGraphicProperties::setPrimitiveCommonGraphicProperties(PrimitiveCommonGraphicProperties * newPrimitiveCommonGraphicProperties)
{
	this->primitiveCommonGraphicProperties = newPrimitiveCommonGraphicProperties;
}
