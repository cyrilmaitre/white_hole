#pragma once
#include "ImageGIF.h"



class ImageGIFFactory
{
public:
	// Getters - Setters
	static ImageGIF* getLoadingSquareCircle();
	static ImageGIF* getLoadingBert();
	static ImageGIF* getSavingGif();
	static ImageGIF* getImpactLaser();
	static ImageGIF* getImpactExplosion();


private:
	// Constructor - Destructor
	ImageGIFFactory(void);
	~ImageGIFFactory(void);

};

