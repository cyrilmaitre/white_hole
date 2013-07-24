#pragma once
#include "MapObject.h"
#include "StarModel.h"

// Define
#define STAR_PLANE	SECTOR_PLANE

class Star : public MapObject
{
public:
	// Constructor - Destructor
	Star(void);
	~Star(void);

	// Getters - Setters
	StarModel* getStarModel();
	void setStarModel(StarModel* p_model);

	sf::Color getDazzleColor();
	void setDazzleColor(sf::Color p_color);

	float getDazzleRotation();
	void setDazzleRotation(float p_rotation);

	float getDazzlePercent();
	void setDazzlePercent(float p_percent);

	// Methods
	void drawDazzle();
	void update();
	void updateSprite();
	void updateDazzle();

	void loadSprite();
	void unloadSprite();

	void notifyStarModelChanged();
	void notifyDazzleRotationChanged();
	void notifyDazzlePercentChanged();
	void notifyDazzleColorChanged();


private:
	// Attributs
	StarModel* mStarModel;
	sf::Sprite* mDazzle;
	sf::Color mDazzleColor;
	float mDazzlePercent;
	float mDazzleRotation;
	mks::Clock mClockDazzle;

	// Methods
	float computeDazzlePercent(MapObject* p_object);
};

