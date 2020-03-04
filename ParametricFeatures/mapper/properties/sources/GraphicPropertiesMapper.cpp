#include "../headers/GraphicPropertiesMapper.h"


void GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(ISolidPrimitiveCR & primitive, GraphicProperties & graphicProperties)
{
	double area, volume;
	DVec3d centroid;
	RotMatrix axes;
	DVec3d momentxyz;

	primitive.ComputePrincipalAreaMoments(area, centroid, axes, momentxyz);
	primitive.ComputePrincipalMoments(volume, centroid, axes, momentxyz);

	//radius = pow(((volume / M_PI)*(3. / 4.)), 1. / 3.);

	graphicProperties.setArea(area);
	/*graphicProperties.setRadius(radius);*/
	graphicProperties.setVolume(volume);
	graphicProperties.setCentroid(centroid);

}
