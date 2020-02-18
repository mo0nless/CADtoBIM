#pragma once

#include <string>
#include <iostream>
#include <fstream> 
#include <filesystem>

#include <ifcparse\IfcSchema.h>
#include <ifcparse\Ifc4.h>
#include <ifcparse\utils.h>
#include <ifcparse\IfcHierarchyHelper.h>

class IfcCone {

private:
	double radius;

public:
	IfcCone(double newRadius);
};