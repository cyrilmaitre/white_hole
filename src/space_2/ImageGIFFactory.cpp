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
ImageGIF* ImageGIFFactory::getLoadingSquareCircle()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterLoadingSquareCircle(false), 0.1, true);
}

ImageGIF* ImageGIFFactory::getLoadingBert()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterLoadingBert(false), 0.1, true);
}

ImageGIF* ImageGIFFactory::getSavingGif()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterSavingGif(false), 0.05, true);
}

ImageGIF* ImageGIFFactory::getImpactLaser()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterImpactLaser(false), 0.1, true);
}

ImageGIF* ImageGIFFactory::getImpactExplosion()
{
	return new ImageGIF(SpriteParameterFactory::getSpriteParameterImpactExplosion(false), 0.05, true);
}
