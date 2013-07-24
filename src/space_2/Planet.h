#pragma once
#include "Resource.h"
#include "MapObject.h"
#include "PlanetType.h"
#include "PlanetModel.h"


class Planet: public MapObject
{
public:
	// Constructor - Destructor
	Planet();
	~Planet(void);

	// Getters - Setters
	std::string getName();
	void setName(std::string p_name);

	float getWeight();
	void setWeight(float p_weight);

	float getTemp();
	void setTemp(float p_temp);

	PlanetModel* getPlanetModel();
	void setPlanetModel(PlanetModel* p_model);

	// Method   
	void updateSprite();
	void draw();
	void loadSprite();
	void unloadSprite();
	void notifyPlanetModelChanged();


private:
	// Attributs
	std::string mName;
	float mWeight;
	float mTemp;

	sf::Sprite *mPlanetLightCard;
	float mPlanetLightCardRotation;

	sf::Sprite *mPlanetLight;
	std::string mPlanetLightSprite;
	float mPlanetLightRotation;
	bool mPlanetLightDraw;

	sf::Sprite *mPlanetRing;
	std::string mPlanetRingSprite;
	float mPlanetRingRotation;
	bool mPlanetRingDraw;

	PlanetModel* mPlanetModel;
};

