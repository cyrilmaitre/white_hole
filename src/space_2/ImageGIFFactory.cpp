#include "ImageGIFFactory.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ImageGIFFactory::ImageGIFFactory(void)
{
}

ImageGIFFactory::~ImageGIFFactory(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ImageGIF* ImageGIFFactory::getGifLoadingSquareCircle()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterLoadingSquareCircle(false), 0.1, true);
}

ImageGIF* ImageGIFFactory::getImpactLaser()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterImpactLaser(false), 0.1, true);
}

ImageGIF* ImageGIFFactory::getImpactExplosion()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterImpactExplosion(false), 0.05, true);
}

ImageGIF* ImageGIFFactory::getExplosionSmall()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterExplosionSmall(false), 0.05, true);
}

ImageGIF* ImageGIFFactory::getExplosionMedium()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterExplosionMedium(false), 0.05, true);
}

ImageGIF* ImageGIFFactory::getExplosionLarge()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterExplosionLarge(false), 0.05, true);
}
