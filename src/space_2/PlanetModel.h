#pragma once
#include "PlanetType.h"
#include "MapObjectModel.h"


class PlanetModel : public MapObjectModel
{
public:
	// Constructor - Destructor
	PlanetModel(KeyValueFile* p_config);
	~PlanetModel(void);

	// Getters - Setters
	float getTempMin();
	void setTempMin(float p_min);

	float getTempMax();
	void setTempMax(float p_max);

	float getWeightMin();
	void setWeightMin(float p_min);

	float getWeightMax();
	void setWeightMax(float p_max);

	std::string getPlanes();
	void setPlanes(std::string p_plane);

	PlanetType* getPlanetType();
	void setPlanetType(PlanetType* p_type);

	// Methods
	float getRandomTemp();
	float getRandomWeight();
	int getRandomPlane();
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	float mTempMin;
	float mTempMax;
	float mWeightMin;
	float mWeightMax;
	std::string mPlanes;
	PlanetType* mPlanetType;
};

