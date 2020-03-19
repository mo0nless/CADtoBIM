#include "../headers/PrimitiveGraphicProperties.h"

PrimitiveGraphicProperties::PrimitiveGraphicProperties()
{
	this->primitiveTypeEnum = PrimitiveTypeEnum::PrimitiveTypeEnum::NONE;
	this->slabProperties = nullptr;
	this->coneProperties = nullptr;
	this->cylinderProperties = nullptr;
	this->sphereProperties = nullptr;
	this->torusProperties = nullptr;
}

PrimitiveTypeEnum::PrimitiveTypeEnum PrimitiveGraphicProperties::getPrimitiveTypeEnum()
{
	return this->primitiveTypeEnum;
}

void PrimitiveGraphicProperties::setPrimitiveTypeEnum(PrimitiveTypeEnum::PrimitiveTypeEnum newPrimitiveTypeEnum)
{
	this->primitiveTypeEnum = newPrimitiveTypeEnum;
}

bool PrimitiveGraphicProperties::tryGetSlabProperties(SlabGraphicProperties& slabGraphicPropertiesR)
{

	if (this->slabProperties == nullptr) {
		return false;
	}
	slabGraphicPropertiesR = *this->slabProperties;
	return true;
}

void PrimitiveGraphicProperties::setSlabProperties(SlabGraphicProperties* newSlabGraphicProperties)
{
	this->slabProperties = newSlabGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetConeGraphicProperties(ConeGraphicProperties & coneGraphicPropertiesR)
{

	if (this->coneProperties == nullptr) {
		return false;
	}
	coneGraphicPropertiesR = *this->coneProperties;
	return true;
}

void PrimitiveGraphicProperties::setConeGraphicProperties(ConeGraphicProperties * newConeGraphicProperties)
{
	this->coneProperties = newConeGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetSphereGraphicProperties(SphereGraphicProperties & sphereGraphicPropertiesR)
{
	if (this->sphereProperties == nullptr) {
		return false;
	}
	sphereGraphicPropertiesR = *this->sphereProperties;
	return true;
}

void PrimitiveGraphicProperties::setSphereGraphicProperties(SphereGraphicProperties * newSphereGraphicProperties)
{
	this->sphereProperties = newSphereGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetCylinderGraphicProperties(CylinderGraphicProperties & cylinderGraphicPropertiesR)
{
	if (this->cylinderProperties == nullptr) {
		return false;
	}
	cylinderGraphicPropertiesR = *this->cylinderProperties;
	return true;
}

void PrimitiveGraphicProperties::setCylinderGraphicProperties(CylinderGraphicProperties * newCylinderGraphicProperties)
{
	this->cylinderProperties = newCylinderGraphicProperties;
}

bool PrimitiveGraphicProperties::tryGetTorusGraphicProperties(TorusGraphicProperties & torusGraphicPropertiesR)
{
	if (this->torusProperties == nullptr) {
		return false;
	}
	torusGraphicPropertiesR = *this->torusProperties;
	return true;
}

void PrimitiveGraphicProperties::setTorusGraphicProperties(TorusGraphicProperties * newTorusGraphicProperties)
{
	this->torusProperties = newTorusGraphicProperties;
}