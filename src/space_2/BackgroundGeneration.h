#pragma once
#include "Resource.h"
#include "BackgroundSpace.h"
#include "SpriteParameterFactory.h"

class BackgroundGeneration
{
public:
	// Constructor - Destructor
	BackgroundGeneration(void);
	~BackgroundGeneration(void);

	// Methode
	static BackgroundSpace* getBackgroundSpace(sf::Vector2i p_size);
};

