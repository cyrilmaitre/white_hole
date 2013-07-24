#pragma once
#include "ImageGIF.h"



class ImageGIFFactory
{
public:
	// Getters - Setters
	static ImageGIF* getGifLoadingSquareCircle();
	static ImageGIF* getImpactLaser();
	static ImageGIF* getImpactExplosion();
	static ImageGIF* getExplosionSmall();
	static ImageGIF* getExplosionMedium();
	static ImageGIF* getExplosionLarge();


private:
	// Constructor - Destructor
	ImageGIFFactory(void);
	~ImageGIFFactory(void);

};

